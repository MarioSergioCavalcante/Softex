const path = require('path');
const express = require('express');
const app = express();
const host = 'localhost';
const port = 8000;

app.use(express.static(path.join(__dirname+'/public-html')));

app.get('/', function(req,res){
    res.sendFile();
});

app.listen(8000);

console.log(`Server rodando em: http://${host}:${port}`);
console.log('Para desligar o servidor: ctrl + c')