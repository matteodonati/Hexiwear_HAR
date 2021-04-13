/**
 *	Libraries.
 */

/* Inclusion of Hexi_OLED_SSD1351.h. */
#include "Hexi_OLED_SSD1351.h"

/* Inclusion of stdint.h. */
#include "stdint.h"


/**
 *	Variables declaration.
 */

/* SSD1351 object. */
extern SSD1351 oled;


/**
 *	Function declaration.
 */
 
/* Function that initializes the display. */
void init_oled();

/* Function that prints an image. */
void print_image(const uint8_t*, int8_t, int8_t);

/* Function that prints a text line. */
void print_text(char*, int8_t, int8_t, uint8_t, uint8_t);