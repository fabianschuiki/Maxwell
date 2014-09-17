/* Copyright (c) 2014 Fabian Schuiki */
#pragma once

namespace maxwell {
namespace repository {

class SourceInfoInterface {
public:
	virtual const Path& getPath() = 0;
};

} // namespace repository
} // namespace maxwell
