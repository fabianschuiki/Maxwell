/* Copyright (c) 2014 Fabian Schuiki */
#pragma once
#include <cassert>

/// \file
/// This file establishes facilities that deal with uniquely identifying source
/// files and tracking locations across multiple source files. A key design goal
/// is to make these structures as efficient as possible, as they are used all
/// throughout the code base.

namespace maxwell {

/// A unique source ID. Each processed source file should be assigned a SourceId
/// to keep track of locations inside the file.
class SourceId {
	/// 0 indicates "invalid", everything else refers to a source file.
	uint32_t id;

public:
	/// Creates an invalid source id.
	SourceId(): id(0) {}
	/// Creates a source id with the given \a id.
	explicit SourceId(uint32_t id): id(id) {}

	/// Returns true if this is a valid source id.
	bool isValid() const { return id != 0; }
	/// Returns true if this is an invalid source id.
	bool isInavlid() const { return id == 0; }
	/// Returns true if this is a valid source id.
	operator bool() const { return id != 0; }

	bool operator==(SourceId l) { return id == l.id; }
	bool operator!=(SourceId l) { return id != l.id; }
	bool operator<=(SourceId l) { return id <= l.id; }
	bool operator>=(SourceId l) { return id >= l.id; }
	bool operator< (SourceId l) { return id <  l.id; }
	bool operator> (SourceId l) { return id >  l.id; }

	/// Returns an opaque ID describing this file ID.
	uint32_t getId() const { return id; }
};


/// A location within a source file. May be used to track locations across
/// multiple files.
class SourceLocation {
	/// Source file this location refers to.
	SourceId sid;
	/// Offset from the start of the source file.
	uint32_t pos;

public:
	/// Creates an invalid source location.
	SourceLocation(): pos(0) {}
	/// Creats a location pointing to the beginning of the source file \a sid.
	explicit SourceLocation(SourceId sid): sid(sid), pos(0) {}
	/// Creates a location pointing to the offset \a pos in the source file \a
	/// sid.
	SourceLocation(SourceId sid, uint32_t pos): sid(sid), pos(pos) {}

	/// Returns true if this is a valid source location.
	bool isValid() const { return sid.isValid(); }
	/// Returns true if this is an invalid source location.
	bool isInvalid() const { return sid.isInvalid(); }
	/// Returns true if this is a valid source location.
	operator bool() const { return sid.isValid(); }

	/// Returns a new location shifted i positions away from the beginning.
	SourceLocation operator+(int i) const { return SourceLocation(sid, pos+i); }
	/// Returns a new location shifted i positions towards the beginning.
	SourceLocation operator-(int i) const { return SourceLocation(sid, pos-i); }
	/// Shifts the location i positions away from the beginning.
	SourceLocation& operator+=(int i) { pos += i; return *this; }
	/// Shifts the location i positions towards the beginning.
	SourceLocation& operator-=(int i) { pos -= i; return *this; }

	bool operator==(SourceLocation l) { return sid == l.sid && id == l.id; }
	bool operator!=(SourceLocation l) { return sid != l.sid || id != l.id; }
	bool operator<=(SourceLocation l) {
		return sid < l.sid || (sid == l.sid && id <= l.id);
	}
	bool operator>=(SourceLocation l) {
		return sid > l.sid || (sid == l.sid && id >= l.id);
	}
	bool operator<(SourceLocation l) {
		return sid < l.sid || (sid == l.sid && id < l.id);
	}
	bool operator>(SourceLocation l) {
		return sid > l.sid || (sid == l.sid && id > l.id);
	}

	/// Returns the source ID of the file this location refers to.
	SourceId getSourceId() const { return sid; }
	/// Returns the offset from the beginning of the source file.
	uint32_t getOffset() const { return pos; }
};


/// A range within a single source file. May not reach across file boundaries,
/// as this usually does not make sense.
class SourceRange {
	/// Source file this range refers to.
	SourceId sid;
	/// Offset from the start of the source file where the range begins.
	uint32_t pos;
	/// Length of the range.
	uint32_t len;

public:
	/// Creates an invalid source range.
	SourceRange(): pos(0), length(0) {}
	/// Creates a source range starting at offset \a pos from the beginning of
	/// source file \a sid, ending after a \a len positions.
	SourceRange(SourceId sid, uint32_t pos, uint32_t len):
		sid(sid),
		pos(pos),
		len(len) {}
	/// Creates a source range starting at \a a and ending just before \a b,
	/// i.e. [a,b). \a a and \a b must refer to the same source file, and \a a
	/// must lie before \a b.
	SourceRange(SourceLocation a, SourceLocation b):
		sid(a.sid),
		pos(a.pos),
		len(b.pos-a.pos) {
		assert(a.sid == b.sid);
		assert(a.pos < b.pos);
	}

	/// Returns true if this is a valid source range.
	bool isValid() const { return sid.isValid(); }
	/// Returns true if this is an invalid source range.
	bool isInvalid() const { return sid.isInvalid(); }
	/// Returns true if this is a valid source range.
	operator bool() const { return sid.isValid(); }

	bool operator==(SourceRange r) const {
		return sid == r.sid && pos == r.pos && len == r.len;
	}
	bool operator!=(SourceRange r) const {
		return sid != r.sid || pos != r.pos || len != r.len;
	}

	/// Returns the source ID of the file this location refers to.
	SourceId getSourceId() const { return sid; }
	/// Returns the offset from the begining of the source file where this range
	/// starts.
	uint32_t getOffset() const { return pos; }
	/// Returns the length of this range.
	uint32_t getLength() const { return len; }
	/// Returns the source location at the beginning of this range.
	SourceLocation getBegin() const { return SourceLocation(sid, pos); }
	/// Returns the source location just after the end of this range.
	SourceLocation getEnd() const { return SourceLocation(sid, pos+len); }

	/// Returns true if the location \a l lies within this range.
	bool contains(SourceLocation l) const {
		return sid == l.sid && pos <= l.pos && pos+len > l.pos;
	}
	/// Returns true if the range \a r is fully enclosed by this range.
	bool contains(SourceRange r) const {
		return sid == r.sid && pos <= r.pos && pos+len >= r.pos+r.len;
	}
	/// Returns true if the given offset \a p lies within this range, assuming
	/// that \a p lies in the same source file as this range.
	bool contains(uint32_t p) const { return pos <= p && pos+len > p; }

	/// Returns true if the range \a r intersects with this range.
	bool intersects(SourceRange r) const {
		return sid == r.sid && pos < r.pos+r.len && pos+len > r.pos;
	}
	/// Returns true if the range \a r touches this range. This means the two
	/// ranges either intersect, or one immediately follows the other.
	bool touches(SourceRange r) const {
		return sid == r.sid && pos <= r.pos+r.len && pos+len >= r.pos;
	}
};

} // namespace maxwell
