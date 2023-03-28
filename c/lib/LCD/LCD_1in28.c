/*****************************************************************************
* | File        :   LCD_1in28.c
* | Author      :   Waveshare team, Julianno F. C. Silva (@juliannojungle)
* | Function    :   Hardware underlying interface
* | Info        :
*                Used to shield the underlying layers of each master
*                and enhance portability
*----------------
* | This version:   V1.0
* | Date        :   2023-03-26
* | Info        :   Basic version
*
******************************************************************************/
#include "LCD_1in28.h"
#include "DEV_Config.h"

#include <stdlib.h> //itoa()
#include <stdio.h>

LCD_1IN28_ATTRIBUTES LCD_1IN28;

/******************************************************************************
function :  Hardware reset
parameter:
******************************************************************************/
static void LCD_1IN28_Reset(void)
{
    DEV_Digital_Write(EPD_RST_PIN, 1);
    DEV_Delay_ms(100);
    DEV_Digital_Write(EPD_RST_PIN, 0);
    DEV_Delay_ms(100);
    DEV_Digital_Write(EPD_RST_PIN, 1);
    DEV_Delay_ms(100);
}

/******************************************************************************
function : send command
parameter:
     Reg : Command register
******************************************************************************/
static void LCD_1IN28_SendCommand(UBYTE Reg)
{
    DEV_Digital_Write(EPD_DC_PIN, 0);
    DEV_Digital_Write(EPD_CS_PIN, 0);
    DEV_SPI_WriteByte(Reg);
    DEV_Digital_Write(EPD_CS_PIN, 1);
}

/******************************************************************************
function : send data
parameter:
    Data : Write data
******************************************************************************/
static void LCD_1IN28_SendData_8Bit(UBYTE Data)
{
    DEV_Digital_Write(EPD_DC_PIN, 1);
    DEV_Digital_Write(EPD_CS_PIN, 0);
    DEV_SPI_WriteByte(Data);
    DEV_Digital_Write(EPD_CS_PIN, 1);
}

/******************************************************************************
function : send data
parameter:
    Data : Write data
******************************************************************************/
static void LCD_1IN28_SendData_16Bit(UWORD Data)
{
    DEV_Digital_Write(EPD_DC_PIN, 1);
    DEV_Digital_Write(EPD_CS_PIN, 0);
    DEV_SPI_WriteByte((Data >> 8) & 0xFF);
    DEV_SPI_WriteByte(Data & 0xFF);
    DEV_Digital_Write(EPD_CS_PIN, 1);
}

