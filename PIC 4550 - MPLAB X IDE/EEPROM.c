#include "EEPROM_Header_File.h"
#include <pic18f4550.h>

void EEPROM_Write(int address,char data)
{
    /*Write Operation*/
    EEADR=address;               //ESCREVE O ENDEREÇO NO REGISTRADOR EEADR
    EEDATA=data;                 //ESCREVE O CARACTER NO REGISTRADOR EEDATA
    EECON1bits.EEPGD=0;          //SELECIONA O ACESSO NA EEPROM
    EECON1bits.CFGS=0;           //ACESSA A EEPROM
    EECON1bits.WREN=1;           //CONFIGURA A ESCRITA NA MEMÓRIA
    INTCONbits.GIE=0;            //DESATIVA INTERRUPÇÕES GLOBAIS
    
    //OS DOIS PRÓXIMOS COMANDOS SÃO NECESSÁRIOS PARA ESCREVER NA EEPROM(EXEMPLO 6-2 NA PÁGINA 84 DO DATASHEET)
    EECON2=0x55;
    EECON2=0xaa;
    
    EECON1bits.WR=1;             //INICIA A ESCRITA NA EEPROM
    INTCONbits.GIE=1;            //ATIVA INTERRUPÇÕES
    
    while(PIR2bits.EEIF==0);     //ESPERA A ESCRITA TERMINAR
 
    PIR2bits.EEIF=0;             //LIMPA O EEIF(NECESSÁRIO LIMPAR VIA SOFTWARE)
    
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
    EEADR=address;               //LOCALIZAÇÃO DA LEITURA
    EECON1bits.WREN=0;           //NECESSÁRIO LIMPAR PARA LEITURA
    EECON1bits.EEPGD=0;          //ACESSA A EEPROM
    EECON1bits.RD=1;             //INICIA A LEITURA DA EEPROM
    return(EEDATA);             //RETORNA O VALOR ESCRITO NO REGISTRADOR EEDATA
}