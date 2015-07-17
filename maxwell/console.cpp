/* Copyright (c) 2015 Fabian Schuiki */
#include "maxwell/console.hpp"
#include <sys/ioctl.h>
#include <unistd.h>


static unsigned console_width = 0;
static bool console_colors = 0;


/// Initializes and updates console information. This function should be called
/// at least at the beginning of the program. \warning This function is not
/// thread safe and should therefore only be called in circumstances where the
/// main thread is the only thread executing.
void maxwell::console::init() {
	struct winsize w;
	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) != 0)
		console_width = 0;
	else
		console_width = w.ws_col;

	console_colors = isatty(STDOUT_FILENO);
}

/// Returns the width of the console window in columns.
unsigned maxwell::console::width() {
	return console_width;
}

/// Returns true if the console supports colors, false otherwise.
bool maxwell::console::hasColors() {
	return console_colors;
}
