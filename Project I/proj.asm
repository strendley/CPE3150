org 0000h
#include <reg932.inc>
cseg at 0
	
		mov P0M1,#0		; set Port 0 to bi-directional
		mov P0M2,#0		
		mov P1M1,#0		; set Port 1 to bi-directional
		mov P1M2,#0		
		mov P2M1,#0		; set Port 2 to bi-directional
		mov P2M2,#0
		
		mov @R0, #0		; initialize registers used to 0
		mov @R1, #0
		mov R2, #0
		mov R3, #0
	
loop:	
		setb p0.3				; set bit
		jnb p0.3, incre				; jump to increment operation
		
		setb p2.2				; set bit
		jnb p2.2, decre			; jump to decrement operation
		
		setb p2.1 				; set bit
		jnb p2.1, evenPar 			; jump to even parity operation
		
		setb p2.0				; set bit
		jnb p2.0, inputVal1a			; jump to input count 1
		
		setb p0.1				; set bit
		jnb p0.1, inputVal2a			; jump to input count 2
		
		setb p0.2				; set bit
		jnb p0.2, addV1V2a			; jump to add counts 1 and 2
		
		setb p1.4				; set bit
		jnb p1.4, snake			; jump to snake if sw5 pressed
		
		setb p2.3				; set bit
		jnb p2.3, clear				; jump to Clear if sw3 pressed
		
		sjmp loop				; loop to monitor sw

inputVal1a:	ajmp inputVal1			; hopscotch jump

inputVal2a:	ajmp inputVal2				; hopscotch jump

addV1V2a:	ajmp addV1V2			; hopscotch jump

clear:	
			lcall delay			; assist in debounce
			mov R2, #00h			; clears registers used by
			mov R3, #00h			; input, add R2 and R3 fn
			setb p2.6			; clears bits used by parity fn
			setb p0.7
			ajmp loop			; loop back to monitor switches

incre:	
		lcall delay				
		cjne @R0, #0fh, incre2		; jump if RO is not 15
		mov @R0, #00h			; if R0 is 15, put 0 in R0
		lcall wrapSound			; then play sound
		ajmp display				; and display 0
	
incre2:	
		lcall delay					; assist in debounce
		inc @R0					; increment R0 when 0-14
		ajmp display					; then display count	

decre:	lcall delay						; assist in debounce
		cjne @R0, #00h, noWrap			; jump if R0 is not 0
		mov @R0, #0fh				; if R0 is 0, put 15 in R0
		lcall wrapSound				; then play sound
		ajmp display				; and display
		
noWrap:
		lcall delay				; assist in debounce
		dec @R0				; decrement R0 when 1-15
		ajmp display				; then display count

evenPar:
		;setb p2.6 				; clear amber LED
		setb p0.7 				; clear green LED
		
		mov A, @R0 			; jumps to oddPar if parity bit = 1
		RRC A				; accumulator rotate right through c
		jc oddPar
		clr p2.6 		; LED9 Amber (bottom right)
		clr p0.7	 		; LED8 Green (bottom middle)
		ajmp loop			; loop back to monitor buttons

oddPar:
		clr p2.6	 		; LED9 Amber (bottom right)
		ajmp loop			; loop back to monitor buttons
		
