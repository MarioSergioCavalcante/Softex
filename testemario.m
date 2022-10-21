clear
clc
close all
server = tcpip('0.0.0.0',8080,'NetworkRole','server', 'Timeout', 0.1, 'InputBufferSize', 2^12);
 
Setpoint =[0]
msg =sprintf('{"t1":"|%.2f|", "t2":"|%.2f|"}',1,Setpoint(1));

for i = 1:500
    
resp = ['HTTP/1.1 200 OK' 10 13 ...
'Date: Mon, 26 Ago 2022 12:28:53 GMT' 10 13 ...
'Server: Matlab/2020a/Softec    ' 10 13 ...
'Last-Modified: Wed, 22 Ago 2021 19:15:56 GMT' 10 13 ...
'Access-Control-Allow-Origin: *' 10 13 ...
'Content-Type: text/plain' 10 13 ...
'Content-Length: ' length(msg)+1  10 13 ...
'Connection: Closed' 10 13 10 13 ...
];
fopen(server);
disp('-------------------------')
fwrite(server,resp);
msg = sprintf('{"t1":"|%.2f|", "t2":"|%.2f|"}',i,Setpoint(i));
disp(msg);

fwrite(server,msg);
while (server.BytesAvailable == 0)
    pause(0.0001)
end

data = fscanf(server,'%c',2^12)
Setpoint(i+1) = str2double(data)
fclose(server);

end
plot(Setpoint','r--','LineWidth',2.0)
axis([0 i 0 30])