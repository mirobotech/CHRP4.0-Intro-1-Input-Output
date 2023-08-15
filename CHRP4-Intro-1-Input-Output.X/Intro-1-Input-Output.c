/*==============================================================================
 Project: Intro-1-Input-Output          Activity: mirobo.tech/intro-1
 Date:    August 11, 2023
 
 This introductory input and output programming activity for the mirobo.tech
 CHRP4 demonstrates pushbutton input, LED (bit) output, port (byte) output,
 MPLAB's built-in time delay functions, and simple 'if' condition structures.
 
 Additional program analysis and programming activities demonstrate the logical
 AND and OR conditional operators, the use of time delay functions to create
 sound output, and software-based simulated start-stop button functionality.
==============================================================================*/

#include    "xc.h"              // Microchip XC8 compiler include file
#include    "stdint.h"          // Include integer definitions
#include    "stdbool.h"         // Include Boolean (true/false) definitions

#include    "CHRP4.h"           // Include CHRP4 constants and functions

// TODO Set linker ROM ranges to 'default,-0-7FF' under "Memory model" pull-down.
// TODO Set linker code offset to '800' under "Additional options" pull-down.

// The main function is required in every C program. The microcontroller begins
// executing the program starting at the first line in the main function.

int main(void)
{
    // These configuration functions run once during program start-up.
    OSC_config();               // Configure internal oscillator for 48 MHz
    CHRP4_config();             // Configure I/O for on-board CHRP4 devices
    
    // The code in this while loop repeats forever.
    while(1)
    {
        // If SW2 is pressed, make a flashy light pattern
        if(SW2 == 0)
        {
            LED2 = 1;
            __delay_ms(100);
            LED3 = 1;
            __delay_ms(100);
            LED4 = 1;
            __delay_ms(100);
            LED5 = 1;
            __delay_ms(100);
            LED2 = 0;
            __delay_ms(100);
            LED3 = 0;
            __delay_ms(100);
            LED4 = 0;
            __delay_ms(100);
            LED5 = 0;
            __delay_ms(100);
        }

        // Add your Program Analysis and Programming Activities code here:

        // Reset the microcontroller and start the bootloader if SW1 is pressed.
        if(SW1 == 0)
        {
            RESET();
        }
    }
}

