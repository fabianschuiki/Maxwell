/* Copyright (c) 2014 Fabian Schuiki */
#pragma once

namespace maxwell {
namespace repository {

/// An object that maintains a set of syntax nodes and tracks changes to the
/// source file that generated them. For each source file, the repository must
/// track
///
/// - the source file's unique ID; and
/// - the hash of the file at the time it was parsed.
///
/// For each node the repository needs to track
///
/// - the unique ID of the source file that generated the node;
/// - an ID unique within the source (the local node ID);
/// - a hash of the node's structure (the structural hash),
/// - source locations (the location hash), and
/// - entire contents (the full hash, or hash); and
/// - the node itself.
///
/// The combination of source ID and node ID forms a node identifier unique
/// across all source files (the node ID). The repository operates on an
/// abstract node interface which needs to provide the information listed above.
/// Thus it has no dependency on a specific node class, but can be made to deal
/// with any class.
///
/// The repository allows nodes to be added, removed, and looked up. It provides
/// means to detect whether a source file or node have been modified. Source
/// files and nodes may be iterated.
class NodeRepository {
public:
	virtual bool add(const Source& src) = 0;
	virtual bool remove(SourceId sid) = 0;
};

} // namespace repository
} // namespace maxwell
