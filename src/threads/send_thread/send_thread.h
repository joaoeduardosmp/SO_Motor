#ifndef SEND_THREAD_H
#define SEND_THREAD_H

#include <stdint.h>
#include "mbed.h"
#include "rtos.h"
#include "EthernetInterface.h"

#define SERVER_IP   "192.168.0.22"
#define PORT        9090

void send_thread(EthernetInterface* ethernet);

#endif
