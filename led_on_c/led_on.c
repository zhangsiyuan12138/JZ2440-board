#define GPFCON  (*(unsigned int *)0x56000050)
#define GPFDAT  (*(unsigned int *)0x56000054)


int main(void)
{
    GPFCON=0x00000100
    GPFDAT=0;
    return 0;
}