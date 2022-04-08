// avr-libc library includes
#include <avr/io.h> //  can be omitted
#include <avr/interrupt.h> // can be omitted
#define LEDPIN 13
/* or use
DDRB = DDRB | B00100000;  // this sets pin 5  as output                       // without changing the value of the other
                         // pins 
*/
void setup()
{
pinMode(LEDPIN, OUTPUT);

// initialize Timer1
cli();         // disable global interrupts
TCCR1A = 0;    // set entire TCCR1A register to 0
TCCR1B = 0;    // set entire TCCR1A register to 0

// enable Timer1 overflow interrupt:
TIMSK1 |= (1 << TOIE1);
// Preload with value 3036
//use 64886 for 100Hz
//use 64286 for 50 Hz
//use 34286 for 2 Hz
TCNT1=0x0BDC;
// Set CS10 bit so timer runs at clock speed: (no prescaling)
TCCR1B |= (1 << CS12); // Sets bit CS12 in TCCR1B
// This is achieved by shifting binary 1 (0b00000001)
// to the left by CS12 bits. This is then bitwise
// OR-ed into the current value of TCCR1B, which effectively set
// this one bit high. Similar: TCCR1B |= _BV(CS12);
//  or: TCCR1B= 0x04;

// enable global interrupts:
sei();
}

ISR(TIMER1_OVF_vect)
{
digitalWrite(LEDPIN, !digitalRead(LEDPIN));
TCNT1=0x0BDC; // reload the timer preload
}

void loop() {}

CTC

But there’s another mode of operation for AVR timers. This mode is called Clear Timer on Compare Match, or CTC. Instead of counting until an overflow occurs, the timer compares its count to a value that was previously stored in a register. When the count matches that value, the timer can either set a flag or trigger an interrupt, just like the overflow case.

To use CTC, you need to figure out how many counts you need to get to a one second interval. Assuming we keep the 1024 prescaler as before, we’ll calculate as follows:

