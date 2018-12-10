#include <stdint.h>
#include "mbed.h"
#include "rtos.h"
#include "EthernetInterface.h"
#include "sensors_thread.h"
#include "send_thread.h"
#include "serial_pc.h"

#define CLIENT_IP   "192.168.0.25"
#define NETMASK     "255.255.255.0"
#define GATEWAY     "0.0.0.0"

EthernetInterface ethernet;
void init_ethernet(void);

Thread thread_1;
Thread thread_2;
Thread thread_3;

int main()
{
    init_serial();
    init_ethernet();
    thread_1.start(sensors_thread);
    thread_2.start(callback(send_thread, &ethernet));
}

void init_ethernet()
{
    pc.printf("Initializing ethernet device. \r\n");
    ethernet.set_network(CLIENT_IP, NETMASK, GATEWAY);
    if(ethernet.connect() != NSAPI_ERROR_OK)
        pc.printf("Error initializing ethernet device.\r\n");
    else
        pc.printf("Ethernet device initialized successfully.\r\n");
}
