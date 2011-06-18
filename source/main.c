#include <stdio.h>


int main(int argc, char * argv[])
{
	//Just open some file for preprocessing.
	FILE * input = fopen("example.mw", "r");
	if (!input) {
		printf("unable to open example.mw\n");
		return -1;
	}
	
	//Scan the file, character by character.
	int pc = 0;
	int line = 0, col = 0;
	
	char buffer[512];
	int i = 0;
	int type = 0;
	int start_line, start_col, end_line, end_col;
	
	while (!feof(input)) {
		int c = fgetc(input);
		buffer[i++] = c;
		buffer[i] = 0;
		
		//Line breaks.
		if (c == '\n') {
			line++;
			col = 0;
		}
		
		//Multiline comments.
		if (c == '*' && pc == '/') {
			type = 1;
			i = 0;
			start_line = line;
			start_col = col;
		}
		if (type == 1 && c == '/' && pc == '*') {
			buffer[i-1] = 0;
			buffer[i-2] = 0;
			buffer[i-3] = 0;
			printf("multi-comment %i.%i:%i.%i : \"%s\"\n",
				   start_line, start_col, line, col,
				   buffer);
			type = 0;
		}
		
		//Singleline comments.
		if (c == '/' && pc == '/') {
			type = 2;
			i = 0;
			start_line = line;
			start_col = col;
		}
		if (type == 2 && c == '\n') {
			buffer[i-1] = 0;
			printf("single-comment %i.%i:%i.%i : \"%s\"\n",
				   start_line, start_col, line, col,
				   buffer);
			type = 0;
		}
		
		//If we're reading a comment, continue since there is not much sense to be made of the rest.
		if (type != 1 && type != 2) {
			
			//String tokens.
			if (c == '"') {
				if (type == 0) {
					type = 3;
					i = 0;
					start_line = line;
					start_col = col;
				}
				else if (type == 3) {
					buffer[i-1] = 0;
					printf("string %i.%i:%i.%i : \"%s\"\n",
						   start_line, start_col, line, col,
						   buffer);
					type = 0;
				}
				else {
					printf("*** unexpected token %c at %i.%i\n", c, line, col);
				}
			}
		}
		
		//Terminate buffer.
		col++;
		pc = c;
	}
	
	//Close the file and return.
	fclose(input);
	return 0;
}
