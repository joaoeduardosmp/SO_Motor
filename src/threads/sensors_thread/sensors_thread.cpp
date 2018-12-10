#include "mbed.h"
#include "rtos.h"
#include "sensors_thread.h"

static Mutex sensors_mutex;

static float last_read_0;

static float last_read_1;

static float last_read_2;

void sensors_thread(void)
{
    AnalogIn AnIn0(A0);
    AnalogIn AnIn1(A3);
    AnalogIn AnIn2(A2);
    while(1)
    {
        sensors_mutex.lock();
        last_read_0 = AnIn0.read();
        last_read_1 = AnIn1.read();
        last_read_2 = AnIn2.read();
        sensors_mutex.unlock();
    }
}

void lock_sensors_mutex(void)
{
    sensors_mutex.lock();
}

void unlock_sensors_mutex(void)
{
    sensors_mutex.unlock();
}

float get_sensor_read(uint8_t read_num)
{
    switch(read_num)
    {
        case 0:
            return last_read_0;
        case 1:
            return last_read_1;
        case 2:
            return last_read_2;
        default:
            break;
    }
}