snake: clr p2.4;		; lights up the red LED
clr p0.5;			; lights up the yellow LED
lcall delay;			; call to delay below
lcall delay
lcall delay
lcall delay
setb p2.4;		; turns off red LED
clr p2.7;		; lights up the green LED
lcall delay
lcall delay
lcall delay
lcall delay
setb p0.5;		; turns off yellow LED
clr p0.4;		; lights up LED6 red
lcall delay
lcall delay
lcall delay
lcall delay
setb p2.7;		; turns off green LED
clr p2.6;		; lights up amber LED
lcall delay
lcall delay
lcall delay
lcall delay
setb p0.4;		; turns off LED6 red
clr p0.7;		; lights up green LED
lcall delay
lcall delay
lcall delay
lcall delay
setb p2.6;		; turns off amber LED
clr p2.5;		; turns on yellow
lcall delay
lcall delay
lcall delay
lcall delay
setb p0.7;		; turn off green
clr p0.6;		; light up LED4 amber
lcall delay
lcall delay
lcall delay
lcall delay
setb p2.5;		; turn off yellow
clr p1.6;		; light up blue
lcall delay
lcall delay
lcall delay
lcall delay
clr p2.4 ; top left red ON
setb p1.6 ; center blue OFF
lcall delay ; delays
lcall delay
lcall delay
lcall delay
setb p0.6 ; middle left amber OFF
setb p0.0 			; set bit for sw6
lcall delay 			; delay for button debounce
jnb p0.0, jumpOut 	 	; jump to jumpOut if sw6 pressed
ajmp snake		 ; keep on snaking if sw6 not pressed
		
jumpOut:
		setb p2.4		 ; if sw6 pressed, turn off red led
		lcall delay		 ; delay
		ajmp loop		 ; loop to monitor switches

inputVal1:
		lcall delay		 ; assists in debounce
		lcall delay
		inc R2			 ; increments R2
		ajmp loop		 ; loop back to monitor switches
			
inputVal2:
		lcall delay		; assists in debounce
		lcall delay
		inc R3			; increments R3
		ajmp loop		; loops back to monitor switches
		
