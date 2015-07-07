/* Copyright (c) 2014 Fabian Schuiki */
#include "maxwell/repository/file/FileSource.hpp"
#include "maxwell/repository/file/FileSourceRepository.hpp"

using namespace maxwell;
using namespace maxwell::repository;

range<Byte*>
FileSource::getContent() const {

	if (!contentLoaded) {
		contentLoaded = true;
		auto& file = repo.dir.getFile(pathHash.lhex());
		file.read(content);
	}

	return make_range(&content[0], &content[0] + content.size());
}
