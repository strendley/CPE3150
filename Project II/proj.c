#include <REG932.h>
#include <uart.h>
#include <uart.c>

#define A3				8383		//~200Hz			// MC preload calculations defined for timer overflow to generate 
#define Bb3				7910									// intended notes/frequencies
#define B3				7492 
#define C4				7062  
#define Db4				6654  
#define D4				6290  
#define Eb4				5926
#define E4				5602
#define F4				5281 
#define Gb4				5022 
#define G4				4702  
#define Ab4				4441
#define A4				4189  
#define Bb4				3955  
#define B4				3731  
#define C5				3524
#define Db5				3327  
#define D5				3140  
#define Eb5				2963  
#define E5				2797  
#define F5				2640
#define Gb5				2490
#define G5				2351
#define Ab5				2220  	
#define A5				2094
#define Bb5				1977
#define B5				1865
#define C6				1763  
#define Db6				1662
#define D6				1569
#define Eb6				1481  
#define E6				1397  
#define F6				1319 
#define Gb6				1245 
#define G6				1175
#define Ab6				1109 
#define A6				1047  
#define Bb6				988			//~2000Hz

										// function prototypes 
void checkModeSW();	
void soundNote();
void continuousWave();
void period0(int);
void period1(int);
void starWars();
void discreteW(int, int);
void discNoLed(int, int);
void noteLights(int);
void delay(int);
void resetLed();
void serialD(char []);
void verifySeq1();
void verifySeq2();

void Curtis();
void Skylar();
void simonGame();
void youWon();
void youLost();
void lose();
void jingleBells();
void twinkle();
void keyboard();

int freqPreload, MC;					// declare variables
int freqPreload2;
int i, k;
int loop = 0;
int time, del;
int num;
int N, D;
int win = 0;
int j, l;
int w = 0;
int w2 = 0;
unsigned char p = 0;

char verify1[] = {'0', '0', '0', '0', '0', '0'};
char seq1[] = {'1', '2', '5', '1', '4', '5'};