addV1V2:
		lcall delay		; assists in debounce
		lcall delay
		clr A			; clears accumulator (Skylar's fn uses A)
		add A, R2		; add R2 to A
		add A, R3		; add R3 to A
		mov @R0, A		; mov A to R0
		sjmp display		; display value in R0 on lights
		
display:
		cjne @R0, #00h, set1				; if R0 does not equal 0, jump
		
		lcall delay
		setb p2.4		; OFF
		setb p0.5		; OFF
		setb p2.7		; OFF
		setb p0.4		; OFF
		ajmp loop		; loop to monitor sw
			
set1:	cjne @R0, #01h, set2				; if R0 does not equal 1, jump
			
		lcall delay
		setb p2.4		; OFF
		setb p0.5		; OFF
		setb p2.7		; OFF
		clr p0.4		; 2^0 ON
		ajmp loop		; loop to monitor sw
			
set2:	cjne @R0, #02h, set3				; if R0 does not equal 2, jump
		
		lcall delay
		setb p2.4		; OFF
		setb p0.5		; OFF
		clr p2.7		; 2^1 ON
		setb p0.4		; OFF
		ajmp loop		; loop to monitor sw

set3:	cjne @R0, #03h, set4				; if R0 does not equal 3, jump
		
		lcall delay
		setb p2.4		; OFF
		setb p0.5		; OFF
		clr p2.7		; 2^1 ON
		clr p0.4		; 2^0 ON
		ajmp loop		; loop to monitor sw
		
set4:	cjne @R0, #04h, set5				; if R0 does not equal 4, jump
		
		lcall delay	
		setb p2.4		; OFF
		clr p0.5		; 2^2 ON
		setb p2.7		; OFF
		setb p0.4		; OFF
		ajmp loop		; loop to monitor sw
		
set5:	cjne @R0, #05h, set6				; if R0 does not equal 5, jump
		
		lcall delay
		setb p2.4		
		clr p0.5		; 2^2 ON	
		setb p2.7		; OFF
		clr p0.4		; 2^0 ON
		ajmp loop		; loop to monitor sw

set6:	cjne @R0, #06h, set7				; if R0 does not equal 6, jump
		
		lcall delay
		setb p2.4		; OFF
		clr p0.5		; 2^2 ON
		clr p2.7		; 2^1 ON
		setb p0.4		; OFF
		ajmp loop		; loop to monitor sw

set7:	cjne @R0, #07h, set8				; if R0 does not equal 7, jump
		
		lcall delay
		setb p2.4		; OFF
		clr p0.5		; 2^2 ON
		clr p2.7		; 2^1 ON
		clr p0.4		; 2^0 ON
		ajmp loop		; loop to monitor sw

display_b: ajmp display			; hopscotch jump

set8:	cjne @R0, #08h, set9				; if R0 does not equal 8, jump			
		
		lcall delay
		clr p2.4		; 2^3 ON
		setb p0.5		; OFF
		setb p2.7		; OFF
		setb p0.4		; OFF
		ajmp loop		; loop to monitor sw

set9:	cjne @R0, #09h, set10				; if R0 does not equal 9, jump
		
		lcall delay
		clr p2.4		; 2^3 ON
		setb p0.5		; OFF
		setb p2.7		; OFF
		clr p0.4		; 2^0 ON
		ajmp loop		; loop to monitor sw

set10:	cjne @R0, #0Ah, set11				; if R0 does not equal 10, jump
		
		lcall delay
		clr p2.4		; 2^3 ON
		setb p0.5		; OFF
		clr p2.7		; 2^1 ON
		setb p0.4		; OFF
		ajmp loop		; loop to monitor sw

set11:	cjne @R0, #0Bh, set12				; if R0 does not equal 11, jump
		
		lcall delay
		clr p2.4		; 2^3 ON
		setb p0.5		; OFF
		clr p2.7		; 2^1 ON
		clr p0.4		; 2^0 ON
		ajmp loop		; loop to monitor sw
		
set12:	cjne @R0, #0Ch, set13				; if R0 does not equal 12, jump
		
		lcall delay
		clr p2.4		; 2^3 ON
		clr p0.5		; 2^2 ON
		setb p2.7		; OFF
		setb p0.4		; OFF
		ajmp loop		; loop to monitor sw

set13:	cjne @R0, #0Dh, set14				; if R0 does not equal 13, jump
		
		lcall delay
		clr p2.4		; 2^3 ON
		clr p0.5		; 2^2 ON
		setb p2.7		; OFF
		clr p0.4		; 2^0 ON
		ajmp loop		; loop to monitor sw
		
set14:	cjne @R0, #0Eh, set15				; if R0 does not equal 14, jump
		
		lcall delay
		clr p2.4		; 2^3 ON
		clr p0.5		; 2^2 ON
		clr p2.7		; 2^2 ON
		setb p0.4		; OFF
		ajmp loop		; loop to monitor sw

set15: cjne @R0, #0Fh, callZero				; if R0 does not equal 15, jump
		
		lcall delay
		clr p2.4		; 2^3 ON
		clr p0.5		; 2^2 ON
		clr p2.7		; 2^1 ON
		clr p0.4		; 2^0 ON	
		ajmp loop		; loop to monitor sw

callZero: ajmp display_b		; hopscotch jump
				
wrapSound:
		mov R1, #200			; loop count
		mov TMOD, #01h 		; timer 1 mode 1 (16 bit mode)
loop3:	mov TH1, #-65536 shr 8		; load high byte with #0ffh (bit 15 to 8 of # in binary)
		mov TL1, #-65536		; preload
		setb TR1			; turn on timer
		cpl p1.7			; toggle speaker port bit
here4:	jnb TF1, here4				; wait for 65536 MC delay
		clr TR1			; turn off timer 1
		clr TF1			; clear overflow flag
		djnz R1, loop3		; loops 200 times
		ret
				
delay:	mov R1, #100				; loop count
		mov TMOD, #01h 		; timer 1 mode 1 (16 bit mode)
loop2:	mov TH1, #-38000 shr 8		; load high byte with bits 15 to 8 of 38000 binary
		mov TL1, #-38000		; preload
		setb TR1			; turn on timer
here3:	jnb TF1, here3				; wait for 38000 MC delay
		clr TR1			; turn off timer 1
		clr TF1			; clear overflow flag
		djnz R1, loop2		; loops 100 times
		ret
end

