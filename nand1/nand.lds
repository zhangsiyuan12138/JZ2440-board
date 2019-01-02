SECTIONS
{
 first  0x00000000 :{start.o sdram.o nand.o}
seconed 0x30000000 :AT(4096) {leds.o}
}