#include <msp430.h>
#include "led.h"
#include "machinaEstato.h"
#include "buzzer.h"
#include "switches.h"
#include "libTimer.h"

void main(){

  configureClocks();

  switch_init();
  buzzer_init();
  led_init();

  enableWDTInterrupts();

  or_sr(0x18);

}
