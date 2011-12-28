<?php

/** Formatting helper functions. */
function varname($token) {
	return "\033[0;32m".(is_string($token) ? $token : $token->text)."\033[0m";
}
function typename($token) {
	return "\033[0;35m".(is_string($token) ? $token : $token->text)."\033[0m";
}
function numeric($token) {
	return "\033[0;36m".(is_string($token) ? $token : $token->text)."\033[0m";
}
function string($token) {
	return "\033[0;31m\"".(is_string($token) ? $token : $token->text)."\"\033[0m";
}
function keyword($token) {
	return "\033[1;34m".(is_string($token) ? $token : $token->text)."\033[0m";
}