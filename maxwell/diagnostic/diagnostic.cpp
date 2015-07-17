/* Copyright (c) 2015 Fabian Schuiki */
#include "maxwell/diagnostic/diagnostic.hpp"

using namespace maxwell;


void
DiagnosticContext::add (std::unique_ptr<Diagnostic>&& d) {
	/// \todo Translate severity as requested.

	if (severity > d->severity)
		severity = d->severity;
	diagnostics.push_back(std::move(d));
}


void
Diagnostic::add (std::unique_ptr<DiagnosticMessage>&& msg) {
	if (severity > msg->severity)
		severity = msg->severity;
	messages.push_back(std::move(msg));
}
