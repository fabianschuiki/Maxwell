/* Copyright © 2013 Fabian Schuiki */
#include "Serializer.hpp"
#include "Coder.hpp"
#include "nodes/nodes.hpp"
#include <sstream>
#include <common/base64.hpp>
#include <stdexcept>

using ast::Serializer;
using ast::Node;
using ast::NodePtr;
using ast::NodeVector;
using ast::NodeFactory;
using ast::Encoder;
using ast::Decoder;
using std::string;
using std::stringstream;
using std::ostream;
using std::istream;
using boost::shared_ptr;

/**
 * Concrete implementation of the Encoder interface. An instance of this class
 * is created upon serialization and handed down the tree for serializing.
 */
class EncoderImpl : public Encoder
{
public:
	ostream& out;
	EncoderImpl(ostream& o) : out(o) {}

	virtual void encode(const NodePtr& node, bool ref = false)
	{
		if (node) {
			if (ref) {
				out << node->getId() << " ";
			} else {
				out << node->getClassName() << " { ";
				node->encode(*this);
				out << "} ";
			}
		} else {
			out << "@ ";
		}
	}

	virtual void encode(const string& str)
	{
		if (str.empty()) {
			out << "$ ";
		} else {
			out << base64::encode(str) << ' ';
		}
	}

	virtual void encode(const NodeVector& nodes, bool ref = false)
	{
		if (nodes.empty()) {
			out << "[] ";
		} else {
			out << "[ ";
			bool first = true;
			for (NodeVector::const_iterator it = nodes.begin(); it != nodes.end(); it++) {
				if (first) {
					first = false;
				} else {
					out << ", ";
				}
				encode(*it, ref);
			}
			out << "] ";
		}
	}
};

/**
 * Concrete implementation of the Decoder interface. An instance of this class
 * is created upon unserialization and handed down the tree for decoding.
 */
class DecoderImpl : public Decoder
{
public:
	istream& in;
	DecoderImpl(istream& i) : in(i) {}

	virtual void decode(NodePtr& node, bool ref = false)
	{
		string className;
		in >> className;
		if (className == "@") {
			node.reset();
		} else {
			string rd;
			in >> rd;
			if (rd != "{") {
				throw std::runtime_error("Node excepted to commence with an opening brace {, got '" + rd + "' instead.");
			}

			node = NodeFactory::make(className);
			node->decode(*this);

			in >> rd;
			if (rd != "}") {
				throw std::runtime_error("Node excepted to terminate with a closing brace }, got '" + rd + "' instead.");
			}
		}
	}

	virtual void decode(string& str)
	{
		string rd;
		in >> rd;
		if (rd == "$") {
			str.clear();
		} else {
			str = base64::decode(rd);
		}
	}

	virtual void decode(NodeVector& nodes, bool ref = false)
	{
		string rd;
		in >> rd;
		if (rd == "[]") {
			nodes.clear();
		} else {
			if (rd != "[") {
				throw std::runtime_error("Vector of nodes expected to commence with an opening bracket [, got '" + rd + "' instead.");
			}
			do {
				NodePtr node;
				decode(node, ref);
				nodes.push_back(node);
				in >> rd;
			} while (rd == ",");
			if (rd != "]") {
				throw std::runtime_error("Vector of nodes expected to terminate with a closing bracket ], got '" + rd + "' instead.");
			}
		}
	}
};

/**
 * @brief Serializes the given node to the given stream.
 */
void Serializer::encode(ostream& out, const NodePtr& node)
{
	EncoderImpl enc(out);
	enc.encode(node);
}

/**
 * @brief Serializes the given node into a string.
 *
 * Simply calls encode() with a stringstream and the node, then returns the
 * generated string.
 */
string Serializer::encode(const NodePtr& node)
{
	stringstream s;
	encode(s, node);
	return s.str();
}

/**
 * @brief Unserializes a node from the given stream.
 */
NodePtr Serializer::decode(istream& in)
{
	DecoderImpl dec(in);
	NodePtr node;
	dec.decode(node);
	return node;
}

/**
 * @brief Unserializes the string and returns the resulting node.
 *
 * Simply calls decode() with a string stream and the node, then returns the
 * generated node.
 */
NodePtr Serializer::decode(const string& str)
{
	stringstream s(str);
	return decode(s);
}