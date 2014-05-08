<?php
namespace Driver;
use Store\Manager;
use IssueList;
use Source\File;
use Entity;

class Analyzer
{
	protected $entityIDs;
	
	protected $initialTypeQueue;
	protected $typeInferenceQueue;
	
	public function __construct()
	{
		$this->entityIDs = array();
		
		$this->initialTypeQueue = array();
		$this->typeInferenceQueue = array();
	}
	
	public function addEntityID($e) { $this->entityIDs[] = $e; }
	public function addEntityIDs(array $e) { $this->entityIDs = array_merge($this->entityIDs, $e); }
	public function getEntityIDs() { return $this->entityIDs; }
	
	public function run()
	{
		$manager = Manager::get();
		$entityStore = $manager->getEntityStore();
		
		$issues = IssueList::get();
		
		//Move the entity IDs into the initial type analysis queue.
		$this->initialTypeQueue = $this->entityIDs;
		$initialTypeDone = array();
		
		//Enter the main loop which proceeds as long as there are entities to analyze.
		while (!$issues->isFatal())
		{
			//Initial type analysis.
			if (count($this->initialTypeQueue)) {
				$entityID = array_shift($this->initialTypeQueue);
				$entity = $entityStore->getEntity($entityID);
				$entityStore->pushRootID($entityID);
				echo "analyzing initial type of {$entity->getID()} ".vartype($entity)." {$entity->getName()}\n";
				
				//Wrap inline constants (strings, arrays, etc.).
				$this->wrapInlineConstants($entity);
				if ($issues->isFatal()) break;
				
				//Wrap member function calls.
				$this->wrapMemberCalls($entity);
				if ($issues->isFatal()) break;
				
				//Bind all identifiers.
				$this->bindIdents($entity);
				if ($issues->isFatal()) break;
				
				//Assemble a list of candidates for callees.
				$this->bindCalleeCandidates($entity);
				if ($issues->isFatal()) break;
				
				//Evaluate type expressions to actual types.
				$this->evaluateTypeExprs($entity);
				if ($issues->isFatal()) break;
				
				//Calculate the initial types of the entities.
				$this->calculateInitialType($entity);
				if ($issues->isFatal()) break;
				
				//Queue this entity for type inference.
				array_push($this->typeInferenceQueue, $entityID);
				array_push($initialTypeDone, $entityID);
				
				//Store the entity back to disk.
				$entityStore->popRootID($entityID);
				$entityStore->persistEntity($entityID);
				
				//Analyze this entity's known entities.
				foreach ($entity->getKnownEntities() as $known) {
					if (!in_array($known->getID(), $initialTypeDone, true) && !in_array($known->getID(), $this->initialTypeQueue, true)) {
						array_push($this->initialTypeQueue, $known->getID());
					}
				}
			}
			
			//Type inference.
			else if (count($this->typeInferenceQueue)) {
				$entityID = array_shift($this->typeInferenceQueue);
				$entity = $entityStore->getEntity($entityID);
				$entityStore->pushRootID($entityID);
				echo "inferring type of {$entity->getID()} ".vartype($entity)."\n";
				
				//Don't spawn any constraints for now.
				//Spawn type constraints for the entities.
				//$this->spawnTypeConstraints($entity, $entity);
				
				//Calculate the required type.
				//$this->calculateRequiredType($entity);
				
				//Choose one of the function candidates for each call.
				//$this->chooseCallCandidate($entity);
				
				//Calculate the inferred types.
				$this->calculateInferredType($entity);
				
				//Store the entity back to disk.
				$entityStore->popRootID($entityID);
				$entityStore->persistEntity($entityID);
			}
			
			//Nothing left to do.
			else break;
		}
	}
	
