/* Automatically generated by ast-gen. DO NOT MODIFY. */
#pragma once

namespace ast {

/// Node kinds that may be used to test whether a Node is of a given subclass.
typedef enum {
	kArrayConstExpr,
	kAssignmentExpr,
	kBinaryOpExpr,
	kBlockExpr,
	kCallArg,
	kCallCandidate,
	kCallCandidateArg,
	kCallExpr,
	kCallExprArg,
	kDefinedType,
	kForExpr,
	kFuncArg,
	kFuncDef,
	kFuncType,
	kGenericType,
	kIdentifierExpr,
	kIfCaseExpr,
	kIfCaseExprCond,
	kIfExpr,
	kImplAccessor,
	kInterfaceQualifier,
	kInvalidType,
	kMapConstExpr,
	kMapConstExprPair,
	kMemberAccessExpr,
	kNamedTypeExpr,
	kNativeQualifier,
	kNilType,
	kNilTypeExpr,
	kNumberConstExpr,
	kOneTupleMappedType,
	kQualifiedType,
	kQualifiedTypeExpr,
	kQualifiedTypeMember,
	kRangeQualifier,
	kSetConstExpr,
	kSpecializedType,
	kSpecializedTypeExpr,
	kStringConstExpr,
	kStructureQualifier,
	kStructureQualifierMember,
	kTupleType,
	kTupleTypeArg,
	kTupleTypeExpr,
	kTupleTypeExprArg,
	kTypeDef,
	kTypeSet,
	kUnaryOpExpr,
	kUnionMappedType,
	kUnionType,
	kUnionTypeExpr,
	kVarDefExpr
} Kind;

/// Node interfaces that may be used to test whether a Node implements a given interface.
typedef enum {
	kCallInterface,
	kCallArgInterface,
	kCallableInterface,
	kGraphInterface,
	kNamedInterface,
	kTypeInterface,
	kTypeExprInterface,
	kVariableInterface
} Interface;

} // namespace ast

