#include <pic18f4550.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "Configuration_Header_File.h"
#include "ADC_Header_File.h"
#include "USART_Header_File.h"
#include "LCD_16x2_8-bit_Header_File.h"
#include "EEPROM_Header_File.h"

#define _XTAL_FREQ 8000000
int power = 1;
int ligado = 0;
int liberado = 0;
int TempIdealInt = 24; //TEMPERATURA DESEJADA
int TempExtAtiv = 25; //TEMPERATURA EXTERNA MÍNIMA PARA LIBERAR A REFRIGERAÇÃO
float TempInternaAtual; //VALOR DA TEMPERATURA INTERNA ATUAL
float TempExternaAtual; //VALOR DA TEMPERATURA EXTERNA ATUAL
char TempInterna[10]; //STRING DA TEMPERATURA INTERNA
char TempExterna[10]; //STRING DA TEMPERATURA EXTERNA
char TempExteAtivacao[10]; //STRING DA TEMPERATURA MINIMA EXTERNA
char TempInternaIdeal[10]; //STRING DA TEMPERATURA INTERNA DESEJADA

void carregaTempIdeal();
void carregaTempExterna();
void TempExternaMinima();
void compTemp();
void letemp();
void mandatempextativ();
void mandatempideal();
void mandatempint();
void mandatempext();
void setatempinterna();
void setatempexterna();
void escreveLCD();
void checaext();
__interrupt() void ISR(void);

void main() {
    OSCCON = 0x72;
    MSdelay(10);
    LCD_Init();
    ADC_Init();
    carregaTempExterna();
    carregaTempIdeal();
    MSdelay(30);
    TRISAbits.TRISA2 = 0;
    TRISAbits.TRISA4 = 0;
    TRISAbits.TRISA5 = 0;
    USART_Init(9600);
    while (1) {
        letemp();
        TempExternaMinima();
        compTemp();
        escreveLCD();
    }
}

__interrupt(high_priority) void ISR1(void) {
    if (RCIF) {
        while (RCIF == 0);
        char res = RCREG;
        if (res == 'I') {
            setatempinterna();
        }
        if (res == 'E') {
            setatempexterna();
        }
        if (res == 'R') {
            mandatempint();
        }
        if (res == 'F') {
            mandatempext();
        }
        if (res == 'L') {
            mandatempideal();
        }
        if (res == 'T'){
            mandatempextativ();
        }
    }
}

void setatempexterna() {
    char valor[3];
    PIE1bits.RCIE = 0;
    while (!TXIF);
    while (RCIF == 0);
    valor[0] = RCREG;
    while (!TXIF);
    while (RCIF == 0);
    valor[1] = RCREG;
    valor[2] = '\0';
    EEPROM_WriteString(0, valor);
    TempExtAtiv = atoi(valor);
    PIE1bits.RCIE = 1;
}

void setatempinterna() {
    char valor[3];
    PIE1bits.RCIE = 0;
    while (!TXIF);
    while (RCIF == 0);
    valor[0] = RCREG;
    while (!TXIF);
    while (RCIF == 0);
    valor[1] = RCREG;
    valor[2] = '\0';
    EEPROM_WriteString(6, valor);
    TempIdealInt = atoi(valor);
    PIE1bits.RCIE = 1;
}

void mandatempint() {
    USART_SendString(TempInterna);
}

void mandatempext() {
    USART_SendString(TempExterna);
}

void mandatempextativ(){
    USART_SendString(TempExteAtivacao);
}

void mandatempideal(){
    USART_SendString(TempInternaIdeal);
}

void escreveLCD() {
    LCD_Clear();
    sprintf(TempInterna, "%.2f ", (float) TempInternaAtual, 0xdf);
    sprintf(TempExterna, "%.2f", (float) TempExternaAtual, 0xdf);
    LCD_String_xy(1, 0, "Temp.Exte.:"); 
    LCD_String_xy(1, 11, TempExterna);
    LCD_String_xy(1, 15, "C");
    LCD_String_xy(2, 0, "Temp.Inte.:"); 
    LCD_String_xy(2, 11, TempInterna);
    LCD_String_xy(2, 15, "C");
    for (int i = 0; i < 5; i++) {
        MSdelay(1000);
    }
    LCD_Clear();
    sprintf(TempExteAtivacao, "%d", (int) TempExtAtiv, 0xdf);
    sprintf(TempInternaIdeal, "%d", (int) TempIdealInt, 0xdf);
    LCD_String_xy(1, 0, "Temp.Ativ.:"); 
    LCD_String_xy(1, 11, TempExteAtivacao);
    LCD_String_xy(1, 13, "C");
    LCD_String_xy(2, 0, "Temp.Ideal:"); 
    LCD_String_xy(2, 11, TempInternaIdeal);
    LCD_String_xy(2, 13, "C");
    for (int i = 0; i < 5; i++) {
        MSdelay(1000);
    }
}

void letemp() {
    TempInternaAtual = (ADC_Read(1)*4.88);
    TempInternaAtual = (TempInternaAtual / 10.00);
    TempExternaAtual = (ADC_Read(3)*4.88);
    TempExternaAtual = (TempExternaAtual / 10.00);
}

void compTemp() {
    if (TempInternaAtual > (TempIdealInt + 0.5) && liberado) {
        ligado = 1;
        PORTAbits.RA2 = ligado;
    } else if (TempInternaAtual < (TempIdealInt - 0.5) || !liberado) {
        ligado = 0;
        PORTAbits.RA2 = ligado;
    }
}

void TempExternaMinima() {
    if (TempExternaAtual > TempExtAtiv) {
        liberado = 1;
        PORTAbits.RA4 = !liberado;
        PORTAbits.RA5 = liberado;
    } else {
        liberado = 0;
        PORTAbits.RA4 = !liberado;
        PORTAbits.RA5 = liberado;
    }
}

void carregaTempExterna() {
    char externa[3];
    for (int i = 0; i < 2; i++) {
        externa[i] = EEPROM_Read(i);
    }
    externa[2] = '\0';
    TempExtAtiv = atoi(externa);
}

void carregaTempIdeal() {
    char ideal[3];
    int adress = 6;
    for (int i = 0; i < 2; i++) {
        ideal[i] = EEPROM_Read(adress);
        adress++;
    }
    ideal[2] = '\0';
    TempIdealInt = atoi(ideal);
}