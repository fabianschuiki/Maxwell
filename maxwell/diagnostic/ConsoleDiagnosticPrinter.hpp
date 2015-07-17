/* Copyright (c) 2015 Fabian Schuiki */
#pragma once
#include "maxwell/diagnostic/diagnostic.hpp"
#include "maxwell/diagnostic/SourceLayout.hpp"
#include "maxwell/filesystem/Path.hpp"
#include <map>

namespace maxwell {

namespace repository {
	class Source;
	class SourceRepository;
}

/// \needsdoc
/// \ingroup diagnostic
class ConsoleDiagnosticPrinter : public DiagnosticConsumer {
public:
	typedef maxwell::filesystem::Path Path;
	typedef maxwell::repository::Source Source;
	typedef maxwell::repository::SourceRepository SourceRepository;

	SourceRepository& sourceRepository;

	ConsoleDiagnosticPrinter(SourceRepository& src): sourceRepository(src) {}

	void consume(Diagnostic const& d);

	unsigned lineWidth = 0;

private:
	Path lookupSourcePath(SourceId id);
	SourceLayout const& lookupSourceLayout(Source* source);

	std::map<Source*,SourceLayout> sourceLayoutCache;
};

} // namespace maxwell