char verify2[] = {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0'};
char seq2[] = {'2', '4', '6', '1', '3', '5', '2', '6', '2', '4'};	

sbit SW1 = P2^0;		//assign bits to ports for switches and leds
sbit SW2 = P0^1;
sbit SW3 = P2^3;
sbit SW4 = P0^2;
sbit SW5 = P1^4;
sbit SW6 = P0^0;
sbit SW7 = P2^1;
sbit SW8 = P0^3;
sbit SW9 = P2^2;

sbit led1 = P2^4;
sbit led2 = P0^5;
sbit led3 = P2^7;
sbit led4 = P0^6;
sbit led5 = P1^6;
sbit led6 = P0^4;
sbit led7 = P2^5;
sbit led8 = P0^7;
sbit led9 = P2^6;

sbit EXTLED1 = P1^2;
sbit EXTLED2 = P1^3;
sbit EXTLED3 = P1^4;

sbit speaker = P1^7;

void checkModeSW()
{
	resetLed();												//reset all led, initialize main menu 

																		//turn on leds that branch to modes 
	//led3 = 0;		//Luke's starwars tune
	led4 = 0;			//Skylar's Song 
	led5 = 0;			//Curtis's Fn
	led6 = 0;			//simon led
	led7 = 0;			//tune 1 led
	led8 = 0;			//tune 2 led
	led9 = 0;			//keyboard led
	
	while(1)
	{																//Curtis and Skylar's branching for modes here: SW 1-5 unused
			
			if(SW4 == 0)						//Branches to Skylar's fn
			{
				led4 = 1;
				delay(1);
				Skylar();
			}
		
			
			if(SW5 == 0)						//Branches to Curtis's fn
			{
				led5 = 1;
				delay(1);
				Curtis();
			}																				
			
			
			if(SW3 == 0)						//starwars tune
			{
				led3 = 1;
				delay(1);
				starWars();
			}
			
			
			if(SW6 == 0)						//simon game
			{
				led6 = 1;
				delay(1);
				simonGame();
			}
			

			if(SW7 == 0)						//tune 1
			{
				led7 = 1;
				delay(1);
				jingleBells();
			}


			if(SW8 == 0)						//tune 2
			{
				led8 = 1;
				delay(1);
				twinkle();
			}
			
			
			if(SW9 == 0)						//keyboard
			{
				led9 = 1;
				delay(1);
				keyboard();
			}
		}
}


void keyboard()
{
	resetLed();
	serialD("You are now using the keyboard mode! Play a tune!\r\n");
	
	while(1)
	{													// load proper values for notes into continuous wave function
			
			led7 = 0;							//light to indicate sw to jump out of keyboard 
		
			if(SW1 == 0)					//SW1 = key1
			{
				led1 = 0;
				freqPreload = F4;
				period1(freqPreload);
			}

			if(SW1 == 1)					//leds only lit when switch above pressed
				led1 = 1;
		

			if(SW2 == 0)					//SW2 = key2
			{
				led2 = 0;
				freqPreload = Eb5;
				period1(freqPreload);
			}
			
			if(SW2 == 1)
				led2 = 1;
	
	
			if(SW3 == 0)					//SW3 = key3
			{
				led3 = 0;
				freqPreload = C6;
				period1(freqPreload);
			}
			
			if(SW3 == 1)
				led3 = 1;
	

	
			if(SW4 == 0)					//SW4 = key4
			{
				led4 = 0;
				freqPreload = F5;
				period1(freqPreload);
			}
			
			if(SW4 == 1)
				led4 = 1;


			
			if(SW5 == 0)					//SW5 = key5
			{
				led5 = 0;
				freqPreload = Ab5;
				period1(freqPreload);
			}
			
			if(SW5 == 1)
				led5 = 1;



			if(SW6 == 0)					//SW6 = key6
			{
				led6 = 0;
				freqPreload = G5;
				period1(freqPreload);
			}
			
			if(SW6 == 1)
				led6 = 1;
			

			
			if(SW7 == 0)					// main menu when SW7 activated
			{											// (jumps back to monitoring switches for mode input)
				delay(2);	
				checkModeSW();
			}
	}
}


void Curtis()
{
	led7 = 0;								//light up led7, SW7 will jump out of your function	to main menu
	resetLed();
	while(1)
	{
		led1 = 0;							//modes
		led2 = 0;
		led3 = 0;
		
		if(SW1 == 0)					//Pick A3
		{
			freqPreload2 = A3;
		}
			
		if(SW2 == 0)					//Pick D4
		{
			freqPreload2 = D4;
		}

		if(SW3 == 0)					//Pick A5
		{
			freqPreload2 = G5;
		}

		if(SW4 == 0)					//Jump up an octave
		{
			led4 = 0;
			freqPreload2 = (A3-2000);
		}
			
		led4 = 1;
			
		if(SW5 == 0)					//
		{
			led5 = 0;
			freqPreload2 = (D4-3500);
		}
	
		led5 = 1;
			
		if(SW6 == 0)					//
		{
			led6= 0;
			freqPreload2 = (G5+2000);
		}
			
		led6 = 1;
		
		
		if(SW8 == 0)					//Plays chosen note
		{
			led8 = 0;
			period1(freqPreload2);
		}
		
		led8 = 1;
		
		if(SW7 == 0)						//  main menu when SW7 activated
		{											
			delay(2);
			led7 = 1;
			checkModeSW();			// (jumps back to monitoring switches for mode input)
		}
	}
}


void Skylar()
{
													//SW7 will jump out of your function	to main menu
	discreteW(B4,300);
	discreteW(F4,300);
	discreteW(E4,300);
	discreteW(D4,300);
	discreteW(D4,300);
	discreteW(B4,300);
	discreteW(E4,300);
	discreteW(D4,300);
	discreteW(B4,300);
	discreteW(E4,300);
	discreteW(B4,300);
	discreteW(D4,300);
	discreteW(D4,300);
	discreteW(E4,300);
	checkModeSW();
}


void simonGame()												//Luke's game and song
{
	discNoLed(D4, 600); 			// sound, reset led then check mode
	resetLed();
	serialD("Welcome to Simon Says\r\n");
	
	while(1)
	{
		led8 = 0;
		led9 = 0;
													//choose mode after sound plays
		if(SW8 == 0)					//start mode one		
		{
			delay(1);						//toggle mode led
			resetLed();
			
			serialD("You have chosen Mode 1\r\n");
			
			delay(1);										//initiate sequence 1,2,5,1,4,5 on leds 
			led1 = 0;						
			delay(1);
			led1 = 1;
			led2 = 0;
			delay(1);
			led2 = 1;
			led5 = 0;
			delay(1);
			led5 = 1;
			led1 = 0;
			delay(1);
			led1 = 1;
			led4 = 0;
			delay(1);
			led4 = 1;
			led5 = 0;
			delay(1);
			led5 = 1;
			
			delay(1);
			led7 = 0;						//light led to show SW7 needs to be pressed to end entered sequence
			
			while(1)	
			{													//if switches pressed, store entered sequence into character array
				if(SW1 == 0)
				{
					verify1[0] = '1';
				}
					
				if(SW2 == 0)
				{
					verify1[1] = '2';
				}
				
				if(SW5 == 0)
				{
					verify1[2] = '5';
				}
					
				if(SW1 == 0)
				{
					verify1[3] = '1';
				}
					
				if(SW4 == 0)
				{
					verify1[4] = '4';
				}
					
				if(SW5 == 0)
				{
					verify1[5] = '5';
				}
					
				if(SW7 == 0)
				{
					led7 = 1;
					verifySeq1();
				}					
			}		
		}

		if(SW9 == 0)					//start mode two		
		{
			delay(1);						//toggle mode led
			resetLed();
			
			serialD("You have chosen Mode 2\r\n");
			
			delay(1);										//initiate sequence 2,4,6,1,3,5,2,6,2,4 on leds
			led2 = 0;						
			delay(1);
			led2 = 1;
			led4 = 0;
			delay(1);
			led4 = 1;
			led6 = 0;
			delay(1);
			led6 = 1;
			led1 = 0;
			delay(1);
			led1 = 1;
			led3 = 0;
			delay(1);
			led3 = 1;
			led5 = 0;
			delay(1);
			led5 = 1;
			led2 = 0;						
			delay(1);
			led2 = 1;
			led6 = 0;
			delay(1);
			led6 = 1;
			led2 = 0;
			delay(1);
			led2 = 1;
			led4 = 0;
			delay(1);
			led4 = 1;
			
			delay(1);
			led7 = 0;						//light led to show SW7 needs to be pressed to end entered sequence
			
			while(1)
			{												//if switches pressed, store entered sequence into character array
				if(SW2 == 0)
				{
					verify2[0] = '2';
				}
					
				if(SW4 == 0)
				{
					verify2[1] = '4';
				}
				
				if(SW6 == 0)
				{
					verify2[2] = '6';
				}
					
				if(SW1 == 0)
				{
					verify2[3] = '1';
				}
					
				if(SW3 == 0)
				{
					verify2[4] = '3';
				}
					
				if(SW5 == 0)
				{
					verify2[5] = '5';
				}
				
				if(SW2 == 0)
				{
					verify2[6] = '2';
				}
				
				if(SW6 == 0)
				{
					verify2[7] = '6';
				}
				
				if(SW2 == 0)
				{
					verify2[8] = '2';
				}
				
				if(SW4 == 0)
				{
					verify2[9] = '4';
				}
					
				if(SW7 == 0)
				{
					led7 = 1;
					verifySeq2();
				}					
			}		
		}					
	}
}	


void verifySeq1()								//compare sequences entered with those programmed/ouput - mode1
{
	for(j = 0; j < 6; j++)
	{
		if(seq1[j] == verify1[j])
			w = w + 1;
	}
	
	if(w == 6)
		youWon();
	
	if(w != 6)
		youLost();
}


void verifySeq2()								//compare sequences entered with those programmed/ouput - mode2
{
	for(l = 0; l < 10; l++)
	{
		if(seq2[l] == verify2[l])
			w2 = w2 + 1;
	}
	
	if(w2 == 10)
		youWon();
	
	if(w != 10)
		youLost();
}


void youWon()							// exe if user wins
{
	led8 = 1;								//clear mode leds
	led9 = 1;
	serialD("You Win!!!\r\n");
	starWars();
	win = 0;
	checkModeSW();
}

void youLost()						//exe if user loses
{
	discNoLed(A3, 700);
	serialD("You Lose!!!\r\n");
	checkModeSW();
}


void starWars()							//Star Wars Tune
{	
	resetLed();
	serialD("Star Wars\r\n");
	discreteW(C5, 700);
	discreteW(G5, 700);
	discreteW(F4, 220);
	discreteW(E4, 220);
	discreteW(D4, 220);
	discreteW(C6, 1100);
	
	discreteW(G5, 750);
	discreteW(F4, 220);
	discreteW(E4, 220);
	discreteW(D4, 220);
	discreteW(C6, 1100);
	
	discreteW(G5, 750);
	discreteW(F4, 220);
	discreteW(E4, 220);
	discreteW(F4, 220);
	discreteW(D4, 800); 
}


void twinkle()											// twinkle twinkle little star tune
{
	resetLed();
	serialD("Twinkle Twinkle Little Star\r\n");
	discreteW(C4, 400);
	delay(0.95);
	
	discreteW(C4, 400);
	delay(0.95);
	
	discreteW(G4, 400);
	delay(0.95);
	
	discreteW(G4, 400);
	delay(0.95);
	
	discreteW(A4, 400);
	delay(0.95);
	
	discreteW(A4, 400);
	delay(0.95);
	
	discreteW(G4, 400);
	delay(0.95);

	checkModeSW();			// (jumps back to monitoring switches for mode input)
		
}


void jingleBells()			// jingle bells tune
{
	resetLed();
	serialD("Jingle Bells\r\n");
	discreteW(E4, 400);
	delay(.85);
	
	discreteW(E4, 400);
	delay(.85);
	
	discreteW(E4, 400);
	delay(1);
	
	discreteW(E4, 400);
	delay(.85);
	
	discreteW(E4, 400);
	delay(.85);
	
	discreteW(E4, 400);
	delay(1);
	
	discreteW(E4, 400);
	delay(.85);
	
	discreteW(G4, 400);
	delay(.85);
	
	discreteW(C4, 400);
	delay(.85);
	
	discreteW(D4, 400);
	delay(.85);
	
	discreteW(E4, 400);
	delay(.85);

	checkModeSW();			// (jumps back to monitoring switches for mode input)
		
}


void noteLights(level)						// dispays leds according to note frequency level
{																	// on simon board and breadboard
		led7 = 1;
		led8 = 1;
		led5 = 1;
		led9 = 1;
		led6 = 1; 
		led3 = 1;
	
		if(level > 4701)							// low note
		{
			EXTLED1 = 0;								// led1 on breadboard
			led7 = 0;										// simon leds
		}
			
		if (level >= 1765 && level <= 4700)	// mid range note
		{
			EXTLED2 = 0;								// led2 and led3 on breadboard
			led8 = 0;										// simon leds										
			led5 = 0;
		}
		
		if(level <= 1764)							// high note
		{
			EXTLED3 = 0;								// led4,5,6 on breadboard
			led9 = 0;										// simon leds
			led6 = 0;
			led3 = 0;
		}
}

void discNoLed(D2, loop2)				// generates wave for specified note and interval
{
	for(i = 0; i < loop2;)
	{
		i = i + 1;
		speaker = ~speaker;
		period0(D2);
	}
		
	loop2 = 0;
}

void discreteW(D, loop)				// generates wave for specified note and interval
{

	for(i = 0; i < loop;)
	{
		if(SW7 == 0)
		{
			delay(1);
			checkModeSW();
		}
			
		i = i + 1;
		speaker = ~speaker;
		noteLights(D);						
		period0(D);
		
		EXTLED1 = 1;							// clear all leds on breadboard and simon board
		EXTLED2 = 1;
		EXTLED3 = 1;
		
		led9 = 1;									
		led6 = 1;
		led3 = 1;
		led8 = 1;
		led5 = 1;
		led7 = 1;
		
	}
		
	loop = 0;
}


void period0(N)						//period for square wave - used for discreteW() fn
{
		TMOD = 0x01;					//timer 0 16 bitmode
		TH0 = -(N) >> 8;
		TL0 = -(N);
		TR0 = 1;
		while(!TF0);
		TR0 = 0;
		TF0 = 0;
}


void timer1ISR()	interrupt 3			// ISR for timer 1 to toggle speaker port
{																	// generates continuous square wave
	speaker = ~speaker;
}


void period1(MC)						//period for continuous square wave
{
		TMOD = 0x10;					//timer 1 16 bitmode
		TH1 = -(MC) >> 8;
		TL1 = -(MC);
		TR1 = 1;
		while(!TF1);
		TR1 = 0;
		TF1 = 0;
}

void delay(num)																			// delay function, input = 1 * 100 will delay 1 second
{
	del = (num*100);
	for(k = 0; k < del; k++)
	{
		TMOD = 0x01;						//timer 0 16 bitmode
		TH0 = -36865 >> 8;
		TL0 = -36865;
		TR0 = 1;
		while(!TF0);
		TR0 = 0;
		TF0 = 0;
	}
}

void resetLed()
{
	led1 = 1;
	led2 = 1;
	led3 = 1;
	led4 = 1;
	led5 = 1;
	led6 = 1;
	led7 = 1;
	led8 = 1;
	led9 = 1;
}


void serialD(char str[])						//Transmit string function 
{
	for(p=0; str[p] != '\0' ; p++)
	{
		uart_transmit(str[p]);					//transmits string, 1 bit at a time until there is nothing left in the string
	}
}


void main()
{
	IEN0 = 0x88;							//enable interrupts
	IP0 = 0x08;								//timer 1 high priority 

	/*P2M1=0;									// set ports to bi-directional
	P1M1=0x2F&P1M1;
	P0M1=0;*/
	
	uart_init();							// initialize uart fn (from uart.c)
	
	P2M1 = 0x00;
	P2M2 = 0x00;
	P1M1 = 0x00;
	P1M2 = 0x00;
	P0M1 = 0x00;
	P0M2 = 0x00;
	
	SW1 = 1;									//make SW1 - SW9 as input
	SW2 = 1;
	SW3 = 1;
	SW4 = 1;
	SW5 = 1;
	SW6 = 1;
	SW7 = 1; 
	SW8 = 1; 
	SW9 = 1; 					
	
	serialD("The Simon2 Board is ready for you to choose a mode!\r\n");
	serialD("Press SW7 at any time to jump to main menu\r\n");
	serialD("SW4: Skylar's Song\r\n");
	serialD("SW5: Curtis's Function\r\n");
	serialD("SW6: Luke's Game\r\n");
	serialD("SW7: Jingle Bells\r\n");
	serialD("SW8: Twinkle Twinkle Little Star\r\n");
	serialD("SW9: 6 Note Keyboard\r\n");
	
	while(1)
	{
		checkModeSW();				//check mode switches continuously
	}
}