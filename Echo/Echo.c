/* Required Header Files */
#include <avr/io.h>
//#include "Lib/lcd.c"


/* PIN Connections */


/* Some Basic Macros */
#define output_low(port,pin) port &= ~(1<<pin)
#define output_high(port,pin) port |= (1<<pin)
#define set_input(portdir,pin) portdir &= ~(1<<pin)
#define set_output(portdir,pin) portdir |= (1<<pin)

#define KEYPAD A  //KEYPAD IS ATTACHED ON PORTA

//Don't Touch the lines below
//*******************************
#define KEYPAD_PORT PORTA
#define KEYPAD_DDR   DDRA
#define KEYPAD_PIN   PINA
//*******************************

/*******************************************
    Function return the keycode of keypressed
    on the Keypad. Keys are numbered as follows

    [00] [01] [02]
    [03] [04] [05]
    [06] [07] [08]
    [09] [10] [11]

   Arguments:
      None

   Return:
      Any number between 0-11 depending on
      keypressed.

      255 (hex 0xFF) if NO keypressed.

   Precondition:
      None. Can be called without any setup.

   *******************************************/
   
/* IMPPORTANT: CHECK THE CODE COMPATIBILITY FOR 4X4 */
uint8_t GetKeyPressed(void)
{
  uint8_t r,c;

  KEYPAD_PORT|= 0X0F;	

  for(c=0;c<4;c++)		// ? c<3
  {
	 KEYPAD_DDR&=~(0XFF);	// ? 7F
	 KEYPAD_DDR|=(0X80>>c);	// ? 40 
	 for(r=0;r<4;r++)
	 {
		if(!(KEYPAD_PIN & (0X08>>r)))
		{
		   return (r*4+c);	// ? 4
		}
	 }
  }

  return 0XFF;//Indicate No key pressed
}

int main(void) 
{
	/* Initializing the LCD module */
//	InitLCD(LS_BLINK|LS_ULINE);
	
	/* Displaying the Home Screen */
//    LCDWriteString("S-Nav has begun!");
    DDRD=0X0F;
    while(1)
    {
        switch(GetKeyPressed()/4)
        {
        case 0:
            PORTD=0X01
            break;
        case 1:
            PORTD=0X02
            break;
        case 2:
            PORTD=0X04
            break;
        case 3:
            PORTD=0X08
            break;
        }
    }


}
