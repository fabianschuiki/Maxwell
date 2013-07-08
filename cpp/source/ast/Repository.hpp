/* Copyright © 2013 Fabian Schuiki */
#pragma once
#include "SourceRepository.hpp"
#include "NodeRepository.hpp"
#include "Node.hpp"
#include <boost/smart_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/filesystem.hpp>

namespace ast {

using boost::shared_ptr;
using boost::scoped_ptr;

/**
 * The Repository represents a persistent store on disk that holds AST nodes.
 */
class Repository : public boost::enable_shared_from_this<Repository>
{
public:
	const boost::filesystem::path path;
	Repository(const boost::filesystem::path& path);

	void flush();

	// Node store.
	NodeId addNode(int source, const NodePtr& node);
	NodeId addNode(const string& source, const NodePtr& node);
	NodePtr getNode(const NodeId& id);

	// Source store.
	int registerSource(const string& s);
	int unregisterSource(const string& s);
	void unregisterSource(int i);

	void markModified(const NodeId& id);

protected:
	/// Repository maintaining the source file ids.
	scoped_ptr<SourceRepository> sourceRepo;
	/// Repository maintaining the nodes per source file.
	scoped_ptr<NodeRepository> nodeRepo;

	void nodeLoaded(const NodeId& id, const NodePtr& node);
};

}