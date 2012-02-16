/* GBA development library for AG0700
 *
 * If you have additions or corrections to this code, please send
 * them to Adam Sampson <a.sampson@abertay.ac.uk>.
 */

#include "gba.h"

volatile uint16_t *BackBuffer = REG_VIDEO_PAGE1;

void WaitVSync()
{
	while(REG_VCOUNT >= 160);   // wait till VDraw
	while(REG_VCOUNT < 160);    // wait till VBlank
}

void FlipBuffers()
{
	// Toggle the DCNT_PAGE bit to show the other page
	uint32_t new_dispcnt = REG_DISPCNT ^ DCNT_PAGE;
	REG_DISPCNT = new_dispcnt;
	
	if (new_dispcnt & DCNT_PAGE)
	{
		// We're now showing the second page -- make the first the back buffer
		BackBuffer = REG_VIDEO_PAGE1;
	}
	else
	{
		// Vice versa
		BackBuffer = REG_VIDEO_PAGE2;
	}
}

void ClearScreen8(uint8_t colour)
{
	// Set up a 32-bit value containing four pixels in the right colour.
	uint32_t value = (colour << 24) | (colour << 16) | (colour << 8) | colour;

	// Fill the display by writing 32 bits at a time.
	volatile uint32_t *p = (volatile uint32_t *) BackBuffer;
	int count = (240 * 160) / 4;
	while (--count > 0)
	{
		*p++ = value;
	}
}

void ClearScreen16(uint16_t colour)
{
	// Set up a 32-bit value containing two pixels in the right colour.
	uint32_t value = (colour << 16) | colour;

	// Fill the display by writing 32 bits at a time.
	volatile uint32_t *p = (volatile uint32_t *) REG_VIDEO_BASE;
	int count = (240 * 160) / 2;
	while (--count > 0)
	{
		*p++ = value;
	}
}