#include <msp430.h>
#include "led.h"
#include "switches.h"
#include "buzzer.h"

unsigned char led_change = 0, green_on = 0, red_on = 0, led_state = 0;
static char redVal[] = {0, LED_RED}, greenval[] = {0, LED_GREEN};
char frequency;
static char ledFlags = 0;

void led_init(){
  P1DIR |= LEDS;
  led_change = 1;
  led_update();
}

void led_update(){
  if (led_change){
    ledFlags = 0;
    if (!(led_state)){
	ledFlags |= LED_RED;
    }
    else{
	ledFlags |= LED_GREEN;
    }

    P1OUT &= (0xff^LEDS) | ledFlags;
    P1OUT |= ledFlags;
    led_change = 0; 
  }
}

void led_toggle(){
  led_state = 1 - led_state;
  led_change = 1;
}

void led_advance(){
  led_state += 1;
  led_change = 1;
}
