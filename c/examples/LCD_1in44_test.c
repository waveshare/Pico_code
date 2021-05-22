/*****************************************************************************
* | File      	:   LCD_1in44_test.c
* | Author      :   Waveshare team
* | Function    :   2.9inch e-paper V2 test demo
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2021-01-20
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
#include "LCD_1in44.h"


bool reserved_addr(uint8_t addr) {
return (addr & 0x78) == 0 || (addr & 0x78) == 0x78;
}

int LCD_1in44_test(void)
{
    DEV_Delay_ms(100);
    printf("LCD_1in44_test Demo\r\n");
    if(DEV_Module_Init()!=0){
        return -1;
    }
    /* LCD Init */
    printf("Pico_LCD_1.44 demo...\r\n");
    LCD_1IN44_Init(HORIZONTAL);
    LCD_1IN44_Clear(WHITE);
    
    //LCD_SetBacklight(1023);
    UDOUBLE Imagesize = LCD_1IN44_HEIGHT*LCD_1IN44_WIDTH*2;
    UWORD *BlackImage;
    if((BlackImage = (UWORD *)malloc(Imagesize)) == NULL) {
        printf("Failed to apply for black memory...\r\n");
        exit(0);
    }
    // /*1.Create a new image cache named IMAGE_RGB and fill it with white*/
    Paint_NewImage((UBYTE *)BlackImage,LCD_1IN44.WIDTH,LCD_1IN44.HEIGHT, 0, WHITE);
    Paint_SetScale(65);
    Paint_Clear(WHITE);
    Paint_SetRotate(ROTATE_0);
    Paint_Clear(WHITE);
    
    // /* GUI */
    printf("drawing...\r\n");
    // /*2.Drawing on the image*/
#if 1
    Paint_DrawPoint(104,9, BLACK, DOT_PIXEL_1X1,  DOT_FILL_RIGHTUP);//240 240
    Paint_DrawPoint(107,8, BLACK, DOT_PIXEL_2X2,  DOT_FILL_RIGHTUP);
    Paint_DrawPoint(111,7, BLACK, DOT_PIXEL_3X3, DOT_FILL_RIGHTUP);
    Paint_DrawPoint(116,6, BLACK, DOT_PIXEL_4X4, DOT_FILL_RIGHTUP);
    Paint_DrawPoint(122,5, BLACK, DOT_PIXEL_5X5, DOT_FILL_RIGHTUP);
    Paint_DrawString_CN(0,15,"ª∂”≠ π”√",&Font24CN, BLACK, BLUE);
    Paint_DrawString_EN(0, 60, "Pico-LCD-1.44", &Font12, WHITE, BLUE);
    Paint_DrawString_EN (0,70 ,"128x128 Pixel", &Font12, WHITE,  BLACK);
    Paint_DrawString_EN(0, 80, "ST7735S Controller", &Font12, RED, WHITE); 

    // /*3.Refresh the picture in RAM to LCD*/
    LCD_1IN44_Display(BlackImage);
    DEV_Delay_ms(2000);
#endif
#if 1
    
     Paint_DrawImage(gImage_1inch44_1,0,0,128,128);
     LCD_1IN44_Display(BlackImage);
     DEV_Delay_ms(2000);

     
     
#endif
	// 4.Test button
    int key0 = 15; 
    int key1 = 17; 
    int key2 = 2; 
    int key3 = 3; 
    
    SET_Infrared_PIN(key0);    
    SET_Infrared_PIN(key1);
    SET_Infrared_PIN(key2);
    SET_Infrared_PIN(key3);

    Paint_Clear(WHITE);
    LCD_1IN44_Display(BlackImage);
    
    while(1){
    	Paint_DrawString_EN(5, 40, " Key     Test", &Font20, WHITE, RED);
        if(DEV_Digital_Read(key0 ) == 0){
        
        	Paint_DrawRectangle(88, 98, 123, 128, YELLOW, DOT_PIXEL_1X1,DRAW_FILL_FULL);
		
        }else  {
        	Paint_DrawRectangle(88, 98, 123, 128, RED, DOT_PIXEL_1X1,DRAW_FILL_FULL);
        }
            
        if(DEV_Digital_Read(key1 ) == 0){
        
           Paint_DrawRectangle(88, 66, 123, 96, YELLOW, DOT_PIXEL_1X1,DRAW_FILL_FULL);
			
        }else  {
            
         	Paint_DrawRectangle(88, 66, 123, 96, RED, DOT_PIXEL_1X1,DRAW_FILL_FULL);
        }
        
        if(DEV_Digital_Read(key2) == 0){
        
            
			Paint_DrawRectangle(88, 34, 123, 64, YELLOW, DOT_PIXEL_1X1,DRAW_FILL_FULL);
        }else  {
            
        	Paint_DrawRectangle(88, 34, 123, 64, RED, DOT_PIXEL_1X1,DRAW_FILL_FULL);
        }
        
        if(DEV_Digital_Read(key3 ) == 0){
        
            
             Paint_DrawRectangle(88, 2, 123, 32, YELLOW, DOT_PIXEL_1X1,DRAW_FILL_FULL);

        }else{
            
             Paint_DrawRectangle(88, 2, 123, 32, RED, DOT_PIXEL_1X1,DRAW_FILL_FULL);   
       
        }		
		LCD_1IN44_Display(BlackImage);             
    }

    /* Module Exit */
    free(BlackImage);
    BlackImage = NULL;
    
    
    DEV_Module_Exit();
    return 0;
}
