/* GBA development header for AG0700, based on:
 * gba.h by eloist
 *
 * If you have additions or corrections to this header, please send
 * them to Adam Sampson <a.sampson@abertay.ac.uk>.
 */

#ifndef GBA_H
#define GBA_H

#include <stdint.h>

#define REGISTER_PTR(type, addr) ((volatile type *) addr)
#define REGISTER(type, addr) (*REGISTER_PTR(type, addr))

// Video memory addresses

#define REG_PALETTE_BG       REGISTER_PTR(uint16_t, 0x5000000)
#define REG_PALETTE_OBJ      REGISTER_PTR(uint16_t, 0x5000200)
#define REG_VIDEO_BASE       REGISTER_PTR(uint16_t, 0x6000000)
#define REG_VIDEO_PAGE1      REGISTER_PTR(uint16_t, 0x6000000)
#define REG_VIDEO_PAGE2      REGISTER_PTR(uint16_t, 0x600A000)

//#define OAMmem (uint32_t*)0x7000000
//#define OAMdata (uint16_t*)0x6100000

// General registers

#define REG_INTERUPT         REGISTER(uint32_t, 0x3007FFC)
#define REG_DISPCNT          REGISTER(uint32_t, 0x4000000)
#define REG_DISPCNT_L        REGISTER(uint16_t, 0x4000000)
#define REG_DISPCNT_H        REGISTER(uint16_t, 0x4000002)
#define REG_DISPSTAT         REGISTER(uint16_t, 0x4000004)
#define REG_VCOUNT           REGISTER(uint16_t, 0x4000006)
#define REG_BG0CNT           REGISTER(uint16_t, 0x4000008)
#define REG_BG1CNT           REGISTER(uint16_t, 0x400000A)
#define REG_BG2CNT           REGISTER(uint16_t, 0x400000C)
#define REG_BG3CNT           REGISTER(uint16_t, 0x400000E)
#define REG_BG0HOFS          REGISTER(uint16_t, 0x4000010)
#define REG_BG0VOFS          REGISTER(uint16_t, 0x4000012)
#define REG_BG1HOFS          REGISTER(uint16_t, 0x4000014)
#define REG_BG1VOFS          REGISTER(uint16_t, 0x4000016)
#define REG_BG2HOFS          REGISTER(uint16_t, 0x4000018)
#define REG_BG2VOFS          REGISTER(uint16_t, 0x400001A)
#define REG_BG3HOFS          REGISTER(uint16_t, 0x400001C)
#define REG_BG3VOFS          REGISTER(uint16_t, 0x400001E)
#define REG_BG2PA            REGISTER(uint16_t, 0x4000020)
#define REG_BG2PB            REGISTER(uint16_t, 0x4000022)
#define REG_BG2PC            REGISTER(uint16_t, 0x4000024)
#define REG_BG2PD            REGISTER(uint16_t, 0x4000026)
#define REG_BG2X             REGISTER(uint32_t, 0x4000028)
#define REG_BG2X_L           REGISTER(uint16_t, 0x4000028)
#define REG_BG2X_H           REGISTER(uint16_t, 0x400002A)
#define REG_BG2Y             REGISTER(uint32_t, 0x400002C)
#define REG_BG2Y_L           REGISTER(uint16_t, 0x400002C)
#define REG_BG2Y_H           REGISTER(uint16_t, 0x400002E)
#define REG_BG3PA            REGISTER(uint16_t, 0x4000030)
#define REG_BG3PB            REGISTER(uint16_t, 0x4000032)
#define REG_BG3PC            REGISTER(uint16_t, 0x4000034)
#define REG_BG3PD            REGISTER(uint16_t, 0x4000036)
#define REG_BG3X             REGISTER(uint32_t, 0x4000038)
#define REG_BG3X_L           REGISTER(uint16_t, 0x4000038)
#define REG_BG3X_H           REGISTER(uint16_t, 0x400003A)
#define REG_BG3Y             REGISTER(uint32_t, 0x400003C)
#define REG_BG3Y_L           REGISTER(uint16_t, 0x400003C)
#define REG_BG3Y_H           REGISTER(uint16_t, 0x400003E)
#define REG_WIN0H            REGISTER(uint16_t, 0x4000040)
#define REG_WIN1H            REGISTER(uint16_t, 0x4000042)
#define REG_WIN0V            REGISTER(uint16_t, 0x4000044)
#define REG_WIN1V            REGISTER(uint16_t, 0x4000046)
#define REG_WININ            REGISTER(uint16_t, 0x4000048)
#define REG_WINOUT           REGISTER(uint16_t, 0x400004A)
#define REG_MOSAIC           REGISTER(uint32_t, 0x400004C)
#define REG_MOSAIC_L         REGISTER(uint32_t, 0x400004C)
#define REG_MOSAIC_H         REGISTER(uint32_t, 0x400004E)
#define REG_BLDMOD           REGISTER(uint16_t, 0x4000050)
#define REG_COLEV            REGISTER(uint16_t, 0x4000052)
#define REG_COLEY            REGISTER(uint16_t, 0x4000054)
#define REG_SG10             REGISTER(uint32_t, 0x4000060)
#define REG_SG10_L           REGISTER(uint16_t, 0x4000060)
#define REG_SG10_H           REGISTER(uint16_t, 0x4000062)
#define REG_SG11             REGISTER(uint16_t, 0x4000064)
#define REG_SG20             REGISTER(uint16_t, 0x4000068)
#define REG_SG21             REGISTER(uint16_t, 0x400006C)
#define REG_SG30             REGISTER(uint32_t, 0x4000070)
#define REG_SG30_L           REGISTER(uint16_t, 0x4000070)
#define REG_SG30_H           REGISTER(uint16_t, 0x4000072)
#define REG_SG31             REGISTER(uint16_t, 0x4000074)
#define REG_SG40             REGISTER(uint16_t, 0x4000078)
#define REG_SG41             REGISTER(uint16_t, 0x400007C)
#define REG_SGCNT0           REGISTER(uint32_t, 0x4000080)
#define REG_SGCNT0_L         REGISTER(uint16_t, 0x4000080)
#define REG_SGCNT0_H         REGISTER(uint16_t, 0x4000082)
#define REG_SGCNT1           REGISTER(uint16_t, 0x4000084)
#define REG_SGBIAS           REGISTER(uint16_t, 0x4000088)
#define REG_SGWR0            REGISTER(uint32_t, 0x4000090)
#define REG_SGWR0_L          REGISTER(uint16_t, 0x4000090)
#define REG_SGWR0_H          REGISTER(uint16_t, 0x4000092)
#define REG_SGWR1            REGISTER(uint32_t, 0x4000094)
#define REG_SGWR1_L          REGISTER(uint16_t, 0x4000094)
#define REG_SGWR1_H          REGISTER(uint16_t, 0x4000096)
#define REG_SGWR2            REGISTER(uint32_t, 0x4000098)
#define REG_SGWR2_L          REGISTER(uint16_t, 0x4000098)
#define REG_SGWR2_H          REGISTER(uint16_t, 0x400009A)
#define REG_SGWR3            REGISTER(uint32_t, 0x400009C)
#define REG_SGWR3_L          REGISTER(uint16_t, 0x400009C)
#define REG_SGWR3_H          REGISTER(uint16_t, 0x400009E)
#define REG_SGFIF0A          REGISTER(uint32_t, 0x40000A0)
#define REG_SGFIFOA_L        REGISTER(uint16_t, 0x40000A0)
#define REG_SGFIFOA_H        REGISTER(uint16_t, 0x40000A2)
#define REG_SGFIFOB          REGISTER(uint32_t, 0x40000A4)
#define REG_SGFIFOB_L        REGISTER(uint16_t, 0x40000A4)
#define REG_SGFIFOB_H        REGISTER(uint16_t, 0x40000A6)
#define REG_DM0SAD           REGISTER(uint32_t, 0x40000B0)
#define REG_DM0SAD_L         REGISTER(uint16_t, 0x40000B0)
#define REG_DM0SAD_H         REGISTER(uint16_t, 0x40000B2)
#define REG_DM0DAD           REGISTER(uint32_t, 0x40000B4)
#define REG_DM0DAD_L         REGISTER(uint16_t, 0x40000B4)
#define REG_DM0DAD_H         REGISTER(uint16_t, 0x40000B6)
#define REG_DM0CNT           REGISTER(uint32_t, 0x40000B8)
#define REG_DM0CNT_L         REGISTER(uint16_t, 0x40000B8)
#define REG_DM0CNT_H         REGISTER(uint16_t, 0x40000BA)
#define REG_DM1SAD           REGISTER(uint32_t, 0x40000BC)
#define REG_DM1SAD_L         REGISTER(uint16_t, 0x40000BC)
#define REG_DM1SAD_H         REGISTER(uint16_t, 0x40000BE)
#define REG_DM1DAD           REGISTER(uint32_t, 0x40000C0)
#define REG_DM1DAD_L         REGISTER(uint16_t, 0x40000C0)
#define REG_DM1DAD_H         REGISTER(uint16_t, 0x40000C2)
#define REG_DM1CNT           REGISTER(uint32_t, 0x40000C4)
#define REG_DM1CNT_L         REGISTER(uint16_t, 0x40000C4)
#define REG_DM1CNT_H         REGISTER(uint16_t, 0x40000C6)
#define REG_DM2SAD           REGISTER(uint32_t, 0x40000C8)
#define REG_DM2SAD_L         REGISTER(uint16_t, 0x40000C8)
#define REG_DM2SAD_H         REGISTER(uint16_t, 0x40000CA)
#define REG_DM2DAD           REGISTER(uint32_t, 0x40000CC)
#define REG_DM2DAD_L         REGISTER(uint16_t, 0x40000CC)
#define REG_DM2DAD_H         REGISTER(uint16_t, 0x40000CE)
#define REG_DM2CNT           REGISTER(uint32_t, 0x40000D0)
#define REG_DM2CNT_L         REGISTER(uint16_t, 0x40000D0)
#define REG_DM2CNT_H         REGISTER(uint16_t, 0x40000D2)
#define REG_DM3SAD           REGISTER(uint32_t, 0x40000D4)
#define REG_DM3SAD_L         REGISTER(uint16_t, 0x40000D4)
#define REG_DM3SAD_H         REGISTER(uint16_t, 0x40000D6)
#define REG_DM3DAD           REGISTER(uint32_t, 0x40000D8)
#define REG_DM3DAD_L         REGISTER(uint16_t, 0x40000D8)
#define REG_DM3DAD_H         REGISTER(uint16_t, 0x40000DA)
#define REG_DM3CNT           REGISTER(uint32_t, 0x40000DC)
#define REG_DM3CNT_L         REGISTER(uint16_t, 0x40000DC)
#define REG_DM3CNT_H         REGISTER(uint16_t, 0x40000DE)
#define REG_TM0D             REGISTER(uint16_t, 0x4000100)
#define REG_TM0CNT           REGISTER(uint16_t, 0x4000102)
#define REG_TM1D             REGISTER(uint16_t, 0x4000104)
#define REG_TM1CNT           REGISTER(uint16_t, 0x4000106)
#define REG_TM2D             REGISTER(uint16_t, 0x4000108)
#define REG_TM2CNT           REGISTER(uint16_t, 0x400010A)
#define REG_TM3D             REGISTER(uint16_t, 0x400010C)
#define REG_TM3CNT           REGISTER(uint16_t, 0x400010E)
#define REG_SCD0             REGISTER(uint16_t, 0x4000120)
#define REG_SCD1             REGISTER(uint16_t, 0x4000122)
#define REG_SCD2             REGISTER(uint16_t, 0x4000124)
#define REG_SCD3             REGISTER(uint16_t, 0x4000126)
#define REG_SCCNT            REGISTER(uint32_t, 0x4000128)
#define REG_SCCNT_L          REGISTER(uint16_t, 0x4000128)
#define REG_SCCNT_H          REGISTER(uint16_t, 0x400012A)
#define REG_P1               REGISTER(uint16_t, 0x4000130)
#define REG_P1CNT            REGISTER(uint16_t, 0x4000132)
#define REG_R                REGISTER(uint16_t, 0x4000134)
#define REG_HS_CTRL          REGISTER(uint16_t, 0x4000140)
#define REG_JOYRE            REGISTER(uint32_t, 0x4000150)
#define REG_JOYRE_L          REGISTER(uint16_t, 0x4000150)
#define REG_JOYRE_H          REGISTER(uint16_t, 0x4000152)
#define REG_JOYTR            REGISTER(uint32_t, 0x4000154)
#define REG_JOYTR_L          REGISTER(uint16_t, 0x4000154)
#define REG_JOYTR_H          REGISTER(uint16_t, 0x4000156)
#define REG_JSTAT            REGISTER(uint32_t, 0x4000158)
#define REG_JSTAT_L          REGISTER(uint16_t, 0x4000158)
#define REG_JSTAT_H          REGISTER(uint16_t, 0x400015A)
#define REG_IE               REGISTER(uint16_t, 0x4000200)
#define REG_IF               REGISTER(uint16_t, 0x4000202)
#define REG_WSCNT            REGISTER(uint16_t, 0x4000204)
#define REG_IME              REGISTER(uint16_t, 0x4000208)
#define REG_PAUSE            REGISTER(uint16_t, 0x4000300)

