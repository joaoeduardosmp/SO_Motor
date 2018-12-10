var net = require('net');

const identifiers = {
    SENSOR_READ: 0x00
}

console.log("Running server...");

var server = net.createServer(socket => {
    socket.on('data', data => {
        console.log(data);
        readBuffer(data);
    })
    console.log("Someone has connected");
    socket.on('end', () => { console.log('Connection over.') });
});

server.listen(9090, '0.0.0.0');

const readBuffer = bufferArray => {
    let identifier = bufferArray[0];
    switch(identifier)
    {
        case identifiers.SENSOR_READ:
            readSensorData(bufferArray);
        default:
            break;
    }
}

const readSensorData = bufferArray => {
    const sensor_0 = bufferArray.readUIntBE(1, 3)/1000;
    const sensor_1 = bufferArray.readUIntBE(4, 3)/1000;
    const sensor_2 = bufferArray.readUIntBE(7, 3)/1000;
    console.log("Sensor 0: " + sensor_0);
    console.log("Sensor 1: " + sensor_1);
    console.log("Sensor 2: " + sensor_2);
}