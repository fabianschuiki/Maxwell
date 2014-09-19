/* Copyright (c) 2014 Fabian Schuiki */
#include "maxwell/mwc/Tool.hpp"

namespace maxwell {
namespace mwc {

class SourceTool : public Tool {
public:
	void run() {
		std::cout << "hello!\n";
	}
};

} // namespace mwc
} // namespace maxwell

MWC_TOOL_MAIN(SourceTool)
