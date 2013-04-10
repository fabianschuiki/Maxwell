

void writeToConsole (struct Stringable *x)
{
	String *s = toString(x);
	console_println(s);
}