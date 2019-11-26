#include "ADC_Header_File.h"
#include <pic18f4550.h>

void ADC_Init() {
    TRISA = 0xff; //CONFIGURA TODAS AS PORTAS A COMO ENTRADA
    ADCON1 = 0x0e; //CONFIGURA O BIT TENSÃO DE REFERÊNCIA E SELECIONA QUAIS PORTAS SERÃO ANALÓGICAS
    ADCON2 = 0x92; //justificado a direita, 4Tad e Fosc/32.
    ADRESH = 0; //LIMPA O REGISTRADOR ADC
    ADRESL = 0;
}

int ADC_Read(int channel) {
    int digital;
    ADCON0 = (ADCON0 & 0b11000011) | ((channel << 2) & 0b00111100); //SELECIONA A PORTA A SER UTILIZADA
    ADCON0 |= ((1 << ADON) | (1 << GO)); //ATIVA A CONVERSÃO
    while (ADCON0bits.GO_nDONE == 1); //ESPERA O FIM DA CONVERSÃO
    digital = (ADRESH * 256) | (ADRESL); //COMBINA OS BITS DOS REGISTRADOR ADC
    return (digital); //RETORNA O VALOR LIDO
}