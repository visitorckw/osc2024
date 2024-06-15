
SECTIONS
{
  . = 0x80000;
  .text : 
  {
      KEEP(*(.text.boot))
      *(.text) 
  } 
  .rodata :{ *(.rodata) }
  .data : { *(.data) }
  .bss :
  {
      __bss_start = .;
	    *(.bss)
	    *(COMMON)
	    __bss_end = .;
  }
  . = ALIGN(8);
  __heap_start = .;
}
__bss_size = (__bss_end - __bss_start) >> 3;
