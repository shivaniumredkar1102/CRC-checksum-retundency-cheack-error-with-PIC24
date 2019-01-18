#define FCY 8000000UL
// PIC24FJ128GA106 Configuration Bit Settings

// 'C' source line config statements

// CONFIG3
#pragma config POSCMOD = XT             // Primary Oscillator Select (XT Oscillator mode selected)
#pragma config OSCIOFNC = OFF           // Primary Oscillator Output Function (OSC2/CLKO/RC15 functions as CLKO (FOSC/2))
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor (Clock switching and Fail-Safe Clock Monitor are disabled)
#pragma config FNOSC = PRI              // Oscillator Select (Primary Oscillator (XT, HS, EC))
#pragma config IESO = ON                // Internal External Switch Over Mode (IESO mode (Two-Speed Start-up) enabled)

// CONFIG1
#pragma config WDTPS = PS32768          // Watchdog Timer Postscaler (1:32,768)
#pragma config FWPSA = PR128            // WDT Prescaler (Prescaler ratio of 1:128)
#pragma config WINDIS = OFF             // Watchdog Timer Window (Windowed Watchdog Timer enabled; FWDTEN must be 1)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config ICS = PGx2               // Comm Channel Select (Emulator/debugger uses EMUC2/EMUD2)
#pragma config GWRP = OFF               // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF                // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF             // JTAG Port Enable (JTAG port is disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
            // JTAG Port Enable (JTAG port is disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdio.h>
#include <p24FJ128GA010.h>
#include <libpic30.h>
#include <string.h>

// define configurable LCD pins 
#define RS_PIN LATBbits.LATB15 // RB15 --> RS
#define E_PIN LATDbits.LATD4  // RD4 --> E 
#define RW_PIN LATDbits.LATD5 //RD5 --> RW
#define D0_PIN LATEbits.LATE0 
#define D1_PIN LATEbits.LATE1
#define D2_PIN LATEbits.LATE2
#define D3_PIN LATEbits.LATE3
#define D4_PIN LATEbits.LATE4 // RE4 --> D4
#define D5_PIN LATEbits.LATE5 // RE5 --> D5
#define D6_PIN LATEbits.LATE6 // RE6 --> D6
#define D7_PIN LATEbits.LATE7 // RE7 --> D7

// Give direction to bits
#define RS_TRIS TRISBbits.TRISB15
#define E_TRIS  TRISDbits.TRISD4
#define RW_TRIS TRISDbits.TRISD5
#define D0_TRIS TRISEbits.TRISE0
#define D1_TRIS TRISEbits.TRISE1
#define D2_TRIS TRISEbits.TRISE2
#define D3_TRIS TRISEbits.TRISE3
#define D4_TRIS TRISEbits.TRISE4
#define D5_TRIS TRISEbits.TRISE5
#define D6_TRIS TRISEbits.TRISE6
#define D7_TRIS TRISEbits.TRISE7

#include "lcd.h"   // import lcd library
#define _XTAL_FREQ 16000000UL
#define poly     0x1021
char text[1000];
unsigned short good_crc;
unsigned short text_length;


void crc_compute(void)
{
    unsigned short ch,i;
    good_crc = 0xffff;
    i = 0;
    text_length = 0;
    
    while((ch=text[i])!=0)
    {
        update_good_crc(ch);
        i++;
        text_length++;
    }
    augment_message_for_good_crc(); 
}

void update_good_crc(unsigned short ch)
{
    unsigned short i,v,xor_flag;
    v = 0x80;
    for(i=0;i<8;i++)
    {
        if(good_crc&0x8000)
        {
          
            xor_flag = 1;
        }
        else
        {
            xor_flag = 0;
        }
        
        good_crc = good_crc << 1;
        
        
        if(ch & v)
        {
            good_crc = good_crc+1;
           
        }
        if(xor_flag)
        {
            
            good_crc = good_crc^poly;
           
        }
        
        v = v >> 1;
    }
     
}

void augment_message_for_good_crc()
{
    unsigned short i,xor_flag;
    for(i=0;i<16;i++)
    {
        if(good_crc&0x8000)
        {
            xor_flag = 1;
        }
        else
        {
            xor_flag = 0;
        }
        good_crc = good_crc << 1;
        if(xor_flag)
        {
            good_crc = good_crc^poly;
        }
       
        
    }
}

void main()
{
    unsigned char buffer[20];
    TRISB = 0;
    RS_TRIS = 0;
    E_TRIS=0;
    RW_TRIS = 0;
    D0_TRIS = 0;
    D1_TRIS = 0;
    D2_TRIS = 0;
    D3_TRIS = 0;
    D4_TRIS=0;
    D5_TRIS=0;
    D6_TRIS=0;
    D7_TRIS=0;
    
    E_PIN = 0;
    RS_PIN = 0;
    RW_PIN = 0;
    
    __delay_ms(100);
    lcd_init();
    __delay_ms(100);
    lcd_cmd();
    __delay_ms(10);
    lcd_print("Hello World :)");
    __delay_ms(100);
    sprintf(text,"%s","AH=SDG&FV=41434&SO=VODA&IM=000000000000000&LT=00000000000&LO=00000000000&DLT=1&DLO=0&BV=0744&DV=1262&SRS=1&ET=05&DT=20180526154419&EBAC=1&DGAC=0&SS=0&FF=000000&GF=0&FR=0000&CB=00000&CR=00000&CY=00000&CT=00000&PFA=0000&PFB=0000&PFY=0000&PFR=0000&VAB=000000&VAR=000000&VAY=000000&VB=000000&VR=000000&VY=000000&WB=000000&WH=000000&WR=000000&WT=000000&WY=000000&AV=1404&SM=0&ES=000000&OP=000000&OT=000000&COT=000000&COL=000000&FL=000000&ALART=00");
    crc_compute();
    __delay_ms(100);
    
    lcd_clr();
    __delay_ms(100);
    sprintf(buffer,"%04X",good_crc);
    lcd_print(buffer);
    __delay_ms(1000);
    lcd_clr();
    __delay_ms(100);
    sprintf(buffer,"%d",text_length);
    lcd_print(buffer);
    
    while(1);

    
}