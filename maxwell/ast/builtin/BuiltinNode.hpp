/* Copyright (c) 2013 Fabian Schuiki */
#pragma once
#include "maxwell/ast/Node.hpp"
#include <string>

namespace ast {
namespace builtin {

using std::string;

class BuiltinNode : public Node
{
public:
	virtual string getClassName() const { throw std::runtime_error("Calling getClassName() on a BuiltinNode does not make sense."); }
	virtual void encode(Encoder& e) { throw std::runtime_error("Calling encode() on a BuiltinNode does not make sense."); }
	virtual void decode(Decoder& d) { throw std::runtime_error("Calling decode() on a BuiltinNode does not make sense."); }
	virtual const NodePtr& resolvePath(const string& path) { throw std::runtime_error("Calling resolvePath() on a BuiltinNode does not make sense."); }
};

} // namespace builtin
} // namespace ast
