#define F_CPU 8000000UL
#include <avr/io.h>

#include "adc.h"
#include "uart.h"
#include <stdio.h>
int main(void)
{	uartBegin(9600, F_CPU); //Inicializa UART
	adcBegin(AVCC, 0x01);   //Inicializa A/D
    adcChannel(ADC0);       //Seleciona canal
	//Aguarda a recepção do primeiro comando, configurando o tempo de amostragem do sinal
	while (!uartRxOk());

	if (uartRxOk())     //verifica se existe novo dado
	{ 
		uint8_t t = uartRx();//armazena dado
		if(t == '1'){
				OCR0A = 78; //A cada 0,01 s gera uma interrupção
		}else{
			if(t == '2'){
					OCR0A = 2*78; //A cada 0,01 s gera uma interrupção
			}
		}
	
	
	}
	
	adcIntEn(1);            //Interrupção do A/D
    uartIntRx(1);           //Interrupção da uart
	PORTD |= (1 << PD6); // Configura o pino PD6 como saída
	//Configura o ínicio da contagem para que aconteçam as interrupções a cada segundo programado.
	TCCR0A = ( 1 << COM0A0) | (1 << WGM01); //OC0A troca de estado Pino de controle para teste do tempo de amostragem, retirar o bit COM no real
	TCCR0B = (1 << CS02) | (1 << CS02);  //Configura o Prescaler de 1024
	TIMSK0 = (1 << OCIE0A); //Habilita a interrupção de comparação com o valor do OCR0A
	sei();                  //Interrupção geral
	while (1);
}

//Tratamendo da interrupção de recepção de dados
ISR(TIMER0_COMPA_vect)
{ 
	 // uartString("Aconteceu!\n");
	   adcSample();      //Inicia conversão  
}

//Tratamendo da interrupção do A/D
ISR(ADC_vect)
{ //uartString("Valor: ");    //Envia string
	//float valor = adcReadOnly()*5.0/1024;
	char teste[100];
    uint16_t valor = ((float) 5/1024)*(adcReadOnly()+1)*100;
	sprintf(teste, "Valor Convertido: %d\r\n", valor);
	uartString(teste); //Ler e envia valor do A/D
	//uartString("\r\n");       //Nova linha
}

