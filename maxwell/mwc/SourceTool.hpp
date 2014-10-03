/* Copyright (c) 2014 Fabian Schuiki */
#include "maxwell/mwc/Tool.hpp"

namespace maxwell {
namespace mwc {

class SourceTool : public Tool {
protected:
	bool run();
	void printUsage();

public:
	template<typename... Args>
	SourceTool(Args&&... args): Tool(args...) {}
};

} // namespace mwc
} // namespace maxwell
