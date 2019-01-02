.text
.global _start
_start:
         ldr sp,=4096
		 bl disable_watch_dog
		 bl enable_sdram
		 bl copy_2th_to_sdram
		 bl creat_page_table
         bl enable_mmu
		 ldr sp,=0xb4000000
		 ldr pc,=0xb0004000
loop1:
     b loop1