	/** Concatenates the arguments into one output line, with the relevant entities highlighted. */
	static public function show()
	{
		$output = "";
		$ranges = array();
		foreach (func_get_args() as $arg) {
			if (is_string($arg)) {
				$output .= $arg." ";
			}
			if ($arg instanceof Entity\Expr\Identifier) {
				$output .= "'{$arg->getName()}' ";
				$ranges[] = $arg->getRange();
			}
			if ($arg instanceof Entity\Expr\VarDef) {
				$output .= "'{$arg->getName()}' ";
				$ranges[] = $arg->getHumanRange();
			}
			if ($arg instanceof \Type\Builtin) {
				$output .= "'{$arg->getName()}' ";
			}
		}
		$i = new \Issue('info', $output, $ranges);
		echo $i."\n";
	}
	
	/** Recursively binds all identifiers. */
	public function bindIdents(Entity\Entity $entity)
	{
		if ($entity instanceof Entity\Expr\Identifier) {
			if (!$entity->analysis->binding->target) {
				//Try to bind the identifier to a builtin type.
				if (in_array($entity->getName(), \Type\Builtin::$names)) {
					$entity->analysis->binding->target = \Type\Builtin::makeWithName($entity->getName());
				}
				
				//Try to bind the identifier to something in scope.
				else {
					$scope = $entity->getScope();
					if (!$scope) {
						throw new \RuntimeException("{$entity->getInternalDescription()} has no scope.");
					}
					/*$result = null;
					while ($scope) {
						if ($scope instanceof Entity\Scope\ScopeDeclaration) {
							if ($scope->getDeclares()->getName() == $entity->getName()) {
								$result = $scope->getDeclares();
								break;
							}
						}
						if ($scope instanceof Entity\Scope\ScopeRoot) {
							foreach ($scope->getRootEntity()->getKnownEntities() as $e) {
								if ($e instanceof \Entity\ExternalDeclaration) {
									foreach ($e->getDeclarations() as $decl) {
										if ($decl->getName() == $entity->getName()) {
											$result = $decl;
											break;
										}
									}
								}
								else if ($e->getName() == $entity->getName()) {
									$result = $e;
									break;
								}
								if ($result) break;
							}
							if ($result) break;
						}
						
						//Jump to the previous scope, or the outer scope if we're at the beginning.
						if ($s = $scope->getUpper())
							$scope = $s;
						else
							$scope = $scope->getOuter();
					}*/
					$result = $this->findNameInScope($entity->getName(), $scope);
					
					if ($result) {
						$entity->analysis->binding->target = $result;
					} else {
						IssueList::add('error', "Entity with name '{$entity->getName()}' is unknown.", $entity);
					}
				}
			}
		}
		else {
			foreach ($entity->getChildEntities() as $e)
				$this->bindIdents($e);
		}
	}
	
	/** Recursively binds all identifiers within type expressions like VarDefs. */
	public function bindIdentsInTypeExprs(Entity\Entity $entity)
	{
		if ($entity instanceof Entity\Expr\Type) {
			$this->bindIdents($entity->getExpr());
		}
		else {
			foreach ($entity->getChildEntities() as $e)
				$this->bindIdentsInTypeExprs($e);
		}	
	}
	
	/** Assembles a list of possible functions to be called for all callee objects. */
	public function bindCalleeCandidates(Entity\Entity $entity)
	{
		if ($entity instanceof Entity\Expr\Call\Callee) {
			$expr = $entity->getExpr();
			$scope = null;
			$name  = null;
			if ($expr instanceof Entity\Expr\Identifier) {
				$scope = $expr->getScope();
				$name  = $expr->getName();
			} else {
				IssueList::add('error', "Expression is not a function that can be called.", $expr);
				return;
			}
			
			//Search the scope for functions that match this name.
			$results = array();
			while ($scope) {
				if ($scope instanceof Entity\Scope\ScopeDeclaration) {
					if ($scope->getDeclares()->getName() == $name) {
						$results[] = $scope->getDeclares();
					}
				}
				if ($scope instanceof Entity\Scope\ScopeRoot) {
					foreach ($scope->getRootEntity()->getKnownEntities() as $e) {
						if ($e instanceof \Entity\ExternalDeclaration) {
							foreach ($e->getDeclarations() as $decl) {
								if ($decl->getName() == $name) {
									$results[] = $decl;
									break;
								}
							}
						}
						else if ($e->getName() == $name) {
							$results[] = $e;
						}
					}
				}
				
				//Jump to the previous scope, or the outer scope if we're at the beginning.
				if ($s = $scope->getUpper())
					$scope = $s;
				else
					$scope = $scope->getOuter();
			}
			
			//Remove all the non-function results, as they are not relevant.
			$results = array_filter($results, function($f) { return $f instanceof Entity\FunctionDefinition; });
			
			if (count($results)) {
				$entity->analysis->setCandidates($results);
			} else {
				IssueList::add('error', "No function called '$name' exists.", $expr);
			}
		} else {
			foreach ($entity->getChildEntities() as $e)
				$this->bindCalleeCandidates($e);
		}
	}
	
