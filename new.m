clear
clc
close all
server = tcpip('172.20.9.110',8080,'NetworkRole','server', 'Timeout', .1, 'InputBufferSize', 2^12);
 msg ='{"tank 1":"|15.10|", "tank 2":"|21|"}';

 board = hil_open('q2_usb', '0');
values = [];
canais = [0 1]
 
Setpoint =[0]
sum_erro = 0;
ki = 0.45; 
kp = 1;
kd = 0.001;
erro_anterior = 0;
t_amos = 0.1;

for i = 1:500
 
 temp = hil_read(board,canais,[],[])';
 T1 = temp(1)*6.25;
 T2 = temp(2)*6.25;
 erro_atual = Setpoint(i) - T1;
 e(i) = erro_atual;
sum_erro = sum_erro + ki*erro_atual;
derro = kd*(erro_anterior - erro_atual)/t_amos;
u(i) = erro_atual * kp + sum_erro * t_amos + derro;
u_real(i) = Intertravamento(u(i),T1,T2);
hil_write_analog(board, 0, u_real(i));
values = [values;temp];
resp = ['HTTP/1.1 200 OK' 10 13 ...
'Date: Mon, 26 Ago 2022 12:28:53 GMT' 10 13 ...
'Server: Matlab/2020a/Softec    ' 10 13 ...
'Last-Modified: Wed, 22 Ago 2021 19:15:56 GMT' 10 13 ...
'Access-Control-Allow-Origin: *' 10 13 ...
'Content-Length: ' num2str(length(msg)+1)  10 13 ...
'Content-Type: text/html' 10 13 ...
'Connection: Closed' 10 13 10 13 ...
];
fopen(server);
fwrite(server,resp);
msg =sprintf('{"t":"|%.2f|", "t":"|%.2f|"}',T1,T2);

fwrite(server,msg);
tic
data = fscanf(server, '%c', 2^12);
toc

  Setpoint(i+1) = Setpoint(i);
if(length(data) >= 20)
    
    if(data(1:3) == 'GET')
        Setpoint(i+1) = str2double(char(data(16:17)));
    end
end
disp(data)
fclose(server);


fclose(server);
end
figure
plot(6.25*values, 'LineWidth',2.0);
axis([0 i 0 30])
legend('Tanque 1', 'Tanque 2')
xlabel('Tempo(s)')
ylabel('Nível (cm)')
hold on
plot(Setpoint,'r--','LineWidth',2.0)

hil_write_analog(board, 0, 0);
hil_close(board);
figure
plot(u,'b','LineWidth',2.0)
hold on
plot(u_real,'r','LineWidth',2.0)
legend('Sinal Controle', 'Real')
xlabel('Tempo(s)')
ylabel('Tensão (V)')
figure
plot(e,'b')
legend('Erro')
