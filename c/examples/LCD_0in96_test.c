/*****************************************************************************
* | File      	:   LCD_0in96_test.c
* | Author      :   Waveshare team
* | Function    :   
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2021-03-11
* | Info        :
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#include "EPD_Test.h"
#include "LCD_0in96.h"


bool reserved_addr(uint8_t addr) {
return (addr & 0x78) == 0 || (addr & 0x78) == 0x78;
}

int LCD_0in96_test(void)
{
    DEV_Delay_ms(100);
    printf("LCD_0in96_test Demo\r\n");
    if(DEV_Module_Init()!=0){
        return -1;
    }

    /* LCD Init */
    printf("0.96inch LCD demo...\r\n");
    LCD_0IN96_Init(HORIZONTAL);
    LCD_0IN96_Clear(WHITE);
    DEV_Delay_ms(1000);
	
	
    UDOUBLE Imagesize = LCD_0IN96_HEIGHT*LCD_0IN96_WIDTH*2;
    UWORD *BlackImage;
    if((BlackImage = (UWORD *)malloc(Imagesize)) == NULL) {
        printf("Failed to apply for black memory...\r\n");
        exit(0);
    }
    // /*1.Create a new image cache named IMAGE_RGB and fill it with white*/
    Paint_NewImage((UBYTE *)BlackImage,LCD_0IN96.WIDTH,LCD_0IN96.HEIGHT, 0, WHITE);
    Paint_SetScale(65);
    Paint_Clear(WHITE);
    Paint_SetRotate(ROTATE_0);
    Paint_Clear(WHITE);

    // /* GUI */
    printf("drawing...\r\n");
    // /*2.Drawing on the image*/