(target time) = (timer resolution) * (# timer counts + 1)

and rearrange to get

 

(# timer counts + 1) = (target time) / (timer resolution)
(# timer counts + 1) = (1 s) / (6.4e-5 s)
(# timer counts + 1) = 15625
(# timer counts) = 15625 - 1 = 15624

You have to add the extra +1 to the number of timer counts because in CTC mode, when the timer matches the desired count it will reset itself to zero. This takes one clock cycle to perform, so that needs to be factored into the calculations. In many cases, one timer tick isn’t a huge deal, but if you have a time-critical application it can make all the difference in the world.

Now the setup() function to configure the timer for these settings is as follows:

void setup()
{

pinMode(LEDPIN, OUTPUT); // you have to define the LEDPIN as say 13
                         // or so earllier in yr program
// initialize Timer1
cli();          // disable global interrupts
TCCR1A = 0;     // set entire TCCR1A register to 0
TCCR1B = 0;     // same for TCCR1B

// set compare match register to desired timer count:
OCR1A = 15624;

// turn on CTC mode:
TCCR1B |= (1 << WGM12);

// Set CS10 and CS12 bits for 1024 prescaler:
TCCR1B |= (1 << CS10);
TCCR1B |= (1 << CS12);

// enable timer compare interrupt:
TIMSK1 |= (1 << OCIE1A);
sei();          // enable global interrupts
}

And you need to replace the overflow ISR with a compare match version:

 

ISR(TIMER1_COMPA_vect)
{
digitalWrite(LEDPIN, !digitalRead(LEDPIN));
}

The LED will now blink on and off at precisely one second intervals. And you are free to do anything you want in loop(). As long as you don’t change the timer settings, it won’t interfere with the interrupts. With different mode and prescaler settings, there’s no limit to how you use timers.

Here’s the complete example in case you’d like to use it as a starting point for your own project.

// Arduino timer CTC interrupt example
//
// avr-libc library includes
#include <avr/io.h>
#include <avr/interrupt.h>
#define LEDPIN 13
void setup()
{
pinMode(LEDPIN, OUTPUT);
// initialize Timer1
cli();          // disable global interrupts
TCCR1A = 0;     // set entire TCCR1A register to 0
TCCR1B = 0;     // same for TCCR1B

// set compare match register to desired timer count:
OCR1A = 15624;

// turn on CTC mode:
TCCR1B |= (1 << WGM12);

// Set CS10 and CS12 bits for 1024 prescaler:
TCCR1B |= (1 << CS10);
TCCR1B |= (1 << CS12);

// enable timer compare interrupt:
TIMSK1 |= (1 << OCIE1A);

// enable global interrupts:
sei();
}

void loop()
{
// main program
}

ISR(TIMER1_COMPA_vect)
{
digitalWrite(LEDPIN, !digitalRead(LEDPIN));
}

Remember that you can use the built-in ISRs to extend timer functionality. For example, if you wanted to read a sensor every 10 seconds, there’s no timer set-up that can go this long without overflowing. However, you can use the ISR to increment a counter variable in your program once per second, then read the sensor when the variable hits 10. Using the same CTC setup as in our previous example, the ISR would look something like this:

 

ISR(TIMER1_COMPA_vect)
{
seconds++;
if(seconds == 10)
{
seconds = 0;
readSensor();
}
}

For a variable to be modified within an ISR, it is good custom to declare it as volatile. In this case, you need to declare volatile byte seconds; or similar at the start of the program.
A word on the Atmega8

The Atmega8 seems to give people problems with use of the timers, one reason is that it doesn’t have a TIMSK1 register (in fact it doesnt have a TIMSKn register), it does have a TIMSK register though that is shared amongst the 3 timers. As I do not have an Atmega8 (like the early Arduino NG) I can not test it, but if you encounter problems, the following programs will help:

// this code sets up counter0 with interrupts enabled on an Atmega8
// beware, it may generate  errors in Arduino IDE 
// as 'milis' uses timer0 
#include <avr/io.h>
#include <avr/io.h>

void setup()
{
DDRD &= ~(1 << DDD4); // Clear the PD4 pin
// PD0 is now an input

PORTD |= (1 << PORTD4); // turn On the Pull-up
// PD4 is now an input with pull-up enabled

TIMSK |= (1 << TOIE0); // enable timer interrupt

TCCR0 |= (1 << CS02) | (1 << CS01) | (1 << CS00);
// Turn on the counter, Clock on Rise

sei();
}
void loop()
{
// Stuff
}


ISR (TIMER0_OVF_vect)
{
// interrupt just fired, do stuff
}

A 1 sec flasher using the timer 1 CTC mode for the Atmega 8 would look like this:

 

void setup()
{     
pinMode(13,OUTPUT);
/* or use:
DDRB = DDRB | B00100000;  // this sets pin 5  as output
                       // without changing the value of the other pins 
*/
// Disable interrupts while loading registers
cli();
// Set the registers
TCCR1A = 0; //Timer Counter Control register
// Set mode
TCCR1B = (1 << WGM12); // turn on CTC mode
// Set prescale values (1024). (Could be done in same statement
// as setting the WGM12 bit.)
TCCR1B |= (1 << CS12) | (1 << CS10);
//Enable timer compare interrupt===> TIMSK1 for ATmega328, 
//TIMSK for ATmega8
TIMSK |= (1 << OCIE1A);
// Set OCR1A
OCR1A = 15624;
// Enable global interrupts
sei();
}
void loop(){}
ISR (TIMER1_COMPA_vect) {
   digitalWrite(13, !digitalRead(13));
   //PORTB ^= _BV(PB5); // as digitalWrite(13,x) is an Arduino 
   //function, direct writing to the port may be preferable
}

It is obvious that this is very akin to the CTC program presented earlier for the Atmega328 and in fact will work on the Atmega238 as well by renaming ‘TIMSK’ to ‘TIMSK1’

Other Atmega chips:

TCCR0 should be TCCR0A in ATmega164P/324P/644

Attiny

The Attiny series has timer interrupts too. This code sets up a 50uS timer in CTC mode on the Attiny85 (pag 79 datasheet)

TCCR0A = (1 << WGM01);   //CTC mode. set WGM01
TCCR0B = (2 << CS00);    //divide by 8  sets 
OCR0A = F_CPU/8 * 0.000050 - 1;    // 50us compare value
TIMSK |= (1<<OCIE0A);              //set interrupt

ISR(TIMER0_COMPA_vect)
{
                                   // code of choice!
}

More on timers here

here

here

here

here

here

here

 

pwm generation by timers

here (Atmega8)

Atmega8 Datasheet

Atmega328 Datasheet
Share this:

    TwitterFacebook11EmailGoogle

Related

Arduino hardware interruptWith 2 comments

Flashing an LED with Attiny13: Timer, Watchdog timer and SleepIn "Attiny"

Timer Interrupts re-visitedIn "Arduino"
Post navigation
Arduino hardware interrupt
Program an ATtiny with an Arduino Nano
79 thoughts on “Timer interrupts”

    Beyaz
    December 29, 2012 at 09:08

    Best explanation of internal timers. Very clear. Thank you very much
    Reply
        Arduino
        September 14, 2014 at 22:05

        My pleasure, I expanded it a bit
        Reply
    Pingback: Utilizando interrupção interna ou por tempo no Arduino | daltonhioki
    Pingback: #2 – Touché meets Pd and Max/MSP « Stefano Trento
    Pingback: #2 – Touché meets Pd and Max/MSP |
    carloschsa
    April 16, 2013 at 00:03

    I appreciate your work. Thanks
    Reply
        Arduino
        June 20, 2013 at 20:39

        Thank you
        Reply
    Pingback: lucadentella.it – Allegro A4988 e Arduino (3)
    comcomAude
    June 12, 2013 at 02:38

    Thx you very much, this help a lot !
    Reply
        Arduino
        June 20, 2013 at 20:29

        Great
        Reply
    Tuyen
    June 20, 2013 at 16:23

    thank you, it’s very usefull,but i think lib should be set:
    #include
    #include
    Reply
    Tuyen
    June 20, 2013 at 16:25

    #include
    #include
    Reply
        Arduino
        September 14, 2014 at 22:27

        Ha Tuyen, sorry for my late reactio, Indeed the comment section of wordpress is not really suitable for code. The includes are: avr/io.h and avr/interrupt.h, both between ‘fishhooks’
        Reply
    Eduardo
    June 29, 2013 at 03:19

    hi guys,

    i had a problem with this code using a Atmega8

    “Interrupt.cpp: In function ‘void setup()’:
    Interrupt.pde:-1: error: ‘TIMSK1’ was not declared in this scope”

    i look on the datasheet and this register has the name TIMSK without “1” but it isn’t works…….someone can help me? thans
    Reply
        Arduino
        August 30, 2013 at 08:34

        I did not specifically have the atmega8 in mind but you could try altering the name
        Reply
        Arduino
        September 14, 2014 at 22:25

        it is over a year that i replied you and looking back at my reply i may have been a bit too hasty and not addressed things well. You seem not to be the only one who is having trouble with TIMSK1 and the Atmega8.
        It may not help you anymore but maybe someone else wuith the same problem is helped by this code:
        in case the includes drop in the code due to wordpress peculiarities:
        they read avr/io.h and avr/interrupt.h, both between ‘fishhooks’
        // this code sets up counter0 and with interrupts enabled
        #include
        #include

        int main(void)
        {
        DDRD &= ~(1 << DDD4); // Clear the PD4 pin
        // PD0 is now an input

        PORTD |= (1 << PORTD4); // turn On the Pull-up
        // PD4 is now an input with pull-up enabled

        TIMSK |= (1 << TOIE0); // enable timer interrupt

        TCCR0 |= (1 << CS02) | (1 << CS01) | (1 << CS00);
        // Turn on the counter, Clock on Rise

        sei();

        while (1)
        {
        // we can read the value of TCNT0 hurray !!
        }
        }

        ISR (TIMER0_OVF_vect)
        {
        // interrupt just fired
        }
        Reply
    Pingback: “Необычное” поведение режима CTC таймера1 | MyLinks
    chuck
    August 20, 2013 at 05:28

    Just wanted to drop you a line to say thanks for the best explanation I have found on the timer/interrupt features. Nice work.
    Saved me a lot of time rather than digging through the depths of the 448 page data sheet.
    Reply
        Arduino
        August 27, 2013 at 19:41

        Thank you
        Reply
    Jan Kromhout
    August 26, 2013 at 21:27

    Great for this, have had a lot of fun to understanding this toppic together with a scoop!
    Reply
        Arduino
        August 27, 2013 at 19:41

        Thank you 🙂
        Reply
    davinci
    October 4, 2013 at 22:47

    Thanks, by far best explanation I’ve encountered!
    Reply
        Arduino
        October 8, 2013 at 22:55

        Thank you
        Reply
    fanzeyi
    March 23, 2014 at 19:56

    Thank you so much! This helps me a lot!
    Reply
        Arduino
        March 23, 2014 at 21:23

        My pleasure
        Reply
    zenmonkey760
    May 21, 2014 at 05:06

    Your explanation has propelled my understanding of timer interrupts like no other piece I’ve read. Thank you so much!
    Reply
        Arduino
        May 21, 2014 at 05:33

        My pleasurw
        Reply
    The Dark Knight
    August 17, 2014 at 12:16

    Amazing work!It saved a lot of time.The data sheet is just too long!
    Reply
        Arduino
        August 18, 2014 at 19:52

        Thanks , my pleasure, glad you liked it
        Reply
    iforce2d
    September 12, 2014 at 18:13

    Wow, a very nice explanation, thankyou!
    Reply
        Arduino
        September 12, 2014 at 19:41

        My pleasure
        Reply
        Arduino
        September 14, 2014 at 22:28

        I have in fact expanded it a bit today
        Reply
    nerdant
    October 14, 2014 at 04:36

    Great article!
    In the section “Timer prescaling and preloading”, I believe there is an line of code missing in your code snippet.

    In the “ISR(TIMER1_OVF_vect)” function you must re-load the TCNT1 register with your preset value. So this line should be added:
    TCNT1=0x0BDC;

    This article here: http://www.hobbytronics.co.uk/arduino-timer-interrupts
    helped me out.
    Reply
        Arduino
        October 15, 2014 at 06:38

        Thanks.
        I have checked my original code simply by running it -without that extra line- and it works fine, exactly as it should work.
        I know the link you provide, as I even provide it at the end of my article :-). Since the link doesn’t give any explanation, I guess they just made a mistake by adding that line. It seems a bit counter-intuitive to have to redefine a parameter.
        Anyway, thanks for your observation and comment 🙂 Always good to see how others do something.
        Reply
            pridy
            September 15, 2016 at 23:34

            Hello,
            one question in generel for setting the counter value:

            The TCNT1 register (filled with 0x0BDC) is a 16 Bit register, right?
            Can we just write it like mentioned above with “TCNT1 = 0x0BDC”?
            Because the datasheet for 2560 says that there is a special procedure required to write to those 16 Bit registers. Or is this covered by IDE optimization?

            Great article though!
            Arduino
            September 16, 2016 at 14:11

            Pridy, thanks for your kind words. It has always worked for me. I am not sure to what special procedure you refer for the 2560. Could that be the description on I think paragraph 17.3? I never bothered with that as as far as I know that is only necessary if you would do direct assembler programming. I have always presumed the IDE compiler took care of that
        Robert
        March 20, 2015 at 11:30

        Yes it solvs my problem, thanks.
        R
        Reply
    les
    October 18, 2014 at 07:39

    this is one of the most informative articles I hav ever encountered! thanx a million! but im stil having some kind of a problem., I cant differentiate between the timer interrupt configuration that cannot interfere with functions like millis (), analogwrite () ,etc. and the ones that can safely be used without worrying about those timer dependent functions! can you help me out please! thank you in advance for your respons!
    Reply
        Arduino
        October 18, 2014 at 18:15

        Les, thanks. I am on mobile so I will be brief for now, most timers are used for some function, but timer 0 is the one that is used most by the system. Timer1 is safe u less u use the servo library and timer2 is safe unless u use the tone function
        Reply
    Stan
    February 11, 2015 at 21:53

    Hello!
    Thank you so much for this! Searched for hours before I found this.

    I have a question though. Can a timer be started at a different time in program than setup()?
    I see you state that setting CS bits starts it, but is there a way to start it and stop it eventually or will it go on forever?
    Reply
        Arduino
        February 19, 2015 at 01:16

        I am getting a bit worried. I left a reply, but it seems not to have been posted. anyway there are several ways to stop teh timer. One can do it by clearing the interupt or by resetting the CS10, 11 and 12 buts in the control register: TCCRxB &= ~(_BV(CS10) | _BV(CS11) | _BV(CS12));
        Reply
    Spencer
    April 8, 2015 at 02:37

    Thank you so much, because of this article I feel I am very close to being able to complete my project. However I am having an issue getting your example to work. I have tried to use the snippet for using a variable to increment and count many seconds (ultimately I need to count minutes), but it doesn’t seem to be working. Here is the code which supposedly checks the timer, it compiles but does not ever blink the LED. Thank you in advance for any insights!

    ISR(TIMER1_COMPA_vect)
    {
    int seconds;
    seconds++;
    if (seconds == 2) {
    seconds = 0;
    // execute code here
    digitalWrite( 13, digitalRead( 13 ) ^ 1 );
    }
    }
    Reply
        Arduino
        April 22, 2015 at 16:39

        seems you are xor-ing th eLED but not sure if you do it right.
        Try : digitalWrite(13, !digitalRead(13));
        Reply
            spencerjroberts
            April 23, 2015 at 04:49

            Thanks for the reply! I figured it out: I just had to make the “seconds” variable a global variable.
            Arduino
            April 23, 2015 at 23:36

            OK thanks for the feedback 🙂
            I am happy you got it working
    haris
    April 26, 2015 at 13:58

    Great article,
    sir,
    i want to read encoders value precisely from robot’s wheel using mega328 timers to trace path of my automatic guided vehicle, how can i do it ? where should i start this job?
    my encoders gives smooth square wave,
    need help,
    kindly explain
    Reply
        Arduino
        April 27, 2015 at 19:35

        You can use the output of your decoders to generate a hardware interrupt on INT0 or INT1 (pin D2, D3 /physical pin 4 or 5)
        That ill let you keep track of the number of rotations and thus the driven distance. However I think you need a bit more to also know the direction. As I do not know what decoders you have, I am not sure if they also indicate change of direction
        Reply
            haris
            April 28, 2015 at 17:37

            To the first i have 2 disk type encoders with 36 holes on each of them which interrupt IR beam from trnsmtr to rcvr on rotation and gives 36 pulses ,

            2nd, yes u r right, i hv to detect direction of my bot, i m thinking to connect 2 wires from H-bridge to digital input of arduino , HIGH or LOW digital input will tell status of direction of my bot.

            my teacher gave me task of counting using timers,cuz interrupt is disturbing controller countinously while running other task

            can i connect sqr wave coming from encoders to timer pin of arduino as external clock by setting CS10,CS11,CS12 bit to 1 ? if yes how ?
            and then run CTC mode for counting
    Zohaib
    May 16, 2015 at 19:58

    I have written a code for one second delay to blink led using Atmega 2560,timers.I want to get 5sec delay .how can i get this by using this code…
    Here is my code:

    #include
    #include
    #define LEDPIN 13
    #define LEDPINn 12
    int seconds=0;

    void setup()
    {

    pinMode(LEDPIN, OUTPUT);

    // initialize Timer1
    noInterrupts();
    TCCR1A = 0; // set entire TCCR1A register to 0
    TCCR1B = 0; // same for TCCR1B

    // set compare match register to desired timer count:
    OCR1A = 156.24;//10ms delay
    // turn on CTC mode:
    TCCR1B |= (1 << WGM12);
    // Set CS10 and CS12 bits for 1024 prescaler:
    TCCR1B |= (1 << CS10);
    TCCR1B |= (1 << CS12);
    // enable timer compare interrupt:
    TIMSK1 |= (1 << OCIE1A);
    // enable global interrupts:
    interrupts();
    pinMode(LEDPINn,OUTPUT);
    noInterrupts();
    TCCR3A=0;
    TCCR3B=0;

    OCR3A=15624;//100 msec delay
    TCCR3B |= (1 << CS30);
    TCCR3B |= (1 << CS32);
    TIMSK3 |= (1 << OCIE3B);
    interrupts();

    }

    void loop()
    {
    // do some crazy stuff while my LED keeps blinking
    }
    ISR(TIMER1_COMPA_vect)
    {

    digitalWrite(LEDPIN, !digitalRead(LEDPIN));

    }

    ISR(TIMER3_COMPA_vect)
    {
    digitalWrite(LEDPIN, !digitalRead(LEDPIN));
    }
    Reply
        Arduino
        May 16, 2015 at 22:13

        That is not so hard and in fact I describe it in the article. Keep a counter in your interrupt routine, increasing the counter with 1 every time the interrupt is called. Then when it comes to 5 you clear the counter and toggle the LED.

        ISR(TIMER1_COMPA_vect)
        {
        seconds++;
        if(seconds == 5)
        {
        seconds = 0;
        digitalWrite(LEDPIN, !digitalRead(LEDPIN));
        }
        }

        ofcourse you have to declare your variable in the setup.
        Reply
    Pingback: Studies On Criticality No. 1 – first steps | studio algorhythmics
    Ver
    August 29, 2015 at 03:29

    Very informative!Thank you so much.
    Reply
        Arduino
        August 30, 2015 at 00:31

        i am glad you liked it
        Reply
    Jeff
    October 20, 2015 at 17:06

    ARDUINO SKETCH TO SLOWLY DIM LIGHT BULB (part 1)

    #include

    /*
    Dim_PSSR_ZC_Tail

    This sketch is a sample sketch using the ZeroCross Tail(ZCT)to generate a sync
    pulse to drive a PowerSSR Tail(PSSRT) for dimming ac lights.

    Connections to an Arduino Duemilanove:
    1. Connect the C terminal of the ZeroCross Tail to digital pin 2 with a 10K ohm pull up to Arduino 5V.
    2. Connect the E terminal of the ZeroCross Tail to Arduino Gnd.
    3. Connect the PowerSSR Tail +in terminal to digital pin 4 and the -in terminal to Gnd.

    */

    #include

    volatile int i=0; // Variable to use as a counter
    volatile boolean zero_cross=0; // Boolean to store a “switch” to tell us if we have crossed zero
    int PSSR1 = 4; // PowerSSR Tail connected to digital pin 4
    int dim = 32; // Default dimming level (0-128) 0 = on, 128 = off
    int freqStep = 60; // Set to 60hz mains
    int LED = 0; // LED on Arduino board on digital pin 13

    void setup()
    {
    pinMode(LED, OUTPUT);
    pinMode(4, OUTPUT); // Set SSR1 pin as output
    attachInterrupt(0, zero_cross_detect, RISING); // Attach an Interupt to digital pin 2 (interupt 0),
    Timer1.initialize(freqStep);
    Timer1.attachInterrupt(dim_check,freqStep);
    }

    void loop() // Main loop
    {
    dim = 0;
    delay(500);
    dim = 1;
    delay(500);
    dim = 2;
    delay(500);
    dim = 3;
    delay(500);
    dim = 4;
    delay(500);
    dim = 5;
    delay(500);
    dim = 6;
    delay(500);
    dim = 7;
    delay(500);
    dim = 8;
    delay(500);
    dim = 9;
    delay(500);
    dim = 10;
    delay(500);
    dim = 11;
    delay(500);
    dim = 12;
    delay(500);
    dim = 13;
    delay(500);
    dim = 14;
    delay(500);
    dim = 15;
    delay(500);
    dim = 16;
    delay(500);
    dim = 17;
    delay(500);
    dim = 18;
    delay(500);
    dim = 19;
    delay(500);
    dim = 20;
    delay(500);
    dim = 21;
    delay(500);
    dim = 22;
    delay(500);
    dim = 23;
    delay(500);
    dim = 24;
    delay(500);
    dim = 25;
    delay(500);
    dim = 26;
    delay(500);
    dim = 27;
    delay(500);
    dim = 28;
    delay(500);
    dim = 29;
    delay(500);
    dim = 30;
    delay(500);
    dim = 31;
    delay(500);
    dim = 32;
    delay(500);
    dim = 33;
    delay(500);
    dim = 34;
    delay(500);
    dim = 35;
    delay(500);
    dim = 36;
    delay(500);
    dim = 37;
    delay(500);
    dim = 38;
    delay(500);
    dim = 39;
    delay(500);
    dim = 40;
    delay(500);
    dim = 41;
    delay(500);
    dim = 42;
    delay(500);
    dim = 43;
    delay(500);
    dim = 44;
    delay(500);
    dim = 45;
    delay(500);
    dim = 46;
    delay(500);
    dim = 47;
    delay(500);
    dim = 48;
    delay(500);
    dim = 49;
    delay(500);
    dim = 50;
    delay(500);
    dim = 51;
    delay(500);
    dim = 52;
    delay(500);
    dim = 53;
    delay(500);
    dim = 54;
    delay(500);
    dim = 55;
    delay(500);
    dim = 56;
    delay(500);
    dim = 57;
    delay(500);
    dim = 58;
    delay(500);
    dim = 59;
    delay(500);
    dim = 60;
    delay(500);
    dim = 61;
    delay(500);
    dim = 62;
    delay(500);
    dim = 63;
    delay(500);
    dim = 64;
    delay(500);
    dim = 65;
    delay(500);
    dim = 66;
    delay(500);
    dim = 67;
    delay(500);
    dim = 68;
    delay(500);
    dim = 69;
    delay(500);
    dim = 70;
    delay(500);
    dim = 71;
    delay(500);
    dim = 72;
    delay(500);
    dim = 73;
    delay(500);
    dim = 74;
    delay(500);
    dim = 75;
    delay(500);
    dim = 76;
    delay(500);
    dim = 77;
    delay(500);
    dim = 78;
    delay(500);
    dim = 79;
    delay(500);
    dim = 80;
    delay(500);
    dim = 81;
    delay(500);
    dim = 82;
    delay(500);
    dim = 83;
    delay(500);
    dim = 84;
    delay(500);
    dim = 85;
    delay(500);
    dim = 86;
    delay(500);
    dim = 87;
    delay(500);
    dim = 88;
    delay(500);
    dim = 89;
    delay(500);
    dim = 90;
    delay(500);
    dim = 91;
    delay(500);
    dim = 92;
    delay(500);
    dim = 93;
    delay(500);
    dim = 94;
    delay(500);
    dim = 95;
    delay(500);
    dim = 96;
    delay(500);
    dim = 97;
    delay(500);
    dim = 98;
    delay(500);
    dim = 99;
    delay(500);
    dim = 100;
    delay(500);
    dim = 101;
    delay(500);
    dim = 102;
    delay(500);
    dim = 103;
    delay(500);
    dim = 104;
    delay(500);
    dim = 105;
    delay(500);
    dim = 106;
    delay(500);
    dim = 107;
    delay(500);
    dim = 108;
    delay(500);
    dim = 109;
    delay(500);
    dim = 110;
    delay(500);
    dim = 111;
    delay(500);
    dim = 112;
    delay(500);
    dim = 113;
    delay(500);
    dim = 114;
    delay(500);
    dim = 115;
    delay(500);
    dim = 116;
    delay(500);
    dim = 117;
    delay(500);
    dim = 118;
    delay(500);
    dim = 119;
    delay(500);
    dim = 120;
    delay(500);
    dim = 121;
    delay(500);
    dim = 122;
    delay(500);
    dim = 123;
    delay(500);
    dim = 124;
    delay(500);
    dim = 125;
    delay(500);
    dim = 126;
    delay(500);
    dim = 127;
    delay(500);
    dim = 128;
    delay(500);
    }

    // Functions

    void dim_check() { // This function will fire the triac at the proper time
    if(zero_cross == 1) { // First check to make sure the zero-cross has happened else do nothing
    if(i>=dim) {
    delayMicroseconds(100); //These values will fire the PSSR Tail.
    digitalWrite(PSSR1, HIGH);
    delayMicroseconds(50);
    digitalWrite(PSSR1, LOW);
    i = 0; // Reset the accumulator
    zero_cross = 0; // Reset the zero_cross so it may be turned on again at the next zero_cross_detect
    } else {
    i++; // If the dimming value has not been reached, increment the counter
    } // End dim check
    } // End zero_cross check
    }

    void zero_cross_detect()
    {
    zero_cross = 1;
    // set the boolean to true to tell our dimming function that a zero cross has occured
    }
    Reply
    Jeff
    October 20, 2015 at 17:07

    ARDUINO SKETCH TO SLOWLY DIM LIGHT BULB (part 2)
    Hello and thanks for this great resource. I’m an arduino newb and am currently struggling with trying to make a light bulb dim very slowly (full brightness to totally off) as smoothly as I possibly can, ideally over the coarse of say 2-5 minutes.

    At this point my hardware is behaving as advertised and it’s a matter of modifying the original sample sketch I was provided by the seller of the hardware solution I’m using (ZeroCross Tail & PowerSSR Tail with an Arduino Duemilanove Atmega 328).

    Modifying the parameters I was given in the original sketch the way I have has led me to a roadblock (SEE SKETCH in “part 1” comment above). I’m sure there’s a more elegant way to accomplish what I have –
    too many individual lines of code with the “dim” and “delay” going incremental for all 128 steps. Regardless, this code is working with the hardware to dim the bulb but the steps (128 steps @ 500ms each) still seem too apparent visually, especially toward the tail end of the fade to darkness and more importantly the overall time the fade takes happens too quickly.

    So now the problem is how can I add more steps in the dimming process (more than the 128 in the sample sketch I started with) as well as have the delay arguments less than 500ms?

    I was told in order to get a smoother longer seamless transition from light to dark I would need to modify the timer settings. Any advice or a direction you can point me in to better focus my time to find a solution would be GREATLY appreciated?
    Reply
        Arduino
        October 21, 2015 at 14:31

        Jeff your code is indeed a bit inefficient. For one thing why would you want to have more than 128 steps? the 128 steps regulate from ON to OFF. Do you really want to divide that into say 256 levels? the difference between those steps will be small. Sure it is possible, but let me handle the 500ms question first.
        as you can see in yr code, there is a delay of 500ms between each step. If you want that to be less you have to alter that to say 200, or 100, whatever you like.
        Now obviously you dont want to do that 128 times, especially not if you may want to chose another delay later. I am not sure if you wrote/changed that part of the code, but this is exactly the sort of thing that asks for a FOR NEXT loop.
        I am not sure how you ended up at my ‘timer interrupt’ post as I have a post that exactly deals with AC dimming: https://arduinodiy.wordpress.com/2012/10/19/dimmer-arduino/ and gives you programs how to do this. Basically you have to replace tour entire ‘void loop()’ by the following:

        void loop() {
        for (int i=5; i <= 128; i++)
        {
        dimming=i;
        delay(10);
        }
        }
        That will take care of it.

        Now with regard to your number of steps: I suggest you first change yr code as I just instructed, before you start messing with the steps. For now let me say that I spot an error in your code. Change the line
        “int freqStep = 60; // Set to 60hz mains”
        into
        “int freqStep = 65; // Set to 60hz mains” the 65 is not your grid frequency it is yr steplength for 128 steps for 60Hz. as it is equal to 8333/128 So if it is 60 you already have 138 steps. If you want more steps you have to lower the number ‘freqStep.
        let me explain.
        I presume your board uses a double phase rectification of the grid frequency for its Zerocrossing pulse. That means that there will be a 120Hz signal after the rectification.
        120Hz is equal to a period of 8333 uSec. Meaning that you have 8333uSec to do your phase cutting your dimming level depends on when in that cycle you do your phase cutting. If you take steps of 60uS you have 139 steps in that cycle. If you take steps of 65 usecs you have 128 steps (128×65=8333).
        So suppose you want 1000 steps, yr frequency step needs to be 8.333. This ofcourse would be a totally impractical number of steps but it is possible
        Reply
            Jeff
            November 1, 2015 at 22:26

            First off I apologize for my delay in replying to your advice (two kids, etc.). Thank you sooooo much! Your knowledge and willingness to share has helped me reach the desired result I was after!

            You wrote:
            “So suppose you want 1000 steps, yr frequency step needs to be 8.333. This of course would be a totally impractical number of steps but it is possible”

            Turns out my desired result was impractical. I used the freqStep = 8.333 and played with the delay and got my lightbulb dimming super smoothly over the course of the desired minutes I needed for my intent.

            Would you have any advice on how to incorporate a physical momentary switch that could trigger one single cycle of the minutes long fade to black I currently have programmed with the first push of the button “Push A”, then have the arduino sit and wait (in darkness) for a second push of the button “Push B” that would reverse my dimming sequence resulting in the same minutes long sequence only this time fading the lamp up from darkness to full brightness? (Additionally, a third push of the button would trigger the result of “Push A”, a fourth push “Push B”, and so on).
            __________________________________________
            CURRENT SKETCH BELOW:
            __________________________________________
            #include

            volatile int i=0; // Variable to use as a counter
            volatile boolean zero_cross=0; // Boolean to store a “switch” to tell us if we have crossed zero
            int PSSR1 = 4; // PowerSSR Tail connected to digital pin 4
            int dim = 32; // Default dimming level (0-128) 0 = on, 128 = off
            int freqStep = 8.333; // Set to 60hz mains
            int LED = 0; // LED on Arduino board on digital pin 13

            void setup()
            {
            pinMode(LED, OUTPUT);
            pinMode(4, OUTPUT); // Set SSR1 pin as output
            attachInterrupt(0, zero_cross_detect, RISING); // Attach an Interupt to digital pin 2 (interupt 0),
            Timer1.initialize(freqStep);
            Timer1.attachInterrupt(dim_check,freqStep);
            }

            void loop() // Main loop
            {
            for (int i=5; i =dim) {
            delayMicroseconds(100); //These values will fire the PSSR Tail.
            digitalWrite(PSSR1, HIGH);
            delayMicroseconds(50);
            digitalWrite(PSSR1, LOW);
            i = 0; // Reset the accumulator
            zero_cross = 0; // Reset the zero_cross so it may be turned on again at the next zero_cross_detect
            } else {
            i++; // If the dimming value has not been reached, increment the counter
            } // End dim check
            } // End zero_cross check
            }

            void zero_cross_detect()
            {
            zero_cross = 1;
            // set the boolean to true to tell our dimming function that a zero cross has occured
            }
            Arduino
            November 1, 2015 at 22:59

            I am happy I helped you get to grasp with the regulation. Do i understand that you want 1 button that takes different actions, depending on how many times or how long it is pushed?
            Check this program HoldButton.It gives you several possibilities depending on how long or how often the button is pressed.

            I would advise to put the program in a seperate procedure and call that procedure from yr main loop. you can then set the required functin in each of the sections
    Jeff
    November 3, 2015 at 08:00

    I followed your advice and put the contents of my main loop into it’s own function named:
    dim2dark_cycle()

    Now my sketch’s main loop calls dim2dark_cycle() after it reads the state of the pushbutton value and sees that it has been pressed. All is working well here so thank you for that!

    Can you suggest how I would write a second function, i.e. dim2light_cycle()
    for fading the lamp from total darkness to full brightness?

    Unfortunately your ‘for loop’ code that I am using for dimming the lamp from full brightness to darkness is confusing for me when I try to figure out how to recode it to make another ‘for loop’ to allow the lamp to fade back up to full brightness.

    Thanks in advance.
    Reply
        Arduino
        November 3, 2015 at 10:20

        you would make that the same way. The push button gives you several options depending on how long pressed, in one of those options you would then write yr for next loop something like:
        for (byte i==128;i >=0;i–)
        {
        dimming=i;
        }
        Now I didnt check this in the ide so there might be some errors in it and I am not sure what variable names you already have used, but this is the general direction u need to go
        Reply
    Peter Müller
    January 5, 2016 at 01:28

    The Timer prescaling and preloading example doesn’t work because TCNT1 is set to 0 after every overflow. TCNT1 is a counter, it can not save a start value.
    You could reset TCNT1 in the interrupt. However, doing so could lead to an unprecise timer.
    Reply
        Arduino
        January 6, 2016 at 02:23

        thanks, it has been awhile but I seem to remember I tried all with the exception of the Atmega8 example.
        As a matter of fact I just tried the programs again and they work.
        The fact that the timer is going back to 0 on overflow is the very essence of the timer, but what happens is that it triggers an interrupt in which i do the action that i need the timer for.
        I dont need to reset the timer in the interrupt as I just use what it is meant for: to generate an interrupt
        Reply
            Peter Müller
            January 7, 2016 at 01:30

            If you preload the timer with 60000, it will count to 65535 and overflow.
            After that, the timer will go back to 0 and again count to 65535, which will take much longer.
            Arduino
            January 7, 2016 at 18:06

            Ah OK, now I understand what you mean, yes timer should be ‘reloaded’. I thought I did, but will check the code as wordpress isnt the friendliest in publishing code. Thanks
            Arduino
            January 9, 2016 at 13:26

            It seems indeed that the specific line disappeared. Unnerving as now I have to go recheck all the program code in my blog, though in this case a character in a comment line seemed to be the culprit.
            Thanks for pointing it out
    Pingback: Arduino for Greenhouse, Garden or Growbox « armoid
    Mark Malaczynski
    March 12, 2016 at 15:50

    Like everyone has said, this is the best explanation on the net. I’m new to this and I wondered if you could help me with a project I’ve started. It involves measuring orientation (ultimately a rocket vertical guidance system) using a rate gyro on an adafruit IMU board. My conclusion is that I will need to use timers/interrupts to read the angular velocity at very small intervals and multiply by time to get the current angle. There will always be error on the gyro reading. Can you offer any advice on how to do this please?
    Reply
        Arduino
        March 12, 2016 at 16:53

        Thanks Mark, The reading of Gyro’s in itself isnt very difficult you could set up a timer that has the resolution you would need. It is the calculations however that are difficult.
        Depending on the Gyro you would either read a voltage, or processed info via I2C (e.g. with the MPU6050/GY521)
        I suggest you do something like this:

        // initialize Timer1
          cli();          // disable global interrupts
          TCCR1A = 0;     // set entire TCCR1A register to 0
          TCCR1B = 0;     // same for TCCR1B

          // set compare match register to desired timer count:
          OCR1A = 15624;

          // turn on CTC mode:
          TCCR1B |= (1 << WGM12);

          // Set CS10 and CS12 bits for 1024 prescaler:
          TCCR1B |= (1 << CS10);
          TCCR1B |= (1 << CS12);

          // enable timer compare interrupt:
          TIMSK1 |= (1 << OCIE1A);

          // enable global interrupts:
          sei();


        Now this is for 1 sec, obviously you can choose the resolution u need.
        In the ISR(TIMER1_COMPA_vect) {} routine you then do your reading
        Reply
    Zarella
    May 18, 2016 at 19:20

    Hello , I love this tutorial. I’m using the MEGA 2560 and I’m trying to use the sensor reading part every 10 mintues. but it doesn’t seem to be working :/

    to test I’m trying to read an RTD PT100 sensor every 10 seconds , here’s the function I put :

    ISR(TIMER1_COMPA_vect)
    {
    seconds++;
    if (seconds == 10)
    {
    seconds = 0;

    float Vout = analogRead(A0);
    float TempCel = (((-A)+ sqrt(pow(A,2)- (40* B * (0.1 -(Vout/1023.0)))))/(2*B)) ;
    Serial.print(“Temperture = “);
    Serial.print(TempCel);
    Serial.println(” C”);

    }
    }

    I am using ISIS proteus to simulate , and A0 doesn’t seem to be recieving any signle .
    please tell me something is wrong with my program. if not, I would focus on the hardware.
    thank you.
    Reply
        Arduino
        May 19, 2016 at 08:42

        I am not familiar enough with isis proteus to say wether maybe the problem is in there.
        It is not clear enough to me if you only used isis proteus or also a real life atmega but first i would try to make sure the connections are right and to minimize any program induced mistakes so:
        1 are you sure you grabbed the right pin for A0? I think it is pin 97
        2 add a line stating: Serial.print(Vout); and see what that does
        Reply
    George
    September 23, 2016 at 19:42

    Appears to be a very good tutorial but I have searched and searched and still come up blank on what “TCCR1B |= (1 << CS10);" actually means. They use this command all the time but no one ever says what it means. I assume it means that in TCCR1B make CS10 equal to a "1"? is this correct? And then comes along commands like "DDRB = DDRB | B00100000;" If I could only find where these types of commands are explained I could take a big jump forward on understanding the timers/counters.
    Reply
        Arduino
        September 24, 2016 at 23:25

        Your assumption is correct.
        it is in fact fairly simpel but it is shorthand for TCCR1B=TCCRB1 | (1<<CS10)
        the |= is a so called compound bitwise assignment operator: A compound bitwise assignment operator performs the appropriate binary operation and stores the result in the left operand.
        If one looks at the TCCR1B register, CS10 is bit 0. CS10 thus has the numerical value of 0
        1<<CS10 therefore is 1<<0, which means one shifts the number 1 0 places t0 the left. Ergo it is 1.
        Subsequently one OR's this with TCCR1B and assigns the resulting value to TCCR1B'
        This is in fact a rather complicated way of writing that one sets bit CS10 (bit0) in the TCCR1B register.
        Suppose the TCCR1B register= 10000100 if one OR' sthat with 00000001 (=1) the result is 10000101. That value is then assigned to TCCR1B
        The only difference between the oldand the new value then is bit 0, the CS10 bit.
        DDRB = DDRB | B00100000; is in fact similar, but here the compound operand |= is replaced by a normal equation. it could also have been written as
        DDRB |=B00100000
        in fact this statement sets bit 6 in het DataDirectionRegister B. one could also have written:
        DDRB |=(1<<6)
        now to make it more complicated, there are also macro' s that are supposed to help you with this, such as the 'bitvalue' macro _BV(x)
        one could write the above as DDRB |= _BV(6) or as DDRB |=_BV(PB6)

        and then ofcourse there is std::bitset….
        Anyway, if iy is still unclear, just ask
        Reply
    Mattia
    October 5, 2016 at 21:57

    Dear Arduino writer, this explanation on time interrupts is really well done and easy to follow, thanks a lot for your work!

    I see you have a deep knowledge of Arduino so probably you could help me on the following issue?

    I am trying to setup a way to perform multiple Interrupt routines in Arduino.. I think multiple CTC should work but I don’t know how to write down the code to match my expectations
    At the end, I would like to find a way to multitask Arduino through interrupts… do you think is this possible?

    Thanks again for your work and time, I am looking forward to hearing from you soon!
    Reply
        Arduino
        October 6, 2016 at 11:25

        Thanks for your kind words. Not sure if i have deep knowledge on the Arduino, I just get around with it.
        I am not sure if “multitasking” would be the proper word but sure the Arduino can perform various tasks.. suspending other tasks, through interrupts.
        However, if you have multiple interrupts, interrupting eachother.. though possible in principle, you may create a lot of other problems.
        Also you do not always need interrupts to have an Arduino perform various tasks.
        Perhaps it would help if you tell a bit more about what it is you want to do.
        Reply
            Mattia
            October 10, 2016 at 17:29

            Thanks for the kind reply, I think I am going to fix more or less what I would like to do. I am writing down a custom library for servomotors (as I did for stepper.. at least if something is not working I can understand why)

            I think to “parallel” the servos working by giving interrupts of over a period of 20 ms (to match the 50 Hz for servo control) and so I can change the pulse to each servo one after the other, each one in this way working at 50 Hz, theoreticaly controlling up to 10 servos with the same arduino (I need only few of them)

            I think this is probably the only way to control servos?

            p.s.: I prefer to write my own libraries even if similar libraries are present in Arduino so in this way I can know what the processr does and eventually why is not doing what is supposed to do.. so I prefer to not use the servo library in Arduino
            Arduino
            October 11, 2016 at 18:33

            seems like a good idea. At least whe writinyr own library you know what is happening
    Pingback: Timers | Pearltrees
    arjunscreamer
    December 3, 2016 at 19:36

    Dear writer, Could you please explain me the timer resolution calculation. What is 6.4e and why subtract it from 5s. Sorry, I’m new to the world of Arduin.

    (# timer counts + 1) = (target time) / (timer resolution)
    (# timer counts + 1) = (1 s) / (6.4e-5 s)
    (# timer counts + 1) = 15625
    (# timer counts) = 15625 – 1 = 15624
    Reply
        Arduino
        December 4, 2016 at 02:37

        it is sometimes hard to get the proper formatting on webpages but it is no substraction but a negative power: e-5
        ‘e’ is the base of the natural log.
        6.4e-5
        However, having said that, I think it is wrong and it shoulde be 0.000064 *which is 6.4*10-5. Some calculators however also write that as e-5, which causes the confusion
        Reply

Leave a Reply

