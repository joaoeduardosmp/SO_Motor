#include "sensors_thread.h"
#include "send_thread.h"
#include "serial_pc.h"

void send_thread(EthernetInterface* ethernet)
{
    pc.printf("Client thread running. \r\n");
    while(1)
    {
        TCPSocket socket;
        if(socket.open(ethernet) != 0)
            pc.printf("Unable to open socket using ethernet. \r\n");
        else if(socket.connect(SERVER_IP, PORT) != 0)
            pc.printf("Unable to connect to server. \r\n");
        else
        {
            lock_sensors_mutex();

            pc.printf("Sending data to server. \r\n");
            uint8_t buffer[16] = {0};
            buffer[0] = ID_SENSOR_READ;

            uint32_t last_read_0_int = ((uint32_t) (get_sensor_read(0)*1000));
            buffer[1] = (last_read_0_int & 0xF00) >> 8;
            buffer[2] = (last_read_0_int & 0x0F0) >> 4;
            buffer[3] = (last_read_0_int & 0x00F);

            uint32_t last_read_1_int = ((uint32_t) (get_sensor_read(1)*1000));
            buffer[4] = (last_read_1_int & 0xF00) >> 8;
            buffer[5] = (last_read_1_int & 0x0F0) >> 4;
            buffer[6] = (last_read_1_int & 0x00F);

            buffer[7] = 0xFF;

            socket.send(buffer, sizeof(buffer));

            unlock_sensors_mutex();
        }
        socket.close();
        wait(5);
    }
}