/* Learn More -- Program Analysis Activities
 * 
 * 1. Analyzing a program to understand its operation is an important skill to
 *    develop. Let's figure out how this program works! Start by testing the
 *    program and observing what happens when it runs in your circuit board.
 *    Quickly press and release SW2 and watch what the light pattern does. How
 *    many lights flash? How many times do they flash? Next, press and hold SW2
 *    and observe the light pattern. Does the light pattern stop immediately
 *    when you let go of SW2?
 * 
 *    Now, examine the program and try to match your observations of the light
 *    pattern to the program code. How many of the lights are controlled by the 
 *    pattern inside the curly braces following the SW2 'if' statement? If SW2
 *    is pressed should the entire light pattern continue until it is finished,
 *    or should it stop as soon as SW2 is released? Can you explain why that is?
 * 
 * 2. Explain the difference between the statements: LED2 = 0; and LED2 = 1;
 *    How does making LED2 become 0 or 1 in the code actually turn LED2 on or
 *    off on the circuit board?
 * 
 * 3. Understanding how a circuit works is another important skill to develop
 *    in interfacing (controlling hardware with software). What voltage do you
 *    expect the microcontroller to output to LED D2 when the statement
 *    'LED2 = 0;' runs? What voltage do you expect the output to be when the
 *    statement 'LED2 = 1;' runs?
 * 
 *    If you have access to a voltmeter, you can use it confirm the output
 *    voltage of the microcontroller in the circuit. Try measuring across one
 *    of the LEDs as the program outputs a 0, and again when it outputs a 1.
 *    The voltage will change quickly so you may need to use a 'peak hold' or
 *    'max' feature if your multimeter has one, or slow down the light pattern
 *    in your program by increasing the time delays. Next, refer to the 
 *    schematic to find one of the microcontroller pins that is connected to
 *    one of the LEDs, and measure between that microcontroller pin and the
 *    negative pin of battery connector BT1 as you run the program again.
 *    Compare your measurements. Which voltage matched your prediction? Can you
 *    explain why?
 * 
 * 4. The statement 'if(SW2 == 0)' contains two equal signs, while the statement
 *    'LED2 = 1;' contains a single equal sign. What operation is performed by a
 *    statement using one equal sign? What operation is performed by a statement
 *    using two equal signs? How are the two operations different?
 * 
 * 5. Find the switch circuits on the schematic diagram. Why does the program
 *    code use the statement 'if(SW2 == 0)' to sense if a switch is pressed?
 *    Can you use the schematic to explain why the input voltage on one of the
 *    microcontroller's switch inputs will be low when the switch is pressed?
 *  
 * 6. The following code structure includes instructions that write to all of 
 *    the bits in the PORTC output latches (called LATC) directly. PORTC (LATC)
 *    connects to CHRP4's on-board LEDs. Let's try some new code to control
 *    the LEDs in a different way than the original SW2 output structure does.
 * 
 *    Copy and paste the following block of code underneath the existing SW2
 *    'if' structure in your program (paste it where shown by the code comment
 *     located at line 56 of the original program above).

        if(SW3 == 0)
        {
            LATC = 0b00000000;
            __delay_ms(100);
            LATC = 0b11110000;
            __delay_ms(100);
        }

 *    What happens when pushbutton SW3 is pressed? Can you think of at least one
 *    advantage and one disadvantage of controlling the LEDs using 'LATC' write
 *    statements rather than by individual 'LEDn = x;' statements?
 * 
 * 7. Next, let's compare the operation of 'if' and 'while' structures to
 *    simulate the operation of momentary buttons. Add the following code below
 *    the SW3 'if' structure you added in analysis activity 6, above:

        // Momentary button using an if structure
        if(SW4 == 0)
        {
            LED4 = 1;
        }
        else
        {
            LED4 = 0;
        }

        // Momentary button using a while structure
        while(SW5 == 0)
        {
            LED5 = 1;
        }
        LED5 = 0;

 *    First, try pressing and releasing SW4 and SW5 one at a time. They should
 *    act the same way, turning their respective LEDs on when each switch is
 *    pressed.
 * 
 *    Next, press and hold SW4 while pressing and releasing SW5. Does SW5 work
 *    as expected?
 * 
 *    Last, press and hold SW5 while pressing and releasing SW4. Does SW4 work
 *    as expected?
 * 
 *    Can you explain the difference in operation between the 'if' and 'while'
 *    structures making up the momentary button code.
 * 
 * 8. Let's explore logical conditions using 'if' statements. Replace the code
 *    added in step 7, above, with this 'nested if' code to make a logical AND
 *    condition which will light LED D4 only if both SW4 and SW5 are pressed:

        // Nested if 'AND' code
        if(SW4 == 0)
        {
            if(SW5 == 0)
            {
                LED4 = 1;
            }
            else
            {
                LED4 = 0;
            }
        }
        else
        {
            LED4 = 0;
        }

 *    Test the code to ensure it works as expected. Does the order of the if
 *    conditions matter? (e.g. swap the conditional checks for SW4 and SW5)
 * 
 * 9. Next, replace the code from activity 8, above, with the following code
 *    which implements the logical AND conditional operator composed of two
 *    ampersands '&&':
 
        // Conditional 'AND' code
        if(SW4 == 0 && SW5 == 0)
        {
            LED4 = 1;
        }
        else
        {
            LED4 = 0;
        }

 *    Does '&&' work the same way as the nested if structures? Can you think of
 *    at least one advantage of using a logical conditional operator instead of
 *    nested if structures?
 * 
 * 10. Replace the double ampersand '&&' with double vertical bars '||' to make
 *    a logical OR conditional operator. Your code should look like this:
  
        // Conditional 'OR' code
        if(SW4 == 0 || SW5 == 0)
        {
            LED4 = 1;
        }
        else
        {
            LED4 = 0;
        }

 *    Describe the conditions under which LED4 turns on.
 * 
 * Programming Activities
 * 
 * 1. The statement '__delay_ms(100);' creates a 100ms delay. Try changing one
 *    or more of the delay values in the program to 500ms and see what happens.
 * 
 *    Can the delay be made even longer? Try 1000 ms. How big can the delay get
 *    before MPLAB-X produces an error message? (Hint: can you think of a fast
 *    and efficient way of guessing an unknown number?)
 * 
 * 2. The '__delay_ms();' function accepts only integers as delay values. To
 *    create delays shorter than 1 ms, a different function must be used. Use
 *    the '__delay_us();' function to specify delays in microseconds.
 * 
 *    You won't be able to see microsecond length LED flashes with your eyes,
 *    but you can measure them using an oscilloscope, or hear them if they are
 *    used to turn a piezo beeper on and off. Try the following code in your
 *    program:
 
        // Make a tone while SW5 is held
        if(SW5 == 0)
        {
            BEEPER = 1;
            __delay_us(567);
            BEEPER = 0;
            __delay_us(567);
        }

 *    Try changing the delay values in both of the __delay_us(); functions.
 *    Does the pitch of the tone increase or decrease if the delay values are
 *    made smaller? Does the opposite happen if the delays are made larger?
 * 
 * 3. This code demonstrates a more compact way of 'toggling' the beeper output
 *    using a logical NOT operator '!'. Replace the code above, with this code:
 
        // Make a tone while SW5 is held
        if(SW5 == 0)
        {
            BEEPER = !BEEPER;
            __delay_us(567);
        }

 *    One difference between this code and the code in activity 2, above, is the
 *    state of the BEEPER pin when SW5 is released. Will you know what state the
 *    BEEPER output will be in after this code runs? While one advantage of this
 *    method is less program code, can you think of one or more disadvantages of
 *    not knowing the output state of a pin when using code like this?
 * 
 * 4. Using modified versions of the original SW2 'if' structure, create a
 *    program that makes a unique LED flashing pattern for each pushbutton.
 * 
 *    Test each of your flashing patterns. Describe what happens when more than
 *    one button is held. Do all of the patterns try to flash the LEDs at the
 *    same time, or sequentially? Explain why this is so.
 * 
 * 5. Create a program that makes a different tone for each pushbutton.
 * 
 *    Test each tone by pressing each button individually. Next, press two or
 *    more buttons at the same time. Describe what you think the tone waveforms
 *    will look like when two or more buttons are held. (You can verify your
 *    prediction if you have access to an oscilloscope and connect it across
 *    the piezo beeper's output resistor.)
 * 
 * 6. Use individual 'if' structures to simulate 'Start' and 'Stop' buttons for
 *    an industrial machine. Use SW3 to turn LED D3 on when it is pressed, and
 *    make LED D3 stay on even after SW3 is released. Use another if structure
 *    for SW4 to turn LED D3 off when it is pressed. Test your program to make
 *    sure that it works the way you expect it to.
 * 
 * 7. Running your program from activity 6, above, describe what happens when
 *    both SW3 and SW4 are held. Does LED D3 stay on? If so, how does its
 *    brightness compare when both button are held to when only SW3 is pressed?
 *    If the brightness is different, can you explain what part of the code is
 *    causing it to change, and why it changes?
 * 
 * 8. As you might imagine, an industrial machine that is able to turn on even
 *    while its 'Stop' button is pressed represents a significant safety hazard.
 *    Using one or more of the logical conditional operators introduced in the
 *    analysis activities, above, modify your start-stop program to make it
 *    safer. SW3 should only be able to turn LED D3 on if switch SW4 is not
 *    being pressed at the same time.
 * 
 * 9. LED D1 is normally used to indicate that a program is running, but it can
 *    be controlled by your program as well. If you examine the CHRP4 schematic,
 *    you will see that LED D1's cathode (or negative) pin is connected to the
 *    microcontroller instead of having its anode (positive) pin connected to
 *    the microcontroller as the other LEDs do. This means that the LED D1
 *    output must be made equal to 0 to turn D1 on.
 * 
 *    Try it! Make a program that controls or flashes LED D1 as part of a light
 *    pattern. (Be careful that you don't change the SW1 reset code when making
 *    your light pattern, or you may not be able to use switch SW1 to reset
 *    the board and enter programming mode using the bootloader. If this
 *    happens, unplug the USB cable and press and hold SW1 while re-connecting
 *    the USB cable. LED D1 will remain off until you release SW1, and then the
 *    bootloader will start. Then, be sure to re-enable the SW1 reset code that
 *    your code edits accidentally disabled.)
 */