	public function evaluateTypeExprs(Entity\Entity $entity)
	{
		if ($entity instanceof Entity\Expr\Type) {
			$expr = $entity->getExpr();
			if ($expr instanceof Entity\Expr\Identifier) {
				$t = $expr->analysis->binding->target;
				if ($t instanceof \Type\Type) {
					$entity->setType($t);
				}
				else if ($t instanceof \Entity\TypeDefinition) {
					$entity->setType(\Type\Defined::makeWithDefinition($t));
				}
				else if ($t instanceof \Entity\Type\TypeVar) {
					if ($tt = $t->getType()) {
						$entity->setType($tt);
					}
				}
				else {
					IssueList::add('error', "Type '{$expr->getName()}' is unknown.", $expr->getRange());
				}
			}
			else if ($expr instanceof Entity\Expr\NativeType) {
				$n = preg_replace('/\s+\*/', "*", $expr->getName());
				$entity->setType(\Type\Native::makeWithName($n));
			}
			else if ($expr instanceof Entity\Expr\TypeSpec) {
				//Make sure the type we're about to specialized and the specialization parameters are set.
				foreach ($entity->getChildEntities() as $e) {
					$this->evaluateTypeExprs($e);
				}

				//Fetch the type we're about to specialize and check whether specialization is possible.
				$type = $expr->getType()->getType();
				if (!$type) {
					throw new \exception("Entity {$expr->getInternalDescription()} is trying to specialize type expression that did not yield a valid type.");
				}
				if (!$type instanceof \Type\Defined) {
					IssueList::add('error', "Non-generic type {$type->toHumanReadableString()} cannot be specialized.", $expr->getRange());
					return;
				}
				$spec = Analyzer\TypeSpecializer::specialize($type->getDefinition(), $expr->getArgs(), $expr->getHumanRangeIfPossible());
				if (!$spec) {
					IssueList::add('error', "Specialization failed.", $expr);
					return;
				}
				$prevType = $entity->getType();
				$entity->setType(\Type\Defined::makeWithDefinition($spec));
				if (!$prevType || $prevType->getDefinition() !== $spec)
					$this->initialTypeQueue[] = $spec->getID();
				//echo "- specializing ".vartype($expr->getType()->getType())."\n";
				//IssueList::add('error', "Type specializations not yet supported.", $expr->getHumanRangeIfPossible());
			}
			else {
				IssueList::add('error', "Invalid type expression.", $expr->getHumanRangeIfPossible());
			}
		}
		else {
			foreach ($entity->getChildEntities() as $e) {
				$this->evaluateTypeExprs($e);
			}
		}
	}
	
