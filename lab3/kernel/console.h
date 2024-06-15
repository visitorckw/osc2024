#ifndef CONSOLE_H
#define CONSOLE_H

struct command;
struct console;

struct console *console_create();
void init_console(struct console *console);
void run_console(struct console *console);
void register_command(struct console *console, struct command *command);
void register_all_commands(struct console *console);
void destroy_console(struct console *console);

#endif
