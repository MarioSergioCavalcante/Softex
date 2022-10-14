const WebSocket = require('ws');
const PORT = 5000;
const wsServer = new WebSocket.Server({
    port: PORT
});

wsServer.on('connection', function(socket) {
    //Mensagem no console simples
    console.log("Um cliente conectou com sucesso!");

    socket.on('message',function(msg){
        console.log('Mensagem Recebida: ' + msg);
      // socket.send("Tome: "+msg);
        wsServer.clients.forEach(function(client){
            client.send(msg);
        })
    });
});


console.log((new Date()) + "\nServidor esta lendo na porta " + PORT )