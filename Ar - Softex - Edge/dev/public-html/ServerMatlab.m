clear
clc
close all
server = tcpip('172.20.9.110',8080,'NetworkRole','server', 'Timeout', .1, 'InputBufferSize', 2^12);

board = hil_open('q2_usb', '0');
values = [];
canais = [0 1]

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

sum_erro = 0;
ki = 0.45; 
kp = 1;
kd = 0.001;
erro_anterior = 0;
t_amos = 0.1;
tic 
for i = 1:50
    Sp(i) = 10;
    temp = hil_read(board,canais,[],[])';
    T1 = temp(1)*6.25;
    T2 = temp(2)*6.25;
    erro_atual = Sp(i) - T1;
    sum_erro = sum_erro + ki*erro_atual;
    derro = kd*(erro_anterior - erro_atual)/t_amos;
    u(i) = erro_atual * kp + sum_erro * t_amos + derro;
    hil_write_analog(board, 0, Intertravamento(u(i),T1,T2));
    values = [values;temp];
    
    msg =sprintf('{"tank 1":"|%.2f|", "tank 2":"|%.2f|"}',T1,T2);
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
    
    erro_anterior = erro_atual;
end
toc
figure
plot(6.25*values);
legend('Tanque 1', 'Tanque 2')
xlabel('Tempo(s)')
ylabel('Nível (cm)')
hold on
plot(Sp,'r--','LineWidth',2.0)

hil_write_analog(board, 0, 0);
hil_close(board);
figure
plot(u)