	/** Recursively calculates the initial type for each entity that does not yet have one set. */
	public function calculateInitialType(Entity\Entity $entity)
	{
		foreach ($entity->getChildEntities() as $e)
			$this->calculateInitialType($e);
		
		if (isset($entity->analysis->type) /*&& !$entity->analysis->type->initial*/) {
			if ($entity instanceof Entity\Expr\VarDef) {
				$t = $entity->getType();
				if (!$t) {
					//For now, infer the type of the VarDef from its initial expression.
					if ($i = $entity->getInitial()) {
						if ($i->analysis->type->initial) {
							$entity->analysis->type->initial = $i->analysis->type->initial;
							//TODO: don't just reuse the type, actually make a copy of the type so now dependency arises.
						} else {
							IssueList::add('error', "Type of initial value of variable '{$entity->getName()}' cannot be inferred.", $i, $entity);
						}
					} else {
						IssueList::add('error', "Type of variable '{$entity->getName()}' cannot be inferred without an initial value.", $entity);
					}
				} else {
					$tt = $t->getType();
					$entity->analysis->type->initial = $tt;
					if (!$tt) {
						IssueList::add('error', "Variable '{$entity->getName()}' has invalid type expression.", $t, $entity);
					}
				}
			}
			
			if ($entity instanceof Entity\Func\Argument) {
				$t = $entity->getType();
				if ($t) {
					$tt = $t->getType();
					if ($tt) {
						$entity->analysis->type->initial = $tt;
					} else {
						IssueList::add('error', "Function argument '{$entity->getName()}' has invalid type expression.", $t, $entity);
					}
				} else {
					IssueList::add('error', "Type of function argument '{$entity->getName()}' cannot be inferred.", $entity);
				}
			}
			
			if ($entity instanceof Entity\Func\Tuple) {
				$fields = array();
				foreach ($entity->getArgs() as $arg) {
					$fields[] = $arg->analysis->type->initial;
				}
				$entity->analysis->type->initial = \Type\Tuple::makeWithFields($fields);
			}
			
			if ($entity instanceof Entity\Type\Member) {
				$t = $entity->getType();
				if ($t) {
					$tt = $t->getType();
					$entity->analysis->type->initial = $tt;
				} else {
					IssueList::add('error', "Member '{$entity->getName()}' has invalid type expression.", $t, $entity);
				}
			}
			
			if ($entity instanceof Entity\Expr\NewOp) {
				$t = $entity->getType();
				if ($t) {
					$tt = $t->getType();
					$entity->analysis->type->initial = $tt;
					if (!$tt) {
						IssueList::add('error', "New operator has invalid type expression.", $t, $entity);
					}
				} else {
					throw new \exception("NewOp {$entity->getID()} has no type expression.");
				}
			}
			
			if ($entity instanceof Entity\Expr\Identifier) {
				if ($target = $entity->analysis->binding->target) {
					if ($entity->analysis->binding->target instanceof \Type\Type || $entity->analysis->binding->target instanceof \Entity\TypeDefinition || $entity->analysis->binding->target instanceof \Entity\Type\TypeVar) {
						$entity->analysis->type->initial = \Type\Builtin::makeWithName("Type");
					} else if ($target->analysis->type) {
						$entity->analysis->type->initial = $target->analysis->type->initial;
					} else {
						//$entity->analysis->type->initial = \Type\Generic::make();
						IssueList::add('error', "Entity referenced by '{$entity->getName()}' has no valid type.", $target, $entity);
					}
				} else {
					//$entity->analysis->type->initial = \Type\Generic::make();
					throw new \exception("Trying to perform initial type analysis on identifier '{$entity->getName()}' which is not bound");
				}
			}
			
			if ($entity instanceof Entity\Expr\Constant) {
				switch ($entity->getType()) {
					case 'number': {
						$v = $entity->getValue();
						if (preg_match('/[.e]/', $v))
							$entity->analysis->type->initial = \Type\Builtin::makeWithName("float");
						else
							$entity->analysis->type->initial = \Type\Builtin::makeWithName("int");
					} break;
					case 'string': {
						/*$t = $this->findTypeInScope("String", $entity->getScope());
						if (!$t) {
							IssueList::add('error', "String constants require a 'String' class to be defined.", $entity);
						} else {
							$entity->analysis->type->initial = $t;//\Type\Builtin::makeWithName("String");
						}*/
						$entity->analysis->type->initial = \Type\Native::makeWithName("const char*");
					} break;
				}
			}
			
			if ($entity instanceof Entity\Expr\Type || $entity instanceof Entity\Expr\TypeSpec) {
				$entity->analysis->type->initial = \Type\Builtin::makeWithName("Type");
			}
			
			if ($entity instanceof Entity\FunctionDefinition) {
				$output = $entity->getOutputArgs()->analysis->type->initial;
				if ($output instanceof \Type\Tuple) {
					$fields = $output->getFields();
					if (count($fields) == 1) {
						$output = array_pop($fields);
					} else if (count($fields) > 1) {
						IssueList::add('error', "Only one return value allowed at the moment.", $entity->getOutputArgs());
					}
				}
				$entity->analysis->type->initial = \Type\Func::makeWithArgs($entity->getInputArgs()->analysis->type->initial, $output);
			}
			
			if ($entity instanceof Entity\Expr\Cast) {
				$t = $entity->getType();
				if (!$t) {
					IssueList::add('error', "Type of cast is invalid.", $entity);
				} else {
					$tt = $t->getType();
					$entity->analysis->type->initial = $tt;
					if (!$tt) {
						IssueList::add('error', "Cast has invalid type expression.", $t, $entity);
					}
				}
			}
		}
	}
	
