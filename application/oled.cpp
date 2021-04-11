/**
 *	Libraries
 */
 
/* Inclusion of oled.h. */
#include "oled.h"


/**
 *	Variables definition.
 */
 
/* SSD1351 object. */
SSD1351 oled(PTB22, PTB21, PTC13, PTB20, PTE6, PTD15);


/**
 *	Functions definition.
 */

/* init_oled function that initializes the display. */
void init_oled()
{	
	/* Set the text properties. */
	oled.SetTextProperties(OLED_TEXT_ALIGN_CENTER);
 
    /* Set the background color to black. */
    oled.FillScreen(COLOR_BLACK);
}

/* print_image function that prints an image. */
void print_image(const uint8_t* image, int8_t x, int8_t y)
{
	/* Print the image. */
	oled.DrawImage(image, x, y);
}

/* print_text function that prints a text line. */
void print_text(char* text, int8_t x, int8_t y, uint8_t width, uint8_t height)
{
	/* Print the text. */
	oled.TextBox((uint8_t*)text, x, y, width, height);
}