// Graphics constants

#define SCREEN_WIDTH         240
#define SCREEN_HEIGHT        160

// Flags in REG_DISPCNT

#define BG2_ENABLE           0x400

#define MODE0                0x0
#define MODE1                0x1
#define MODE2                0x2
#define MODE3                0x3
#define MODE4                0x4
#define MODE5                0x5

#define DCNT_PAGE            0x10

// Key bits (in REG_P1)

#define KEY_A                1
#define KEY_B                2
#define KEY_SELECT           4
#define KEY_START            8
#define KEY_RIGHT            16
#define KEY_LEFT             32
#define KEY_UP               64
#define KEY_DOWN             128
#define KEY_R                256
#define KEY_L                512

// DMA flags (untested -- probably broken)

// Enable DMA operation
#define DMACNT_ENABLE        ((1 << 31) & (0x80000000))
// Increment Destination after copy
#define DMACNT_INCDEST       (0)
// Decrement Destination after copy
#define DMACNT_DECDEST       ((1 << 21) & (0x200000))
// Leave Destination unchanged after copy
#define DMACNT_FIXDEST       ((1 << 22) & (0x400000))
// Increment Source after copy
#define DMACNT_INCSRC        (0)
// Decrement Source after copy
#define DMACNT_DECSRC        ((1 << 23) & (0x800000))
// Leave Source unchanged after copy
#define DMACNT_FIXSRC        ((1 << 24) & (0x1000000))
// Copy 32 bits at a time
#define DMACNT_32BIT         ((1 << 26) & (0x4000000))
// Copy 16 bits at a time
#define DMACNT_16BIT         (0)

