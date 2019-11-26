#include "EEPROM_Header_File.h"
#include <pic18f4550.h>

void EEPROM_Write(int address,char data)
{
    /*Write Operation*/
    EEADR=address;               //ESCREVE O ENDERE�O NO REGISTRADOR EEADR
    EEDATA=data;                 //ESCREVE O CARACTER NO REGISTRADOR EEDATA
    EECON1bits.EEPGD=0;          //SELECIONA O ACESSO NA EEPROM
    EECON1bits.CFGS=0;           //ACESSA A EEPROM
    EECON1bits.WREN=1;           //CONFIGURA A ESCRITA NA MEM�RIA
    INTCONbits.GIE=0;            //DESATIVA INTERRUP��ES GLOBAIS
    
    //OS DOIS PR�XIMOS COMANDOS S�O NECESS�RIOS PARA ESCREVER NA EEPROM(EXEMPLO 6-2 NA P�GINA 84 DO DATASHEET)
    EECON2=0x55;
    EECON2=0xaa;
    
    EECON1bits.WR=1;             //INICIA A ESCRITA NA EEPROM
    INTCONbits.GIE=1;            //ATIVA INTERRUP��ES
    
    while(PIR2bits.EEIF==0);     //ESPERA A ESCRITA TERMINAR
 
    PIR2bits.EEIF=0;             //LIMPA O EEIF(NECESS�RIO LIMPAR VIA SOFTWARE)
    
}

void EEPROM_WriteString(int address,char *data)
{
    while(*data!=0)
    {
        EEPROM_Write(address,*data);
        address++;
        *data++;
    }    
}

char EEPROM_Read(int address)
{
    /*Read operation*/
    EEADR=address;               //LOCALIZA��O DA LEITURA
    EECON1bits.WREN=0;           //NECESS�RIO LIMPAR PARA LEITURA
    EECON1bits.EEPGD=0;          //ACESSA A EEPROM
    EECON1bits.RD=1;             //INICIA A LEITURA DA EEPROM
    return(EEDATA);             //RETORNA O VALOR ESCRITO NO REGISTRADOR EEDATA
}