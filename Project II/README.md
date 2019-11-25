# Project II

All team members worked together to construct the definitions for the preload values that create a specific frequency in C.

### Roles and Work Effort Distribution:
*Curtis Collins* - Lead programmer in check mode switch function, and note light/LED functions. Contribution: 33%

*Luke Malloy* - Lead programmer in delay, continuous wave function, keyboard functions. Contribution: 33%

*Skylar Trendley* - Lead programmer for tune1, tune2 and discrete wave function. Contribution: 33%

### Summary:
Using the Keil environment, our team created a project that allowed us to use the Simon2 Board as a keyboard. We produced multiple functions that facilitate the operation of the keyboard. They include:
- checkModeSW() - Calls resetLED() and branches to the correct function depending on user input.
- timer1ISR() - Interrupt Service Routine for timer 1 that toggles speaker port bit p1.7.
- period0/1() - Sets the period for square wave using timer or timer 1.
- tune1() - Uses discreteW() to generate the song “twinkle twinkle little star”.
- tune2() - Uses discreteW() to generate the song “jingle bells”.
- discreteW() - Is passed a preload value, period0() is called and the proper preload value for that note is loaded into TH0 and TL0. Is also passed a loop count so that the note is played for a specified amount of loops.
- noteLights() - Generates a square wave corresponding to musical notes and lights up LEDs.
- delay() - Delay using timer 1 for 1 second.
- resetLED() - Sets all LEDs back to unlit.
- serialD() - UART transmit sequence of characters in a given input string passed to the function.
- keyboard() - matches the corresponding switches to the LEDs for musical notes.


Reference for musical note frequencies:
https://pages.mtu.edu/~suits/notefreqs.html

### Problems:
Problems we encountered while programming the keyboard function include:
1. Nested functions for the menus.
2. When initially programming different tunes and individual functions into the keyboard program, we were stuck on the idea of being able to switch out while performing a song for loop. We then decided to initiate checkModeSW() that will return to the main menu if SW7 is pressed while the tune is playing. This was placed inside of the discreteW() function that creates a discrete waveform primarily for playing tunes.
3. UART display & Putty - When programming the display for the song titles of Tune 1 and Tune 2, we were having issues with Putty. After clicking on Serial and typing in COM3 and selecting NONE for flow control, putty refused to open. It was solved as simply as choosing a serial session instead of the default SSH option. Oops!
4. Continuous wave vs discrete wave - to create the keyboard notes, we easily found a way to toggle the speaker port at each overflow of the timer using an interrupt while the SW was activated. However, using this method, we were not able to create songs. In order to create a discrete waveform, we designed a function that accepted a preload value and a loop count such that the note would be played for a specified amount of time. 

### Calculations:
Frequency calculations for all 37 preload values were done in the following fashion:

![freq2](https://user-images.githubusercontent.com/26886594/69513962-657f7780-0f0f-11ea-96d5-83aec28ffa0f.PNG)

This example is the preload value used for A3. All other note calculations were done in this same manner, repeated for each frequency.


The 1 second delay calculations were done in the following fashion:
N = tD/tMC

![delay2](https://user-images.githubusercontent.com/26886594/69513986-74662a00-0f0f-11ea-8413-a4087893626e.PNG)


This value was then parsed by looping for 100 times and then preloading -36865 into THO and TLO for a total of 3686500 machine cycles. Our delay function takes an integer and multiplies it by 100 to get the total number of loops. Delay(5); would produce a 5 second delay, looping 500 times with -36865 as the preload value. 

### Features Used:
- Timer 0 was used to output a discrete square wave with the help of a loop that is passed to the function. This allows the note to be played for a specified interval. 
- Timer 0 was also used to create a delay function. Timer 0 needs a preload value of -36865 to create a delay of 1 second with the help of a loop. The value passed to the delay function is then multiplied by 100. Therefore a delay(1); statement would cause the timer to count from 9001h to FFFFh 100 times. This gives us a MC count of 3686500, which is what we have calculated to be necessary for a 1 second delay. Passing the delay function a 2 would generate a 2 second delay thus looping 200 times, and so on. 
- Timer 1 was used to output a continuous square wave on P1.7. It uses interrupt 3. At each overflow of the timer, the interrupt service routine is serviced and the speaker port bit P1.7 is toggled. To enable this use of the interrupt 3 in ROM location 001Bh of the interrupt vector space for the 8051, we had to enable the timer 1 interrupt and enable all interrupts for the device by setting the interrupt enable register to 0x88h.
- The UART of the 8051 was used to transmit the titles of our songs and short tunes to the screen. It was also used to display a menu to the user and notify the user whenever the system was ready for input. To implement the uart transmit function, we designed a function that was passed a character array, whose value was set to be a string. This character array was transmitted, index by index using the bitwise transmission feature of the UART using a for loop. As soon as the array was empty, transmission ceases and the “string” is fully transmitted. 
- For the external hardware implementation portion, we connected a set of 3 leds a set of 2 leds and a set of 1 led to the breadboard such that when a low note plays, the set of 1 illuminates, when a note in the mid range plays, the set of 2 leds illuminates and when a high frequency note plays, the set of three leds illuminates. This was easily achieved with a set of if statements that operated on the preload value for the note that is currently being played. We assigned three port bits to control this hardware externally. P1.2 is assigned to the set of one led, P1.3 is assigned to the set of 2 leds and P1.1 is assigned to controlling the set of 3 leds.  

### Pins:

**Switches:**

- P2.0 = switch 1
- P0.1 = switch 2
- P2.3 = switch 3
- P0.2 = switch 4 (skylar’s song)
- P1.4 = switch 5 (curtis’ function)
- P0.0 = switch 6 (luke’s game)
- P2.1 = switch 7 (tune 1)
- P0.3 = switch 8 (tune 2)
- P2.2 = switch 9 (keyboard)

**LEDs:**

- P2.4 = LED1
- P0.5 = LED2
- P2.7 = LED3
- P0.6 = LED4
- P1.6 = LED5
- P0.4 = LED6
- P2.5 = LED7
- P0.7 = LED 8
- P2.6 = LED 9

**Breadboard:**
- P1.1= External Led bank of 3
- P1.2= External Led bank of 1
- P1.3= External Led bank of 2

### Simon Board:

![simon_board2](https://user-images.githubusercontent.com/26886594/69514209-11c15e00-0f10-11ea-8e69-8391f71dc49b.PNG)

