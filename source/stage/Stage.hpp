/* Copyright © 2013 Fabian Schuiki */
#pragma once
#include <ast/Node.hpp>
#include <ast/Repository.hpp>
#include <ast/nodes/ast.hpp>
#include <string>
#include <set>

namespace stage {

using std::string;
using std::set;
using ast::Node;
using ast::NodePtr;
using ast::NodeId;
using ast::Repository;

/**
 * @brief Base class for all AST processing stages.
 *
 * Individual stages implement the virtual methods below to perform their
 * processing steps. The StageManager object maintains a list of all stages and
 * the order in which they're supposed to be executed.
 */
class Stage
{
public:
	Repository& repository;
	int verbosity;
	Stage(Repository& r) : repository(r), verbosity(0) {}

	/// Overridden by subclasses to return the stage name.
	virtual string getName() const = 0;
	/// Overridden by subclasses to return the stage identifier.
	virtual int getId() const = 0;

	void run(const NodePtr& node);
	void run(const NodeId& id);

	typedef set<NodeId> Dependencies;

protected:
	NodePtr currentNode;
	Dependencies dependencies; // dependencies of the tuple (stage,currentNode)

	/// Overridden by subclasses to implement stage behaviour.
	virtual void process(const NodePtr& node) = 0;

	void addDependency(const NodeId& id);
	void addDependency(const NodeId& id, string path) { addDependency(id + path); }
	template <typename T> void addDependency(const T& node) { addDependency(node->getId()); }
	template <typename T> void addDependency(const T& node, string path) { addDependency(node->getId(), path); }

	void println(int verbosity, const string& msg, string metadata = "");
	template <typename T> void println(int verbosity, const string& msg, const T& ided) { println(verbosity, msg, ided->getId().str()); }
};

}