	public function spawnTypeConstraints(Entity\RootEntity $root, Entity\Entity $entity)
	{
		foreach ($entity->getChildEntities() as $e)
			$this->spawnTypeConstraints($root, $e);
		
		//Variable definitions have a type constraint between the initial expression and the type of the variable itself.
		if ($entity instanceof Entity\Expr\VarDef) {
			if ($i = $entity->getInitial()) {
				$root->analysis->constraints->add(\Analysis\Constraint::make($entity, $i));
			}
		}
		
		//Identifiers are supposed to have the same type as their target variable definitions.
		if ($entity instanceof Entity\Expr\Identifier) {
			if ($t = $entity->analysis->binding->target) {
				if ($t instanceof Entity\Expr\VarDef) {
					$root->analysis->constraints->add(\Analysis\Constraint::make($entity, $t));
				}
			}
		}
	}
	
	/** Recursively calculates the inferred type of the entity, based on constraints and the initial type. */
	public function calculateInferredType(Entity\Entity $entity)
	{
		foreach ($entity->getChildEntities() as $e)
			$this->calculateInferredType($e);
		if (IssueList::get()->isFatal()) return;
		
		if (isset($entity->analysis->type) && !$entity->analysis->type->inferred) {
			$entity->analysis->type->inferred = $entity->analysis->type->initial;
			
			/*if ($entity instanceof Entity\Expr\Identifier) {
				$t = $entity->analysis->binding->target;
				if (isset($t->analysis->type)) {
					if ($tt = $t->analysis->type->inferred) {
						$entity->analysis->type->inferred = $tt;
					} else {
						IssueList::add('error', "Entity referenced by '{$entity->getName()}' has no valid type.", $t, $entity);
					}
				}
			}*/
			if ($entity instanceof Entity\Expr\Operator\Binary) {
				$lt = $entity->getLHS()->analysis->type->inferred;
				$rt = $entity->getRHS()->analysis->type->inferred;
				if ($lt && $rt) {
					if (in_array($entity->getOperator(), array("==", "!=", "<", ">", "<=", ">=", "&&", "||"))) {
						$entity->analysis->type->inferred = \Type\Builtin::makeWithName("bool");
					} else if (\Type\Type::equal($lt, $rt)) {
						$entity->analysis->type->inferred = $lt;
					} else if ($lt instanceof \Type\Native || $rt instanceof \TypeNative) {
						//IssueList::add('warning', "Ignoring types for binary operator since one or both sides are of a native C type.", $entity);
						$entity->analysis->type->inferred = $lt;
					} else {
						IssueList::add('error', "Binary operator requires both operands to be of same type. Left operand is {$lt->toHumanReadableString()}, right operand is {$rt->toHumanReadableString()}.", $entity, array($entity->getLHS(), $entity->getRHS()));
					}
				}
			}
			
			if ($entity instanceof Entity\Expr\Operator\Unary) {
				if ($entity->getOperator() == '&') {
					$t = $entity->getOperand()->analysis->type->inferred;
					if (!$t instanceof \Type\Native) {
						IssueList::add('error', "The pointer operator & is not allowed on type {$t->toHumanReadableString()}, only on native C types.", $entity);
					} else {
						$entity->analysis->type->inferred = \Type\Native::makeWithName($t->getName()."*");
					}
				}
				else if ($entity->getOperator() == '!') {
					$entity->analysis->type->inferred = \Type\Builtin::makeWithName("bool");
				}
				else if ($entity->getOperator() == '*') {
					$t = $entity->getOperand()->analysis->type->inferred;
					if ($t instanceof \Type\Native) {
						$pointerCount = 0;
						$hasArray = false;
						$s = $t->getName();
						for ($i = 0; $i < strlen($s); $i++) {
							if ($s[$i] == '*') $pointerCount++;
							if ($s[$i] == '[') $hasArray = true;
						}
						
						if (!$pointerCount && !$hasArray) {
							IssueList::add('error', "Native C type $s cannot be dereferenced since it is not a pointer type.", $entity);
						} else {
							$rs = strrev($s);
							$rs_deref = trim(preg_replace('/(\[[^\]]\]|\*)/', "", $rs, 1, $count));
							if (!$count) {
								throw new \exception("Dereferencing $s should work, but yielded a replacement count of 0.");
							}
							$entity->analysis->type->inferred = \Type\Native::makeWithName(strrev($rs_deref));
						}
					}
					else if ($entity->getOperand() instanceof Entity\Expr\Constant) {
						$op = $entity->getOperand();
						if ($op->getType() == 'string') {
							$entity->analysis->type->inferred = \Type\Native::makeWithName("char");
						} else {
							IssueList::add('error', "The ASCII operator * is only allowed on string constants.", $entity);
						}
					}
					else {
						IssueList::add('error', "The dereferencing operator * is only allowed on native C types or on string constants.", $entity);
					}
				}
				else {
					IssueList::add('error', "Unary operator {$entity->getOperator()} not yet supported.", $entity);
				}
			}
			
			if ($entity instanceof Entity\Expr\MemberAccess) {
				$t = $entity->getExpr()->analysis->type->inferred;
				if ($t instanceof \Type\Defined) {
					$def = $t->getDefinition();
					
					$member = null;
					foreach ($def->getMembers() as $m) {
						if ($m->getName() == $entity->getName()) {
							$member = $m;
							break;
						}
					}
					if (!$member) {
						IssueList::add('error', "Type '{$def->getName()}' has no member '{$entity->getName()}'.", $entity, $def);
					} else {
						$entity->analysis->type->inferred = $member->analysis->type->initial;
					}
				} else {
					IssueList::add('error', "Only user-defined types have accessible members.", $entity);
				}
			}
			
			if ($entity instanceof Entity\Expr\ElementAccess) {
				$t = $entity->getExpr()->analysis->type->inferred;
				if (!$t instanceof \Type\Native) {
					IssueList::add('error', "Element access [] is only allowed on native C types at the moment.", $entity);
				} else {
					$pointerCount = 0;
					$hasArray = false;
					$s = $t->getName();
					for ($i = 0; $i < strlen($s); $i++) {
						if ($s[$i] == '*') $pointerCount++;
						if ($s[$i] == '[') $hasArray = true;
					}
					
					if (!$pointerCount && !$hasArray) {
						IssueList::add('error', "Elements of native C type $s cannot be accessed since it is not a pointer type.", $entity);
					} else {
						$rs = strrev($s);
						$rs_deref = trim(preg_replace('/(\[[^\]]\]|\*)/', "", $rs, 1, $count));
						if (!$count) {
							throw new \exception("Dereferencing $s should work, but yielded a replacement count of 0.");
						}
						$entity->analysis->type->inferred = \Type\Native::makeWithName(strrev($rs_deref));
					}
				}
			}
			
			if ($entity instanceof Entity\Expr\Identifier) {
				$target = $entity->analysis->binding->target;
				if ($target instanceof \Entity\FunctionDefinition) {
					if ($target->analysis->type->initial) {
						$entity->analysis->type->inferred = $target->analysis->type->initial;
					} else {
						IssueList::add('error', "Function referenced by '{$entity->getName()}' has no valid type.", $target, $entity);
					}
				}
			}
			if ($entity instanceof Entity\Expr\Call) {
				//implement stuff here...
				$this->chooseCallCandidate($entity);
			}
			if ($entity instanceof Entity\Expr\Call\Argument) {
				$t = $entity->getExpr()->analysis->type->inferred;
				if ($t) {
					$entity->analysis->type->inferred = $t;
				} else {
					IssueList::add('error', "Type of call argument cannot be infered.", $entity);
				}
			}
			if ($entity instanceof Entity\Expr\Call\Tuple) {
				$fields = array();
				foreach ($entity->getArgs() as $arg) {
					$fields[] = $arg->analysis->type->inferred;
				}
				$entity->analysis->type->inferred = \Type\Tuple::makeWithFields($fields);
			}
		}
	}
	
