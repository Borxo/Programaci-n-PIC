/*
 * Programa: Matriz de led imagen est�tica. 
 * Microcontrolador: PIC16F1936.
 * Autor: Borxo Garc�a.
 * Fecha: 07/07/2019.
 */

//Palabras de configuraci�n
// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = OFF      // MCLR Pin Function Select (MCLR/VPP pin function is digital input)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable (Brown-out Reset disabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = OFF       // Internal/External Switchover (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is disabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config PLLEN = ON       // PLL Enable (4x PLL enabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LVP = OFF        // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)

//Velocidad del oscilador interno//
#define _XTAL_FREQ 4000000

//Librerias//
#include <xc.h>

//Variables//
volatile int fila =0; 
volatile int i=0;
const unsigned int Simbolo[] = 
{   // B0,  B1,  B2,  B3,  B4
      0x19,0x16,0x0D,0x16,0x19, //Coraz�n.
};

void interrupt linea (void) //Interrupci�n para multiplexaci�n. 
{
    TMR2IF=0; //Borra el flag
    switch (fila)
    {
        case 0: 
            PORTB=0b11111110;
            PORTA=Simbolo[i];
            break;
        case 1: 
            PORTB=0b11111101;
            PORTA=Simbolo[i+1];
            break;
        case 2: 
            PORTB=0b11111011;
            PORTA=Simbolo[i+2];
            break;
        case 3: 
            PORTB=0b11110111;
            PORTA=Simbolo[i+3];
            break;
        case 4: 
            PORTB=0b11101111;
            PORTA=Simbolo[i+4];
            break;
     }if (++fila==5)fila=0; 
}

void main (void)
{   
    //Configuraci�n de los puertos//
    TRISA=0x00;                 //Configuraci�n Puerto A como salidas.
    TRISB=0x00;                 //Configuraci�n Puerto A como salidas.
    
    //Configuraci�n del Timer e interrupci�n//
    T2CON=0b01111110;           //Configuraci�n del Timer2 Preescaler 16, posescaler 16.
    PR2=198;                    //Valor del desbordamiento del Timer2.
    PEIE=1;TMR2IE=1;GIE=1;      //Habilitaci�n de la interrupci�n.
    
    //Oscilador//
    OSCCON=0b01101000;          //4Mhz
    
    while(1)
    {
        //No se utiliza ya que se procesa todo en la interrupci�n.
    }
}
