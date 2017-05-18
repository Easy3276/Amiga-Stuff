ENTRY(_start)

SECTIONS
{
  __SUPER_SP = 0x40000;
  __USER_SP = 0x3fc00;
  __HEAP_END = 0x3f000;
  . = 0x400;

  .text : {
    __start = .;
    __stext = .;
    *(.text*)
    . = ALIGN(4);
    __etext = .;
  }

  .data : {
    . = ALIGN(4);
    __sdat = .;
    *(.data*)
   . = ALIGN(4);
    __edat = .;
  }

  .bss : {
    . = ALIGN(4);
    __sbss = .;
    *(.bss*)
    . = ALIGN(4);
    __ebss = .;
    __end = .;
  }

  /DISCARD/ : {
    *(.eh_frame)
  }
}
