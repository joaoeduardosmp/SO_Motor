#ifndef RECEIVE_THREAD_H
#define RECEIVE_THREAD_H

#include <stdint.h>
#include "mbed.h"
#include "rtos.h"
#include "EthernetInterface.h"

void receive_thread(EthernetInterface* ethernet);

bool should_motor_stop(void);

#endif
