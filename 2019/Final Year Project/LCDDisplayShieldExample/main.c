#include <msp430g2553.h>
#include "LCDDisplay.h"

char cursorState = 0;

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop WDT
    BCSCTL1 = CALBC1_1MHZ; // Set DCO to 1MHz
    DCOCTL = CALDCO_1MHZ; // Set DCO to 1MHz
    
    P1DIR |= (BIT0);              // P1.2 to output
    P1OUT &= ~(BIT0);              // Set the LEDs P1.0 and P1.6 to on
    
    LCDConfigure();
    LCDBackLight(500);
    
    LCDHome();
    LCDWriteString("Use the keys to");
    LCDSetLocation(1,0);
    LCDWriteString("move the cursor");

    
    while(1)
    {
        // Service Switch Presses
        if (pressRelease1)
        {
            switch (pressRelease1) {
                case SW2:
                    LCDHome();
                    LCDWriteString("S0");
                    break;
            }
            pressRelease1 = 0;
        }
        
        if (pressRelease2) {
            switch (pressRelease2) {
                case LEFT:
                    LCDBack();
                    break;
                case DOWN:
                    LCDDown();
                    break;
                case RIGHT:
                    LCDForward();
                    break;
                case UP:
                    LCDUp();
                    break;
                case SELECT:
                    cursorState = (cursorState+1) % 4;   // Increment state and wrap if exceeds total number of states
                    switch (cursorState) {
                        case 0:
                            LCDBlinkOff();
                            break;
                        case 1:
                            LCDCursorOn();
                            break;
                        case 2:
                            LCDBlinkOn();
                            break;
                        case 3:
                            LCDCursorOff();
                            break;
                    }
                    break;
            }
            pressRelease2 = 0;
        }
    }
}
