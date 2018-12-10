#ifndef SENSORS_THREAD_H
#define SENSORS_THREAD_H

#include <stdint.h>

#define ID_SENSOR_READ  0x00

void sensors_thread(void);
void lock_sensors_mutex(void);
void unlock_sensors_mutex(void);
float get_sensor_read(uint8_t read_num);

#endif
