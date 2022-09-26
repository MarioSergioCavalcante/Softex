#define F_CPU 8000000UL
#include <avr/io.h>

#include "adc.h"
#include "uart.h"
#include <stdio.h>
int main(void)
{	uartBegin(9600, F_CPU); //Inicializa UART
	adcBegin(AVCC, 0x01);   //Inicializa A/D
    adcChannel(ADC0);       //Seleciona canal
	//Aguarda a recep��o do primeiro comando, configurando o tempo de amostragem do sinal
	while (!uartRxOk());

	if (uartRxOk())     //verifica se existe novo dado
	{ 
		uint8_t t = uartRx();//armazena dado
		if(t == '1'){
				OCR0A = 78; //A cada 0,01 s gera uma interrup��o
		}else{
			if(t == '2'){
					OCR0A = 2*78; //A cada 0,01 s gera uma interrup��o
			}
		}
	
	
	}
	
	adcIntEn(1);            //Interrup��o do A/D
    uartIntRx(1);           //Interrup��o da uart
	PORTD |= (1 << PD6); // Configura o pino PD6 como sa�da
	//Configura o �nicio da contagem para que aconte�am as interrup��es a cada segundo programado.
	TCCR0A = ( 1 << COM0A0) | (1 << WGM01); //OC0A troca de estado Pino de controle para teste do tempo de amostragem, retirar o bit COM no real
	TCCR0B = (1 << CS02) | (1 << CS02);  //Configura o Prescaler de 1024
	TIMSK0 = (1 << OCIE0A); //Habilita a interrup��o de compara��o com o valor do OCR0A
	sei();                  //Interrup��o geral
	while (1);
}

//Tratamendo da interrup��o de recep��o de dados
ISR(TIMER0_COMPA_vect)
{ 
	 // uartString("Aconteceu!\n");
	   adcSample();      //Inicia convers�o  
}

//Tratamendo da interrup��o do A/D
ISR(ADC_vect)
{ //uartString("Valor: ");    //Envia string
	//float valor = adcReadOnly()*5.0/1024;
	char teste[100];
    uint16_t valor = ((float) 5/1024)*(adcReadOnly()+1)*100;
	sprintf(teste, "Valor Convertido: %d\r\n", valor);
	uartString(teste); //Ler e envia valor do A/D
	//uartString("\r\n");       //Nova linha
}

