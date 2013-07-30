/* Copyright © 2013 Fabian Schuiki */
#pragma once
#include <ast/Node.hpp>

namespace stage {
namespace algorithm {
namespace type {

using ast::NodePtr;

NodePtr simplify(const NodePtr& input);
bool equal(const NodePtr& a, const NodePtr& b);
NodePtr intersect(const NodePtr& a, const NodePtr& b);

} // namespace type
} // namespace algorithm
} // namespace stage