	public function chooseCallCandidate(Entity\Entity $entity)
	{
		if ($entity instanceof Entity\Expr\Call) {
			$type = $entity->getArgs()->analysis->type->inferred;
			if (!$type) {
				throw new \exception("Argument tuple inferred type is null.");
			}
			$candidates = array_filter($entity->getCallee()->analysis->getCandidates(), function($c) use ($type) {
				$t = $c->analysis->type->initial->getInput();
				if (!$t) {
					throw new \exception("Inferred type of candidate {$c->getName()} input is null.");
				}
				return \Type\Type::equal($t, $type);
			});
			
			if (count($candidates) == 1) {
				$analysis = $entity->getCallee()->analysis;
				$candidate = array_pop($candidates);
				$analysis->binding->target = $candidate;
				$analysis->type->inferred = $candidate->analysis->type->initial;
				$entity->analysis->type->inferred = $analysis->type->inferred->getOutput();
			}
			else if (count($candidates) > 1) {
				IssueList::add('error', "Multiple functions match type {$type->toHumanReadableString()} of the call.", $entity, $candidates);
			}
			else {
				$msg = "Call requires function of type {$type->toHumanReadableString()}. Candidates are:";
				foreach ($entity->getCallee()->analysis->getCandidates() as $candidate) {
					$msg .= "\n{$candidate->getName()} {$candidate->analysis->type->initial->getInput()->toHumanReadableString()}";
				}
				IssueList::add('error', $msg, $entity, $entity->getCallee()->analysis->getCandidates());
			}
		} else {
			foreach ($entity->getChildEntities() as $e)
				$this->chooseCallCandidate($e);
		}
	}
	