#if 1

	Paint_DrawPoint(2,2, BLACK, DOT_PIXEL_1X1,  DOT_FILL_RIGHTUP);
	Paint_DrawPoint(2,6, BLACK, DOT_PIXEL_2X2,  DOT_FILL_RIGHTUP);
	Paint_DrawPoint(2,11, BLACK, DOT_PIXEL_3X3, DOT_FILL_RIGHTUP);
	Paint_DrawPoint(2,16, BLACK, DOT_PIXEL_4X4, DOT_FILL_RIGHTUP);
	Paint_DrawPoint(2,21, BLACK, DOT_PIXEL_5X5, DOT_FILL_RIGHTUP);
	Paint_DrawLine( 10,  5, 40, 35, MAGENTA, DOT_PIXEL_2X2, LINE_STYLE_SOLID);
	Paint_DrawLine( 10, 35, 40,  5, MAGENTA, DOT_PIXEL_2X2, LINE_STYLE_SOLID);

	Paint_DrawLine( 80,  20, 110, 20, BLACK, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
	Paint_DrawLine( 95,   5,  95, 35, BLACK, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);

	Paint_DrawRectangle(10, 5, 40, 35, RED, DOT_PIXEL_2X2,DRAW_FILL_EMPTY);
	Paint_DrawRectangle(45, 5, 75, 35, BLUE, DOT_PIXEL_2X2,DRAW_FILL_FULL);

	Paint_DrawCircle( 95,20, 15, RED  ,DOT_PIXEL_1X1,DRAW_FILL_EMPTY);
	Paint_DrawCircle(130,20, 15, GREEN   ,DOT_PIXEL_1X1,DRAW_FILL_FULL);
	
	Paint_DrawNum (23, 37 ,123.456789, &Font12,6,  0xfff0, 0x000f);
	Paint_DrawString_EN(1, 37, "ABC", &Font12, 0x000f, 0xfff0);
	Paint_DrawString_CN(1,44, "Î¢Ñ©µç×Ó",  &Font24CN, BLUE, WHITE);
	
    /*3.Refresh the picture in RAM to LCD*/
	
    LCD_0IN96_Display(BlackImage);
    DEV_Delay_ms(3000);
	DEV_SET_PWM(100);//Set the backlight max:100
#endif
#if 1
     Paint_DrawImage(gImage_0inch96_1,0,0,160,80);
     LCD_0IN96_Display(BlackImage);
     DEV_Delay_ms(3000);
     
#endif
	int key_up = 2;
	int	key_down = 18;
	int key_left = 16;
	int key_right = 20;
	int key_ctrl = 3;
	int key_A = 15; 
    int key_B = 17; 
	int BL_Value = 50;	
	
	DEV_KEY_Config(key_up);
    DEV_KEY_Config(key_down);
	DEV_KEY_Config(key_left);
    DEV_KEY_Config(key_right);
	DEV_KEY_Config(key_ctrl);
    DEV_KEY_Config(key_A);
    DEV_KEY_Config(key_B);
	
    Paint_Clear(WHITE);
    LCD_0IN96_Display(BlackImage);
	while(1)
	{
		Paint_DrawRectangle(40,30,65,50, BLUE, DOT_PIXEL_2X2,DRAW_FILL_EMPTY);
		Paint_DrawRectangle(70,0,90,25, BLUE, DOT_PIXEL_2X2,DRAW_FILL_EMPTY);
		Paint_DrawRectangle(95,30,120,50, BLUE, DOT_PIXEL_2X2,DRAW_FILL_EMPTY);
		Paint_DrawRectangle(70,55,90,80, BLUE, DOT_PIXEL_2X2,DRAW_FILL_EMPTY);
		
		Paint_DrawRectangle(139,1,159,26, BLUE, DOT_PIXEL_2X2,DRAW_FILL_EMPTY);
		Paint_DrawRectangle(139,54,159,79, BLUE, DOT_PIXEL_2X2,DRAW_FILL_EMPTY);
		
		Paint_DrawCircle( 80,40,15, RED  ,DOT_PIXEL_2X2,DRAW_FILL_EMPTY);				
		if(DEV_Digital_Read(key_left) == 0){
			Paint_DrawRectangle(40,30,65,50, BLUE, DOT_PIXEL_2X2,DRAW_FILL_FULL);
		}else{
			Paint_DrawRectangle(43,33,62,47, WHITE, DOT_PIXEL_2X2,DRAW_FILL_FULL);	
		}
		if(DEV_Digital_Read(key_up) == 0){
			Paint_DrawRectangle(70,0,90,25, BLUE, DOT_PIXEL_2X2,DRAW_FILL_FULL);				
		}else{
			Paint_DrawRectangle(73,3,87,22, WHITE, DOT_PIXEL_2X2,DRAW_FILL_FULL);
		}
		if(DEV_Digital_Read(key_right) == 0){
			Paint_DrawRectangle(95,30,120,50, BLUE, DOT_PIXEL_2X2,DRAW_FILL_FULL);				
		}else{
			Paint_DrawRectangle(98,33,117,47, WHITE, DOT_PIXEL_2X2,DRAW_FILL_FULL);	
		}
		if(DEV_Digital_Read(key_down) == 0){
			Paint_DrawRectangle(70,55,90,80, BLUE, DOT_PIXEL_2X2,DRAW_FILL_FULL);				
		}else{
			Paint_DrawRectangle(73,58,87,77, WHITE, DOT_PIXEL_2X2,DRAW_FILL_FULL);	
		}
		if(DEV_Digital_Read(key_ctrl) == 0){
			Paint_DrawCircle( 80,40,15, RED ,DOT_PIXEL_2X2,DRAW_FILL_FULL);
		}else{
			Paint_DrawCircle( 80,40,12, WHITE ,DOT_PIXEL_2X2,DRAW_FILL_FULL);	
		}	
		
		if(DEV_Digital_Read(key_A) == 0)
		{	
			Paint_DrawRectangle(139,1,159,26, BLUE, DOT_PIXEL_2X2,DRAW_FILL_FULL);
			BL_Value+=5;
			if(BL_Value>=100)
			{
				BL_Value=100;
			}
		}else{
			Paint_DrawRectangle(142,4,156,23, WHITE, DOT_PIXEL_2X2,DRAW_FILL_FULL);
		}
		if(DEV_Digital_Read(key_B) == 0)
		{
			Paint_DrawRectangle(139,54,159,79, BLUE, DOT_PIXEL_2X2,DRAW_FILL_FULL);
			BL_Value-=5;
			if(BL_Value<=0)
			{
				BL_Value=0;
			}
		}else{
			Paint_DrawRectangle(142,57,156,76, WHITE, DOT_PIXEL_2X2,DRAW_FILL_FULL);
		}
		DEV_SET_PWM(BL_Value);
		LCD_0IN96_Display(BlackImage);
	}
    /* Module Exit */
    free(BlackImage);
    BlackImage = NULL;
    
    
    DEV_Module_Exit();
    return 0;
}
