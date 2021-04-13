/* 
 * File:   Main.c
 * Author: Local Hero
 *
 * Created on 26 de marzo de 2018, 10:18
 */

#include "Config.h"
#include "Main.h"
#include "Func.h"



// Global variables
unsigned int Pot6[M];      // For storing ADC output
unsigned int Pot5[M];
unsigned int Pot4[M];
unsigned int posicion = 0;

//---------------------------------------------------------------------------
// ISR routine. ADC
//---------------------------------------------------------------------------
//void __attribute__((interrupt, auto_psv)) _ADCInterrupt(void)
//{
//	IFS0bits.ADIF = 0;          // Clean flag
//    Pot6[posicion] = ADCBUF6;   // Reading the ADC    
//    ADCON1bits.ADON = 1;        // turn ADC ON
//}
 void __attribute__((interrupt, auto_psv)) _T3Interrupt(void){
     
     IFS0bits.T3IF =  0;
     T3CONbits.TON = 0; 
     TMR3 = 0;
    while (!ADCON1bits.DONE);
    
    Pot6[posicion] = ADCBUF6;
    Pot5[posicion] = ADCBUF5;
    Pot4[posicion] = ADCBUF4;
    
    posicion++;
    if(posicion>M){
        posicion = 0;
    }
    T3CONbits.TON = 1; //Habilito el timer
 }

//---------------------------------------------------------------------------
// Main routine
//---------------------------------------------------------------------------

// Función principal. Siempre incluye un bucle infinito.

int main (void)
{ 
    //Parametros:
    float media = 0.0;
    unsigned int maxi = 0;
    unsigned int mini =0;
    
    // Initialize 
    InitIO();                    // Initialize I/O ports
    InitTMR3();                  // Initialize TMR3
    InitADC();                  // Initialize ADC
    ConfigInt();               // Configure interrupts 
    
    T3CONbits.TON = 1;         // Start TMR3
        
    while (1)   // bucle infinito
    {
        //Probar las fucniones relaizadas tarea 2, 3
        media = Avg(Pot4,M);
        maxi = Vmax(Pot6,M);
        mini = Vmin(Pot6,M);
        
        if (media>MITAD){
            LATDbits.LATD0 = 0; //encender los leds
            LATDbits.LATD1 = 0;
            LATDbits.LATD2 = 0;
            LATDbits.LATD3 = 0;
        }//IF
        else{
            LATDbits.LATD0 = 1; //Apagar los leds
            LATDbits.LATD1 = 1;
            LATDbits.LATD2 = 1;
            LATDbits.LATD3 = 1;
        }//Else
    }
    
    return 0;
    
}// Main
