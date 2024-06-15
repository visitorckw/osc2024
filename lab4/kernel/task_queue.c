#include "task_queue.h"

#include "bsp/irq.h"
#include "kernel/io.h"
#include "memory.h"

typedef struct task_t {
	void (*func)();
	int priority;
	int running; // Set to 1 if the task is under processing
	struct task_t *prev;
	struct task_t *next;
} task_t;

static task_t *task_head = 0;

void init_task_queue()
{
	task_head = (task_t *)0;
}

void print_task_queue()
{
	task_t *tmp = task_head;
	int count = 0;
	print_string("\n----------------\n");
	while (tmp) {
		print_string("Task: ");
		print_d(count++);
		print_string(", Priority: ");
		print_d(tmp->priority);
		print_string(", Running: ");
		print_d(tmp->running);
		print_string("\n");
		tmp = tmp->next;
	}
	print_string("----------------\n");
}

void add_task(void (*func)(void), int priority)
{
	task_t *new_task = (task_t *)simple_malloc(sizeof(task_t));
	*new_task = (task_t) {
		.func = func,
		.priority = priority,
		.running = 0,
		.next = 0,
		.next = 0
	};

	if (!task_head) {
		task_head = new_task;
		return;
	}
	task_t *cur = task_head;
	while (cur->next && cur->priority <= priority) {
		cur = cur->next;
	}
	if (!cur->next && cur->priority <= priority) {
		cur->next = new_task;
		new_task->prev = cur;
	} else {
		new_task->next = cur;
		new_task->prev = cur->prev;
		if (!new_task->prev)
			task_head = new_task;
		cur->prev = new_task;
	}
}

void run_task()
{
	while (task_head && !task_head->running) {
		el1_disable_interrupt();
		task_t *tmp = task_head;
		tmp->running = 1;
		el1_enable_interrupt();
		tmp->func();
		el1_disable_interrupt();
		if (tmp->prev)
			tmp->prev->next = tmp->next;
		if (tmp->next)
			tmp->next->prev = tmp->prev;
		if (task_head == tmp)
			task_head = tmp->next;
		el1_enable_interrupt();
	}
}
