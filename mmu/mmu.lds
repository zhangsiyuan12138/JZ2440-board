SECTIONS
{
    first 0x00000000 :{start.o init.o}
	seconed 0xb0004000:AT(2048){leds.o}
}
