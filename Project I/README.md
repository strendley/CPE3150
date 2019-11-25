# Project I - Introduction to the Microcontroller

### Roles and Work Effort Distribution:
*Curtis Collins* – Programmed LED button display. Programmed delay function (with assistance for calculations). Assisted with troubleshooting/debugging. Contributed 33.33% of the total percentage effort.
Individual - LED Snake Function

*Luke Malloy* – Programmed button monitoring loop. Programmed output frequency function (with assistance for calculations). Assisted with troubleshoot/debugging. Contributed 33.33% of the total percentage effort.
Individual - Input two counts, add them, move to R0 and display them

*Skylar Trendley* – Programmed INC/DEC operations. Programmed wrapAround. Assisted with troubleshooting/debugging. Contributed 33.33% of the total percentage effort.
Individual - Parity Function

### Summary: 
Using the Keil environment, our team created a project that allowed us to program an up-down counter on the 8051 microcontrollers. We produced multiple functions that generate the operations of the up-down counter. They include:
- Loop - monitor buttons for input (inc/dec/individual functions)
- Incre - if register 0 == 0Fh, set register 0 to 00h
- Inc2 - increment register 0 by 1
- Decre - if register 0 == 00h, set register 0 to 0Fh 
- noWrap - decrement register 0 by 1
- Delay - create a delay between functions using timers
- WrapSound - if wraparound, activate buzzer sound 
- Display - calls Set0-Set15 to light up LEDs-
- Set0 - Set15 - set or clear proper port bits to display corresponding LEDs


### Calculations

The Simon Board uses an MCU that has an RC oscillator operating at 7.373 MHz. Each machine cycle consists of two clock cycles, thus it is 6 times faster that MCU’s with fosc values of 12MHz studied in class. Most instructions execute within 1 or two machine cycles. 

We set out to generate a 1 second delay with the use of the on board timers. 

![delay](https://user-images.githubusercontent.com/26886594/69513279-e7ba6c80-0f0c-11ea-9938-ffa6b282df1f.PNG)


To achieve such a delay, we needed a nested loop where a value of roughly 36000 was loaded into the TH1 and TL1 as we needed to use the 16 bit mode. 36000  times 100 in the loop count gave us 3600000 which was close enough to the intended delay. Now, we could stack the delays in 1s intervals so that we could achieve known greater delays.

For the buzzer frequency upon wraparound, we set out to achieve a frequency of 1000Hz. 

![freq](https://user-images.githubusercontent.com/26886594/69513293-f2750180-0f0c-11ea-8b96-86f04d95853c.PNG)

However, using these values did not produce a sound. We then increased the value loaded into TH1 and TL1 to the max (65k) and experimented with the loop count. We found that the maximum value allowed in the 16 bit mode with a loop of over 100 produced an adequate alarm. We still need to accurately determine the frequency produced by this subroutine, as our original calculation is off due to not accounting for the mov dir, #data  and djnz instructions taking 2 machine cycles each. We will be aware of this in the future when calculating the frequencies and delays produced by the timers as moving a byte into the either THx or TLx takes 2 machine cycles each. Through this, we also now know that our delay subroutine must not be giving a true delay of 1 second either. Thus, by increasing the machine cycles by roughly 4 to adjust for the MC needed for these instructions, we were able to produce roughly the intended frequency.


### Problems
Problems we encountered while programming the up-down counter include:
- Proper monitoring of the LEDs - We realized that when programming the LED port bits, that setb would turn the light off, and clr would turn the light on. This mistake was fixed and the error ceased.
- Time delay - when attempting to delay the LED lights after the increment/decrement functions are called, we could not get a delay to work properly in our code. We then realized that it was calling the delay function in the midst of the code due to its positioning, so it was moved to the bottom of our code before “end”, which allowed us to jump to it only when necessary.
- Inc wraparound - when programming the wraparound of 15 back to 0, we attempted to find a method to do a direct comparison jump. We then discovered that we could use cjne to do a direct jump by making the numbers 0-14 jump through the cnje operation and having the option for when the case is met below it. This allowed us to properly wrap around at 15. 
- WrapSound - When attempting to make the buzzer sound activate upon wraparound, we noticed our program would get caught at 15 or would not do an immediate decrement at 0, and the microcontroller made a faint attempt to activate the buzzer’s sound. By commenting out wrapSound, we found that the wraparound operations were fine, but the wrapSound was entering an infinite loop that it could not jump out of. During further inspection of the wrapSound function, we found that we had been complimenting in the wrong place and needed a loop to TF1 to wait for the MC delay. This problem was fixed and the buzzer sound activated properly.
- Debounce - For the count to not immediately increment more than one time per button press, delays were used in the inc and dec functions to slow down the process as pressing the switch one time could send more than one signal to the microcontroller. Before this was perfected, the MCU thought that the switch was being activated more than it actually was.


### Simon Board Assignments for Main Program:
- P0.3 - SW8 - will increment R0 and display value when pressed
- P2.2 - SW9 - will decrement R0 and display value when pressed
- P2.4 - LED1 Red - represents “1” in binary 
- P0.5 - LED2 Yellow - represents “2” in binary
- P2.7 - LED3 Green - represents “4” in binary
- P0.4 - LED6 Red - represents “8” in binary

### Simon Board Layout:

![simon_board](https://user-images.githubusercontent.com/26886594/69513311-015bb400-0f0d-11ea-8006-104ec32ebc9d.PNG)