// Prototypes for things in gba.cpp

// The 8bpp display we're currently drawing to
extern volatile uint16_t *BackBuffer;

// Wait for the start of the next video frame
void WaitVSync();

// Swap the front and back buffers.
// (If page-flipping is not already in use, this will enable it.)
void FlipBuffers();

// Clear the screen in an 8bpp mode
void ClearScreen8(uint8_t colour);

// Clear the screen in a 16bpp mode
void ClearScreen16(uint16_t colour);

// Graphics utility functions (short enough to be worth inlining)

// Construct an RGB colour value
static inline uint16_t RGB(uint16_t r, uint16_t g, uint16_t b)
{
	return (b << 10) | (g << 5) | r;
}

// Plot a pixel on the background in a 16bpp mode
static inline void PlotPixel16(int x, int y, uint16_t colour)
{
	// FIXME: check x, y in bounds
	REG_VIDEO_BASE[y * SCREEN_WIDTH + x] = colour;
}

// Get the colour of a pixel on the background in a 16bpp mode
static inline uint16_t GetPixel16(int x, int y)
{
	return REG_VIDEO_BASE[y * SCREEN_WIDTH + x];
}

// Plot a pixel on the background in an 8bpp mode
static inline void PlotPixel8(int x, int y, uint8_t colour)
{
	// FIXME: check x, y in bounds
	volatile uint16_t& pixel(BackBuffer[(y * SCREEN_WIDTH + x) / 2]);
	if (x % 2 == 0)
	{
		pixel = (pixel & 0xFF00) | colour;
	}
	else
	{
		pixel = (pixel & 0x00FF) | (colour << 8);
	}
}

// Get the colour of a pixel on the background in an 8bpp mode
static inline uint8_t GetPixel8(int x, int y)
{
	volatile uint16_t& pixel(BackBuffer[(y * SCREEN_WIDTH + x) / 2]);
	if (x % 2 == 0)
	{
		return pixel & 0xFF;
	}
	else
	{
		return (pixel >> 8) & 0xFF;
	}
}

// Set a background palette colour
static inline void SetPaletteBG(uint8_t entry, uint16_t colour)
{
	REG_PALETTE_BG[entry] = colour;
}

// Get a background palette colour
static inline uint16_t GetPaletteBG(uint8_t entry)
{
	return REG_PALETTE_BG[entry];
}

#endif