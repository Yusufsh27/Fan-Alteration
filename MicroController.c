Microcontroller code:
//****************************************************************************
//Filename:		FanMiniProject.c
//Author:		Yusuf Shaikh
//Date:  		9-21-16
//Version:		1.0
//Device:		16f18324
//Description:	Blink an LED using a time wasting loop 5Hz
//Complier:		XC8
//
//****************************************************************************
//****************************************************************************
// Configuration
// Window -> PIC Memory Views -> Configuration Bits
//****************************************************************************
// CONFIG1
#pragma config FEXTOSC = OFF    // FEXTOSC External Oscillator mode Selection bits->Oscillator not enabled
#pragma config RSTOSC = HFINT1    // Power-up default value for COSC bits->HFINTOSC
#pragma config CLKOUTEN = OFF    // Clock Out Enable bit->CLKOUT function is disabled; I/O or oscillator function on OSC2
#pragma config CSWEN = ON    // Clock Switch Enable bit->Writing to NOSC and NDIV is allowed
#pragma config FCMEN = ON    // Fail-Safe Clock Monitor Enable->Fail-Safe Clock Monitor is enabled

// CONFIG2
#pragma config MCLRE = ON    // Master Clear Enable bit->MCLR/VPP pin function is MCLR; Weak pull-up enabled
#pragma config PWRTE = OFF    // Power-up Timer Enable bit->PWRT disabled
#pragma config WDTE = OFF    // Watchdog Timer Enable bits->WDT disabled; SWDTEN is ignored
#pragma config LPBOREN = OFF    // Low-power BOR enable bit->ULPBOR disabled
#pragma config BOREN = ON    // Brown-out Reset Enable bits->Brown-out Reset enabled, SBOREN bit ignored
#pragma config BORV = LOW    // Brown-out Reset Voltage selection bit->Brown-out voltage (Vbor) set to 2.45V
#pragma config PPS1WAY = ON    // PPSLOCK bit One-Way Set Enable bit->The PPSLOCK bit can be cleared and set only once; PPS registers remain locked after one clear/set cycle
#pragma config STVREN = ON    // Stack Overflow/Underflow Reset Enable bit->Stack Overflow or Underflow will cause a Reset
#pragma config DEBUG = OFF    // Debugger enable bit->Background debugger disabled

// CONFIG3
#pragma config WRT = OFF    // User NVM self-write protection bits->Write protection off
#pragma config LVP = ON    // Low Voltage Programming Enable bit->Low Voltage programming enabled. MCLR/VPP pin function is MCLR. MCLRE configuration bit is ignored.

// CONFIG4
#pragma config CP = OFF    // User NVM Program Memory Code Protection bit->User NVM code protection disabled
#pragma config CPD = OFF    // Data NVM Memory Code Protection bit->Data NVM code protection disabled

//****************************************************************************
// Includes
//****************************************************************************
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

//****************************************************************************
// Defines
//****************************************************************************
#define _XTAL_FREQ  4000000

//****************************************************************************
// Global Variables
//****************************************************************************
uint16_t count = 0;
int Burst = 0;                         // Enable Change PWM Mode
uint16_t DigitalValue = 255;

 void interrupt my_isr(void)
 { 
     if(TMR0IE && TMR0IE)
     {
            TMR0IF = 0; //clear flag
            DigitalValue = ADRESH;
            ADGO = 1; 
		    Burst = 1;
		    return;
     } 
            
 }
void main(void)
{     
    OSCCON1 = 0x60; // HFINTOSC   
    OSCFRQ = 0x03;  // HFFRQ 4_MHz;
    TRISC = 0b11111111; // Disable Output Drivers
    RC5PPS = 0b00010; // PWM5 on RC5
    PPSLOCK = 1;
    TMR0H = 156;
    
    T0CON0 = 0b10000000;
    T0CON1 = 0b01011010;
   
    ADCON0 = 0b00000111;
    ADCON1 = 0b01010000;
    
    PWM5CON = 0;
    PR2 = 0b11111111;
    TMR2ON = 1;
    PWM5DCH = 0;
    PWM5DCL = 0;
    PWM5CON = 0b10000000;
    TRISC5 = 0;
    
    TMR0IE = 1;
    PEIE = 1;
    GIE = 1;
    
    ADGO = 1;
    
    while (1)
    {
		if (Burst == 1)                    // if flag is enabled
		{
				if (DigitalValue < 41)
					PWM5DCH = 41;
				else if (DigitalValue < 51) 
					PWM5DCH = 53.75;
				else if (DigitalValue < 63)
					PWM5DCH = 66.5;
				else if (DigitalValue < 75)
					PWM5DCH = 79.25;
				else if (DigitalValue < 88)
					 PWM5DCH = 92;
				else if (DigitalValue < 100)
					PWM5DCH = 104.75;
				else if (DigitalValue < 112)
					PWM5DCH = 117.5;
				else if (DigitalValue < 124)
					PWM5DCH = 130.25;
				else if (DigitalValue < 137)
					PWM5DCH = 143;
				else if (DigitalValue < 149)
					PWM5DCH = 155.75;
				else if (DigitalValue < 161) 
					PWM5DCH = 168.5;
				else if (DigitalValue < 173)
					PWM5DCH = 181.25;
				else if (DigitalValue < 186)
					PWM5DCH = 194;
				else if (DigitalValue < 198)
					PWM5DCH = 206.75;
				else if (DigitalValue < 210)
					PWM5DCH = 219.5;
                else if (DigitalValue < 222) 
					PWM5DCH = 232.25;
                else if (DigitalValue < 235)
					PWM5DCH = 245; // Possibly Change
				else
					PWM5DCH = 255;
        }
        else
        {
            PWM5DCH = 255; //Full burst mode
            __delay_ms(3000);
            Burst = 1;
        }
			 	                     //Then leave burst mode
    }
}