	private function findNameInScope($name, Entity\Scope\Scope $scope)
	{
		$result = null;
		while ($scope) {
			if ($scope instanceof Entity\Scope\ScopeDeclaration) {
				if ($scope->getDeclares()->getName() == $name) {
					$result = $scope->getDeclares();
					break;
				}
			}
			if ($scope instanceof Entity\Scope\ScopeRoot) {
				$root = $scope->getRootEntity();
				if ($root->getName() == $name) {
					$result = $scope->getRootEntity();
					break;
				}
				if ($root instanceof Entity\TypeDefinition) {
					foreach ($root->getTypeVars() as $tv) {
						if ($tv->getName() == $name) {
							$result = $tv;
							break;
						}
					}
				}
				foreach ($scope->getRootEntity()->getKnownEntities() as $e) {
					if ($e instanceof \Entity\ExternalDeclaration) {
						foreach ($e->getDeclarations() as $decl) {
							if ($decl->getName() == $name) {
								$result = $decl;
								break;
							}
						}
					}
					else if ($e->getName() == $name) {
						$result = $e;
						break;
					}
					if ($result) break;
				}
				if ($result) break;
			}
			
			//Jump to the previous scope, or the outer scope if we're at the beginning.
			if ($s = $scope->getUpper())
				$scope = $s;
			else
				$scope = $scope->getOuter();
		}
		return $result;
	}
	
