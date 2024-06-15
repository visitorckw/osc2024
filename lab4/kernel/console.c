#include "console.h"

#include "command/command.h"
#include "io.h"
#include "lib/stdlib.h"
#include "lib/string.h"

struct console {
	struct command commands[64];
	int num_commands;
};

struct console console;

struct console *console_create()
{
	console.num_commands = 0;
	return &console;
}

static void read_command(char *);
static int parse_command(char *, char **);
void _print_help(struct console *console);

void init_console(struct console *console)
{
	console->num_commands = 0;
}

void run_console(struct console *console)
{
	char input[256];
	while (1) {
		print_string("\n$ ");

		read_command(input);
		int argc = 0;
		char *argv[16];
		argc = parse_command(input, argv);

		if (argc == 0) {
			continue;
		}
		if (strcmp(argv[0], "help") == 0) {
			_print_help(console);
			continue;
		}
		int i = 0;
		for (i = 0; i < console->num_commands; i++) {
			if (strcmp(argv[0], console->commands[i].name) == 0) {
				console->commands[i].function(argc, argv);
				break;
			}
		}
		if (i == console->num_commands) {
			print_string("\ncommand not found\n");
		}
	}
}

void register_command(struct console *console, struct command *command)
{
	console->commands[console->num_commands] = *command;
	console->num_commands++;
}

void register_all_commands(struct console *console)
{
	register_command(console, &hello_command);
	register_command(console, &mailbox_command);
	register_command(console, &reboot_command);
	register_command(console, &ls_command);
	register_command(console, &cat_command);
	register_command(console, &exec_command);
	register_command(console, &test_malloc_command);
	register_command(console, &async_io_demo_command);
	register_command(console, &set_timeout_command);
	register_command(console, &test_kmalloc_command);
	register_command(console, &test_kfree_command);
}

static void read_command(char *x)
{
	char input_char;
	x[0] = 0;
	int input_index = 0;
	while ((input_char = read_c()) != '\n') {
		x[input_index] = input_char;
		input_index += 1;
		print_char(input_char);
	}
	if (x[input_index - 1] == '\n') {
		x[input_index - 1] = '\0';
	} else {
		x[input_index] = '\0';
	}
}

static int parse_command(char *command, char **argv)
{
	int argc = 0;

	char *token = strtok(command, " ");
	while (token != NULL) {
		argv[argc] = token;
		argc++;
		token = strtok(NULL, " ");
	}
	return argc;
}

void _print_help(struct console *console)
{
	print_string("\n");

	print_string("help : print this help menu\n");
	for (int i = 0; i < console->num_commands; i++) {
		print_string(console->commands[i].name);
		print_string(" : ");
		print_string(console->commands[i].description);
		print_string("\n");
	}
}
