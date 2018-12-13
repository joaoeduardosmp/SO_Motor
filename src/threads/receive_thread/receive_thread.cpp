#include "receive_thread.h"
#include "send_thread.h"
#include "serial_pc.h"

uint8_t should_stop = false;

void receive_thread(EthernetInterface* ethernet)
{
    pc.printf("Client thread running. \r\n");
    while(1)
    {
        TCPSocket socket;
        socket.set_blocking(false);
        if(socket.open(ethernet) != 0)
            pc.printf("Unable to open socket using ethernet. \r\n");
        else if(socket.connect(SERVER_IP, PORT) != 0)
            pc.printf("Unable to connect to server. \r\n");
        else
        {
            pc.printf("Sending data to server, telling it if it should stop. \r\n");
            uint8_t buffer[1] = {0x01};
            socket.send(buffer, sizeof(buffer));

            uint8_t rec_buf[1];
            socket.recv(rec_buf, sizeof(rec_buf));
            pc.printf("Received from server: \r\n");
            if(rec_buf[0] == 0x00)
                pc.printf("\tShouldn't stop\r\n");
            else
                pc.printf("\tShould stop\r\n");
            pc.printf("\r\n");
            should_stop = rec_buf[0] != 0x00;
        }
        socket.close();
        wait(5);
    }
}

bool should_motor_stop(void)
{
    return should_stop;
}