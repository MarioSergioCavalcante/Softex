/*
 * uart.h
 * Definicoes das funcoes da biblioteca uart.
 * Para o microcontrolador ATmega328P
 * Foi testada velocidade ate 38400 bps com clock de 8 MHz
 * Created: 29/08/2020 17:00:00
 * Author: Mário Sérgio Cavalcante
 */ 

#ifndef UART_H_
#define UART_H_
#include <inttypes.h>
#include <avr/io.h>

void    uartBegin(uint32_t baud, uint32_t freq_cpu); //inicaliza a porta de comunicação uart do ATmega328
uint8_t uartTxOk (void);           //verifica se novo dado pode ser enviado pela UART
void    uartTx(uint8_t dado);      //Envia um byte pela porta uart
uint8_t uartRxOk (void);           //verifica se uart possui novo dado
uint8_t uartRx();                  //Ler byte recebido na porta uart
void    uartIntRx(uint8_t x);      //Habilita interrupção de recepcao
void    uartIntTx(uint8_t x);      //Habilita interrupção de transmissão
void    uartString(char *c);       //Envia uma string pela porta uart. Ultimo valor da string deve ser 0.
void    uartDec1B(uint8_t valor);  //Envia pela uart variavel de 1 byte  ( 8 bits) com digitos em decimal
void    uartDec2B(uint16_t valor); //Envia pela uart variavel de 2 bytes (16 bits) com digitos em decimal
void    uartDec4B(uint32_t valor); //Envia pela uart variavel de 4 bytes (32 bits) com digitos em decimal
void    uartHex1B(uint8_t valor);  //Envia pela uart variavel de 1 byte  ( 8 bits) com digitos em hexadecimal
void    uartHex2B(uint16_t valor); //Envia pela uart variavel de 2 bytes (16 bits) com digitos em hexadecimal
void    uartHex4B(uint32_t valor); //Envia pela uart variavel de 4 bytes (32 bits) com digitos em hexadecimal

#endif /* UART_H_ */