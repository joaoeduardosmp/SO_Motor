#include "serial_pc.h"

Serial pc(USBTX, USBRX);

void init_serial(void)
{
    pc.baud(115200);
    pc.printf("Initializing SO_Projeto.\r\n");
}