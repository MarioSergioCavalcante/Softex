const path = require('path');
const express = require('express');
var https = require('https');
var fs = require('fs');
const app = express();
const host = 'localhost';
const port = 8000;

app.use(express.static(path.join(__dirname+'/public-html')));
app.get('/', function(req,res){
    res.sendFile();
});
app.get()
https
  .createServer(
    {
      key: fs.readFileSync("server.key"),
      cert: fs.readFileSync("server.crt"),
    },
    app
  )
  .listen(8000, function () {
    console.log(`Server rodando em: https://${host}:${port}`);
    console.log('Para desligar o servidor: ctrl + c');
  });

