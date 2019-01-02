.extern main

.text
.global _start
_start:
       bl disable_watchdog
       bl clock_init
       bl open_icache
       bl sdram_init
       bl uart0_init
       bl nand_init
       
       ldr sp, =0x34000000
       ldr r0,=0
       ldr r1,=_start
       ldr r2,=__bss_start     @0x33f80000
       sub r2,r2,r1
       bl copy_uboot_to_sdram       
       ldr pc,=on_sdram
       
on_sdram:    
       bl clean_bss
       ldr lr,=main_return 
       ldr pc,=main
main_return:
           b main_return


















































