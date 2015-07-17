/* Copyright (c) 2015 Fabian Schuiki */
#pragma once
#include "maxwell/location.hpp"
#include "maxwell/iterator.hpp"
#include "maxwell/range.hpp"
#include <memory>
#include <functional>
#include <set>
#include <vector>


namespace maxwell {

class Diagnostic;
class DiagnosticConsumer;
class DiagnosticContext;
class DiagnosticMessage;


enum DiagnosticSeverity {
	kFatal,
	kError,
	kWarning,
	kInfo,
	kNone
};


/// \needsdoc
class DiagnosticConsumer {
public:
	virtual void consume(Diagnostic const& d) = 0;
};


/// \needsdoc
/// \ingroup diagnostic
class DiagnosticContext {
	typedef std::vector<std::unique_ptr<Diagnostic>> diagnostics_type;

public:
	typedef dereferencing_iterator<diagnostics_type::iterator> iterator;
	typedef dereferencing_iterator<diagnostics_type::const_iterator> const_iterator;

	void add(std::unique_ptr<Diagnostic>&& d);

	DiagnosticSeverity getSeverity() const { return severity; }

	bool isFatal()   const { return severity <= kFatal; }
	bool isError()   const { return severity <= kError; }
	bool isWarning() const { return severity <= kWarning; }
	bool isInfo()    const { return severity <= kInfo; }

	void eachDiagnostic(std::function<void(Diagnostic&)> fn) {
		for (auto const& d : diagnostics)
			fn(*d);
	}

	void eachDiagnostic(std::function<void(Diagnostic const&)> fn) const {
		for (auto const& d : diagnostics)
			fn(*d);
	}

	range<iterator> getDiagnostics() {
		return make_range(
			iterator(diagnostics.begin()), iterator(diagnostics.end())
		);
	}

	range<const_iterator> getDiagnostics() const {
		return make_range(
			const_iterator(diagnostics.begin()), const_iterator(diagnostics.end())
		);
	}

private:
	DiagnosticSeverity severity = kNone;
	diagnostics_type diagnostics;
};


/// \needsdoc
/// \ingroup diagnostic
class Diagnostic {
	typedef std::vector<std::unique_ptr<DiagnosticMessage>> messages_type;

public:
	typedef dereferencing_iterator<messages_type::iterator> iterator;
	typedef dereferencing_iterator<messages_type::const_iterator> const_iterator;

	Diagnostic(unsigned id = 0): id(id) {}

	void add(std::unique_ptr<DiagnosticMessage>&& msg);

	unsigned getId() const { return id; }
	DiagnosticSeverity getSeverity() const { return severity; }

	void eachMessage(std::function<void(DiagnosticMessage&)> fn) {
		for (auto const& msg : messages)
			fn(*msg);
	}

	void eachMessage(std::function<void(DiagnosticMessage const&)> fn) const {
		for (auto const& msg : messages)
			fn(*msg);
	}

	range<iterator> getMessages() {
		return make_range(
			iterator(messages.begin()), iterator(messages.end())
		);
	}

	range<const_iterator> getMessages() const {
		return make_range(
			const_iterator(messages.begin()), const_iterator(messages.end())
		);
	}

private:
	friend class DiagnosticContext;

	unsigned id;
	DiagnosticSeverity severity = kNone;
	messages_type messages;
};


/// \needsdoc
/// \ingroup diagnostic
class DiagnosticMessage {
public:
	DiagnosticMessage(DiagnosticSeverity severity, std::string const& text):
		severity(severity),
		text(text) {}

	DiagnosticSeverity getSeverity() const { return severity; }
	std::string const& getText() const { return text; }
	SourceRange const& getMainRange() const { return mainRange; }
	std::vector<SourceRange> const& getHighlitRanges() const { return highlitRanges; }
	std::vector<SourceRange> const& getVisibleRanges() const { return visibleRanges; }

	void setMainRange(SourceRange const& r) { mainRange = r; }
	void addHighlitRange(SourceRange const& r) { highlitRanges.push_back(r); }
	void addVisibleRange(SourceRange const& r) { visibleRanges.push_back(r); }

private:
	friend class Diagnostic;

	DiagnosticSeverity severity;
	std::string text;
	SourceRange mainRange;
	std::vector<SourceRange> highlitRanges;
	std::vector<SourceRange> visibleRanges;
};


} // namespace maxwell