/******************************************************************************
function : Initialize the lcd register
parameter:
******************************************************************************/
static void LCD_1IN28_InitReg(void)
{
    LCD_1IN28_SendCommand(0x11); /* Sleep mode OFF */

    DEV_Delay_ms(120); /* Delay 120ms */

    LCD_1IN28_SendCommand(0xEF); /* Inter register enable 2 */

    LCD_1IN28_SendCommand(0xEB);
    LCD_1IN28_SendData_8Bit(0x14);

    /* BEGIN set inter_command HIGH */
    LCD_1IN28_SendCommand(0xFE); /* Inter register enable 1 */
    LCD_1IN28_SendCommand(0xEF); /* Inter register enable 2 */
    /* END set inter_command HIGH */

    LCD_1IN28_SendCommand(0xEB);
    LCD_1IN28_SendData_8Bit(0x14);

    LCD_1IN28_SendCommand(0x84);
    LCD_1IN28_SendData_8Bit(0x40);

    LCD_1IN28_SendCommand(0x85);
    LCD_1IN28_SendData_8Bit(0xFF);

    LCD_1IN28_SendCommand(0x86);
    LCD_1IN28_SendData_8Bit(0xFF);

    LCD_1IN28_SendCommand(0x87);
    LCD_1IN28_SendData_8Bit(0xFF);

    LCD_1IN28_SendCommand(0x88);
    LCD_1IN28_SendData_8Bit(0x0A);

    LCD_1IN28_SendCommand(0x89);
    LCD_1IN28_SendData_8Bit(0x21);

    LCD_1IN28_SendCommand(0x8A);
    LCD_1IN28_SendData_8Bit(0x00);

    LCD_1IN28_SendCommand(0x8B);
    LCD_1IN28_SendData_8Bit(0x80);

    LCD_1IN28_SendCommand(0x8C);
    LCD_1IN28_SendData_8Bit(0x01);

    LCD_1IN28_SendCommand(0x8D);
    LCD_1IN28_SendData_8Bit(0x01);

    LCD_1IN28_SendCommand(0x8E);
    LCD_1IN28_SendData_8Bit(0xFF);

    LCD_1IN28_SendCommand(0x8F);
    LCD_1IN28_SendData_8Bit(0xFF);

    /* Display function control */
    LCD_1IN28_SendCommand(0xB6);
    LCD_1IN28_SendData_8Bit(0x00);
    LCD_1IN28_SendData_8Bit(0x00);
    /* END Display function control */

    /* Memory access control - defined on LCD_1IN28_SetAttributes */
    // LCD_1IN28_SendCommand(0x36);
    // LCD_1IN28_SendData_8Bit(0x48);
    /* END Memory access control */

    /* Pixel format */
    LCD_1IN28_SendCommand(0x3A);
    LCD_1IN28_SendData_8Bit(0x05);
    /* END Pixel format */

    LCD_1IN28_SendCommand(0x90);
    LCD_1IN28_SendData_8Bit(0x08);
    LCD_1IN28_SendData_8Bit(0x08);
    LCD_1IN28_SendData_8Bit(0x08);
    LCD_1IN28_SendData_8Bit(0x08);

    LCD_1IN28_SendCommand(0xBD);
    LCD_1IN28_SendData_8Bit(0x06);

    LCD_1IN28_SendCommand(0xBC);
    LCD_1IN28_SendData_8Bit(0x00);

    LCD_1IN28_SendCommand(0xFF);
    LCD_1IN28_SendData_8Bit(0x60);
    LCD_1IN28_SendData_8Bit(0x01);
    LCD_1IN28_SendData_8Bit(0x04);

    /* Voltage regulator 1a */
    LCD_1IN28_SendCommand(0xC3);
    LCD_1IN28_SendData_8Bit(0x13);
    /* END Voltage regulator 1a */

    /* Voltage regulator 1b */
    LCD_1IN28_SendCommand(0xC4);
    LCD_1IN28_SendData_8Bit(0x13);
    /* END Voltage regulator 1b */

    /* Voltage regulator 2a */
    LCD_1IN28_SendCommand(0xC9);
    LCD_1IN28_SendData_8Bit(0x22);
    /* END Voltage regulator 2a */

    LCD_1IN28_SendCommand(0xBE);
    LCD_1IN28_SendData_8Bit(0x11);

    LCD_1IN28_SendCommand(0xE1);
    LCD_1IN28_SendData_8Bit(0x10);
    LCD_1IN28_SendData_8Bit(0x0E);

    LCD_1IN28_SendCommand(0xDF);
    LCD_1IN28_SendData_8Bit(0x21);
    LCD_1IN28_SendData_8Bit(0x0c);
    LCD_1IN28_SendData_8Bit(0x02);

    /* Set gamma1 */
    LCD_1IN28_SendCommand(0xF0);
    LCD_1IN28_SendData_8Bit(0x45);
    LCD_1IN28_SendData_8Bit(0x09);
    LCD_1IN28_SendData_8Bit(0x08);
    LCD_1IN28_SendData_8Bit(0x08);
    LCD_1IN28_SendData_8Bit(0x26);
    LCD_1IN28_SendData_8Bit(0x2A);
    /* END Set gamma1 */

    /* Set gamma2 */
    LCD_1IN28_SendCommand(0xF1);
    LCD_1IN28_SendData_8Bit(0x43);
    LCD_1IN28_SendData_8Bit(0x70);
    LCD_1IN28_SendData_8Bit(0x72);
    LCD_1IN28_SendData_8Bit(0x36);
    LCD_1IN28_SendData_8Bit(0x37);
    LCD_1IN28_SendData_8Bit(0x6F);
    /* END Set gamma2 */

    /* Set gamma3 */
    LCD_1IN28_SendCommand(0xF2);
    LCD_1IN28_SendData_8Bit(0x45);
    LCD_1IN28_SendData_8Bit(0x09);
    LCD_1IN28_SendData_8Bit(0x08);
    LCD_1IN28_SendData_8Bit(0x08);
    LCD_1IN28_SendData_8Bit(0x26);
    LCD_1IN28_SendData_8Bit(0x2A);
    /* END Set gamma3 */

    /* Set gamma4 */
    LCD_1IN28_SendCommand(0xF3);
    LCD_1IN28_SendData_8Bit(0x43);
    LCD_1IN28_SendData_8Bit(0x70);
    LCD_1IN28_SendData_8Bit(0x72);
    LCD_1IN28_SendData_8Bit(0x36);
    LCD_1IN28_SendData_8Bit(0x37);
    LCD_1IN28_SendData_8Bit(0x6F);
    /* END Set gamma4 */

    LCD_1IN28_SendCommand(0xED);
    LCD_1IN28_SendData_8Bit(0x1B);
    LCD_1IN28_SendData_8Bit(0x0B);

    LCD_1IN28_SendCommand(0xAE);
    LCD_1IN28_SendData_8Bit(0x77);

    LCD_1IN28_SendCommand(0xCD);
    LCD_1IN28_SendData_8Bit(0x63);

    LCD_1IN28_SendCommand(0x70);
    LCD_1IN28_SendData_8Bit(0x07);
    LCD_1IN28_SendData_8Bit(0x07);
    LCD_1IN28_SendData_8Bit(0x04);
    LCD_1IN28_SendData_8Bit(0x0E);
    LCD_1IN28_SendData_8Bit(0x0F);
    LCD_1IN28_SendData_8Bit(0x09);
    LCD_1IN28_SendData_8Bit(0x07);
    LCD_1IN28_SendData_8Bit(0x08);
    LCD_1IN28_SendData_8Bit(0x03);

    /* Frame rate */
    LCD_1IN28_SendCommand(0xE8);
    LCD_1IN28_SendData_8Bit(0x34);
    /* END Frame rate */

    LCD_1IN28_SendCommand(0x62);
    LCD_1IN28_SendData_8Bit(0x18);
    LCD_1IN28_SendData_8Bit(0x0D);
    LCD_1IN28_SendData_8Bit(0x71);
    LCD_1IN28_SendData_8Bit(0xED);
    LCD_1IN28_SendData_8Bit(0x70);
    LCD_1IN28_SendData_8Bit(0x70);
    LCD_1IN28_SendData_8Bit(0x18);
    LCD_1IN28_SendData_8Bit(0x0F);
    LCD_1IN28_SendData_8Bit(0x71);
    LCD_1IN28_SendData_8Bit(0xEF);
    LCD_1IN28_SendData_8Bit(0x70);
    LCD_1IN28_SendData_8Bit(0x70);

    LCD_1IN28_SendCommand(0x63);
    LCD_1IN28_SendData_8Bit(0x18);
    LCD_1IN28_SendData_8Bit(0x11);
    LCD_1IN28_SendData_8Bit(0x71);
    LCD_1IN28_SendData_8Bit(0xF1);
    LCD_1IN28_SendData_8Bit(0x70);
    LCD_1IN28_SendData_8Bit(0x70);
    LCD_1IN28_SendData_8Bit(0x18);
    LCD_1IN28_SendData_8Bit(0x13);
    LCD_1IN28_SendData_8Bit(0x71);
    LCD_1IN28_SendData_8Bit(0xF3);
    LCD_1IN28_SendData_8Bit(0x70);
    LCD_1IN28_SendData_8Bit(0x70);

    LCD_1IN28_SendCommand(0x64);
    LCD_1IN28_SendData_8Bit(0x28);
    LCD_1IN28_SendData_8Bit(0x29);
    LCD_1IN28_SendData_8Bit(0xF1);
    LCD_1IN28_SendData_8Bit(0x01);
    LCD_1IN28_SendData_8Bit(0xF1);
    LCD_1IN28_SendData_8Bit(0x00);
    LCD_1IN28_SendData_8Bit(0x07);

    LCD_1IN28_SendCommand(0x66);
    LCD_1IN28_SendData_8Bit(0x3C);
    LCD_1IN28_SendData_8Bit(0x00);
    LCD_1IN28_SendData_8Bit(0xCD);
    LCD_1IN28_SendData_8Bit(0x67);
    LCD_1IN28_SendData_8Bit(0x45);
    LCD_1IN28_SendData_8Bit(0x45);
    LCD_1IN28_SendData_8Bit(0x10);
    LCD_1IN28_SendData_8Bit(0x00);
    LCD_1IN28_SendData_8Bit(0x00);
    LCD_1IN28_SendData_8Bit(0x00);

    LCD_1IN28_SendCommand(0x67);
    LCD_1IN28_SendData_8Bit(0x00);
    LCD_1IN28_SendData_8Bit(0x3C);
    LCD_1IN28_SendData_8Bit(0x00);
    LCD_1IN28_SendData_8Bit(0x00);
    LCD_1IN28_SendData_8Bit(0x00);
    LCD_1IN28_SendData_8Bit(0x01);
    LCD_1IN28_SendData_8Bit(0x54);
    LCD_1IN28_SendData_8Bit(0x10);
    LCD_1IN28_SendData_8Bit(0x32);
    LCD_1IN28_SendData_8Bit(0x98);

    LCD_1IN28_SendCommand(0x74);
    LCD_1IN28_SendData_8Bit(0x10);
    LCD_1IN28_SendData_8Bit(0x85);
    LCD_1IN28_SendData_8Bit(0x80);
    LCD_1IN28_SendData_8Bit(0x00);
    LCD_1IN28_SendData_8Bit(0x00);
    LCD_1IN28_SendData_8Bit(0x4E);
    LCD_1IN28_SendData_8Bit(0x00);

    LCD_1IN28_SendCommand(0x98);
    LCD_1IN28_SendData_8Bit(0x3e);
    LCD_1IN28_SendData_8Bit(0x07);

    LCD_1IN28_SendCommand(0x35); /* Tearing effect ON */

    LCD_1IN28_SendCommand(0x21); /* Display color inversion ON */

    LCD_1IN28_SendCommand(0x11); /* Sleep mode OFF */

    DEV_Delay_ms(12); /* Delay 12ms */

    LCD_1IN28_SendCommand(0x29); /* Display ON */

    DEV_Delay_ms(20); /* Delay 20ms */
}

