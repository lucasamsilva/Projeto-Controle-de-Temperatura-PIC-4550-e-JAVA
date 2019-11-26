
#include "LCD_16x2_8-bit_Header_File.h"


void LCD_Init()
{
   	TRISB = 0x00;          
    TRISD = 0x00;          
    MSdelay(15);
	LCD_Command(0x38);     
    LCD_Command(0x0c);     
    LCD_Command(0x06);     
	LCD_Command(0x01);     
	MSdelay(2);	
}

void LCD_Clear()
{
    	LCD_Command(0x01);     /*clear display screen*/
        MSdelay(2);
}

void LCD_Command(char cmd )
{
	ldata= cmd;               
	RS = 0;                
	EN = 1;                 
	MSdelay(1);
	EN = 0;
}

void LCD_Char(char dat)
{
	ldata= dat;            
	RS = 1;                
	EN=1;                  
	MSdelay(1);
	EN=0;
}


void LCD_String(const char *msg)
{
	while((*msg)!=0)
	{		
	  LCD_Char(*msg);
	  msg++;	
    }
		
}

void LCD_String_xy(char row,char pos,const char *msg)
{
    char location=0;
    if(row<=1)
    {
        location=(0x80) | ((pos) & 0x0f);     
        LCD_Command(location);
    }
    else
    {
        location=(0xC0) | ((pos) & 0x0f);      
        LCD_Command(location);    
    }  
    

    LCD_String(msg);

}

void MSdelay(unsigned int val)
{
     unsigned int i,j;
        for(i=0;i<=val;i++)
            for(j=0;j<81;j++);      
 }


