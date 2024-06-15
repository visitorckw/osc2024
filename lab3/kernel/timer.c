#include "timer.h"

#include "bsp/irq.h"
#include "kernel/io.h"
#include "memory.h"

typedef struct timer_t {
	void (*func)(void *);
	void *arg;
	int time;
	struct timer_t *next;
} timer_t;

static timer_t *head = (timer_t *)0;

void set_timeout(void (*callback)(void *), void *arg, int delay)
{
	timer_t *timer = (timer_t *)simple_malloc(sizeof(timer_t));

	timer->func = callback;
	timer->arg = arg;
	timer->time = timer_get_uptime() + delay;
	timer->next = 0;

	if (head == 0 || timer->time < head->time) {
		// Insert at the beginning of the list
		timer->next = head;
		head = timer;
		core_timer_enable();
		return;
	}

	timer_t *cur = head;
	while (cur->next != 0 && cur->next->time <= timer->time)
		cur = cur->next;
	timer->next = cur->next;
	cur->next = timer;
}

void timer_irq_handler()
{
	// Check the timer queue
	while (head != 0 && timer_get_uptime() >= head->time) {
		head->func(head->arg);
		head = head->next;
	}

	if (head != 0)
		core_timer_enable();
}
