#include <msp430.h>
#include "switches.h"
#include "led.h"
#include "machinaEstato.h"

char switch_down, period, switch_up;
//c8 - c7
int high_notes [] = {4186, 3951, 3729, 3520, 3322, 3134, 2959, 2798, 2637, 2489, 2349, 2217, 2093};
//b7 - b6
int low_notes [] = {1972, 1864, 1760, 1661, 1567, 1479, 1396, 1318, 1244, 1174, 1108, 1046, 987};

static char switch_update_interrupt_sense(){
  char p2val = P2IN;
  P2IES |= (p2val & SWITCHES);
  P2IES &= (p2val | ~SWITCHES);
  return p2val;
}

void switch_init(){
  P2REN |= SWITCHES;
  P2IE |= SWITCHES;
  P2OUT |= SWITCHES;
  P2DIR &= ~SWITCHES;
  switch_update_interrupt_sense();
  switch_interrupt_handler();
  led_update();
}


void switch_interrupt_handler(){

  char p2val = switch_update_interrupt_sense();
  char button_1 = (p2val & SW1) ? 0 : SW1;
  char button_2 = (p2val & SW2) ? 0 : SW2;
  char button_3 = (p2val & SW3) ? 0 : SW3;
  char button_4 = (p2val & SW4) ? 0 : SW4;

  if(button_1){
    led_state = 0;
    led_change = 1;
    
    ocarinaTheme();
    
    led_advance();
    led_update();
    switch_down = 1; 
  }
  
  if(button_2){
    led_state = 0;
    led_change = 1;

    nothingTheme();
    
    led_advance();
    led_update();
    switch_down = 1;
  }
  
  if(button_3){
    led_state = 0;
    led_change = 1;
    led_advance();
    led_update();
    switch_down = 1;
  }
  
  if(button_4){
    led_state = 0;
    superMarioTheme();
    led_change = 1;
    led_advance();
    led_update();
    switch_down = 1;
  }

}
