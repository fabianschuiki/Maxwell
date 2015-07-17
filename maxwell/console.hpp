/* Copyright (c) 2015 Fabian Schuiki */
#pragma once
#include <ostream>

namespace maxwell {
namespace console {


void init();
unsigned width();
bool hasColors();


template<unsigned... Codes>
struct Modifier {
	friend std::ostream& operator<< (std::ostream& os, Modifier) {
		if (hasColors()) {
			os << "\033[";
			print<Codes...>(os);
			os << 'm';
		}
		return os;
	}

	Modifier() {} // otherwise clang complains about lack of user-defined c'tor

	template<unsigned First, unsigned Second, unsigned... Rest>
	static void print(std::ostream& os) {
		os << First << ';';
		print<Second, Rest...>(os);
	}

	template<unsigned Code>
	static void print(std::ostream& os) {
		os << Code;
	}

	template<unsigned... Others>
	Modifier<Codes..., Others...> operator+ (Modifier<Others...> const&) const {
		return Modifier<Codes..., Others...>();
	}
};

// Formatting
static const Modifier<1> bold;
static const Modifier<2> dim;
static const Modifier<4> underline;
static const Modifier<5> blink;
static const Modifier<7> invert;
static const Modifier<8> hide;

static const Modifier<0>  reset;
static const Modifier<21> unbold;
static const Modifier<22> undim;
static const Modifier<24> ununderline;
static const Modifier<25> unblink;
static const Modifier<27> uninvert;
static const Modifier<28> unhide;

template<unsigned B>
struct Colors {
	Modifier<B+9> def;

	Modifier<B+0> black;
	Modifier<B+1> red;
	Modifier<B+2> green;
	Modifier<B+3> yellow;
	Modifier<B+4> blue;
	Modifier<B+5> magenta;
	Modifier<B+6> cyan;
	Modifier<B+7> lightgray;

	Modifier<B+60> darkgray;
	Modifier<B+61> lightred;
	Modifier<B+62> lightgreen;
	Modifier<B+63> lightyellow;
	Modifier<B+64> lightblue;
	Modifier<B+65> lightmagenta;
	Modifier<B+66> lightcyan;
	Modifier<B+67> white;

	Colors() {} // otherwise clang complains about lack of user-defined c'tor
};

/// Foreground color modifiers.
static const Colors<30> fg;
/// Background color modifiers.
static const Colors<40> bg;


} // namespace console
} // namespace maxwell
