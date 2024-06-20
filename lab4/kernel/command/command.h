#ifndef _ALL_H
#define _ALL_H

struct command {
	char name[16];
	char description[64];
	void (*function)(int argc, char **argv);
};

extern struct command hello_command;
extern struct command mailbox_command;
extern struct command reboot_command;
extern struct command ls_command;
extern struct command cat_command;
extern struct command test_malloc_command;
extern struct command async_io_demo_command;
extern struct command exec_command;
extern struct command set_timeout_command;
extern struct command test_kmalloc_command;
extern struct command test_kfree_command;

#endif
