const path = require('path');
const express = require('express');
var http = require('http');
var https = require('https');
var fs = require('fs');
var cors = require('cors');
const app = express();
const host = 'localhost';
const port = 8443;

app.use(cors());
app.use(express.static(path.join(__dirname+'/public-html')));
app.get('/', function(req,res){
    res.sendFile();
});
https
  .createServer(
    {
      key: fs.readFileSync("server.key"),
      cert: fs.readFileSync("server.crt"),
    },
    app
  )
  .listen(port, function () {
    console.log(`Server rodando em: https://${host}:${port}`);
    console.log('Para desligar o servidor: ctrl + c');
  });
