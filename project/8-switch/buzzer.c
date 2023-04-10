#include <msp430.h>AA
#include "libTimer.h"
#include "buzzer.h"
static int counterForSMTheme = 0, ocarina = 0, nothing = 0, something = 0;;

void buzzer_init()
{
    /* 
       Direct timer A output "TA0.1" to P2.6.  
        According to table 21 from data sheet:
          P2SEL2.6, P2SEL2.7, anmd P2SEL.7 must be zero
          P2SEL.6 must be 1
        Also: P2.6 direction must be output
    */
    timerAUpmode();		/* used to drive speaker */
    P2SEL2 &= ~(BIT6 | BIT7);
    P2SEL &= ~BIT7; 
    P2SEL |= BIT6;
    P2DIR = BIT6;		/* enable output to speaker (P2.6) */
   
}

void buzzer_set_period(short cycles) /* buzzer clock = 2MHz.  (period of 1k results in 2kHz tone) */
{
  CCR0 = cycles; 
  CCR1 = cycles >> 1;		/* one half cycle */
}

void delay_ms(unsigned int ms){
  while (ms){
    __delay_cycles(1000); //1000 for 1MHz and 16000 for 16MHz
    ms--;
	}
}


void ocarinaTheme(){
  switch(ocarina){
  case 0:
  case 1: buzzer_set_period(2959); ocarina++; break;
  case 2: buzzer_set_period(3134); ocarina++; break; 
  case 4: buzzer_set_period(3322); ocarina++; break; 
  case 3: buzzer_set_period(3520); ocarina++; break; 
  case 5: buzzer_set_period(2637); ocarina++; break; 
  case 6: buzzer_set_period(2489); ocarina = 0; break; 
  }
}

void nothingTheme(){
  switch(nothing){
  case 0:
  case 1: buzzer_set_period(1567); nothing++; break;
  case 2: buzzer_set_period(1661); nothing++; break; 
  case 4: buzzer_set_period(1567); nothing++; break; 
  case 3: buzzer_set_period(1769); nothing++; break; 
  case 5: buzzer_set_period(1864); nothing++; break; 
  case 6: buzzer_set_period(1396); nothing = 0; break;
  }
}

void somethingTheme(){
  switch(nothing){
  case 0:
  case 1: buzzer_set_period(2349); something++; break;
  case 2: buzzer_set_period(1108); something++; break; 
  case 4: buzzer_set_period(2217); something++; break; 
  case 3: buzzer_set_period(2046); something++; break; 
  case 5: buzzer_set_period(2093); something++; break; 
  case 6: buzzer_set_period(987); something = 0; break;
  }
}

void superMarioTheme(){
  switch(counterForSMTheme){
  case 0:
  case 1:
  case 2:
  case 4: buzzer_set_period(750); counterForSMTheme++; break; //E note
  case 3: buzzer_set_period(950); counterForSMTheme++; break; //C note
  case 5: buzzer_set_period(630); counterForSMTheme++; break; //G note
  case 6: buzzer_set_period(1260); counterForSMTheme = 0; break; //Lower G note
  }
}
