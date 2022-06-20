#ifndef ADC_H_
#define ADC_H_
#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define AREF 0 //Tensão de referência = Aref
#define AVCC 1 //Tensão de referência = Avcc
#define VR11 2 //Tensão de referência = 1,1 V
#define ADC0 0 //Seleciona ADC0
#define ADC1 1 //Seleciona ADC1
#define ADC2 2 //Seleciona ADC2
#define ADC3 3 //Seleciona ADC3
#define ADC4 4 //Seleciona ADC4
#define ADC5 5 //Seleciona ADC5
#define Vtemp 6 //Seleciona Sensor de temperatura
#define V11   7 //seleciona tensão de 1,1 V
#define Vgnd  8 //seleciona GND

void adcBegin(uint8_t ref, uint8_t did);//Inicializa o ADC
void adcChannel(uint8_t channel);       //Seleciona canal
void adcIntEn(uint8_t x);               //Habilita interrupção
void adcSample(void);                   //Inicia conversão
uint8_t  adcOk(void);                   //Verifica se conversão foi concluída
uint16_t adcReadOnly();                 //Ler ADC
uint16_t adcRead();                     //Converte, aguarda e ler ADC

#endif /* ADC_H_ */