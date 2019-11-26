#include "USART_Header_File.h"
#include <pic18f4550.h>
#define F_CPU 8000000/64

void USART_Init(int baud_rate) {
    float temp;
    TRISC6 = 0; //CONFIGURA O PINO C6 COMO SAIDA (TX)
    TRISC7 = 1; //CONFIGURA O PINO C7 COMO ENTRADA (RX)
    temp = (((float) (F_CPU) / (float) baud_rate) - 1); //CALCULA O VALOR DO BAUD RATE
    SPBRG = (int) temp; /*baud rate=9600 SPBRG=(F_CPU /(64*9600))-1*/
    TXSTA = 0x20; //ATIVA TX
    RCSTA = 0x90; //ATIVA RX
    INTCONbits.GIE = 1; //ATIVA INTERRUPÇÃO GLOBAL
    INTCONbits.PEIE = 1; //ATIVA INTERRUPÇÃO DE PERIFÉRICOS
    PIE1bits.RCIE = 1; //ATIVA INTERRUPÇÃO RX
}

void USART_TxChar(char out) {
    while (TXIF == 0); 
    TXREG = out; 
}

void USART_SendString(const char *out) {
    while (*out != '\0') {
        USART_TxChar(*out);
        out++;
    }
}