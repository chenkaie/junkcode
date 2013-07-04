//arm-linux-gcc testasm.c -S
xxx(int a1, int a2, int a3, int a4, int a5, int a6)
{
}

main()
{
    asm("nop");
    asm("nop");
    asm("nop");
    /****************/
    /* 用夾擊法     */
    xxx(1,2,3,4,5,6);
    /****************/
    asm("nop");
    asm("nop");
    asm("nop");
}
