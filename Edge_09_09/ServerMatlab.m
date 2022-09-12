clear
clc
close all
server = tcpip('192.168.1.69',8080,'NetworkRole','server', 'Timeout', .1, 'InputBufferSize', 2^12);
 msg ='{"tank 1":"|15.10|", "tank 2":"|21|"}';
resp = ['HTTP/1.1 200 OK' 10 13 ...
'Date: Mon, 26 Ago 2022 12:28:53 GMT' 10 13 ...
'Server: Apache/2.2.14 (Win32)' 10 13 ...
'Last-Modified: Wed, 22 Ago 2021 19:15:56 GMT' 10 13 ...
'Access-Control-Allow-Origin: *' 10 13 ...
'Content-Type: text/json' 10 13 ...
'Connection: Closed' 10 13 10 13 ...
'' 10 13 ...
msg];
fopen(server);
response = char(fread(server,2^11)');
fwrite(server,resp);
disp(response);
fclose(server);
Setpoint =[0]
for i = 1:100
    tic
msg =sprintf('{"tank 1":"|%.2f|", "tank 2":"|%.2f|"}',i,Setpoint(i));
resp = ['HTTP/1.1 200 OK' 10 13 ...
'Date: Mon, 26 Ago 2022 12:28:53 GMT' 10 13 ...
'Server: Matlab/2020a/Softec    ' 10 13 ...
'Last-Modified: Wed, 22 Ago 2021 19:15:56 GMT' 10 13 ...
'Access-Control-Allow-Origin: *' 10 13 ...
'Content-Type: text/json' 10 13 ...
'Connection: Closed' 10 13 10 13 ...
'' 10 13 ...
msg];
fopen(server);
response = char(fread(server,2^11)');
fwrite(server,resp);

Setpoint(i+1) = str2double(char(response(16:17)));

fclose(server);
toc
end