	private function findTypeInScope($name, Entity\Scope\Scope $scope)
	{
		$t = $this->findNameInScope($name, $scope);
		if ($t) {
			return \Type\Defined::makeWithDefinition($t);
		}
		return null;
	}
	
	private function wrapInlineConstants(Entity\Entity $entity)
	{
		foreach ($entity->getChildEntities() as $e)
			$this->wrapInlineConstants($e);
		if (IssueList::get()->isFatal()) return;

		//Wrap string constants in an appropriate initializer function.
		if ($entity instanceof Entity\Expr\Constant && $entity->getType() == "string") {
			$parent = $entity->getParent();

			//Don't wrap string constants inside unary* operators, since they indicate an ASCII
			//value instead of a String object.
			if ($parent instanceof Entity\Expr\Operator\Unary && $parent->getOperator() == "*") return;
			
			//Check whether the constant is already wrapped.
			if ($parent instanceof Entity\Expr\Call\Argument) {
				$call = $parent->getParent()->getParent(); //Call
				if (($expr = $call->getCallee()->getExpr()) instanceof Entity\Expr\Identifier) {
					if ($expr->getName() == "_makeString") return;
				}
			}
			
			//Create a new call.
			$ident = new Entity\Expr\Identifier;
			$ident->generateID();
			$ident->setName("_makeString");
			$ident->setRange($entity->getRange());
			
			$callee = new Entity\Expr\Call\Callee;
			$callee->generateID();
			$callee->setExpr($ident);
			$callee->setRange($entity->getRange());
			
			$arg = new Entity\Expr\Call\Argument;
			$arg->generateID();
			$arg->setExpr($entity);
			$arg->setRange($entity->getRange());
			
			$tuple = new Entity\Expr\Call\Tuple;
			$tuple->generateID();
			$tuple->setArgs(array($arg));
			$tuple->setRange($entity->getRange());
			
			$call = new Entity\Expr\Call;
			$call->generateID();
			$call->setCallee($callee);
			$call->setArgs($tuple);
			$call->setRange($entity->getRange());
			
			//Replace the constant with this call.
			$parent->replaceChild($entity, $call);
			
			//Initialize the scope.
			$call->initScope($entity->getScope());
		}
	}
	
	private function wrapMemberCalls(Entity\Entity $entity)
	{
		foreach ($entity->getChildEntities() as $e)
			$this->wrapMemberCalls($e);
		if (IssueList::get()->isFatal()) return;
		
		if ($entity instanceof Entity\Expr\Call) {
			$expr = $entity->getCallee()->getExpr();
			if ($expr instanceof Entity\Expr\MemberAccess) {
				//Resolve the member access.
				$identifier = new Entity\Expr\Identifier;
				$identifier->generateID();
				$identifier->setRange($expr->getHumanRange());
				$identifier->setName($expr->getName());
				$entity->getCallee()->setExpr($identifier);
				
				$arg = new Entity\Expr\Call\Argument;
				$arg->generateID();
				$arg->setRange($expr->getExpr()->getRange());
				$arg->setHumanRange($expr->getExpr()->getHumanRange());
				$arg->setExpr($expr->getExpr());
				
				$args = $entity->getArgs()->getArgs();
				array_unshift($args, $arg);
				$entity->getArgs()->setArgs($args);
				
				$scope = $expr->getScope();
				$entity->getCallee()->initScope($scope);
			}
		}
	}
}