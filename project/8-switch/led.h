#include <msp430.h>

#ifndef led_included
#define led_included

#define LED_RED BIT0
#define LED_GREEN BIT6
#define LEDS (BIT0 | BIT6)

void led_init();
void led_update();

extern unsigned char led_change, green_led_state, red_led_state, green_on, red_on, led_state;
void led_switch();
void led_advance();

#endif
