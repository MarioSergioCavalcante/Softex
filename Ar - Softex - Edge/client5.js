// Get net module 
const net = require('net');

//Configuration ===================================
const port = 8080;
//=================================================

//================= Client 1 ==========================
//Create the socket client.
const client1 = new net.Socket();

//Connect to the server on the configured port 
client1.connect(port,function(){
   //Log when the connection is established
   console.log(`CLient 1 :Connected to server on port ${port}`);
   
   //Try to send data to the server 
   client1.write('Sp: 15');

});
//Handle data coming from the server
client1.on('data',function(data){
   console.log(`Client 1 received from server : ${data}`);
   client1.write('Sp: 10');    
});
// Handle connection close 
client1.on('close',function(){
   console.log('Client 1 :Connection Closed');
});
//Handle error
client1.on('error',function(error){
   console.error(`Connection Error ${error}`); 
});