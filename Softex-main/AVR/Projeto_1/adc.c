#include "adc.h"

//---------------------------------------------------------------------------
//Configura o conversor ADC do ATmega328
//ref = 0. Utilizar tensão de referência Aref
//ref = 1. Utilizar tensão de referência Avcc
//ref = 2. Utilizar tensão de referência interna de 1,1 V
//did: valor para o registrador DIDR0
//---------------------------------------------------------------------------
void adcBegin(uint8_t ref, uint8_t did)
{ ADCSRA = 0;   //configuração inicial
  ADCSRB = 0;   //configuração inicial
  DIDR0  = did; //configura DIDR0
  if (ref == 0)
  {	 ADMUX &= ~((1<<REFS1) | (1<<REFS0));//Aref
  }
  if ((ref == 1) || (ref > 2))
  { ADMUX &= ~(1<<REFS1); //Avcc
    ADMUX |=  (1<<REFS0); //Avcc
  }
  if (ref == 2)
  { ADMUX |= (1<<REFS1) | (1<<REFS0);  //Tensão interna de ref (1.1V)
  }
  ADMUX &= ~(1<<ADLAR); //Alinhamento a direita
  ADCSRA |= (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);//habilita AD. Prescaler de 128 (clk_AD = F_CPU/128)
}

//---------------------------------------------------------------------------
//Seleciona canal do ADC
//0 <= channel <= 5 - Leitura dos pinos AD0 a AD5
//channel = 6 - Leitura do sensor de temperatura
//channel = 7 - 1,1V
//channel > 7 - GND
//---------------------------------------------------------------------------
void adcChannel(uint8_t channel)
{ if (channel <= 5)//seleciona um canal no multiplex
    ADMUX = (ADMUX & 0xF0) | channel; 
  if (channel == 6)//seleciona sensor interno de temperatura
    ADMUX = (ADMUX & 0xF0) | 0x08; 
  if (channel == 7)//seleciona 1,1 V
    ADMUX = (ADMUX & 0xF0) | 0x0E; 
  if (channel > 7)//seleciona GND
    ADMUX = (ADMUX & 0xF0) | 0x0F; 
}

//---------------------------------------------------------------------------
//Habilita ou desabilita interrupção do ADC
//Se x = 0, desabilita interrupção
//Caso contrário, habilita interrupção
//---------------------------------------------------------------------------
void adcIntEn(uint8_t x)
{ if (x)
    ADCSRA |= (1<<ADIE);//habilita interrupção do ADC    
  else
    ADCSRA &= ~(1<<ADIE);//Desabilita interrupção do ADC  
}

//---------------------------------------------------------------------------
//Inicia conversão
//---------------------------------------------------------------------------
void adcSample(void)
{ ADCSRA |= (1<<ADSC);//Inicia conversão
}

//---------------------------------------------------------------------------
//Verifica se conversão foi concluída
//Retorna valor 0 se conversão concluída. 64 se não.
//---------------------------------------------------------------------------
uint8_t adcOk(void)
{ return (ADCSRA & (1<<ADSC));
}

//---------------------------------------------------------------------------
//Ler o ADC e retorna o valor lido do ADC
//---------------------------------------------------------------------------
uint16_t adcReadOnly()
{ return (ADCL | (ADCH<<8));//retorna o valor do ADC 
}

//---------------------------------------------------------------------------
//Converte, aguarda, ler e retorna valor lido do ADC
//---------------------------------------------------------------------------
uint16_t adcRead()
{ adcSample();         //Inicia conversão
  while(adcOk());      //Aguarda fim da conversão (ADSC = 0)
  return adcReadOnly();//retorna o valor do ADC
}