#include "io.h"
#include "lib/stdlib.h"
#include "bsp/uart.h"

char read_c()
{
	return uart_getc();
}
void read_s(char *s)
{
	char input_char;
	s[0] = 0;
	int input_index = 0;
	while ((input_char = read_c()) != '\n') {
		if (input_char == '\b' ||
		    input_char == 127) { // manage backspace
			if (input_index >
			    0) { // ensure there's character to delete
				input_index -= 1; // delete the last character
				print_string(
					"\b \b"); // delete the last character console \b
				continue;
			}
		}
		s[input_index] = input_char;
		input_index += 1;
		print_char(input_char);
	}

	s[input_index] = 0;
}

void print_char(const char c)
{
	return uart_send(c);
}
void print_string(const char *s)
{
	return uart_puts(s);
}
void print_h(const int x)
{
	uart_hex(x);
}

void print_d(const int x)
{
	char buffer[10];

	itoa(x, buffer);
	print_string(buffer);
}
