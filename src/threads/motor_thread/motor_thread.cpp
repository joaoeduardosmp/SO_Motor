#include "mbed.h"
#include "rtos.h"
#include "motor_thread.h"
#include "sensors_thread.h"
#include "receive_thread.h"

static void servo_angle(PwmOut* pwm, Direction direction)
{
    //0º -> 1ms -> 25%
    //180º -> 2ms -> 50%
    //90º -> 1.5ms -> 37.5%
    if(direction == RIGHT)
        pwm->write(0.7f/20);
    else
        pwm->write(3.0f/20);
}

void motor_thread(void)
{
    Direction last_direction;
    PwmOut pwm(D13);
    pwm.period_ms(20);
    pwm.write(0.375f);
    while(1)
    {
        lock_sensors_mutex();
        if(!should_motor_stop())
        {
            float sensor_0 = get_sensor_read(0);
            float sensor_1 = get_sensor_read(1);
            if(sensor_0 > sensor_1 && last_direction != RIGHT)
            {
                last_direction = RIGHT;
                servo_angle(&pwm, RIGHT);
            }
            else if(sensor_1 > sensor_0 && last_direction != LEFT)
            {
                last_direction = LEFT;
                servo_angle(&pwm, LEFT);
            }
            wait_ms(100);
        }
        unlock_sensors_mutex();
    }
}