/********************************************************************************
function: Set the resolution and scanning method of the screen
parameter:
    Scan_dir:   Scan direction
********************************************************************************/
static void LCD_1IN28_SetAttributes(UBYTE Scan_dir)
{
    //Get the screen scan direction
    LCD_1IN28.SCAN_DIR = Scan_dir;
    UBYTE MemoryAccessReg = 0x00;

    //Get GRAM and LCD width and height
    if(Scan_dir == HORIZONTAL) {
        LCD_1IN28.HEIGHT = LCD_1IN28_WIDTH;
        LCD_1IN28.WIDTH = LCD_1IN28_HEIGHT;
        MemoryAccessReg = 0x48;
    } else {
        LCD_1IN28.HEIGHT = LCD_1IN28_HEIGHT;
        LCD_1IN28.WIDTH = LCD_1IN28_WIDTH;
        MemoryAccessReg = 0x24;
    }

    // Set the read / write scan direction of the frame memory
    LCD_1IN28_SendCommand(0x36); //MX, MY, RGB mode
    LCD_1IN28_SendData_8Bit(MemoryAccessReg); //0x08 set RGB
}

/********************************************************************************
function : Initialize the lcd
parameter:
********************************************************************************/
void LCD_1IN28_Init(UBYTE Scan_dir)
{
    DEV_SET_PWM(90);
    //Hardware reset
    LCD_1IN28_Reset();

    //Set the resolution and scanning method of the screen
    LCD_1IN28_SetAttributes(Scan_dir);

    //Set the initialization register
    LCD_1IN28_InitReg();
}

