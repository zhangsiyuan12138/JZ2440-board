SECTIONS
{
  . = 0x30000000;
  .text  : {*(.test)}
  .rodata : {*(.rodata)}
  .dtat  : {*(.data)}
  .bss   : {*(.bss) *(COMMON)}

}




