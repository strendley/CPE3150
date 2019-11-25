;inside button monitoring loop
setb p2.1 			; set bit
jnb p2.1, evenPar 		; jump to even parity operation

;functions
evenPar:
		;setb p2.6     		; clear amber LED
		setb p0.7     		; clear green LED
		
		mov A, @R0 			; jumps to oddPar if parity bit = 1
		RRC A				; rotate right accumulator 
		jc oddPar
		clr p2.6            ;		 LED9 Amber (bottom right)
		clr p0.7	   		; LED8 Green (bottom middle)
		ajmp loop			; loop back to monitor buttons

oddPar:
		clr p2.6	 		; LED9 Amber (bottom right)
		ajmp loop			; loop back to monitor buttons