/********************************************************************************
function: Sets the start position and size of the display area
parameter:
    Xstart: X direction Start coordinates
    Ystart: Y direction Start coordinates
    Xend  : X direction end coordinates
    Yend  : Y direction end coordinates
********************************************************************************/
void LCD_1IN28_SetWindows(UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend)
{
    //set the X coordinates
    LCD_1IN28_SendCommand(0x2A);
    LCD_1IN28_SendData_8Bit(0x00);
    LCD_1IN28_SendData_8Bit(Xstart);
    LCD_1IN28_SendData_8Bit(0x00);
    LCD_1IN28_SendData_8Bit(Xend-1);

    //set the Y coordinates
    LCD_1IN28_SendCommand(0x2B);
    LCD_1IN28_SendData_8Bit(0x00);
    LCD_1IN28_SendData_8Bit(Ystart);
    LCD_1IN28_SendData_8Bit(0x00);
    LCD_1IN28_SendData_8Bit(Yend-1);

    LCD_1IN28_SendCommand(0X2C);
    // printf("%d %d\r\n",x,y);
}

/******************************************************************************
function :  Clear screen
parameter:
******************************************************************************/
void LCD_1IN28_Clear(UWORD Color)
{
    UWORD j,i;
    UWORD Image[LCD_1IN28.WIDTH*LCD_1IN28.HEIGHT];

    Color = ((Color<<8)&0xff00)|(Color>>8);

    for (j = 0; j < LCD_1IN28.HEIGHT*LCD_1IN28.WIDTH; j++) {
        Image[j] = Color;
    }

    LCD_1IN28_SetWindows(0, 0, LCD_1IN28.WIDTH, LCD_1IN28.HEIGHT);
    DEV_Digital_Write(EPD_DC_PIN, 1);
    DEV_Digital_Write(EPD_CS_PIN, 0);
    // printf("HEIGHT %d, WIDTH %d\r\n",LCD_1IN28.HEIGHT,LCD_1IN28.WIDTH);

    for (j = 0; j < LCD_1IN28.HEIGHT; j++) {
        DEV_SPI_Write_nByte((uint8_t *)&Image[j*LCD_1IN28.WIDTH], LCD_1IN28.WIDTH*2);
    }

    DEV_Digital_Write(EPD_CS_PIN, 1);
}

