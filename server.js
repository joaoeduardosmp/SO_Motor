var net = require('net');

var readline = require('readline');

var buffer = "";

var shouldStop = false;

var rl = readline.createInterface({
  input: process.stdin
});

rl.on('line',line => {
    if(line == 'stop')
        shouldStop = true;
    if(line == 'continue')
        shouldStop = false;
})

const identifiers = {
    SENSOR_READ: 0x00,
    QUERY_STOP: 0x01
}

console.log("Running server...");

var server = net.createServer(socket => {
    socket.on('data', data => {
        console.log(data);
        readBuffer(data, socket);
    })
    console.log("Someone has connected");
    socket.on('end', () => { console.log('Connection over.') });
});

server.listen(9090, '0.0.0.0');

const readBuffer = (bufferArray, socket) => {
    let identifier = bufferArray[0];
    switch(identifier)
    {
        case identifiers.SENSOR_READ:
            readSensorData(bufferArray);
        case identifiers.QUERY_STOP:
            sendStopData(socket);
        default:
            break;
    }
}

const sendStopData = socket => {
    console.log("Telling server if it should stop (shouldStop=" + shouldStop + ")")
    if(shouldStop)
        socket.write(Buffer.from([0x01]))
    else
        socket.write(Buffer.from([0x00]))
}

const readSensorData = bufferArray => {
    console.log("Reading sensor data: ");
    const sensor_0 = bufferArray.readUIntBE(1, 3)/1000;
    const sensor_1 = bufferArray.readUIntBE(4, 3)/1000;
    console.log("\tSensor 0: " + sensor_0);
    console.log("\tSensor 1: " + sensor_1);
}