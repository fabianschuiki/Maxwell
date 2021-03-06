/* Copyright (c) 2014 Fabian Schuiki */
#include "maxwell/filesystem/disk/DiskFile.hpp"
#include <boost/filesystem/fstream.hpp>
#include <stdexcept>
using namespace maxwell::filesystem;


bool DiskFile::exists() const {
	return boost::filesystem::exists(path);
}

void DiskFile::unlink() const {
	boost::filesystem::remove(path);
}


void DiskFile::read(std::vector<Byte>& dst) const {
	boost::filesystem::ifstream fin(path, std::ios_base::binary);
	if (fin.good()) {
		fin.seekg(0, std::ios_base::end);
		dst.resize(fin.tellg());
		fin.seekg(0, std::ios_base::beg);
		fin.read((char*)&dst[0], dst.size());
	} else {
		throw std::runtime_error("file cannot be read");
	}
}

void DiskFile::write(const Buffer<const Byte>& src) {
	boost::filesystem::ofstream fout(path, std::ios_base::binary | std::ios_base::trunc);
	if (fout.good()) {
		fout.write((const char*)src.getStart(), src.getLength());
	} else {
		throw std::runtime_error("file cannot be written");
	}
}

time_t DiskFile::getModificationTime() const {
	return boost::filesystem::last_write_time(path);
}
