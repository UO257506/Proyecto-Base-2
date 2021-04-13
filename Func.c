#include "Main.h"
#include "Func.h"

/* Este archivo contendrá la definición de las funciones auxiliares que se
 * necesiten para la ejecución del código.
 * Pueden añadirse tantas como se quiera.
 * El objetivo es encapsular lo máximo posible el código y reutilizar todas las+
 * funciones posibles.
 * En el archivo FUNC.H deberán incluirse los prototipos de estas funciones.
 */

// Ejemplo:
// FUNCIÓN PARA INICIALIZACIÓN DE PUERTOS E/S
// Parámetros de entrada: ninguno (void).
// Parámetros de salida: ninguno (void).
void InitIO()
{
	TRISB = 0xFFFF;     // Initialize AN6 as input                
    TRISD = 0xFFF0;     // LED outputs
    LATD = 0xFFF0;      // LED on
    return;
}// InitIO

//---------------------------------------------------------------------------
// InitTMR3
//---------------------------------------------------------------------------
void InitTMR3()
{   
    //Initialize Timer3 for 10ms period
    T3CON = 0;                    // Turn off Timer3 by clearing control register
	TMR3 = 0;                     // Start Timer1 at zero
	PR3 = (FCY/256)*0.01;         // Set period register value for 10 ms (100 Hz)
    T3CON = 0x0030;               // Configure Timer3 (timer off, continue in IDLE, not gated, 1:256 prescaler, internal clock)    
    return;
}

//---------------------------------------------------------------------------
// InitADC. ADC intial configuration
//---------------------------------------------------------------------------
void InitADC()
{   
    // ADCON1 CONFIGURATION
    ADCON1bits.ADON = 0;        // Initially, stopped.
    ADCON1bits.ADSIDL = 0;      // No IDLE
    ADCON1bits.FORM = 0b00;     // Output format = unsigned integer
    ADCON1bits.SSRC = 0b111;    // Source for triggering conversion = auto (111) con 010 disparo con TMR3
    ADCON1bits.ASAM = 1;        // Sampling after conversion ends

    // ADCON2 CONFIGURATION
    ADCON2bits.VCFG = 0b000;    // Vref+ = VDD, Vref- = VSS.
    ADCON2bits.SMPI = 0b1011;   // Interrupts after 12 conversion
    ADCON2bits.BUFM = 0;        // 16 words
    ADCON2bits.CSCNA = 1;
    ADCON2bits.ALTS = 0;
    ADCON2bits.BUFS = 0;
           
    // ADCON3 CONFIGURATION
    ADCON3bits.SAMC = 0b01111;   // 15·Tad 
    ADCON3bits.ADCS = 4;        // Clock Tad
    ADCON3bits.ADRC = 0;        // internal clock
    
    // ADCPCFG
    ADPCFG = 0xFFFF;	
    ADPCFGbits.PCFG6 = 0;       // AN6 as analog input
    ADPCFGbits.PCFG5 = 0;
    ADPCFGbits.PCFG4 = 0;
    
    
    // ADCSSL
    ADCSSL = 0x0000;
    ADCSSLbits.CSSL6 = 1;       // AN6 conversion
    ADCSSLbits.CSSL5 = 1;
    ADCSSLbits.CSSL4 = 1;
    ADCON1bits.ADON = 1;        // turn ADC ON
    return;
}

//---------------------------------------------------------------------------
// ConfigInt(). For configuring interrupts
//---------------------------------------------------------------------------
void ConfigInt()
{
    // Configuring the interrupts
    INTCON1bits.NSTDIS = 1;         // Disable nesting interrputs 
    /*
    IFS0bits.ADIF = 0;              // Clear ADC flag
    IEC0bits.ADIE = 1;              // Enable ADC mask
    IPC2bits.ADIP = 4;              // ADC priority level
     */ //Configuracion interrupcion TMR3
    
    IFS0bits.T3IF = 0;              // Clear ADC flag
    IEC0bits.T3IE = 1;              // Enable ADC mask
    IPC1bits.T3IP = 4;              // ADC priority level
    
    
    SET_CPU_IPL(3);                 // Set CPU priority level to a value below the lowest interrupt
    return;   
}

float Avg(unsigned int array[], unsigned int size){
    unsigned long suma = 0;
    unsigned int i = 0;
    for (i=0;i<size;i++){
        suma = suma + array[i];
    }
    return suma/(size);
}

float Vmin(unsigned int array[], unsigned int size){
    unsigned int min = 0;
    unsigned int i = 0;
    for (i=0;i<size;i++){
        if (min > array[i])
            min=array[i];
    }
    
    return min;
}

float Vmax (unsigned int array[], unsigned int size){
    unsigned int max = 0;
    unsigned int i = 0;
    for (i=0;i<size;i++){
        if (max < array[i])
            max=array[i];
    }
    
    return max;
}