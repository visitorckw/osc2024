#include "base.h"
#include "irq.h"
#include "uart.h"

uint32_t get_irq()
{
	return *CORE0_IRQ_SOURCE;
}

uint32_t is_core_timer_irq()
{
	return *CORE0_IRQ_SOURCE == (1 << 1);
}

uint32_t is_gpu_irq()
{
	return *CORE0_IRQ_SOURCE == (1 << 8);
}

static const char *entry_error_messages[] = {
	"SYNC_INVALID_EL1t",   "IRQ_INVALID_EL1t",
	"FIQ_INVALID_EL1t",    "ERROR_INVALID_EL1T",

	"SYNC_INVALID_EL1h",   "IRQ_INVALID_EL1h",
	"FIQ_INVALID_EL1h",    "ERROR_INVALID_EL1h",

	"SYNC_INVALID_EL0_64", "IRQ_INVALID_EL0_64",
	"FIQ_INVALID_EL0_64",  "ERROR_INVALID_EL0_64",

	"SYNC_INVALID_EL0_32", "IRQ_INVALID_EL0_32",
	"FIQ_INVALID_EL0_32",  "ERROR_INVALID_EL0_32"
};

const char *get_exception_message(unsigned long type)
{
	return entry_error_messages[type];
}

void el1_enable_interrupt()
{
	// Clear the D, A, I, F bits in the DAIF register
	// to enable interrupts in EL1
	asm volatile("msr daifclr, 0xf;");
}

void el1_disable_interrupt()
{
	// Set 1 to the D, A, I, F bits in the DAIF register
	// to disable interrupts in EL1
	asm volatile("msr daifset, 0xf;");
}
