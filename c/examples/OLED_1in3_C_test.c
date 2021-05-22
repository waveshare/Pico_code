/*****************************************************************************
* | File      	:   OLED_1in3_test.c
* | Author      :   
* | Function    :   
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2021-03-16
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
******************************************************************************/
#include "EPD_Test.h"
#include "LCD_1in14.h"
#include "OLED_1in3_c.h"
#include "ImageData.h"
#include "GUI_Paint.h"



int OLED_1in3_C_test(void)
{
    DEV_Delay_ms(100);
    
    printf("OELD_test Demo\r\n");
    if(DEV_Module_Init()!=0){
        while(1){
            printf("END\r\n");
        }
    }
    
    /* Init */
    OLED_1in3_C_Init();
    OLED_1in3_C_Clear();
    
    UBYTE *BlackImage;
    UWORD Imagesize = ((OLED_1in3_C_WIDTH%8==0)? (OLED_1in3_C_WIDTH/8): (OLED_1in3_C_WIDTH/8+1)) * OLED_1in3_C_HEIGHT;
    if((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
        while(1){
            printf("Failed to apply for black memory...\r\n");
        }
    }
    printf("Paint_NewImage\r\n");
    Paint_NewImage(BlackImage, OLED_1in3_C_WIDTH, OLED_1in3_C_HEIGHT, 0, WHITE);	
    
    
    
    printf("Drawing\r\n");
    //1.Select Image
    Paint_SelectImage(BlackImage);
    DEV_Delay_ms(500);
    Paint_Clear(BLACK);
    
    // 2.Drawing on the image
    printf("Drawing:page 1\r\n");
    Paint_DrawPoint(20, 10, WHITE, DOT_PIXEL_1X1, DOT_STYLE_DFT);
    Paint_DrawPoint(30, 10, WHITE, DOT_PIXEL_2X2, DOT_STYLE_DFT);
    Paint_DrawPoint(40, 10, WHITE, DOT_PIXEL_3X3, DOT_STYLE_DFT);
    Paint_DrawLine(10, 10, 10, 20, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawLine(20, 20, 20, 30, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawLine(30, 30, 30, 40, WHITE, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
    Paint_DrawLine(40, 40, 40, 50, WHITE, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
    Paint_DrawCircle(60, 30, 15, WHITE, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawCircle(100, 40, 20, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(50, 30, 60, 40, WHITE, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawRectangle(90, 30, 110, 50, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    BlackImage[0] = 0xf0;
    // 3.Show image on page1
    OLED_1in3_C_Display(BlackImage);
    DEV_Delay_ms(2000);
    Paint_Clear(BLACK);
    
    
    
    // Drawing on the image
    printf("Drawing:page 2\r\n");
    Paint_DrawString_EN(10, 0, "Pico-OLED", &Font16, WHITE, BLACK);
    Paint_DrawString_EN(10, 17, "hello world", &Font8, WHITE, BLACK);
    Paint_DrawNum(10, 30, 123.1, &Font8,2, WHITE, WHITE);
    Paint_DrawNum(10, 43, 987654.2, &Font12,2, WHITE, WHITE);
    // Show image on page2
    OLED_1in3_C_Display(BlackImage);
    DEV_Delay_ms(2000);
    Paint_Clear(BLACK);
    
    // Drawing on the image
    printf("Drawing:page 3\r\n");
    Paint_DrawString_CN(10, 0,"ÄãºÃAbc", &Font12CN, WHITE, WHITE);
    Paint_DrawString_CN(0, 20, "µç×Ó", &Font24CN, WHITE, WHITE);
    // Show image on page3
    OLED_1in3_C_Display(BlackImage);
    DEV_Delay_ms(2000);
    
    // Show image on page4
    OLED_1in3_C_Display(gImage_1inch3_C_1);
    DEV_Delay_ms(5000);
    
    
    Paint_NewImage(BlackImage, OLED_1in3_C_WIDTH, OLED_1in3_C_HEIGHT, 180, WHITE);	
    Paint_Clear(BLACK);
    int key0 = 15; 
    int key1 = 17;
    int key = 0;
    DEV_GPIO_Mode(key0, 0);
    DEV_GPIO_Mode(key1, 0);
    
    Paint_Clear(BLACK);
    OLED_1in3_C_Display(BlackImage);
    
    
    while(1){
        if(DEV_Digital_Read(key1 ) == 0){
            Paint_DrawRectangle(115, 5, 125, 15, WHITE, DOT_PIXEL_2X2,DRAW_FILL_FULL);
            key = 1;
        }else {
            Paint_DrawRectangle(115, 5, 125, 15, BLACK, DOT_PIXEL_2X2,DRAW_FILL_EMPTY);
        }
            
        if(DEV_Digital_Read(key0 ) == 0){
            Paint_DrawRectangle(115, 50, 125, 60, WHITE, DOT_PIXEL_2X2,DRAW_FILL_FULL);
        }else {
            Paint_DrawRectangle(115, 50, 125, 60, BLACK, DOT_PIXEL_2X2,DRAW_FILL_EMPTY);
            key = 1;
            
        }
        if(key == 1){
            OLED_1in3_C_Display(BlackImage);
            Paint_Clear(BLACK);
        }
        
    }

    
    
    DEV_Module_Exit();
    return 0;
}