/******************************************************************************
function :  Sends the image buffer in RAM to displays
parameter:
******************************************************************************/
void LCD_1IN28_Display(UWORD *Image)
{
    UWORD j;
    LCD_1IN28_SetWindows(0, 0, LCD_1IN28.WIDTH, LCD_1IN28.HEIGHT);
    DEV_Digital_Write(EPD_DC_PIN, 1);
    DEV_Digital_Write(EPD_CS_PIN, 0);

    for (j = 0; j < LCD_1IN28.HEIGHT; j++) {
        DEV_SPI_Write_nByte((uint8_t *)&Image[j*LCD_1IN28.WIDTH], LCD_1IN28.WIDTH*2);
    }

    DEV_Digital_Write(EPD_CS_PIN, 1);
    LCD_1IN28_SendCommand(0x29);
}

void LCD_1IN28_DisplayWindows(UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend, UWORD *Image)
{
    // display
    UDOUBLE Addr = 0;
    UWORD j;
    LCD_1IN28_SetWindows(Xstart, Ystart, Xend , Yend);
    DEV_Digital_Write(EPD_DC_PIN, 1);
    DEV_Digital_Write(EPD_CS_PIN, 0);

    for (j = Ystart; j < Yend - 1; j++) {
        Addr = Xstart + j * LCD_1IN28.WIDTH ;
        DEV_SPI_Write_nByte((uint8_t *)&Image[Addr], (Xend-Xstart)*2);
    }

    DEV_Digital_Write(EPD_CS_PIN, 1);
}

void LCD_1IN28_DisplayPoint(UWORD X, UWORD Y, UWORD Color)
{
    LCD_1IN28_SetWindows(X,Y,X,Y);
    LCD_1IN28_SendData_16Bit(Color);
}

void Handler_1IN28_LCD(int signo)
{
    //System Exit
    printf("\r\nHandler:Program stop\r\n");
    DEV_Module_Exit();
    exit(0);
}
