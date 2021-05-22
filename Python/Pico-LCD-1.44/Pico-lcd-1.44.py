
from machine import Pin,SPI,PWM
import framebuf
import time

BL = 13
DC = 8
RST = 12
MOSI = 11
SCK = 10    
CS = 9


class LCD_1inch44(framebuf.FrameBuffer):
    def __init__(self):
        self.width = 128
        self.height = 128
        
        self.cs = Pin(CS,Pin.OUT)
        self.rst = Pin(RST,Pin.OUT)
        
        self.cs(1)
        self.spi = SPI(1)
        self.spi = SPI(1,1000_000)
        self.spi = SPI(1,10000_000,polarity=0, phase=0,sck=Pin(SCK),mosi=Pin(MOSI),miso=None)
        self.dc = Pin(DC,Pin.OUT)
        self.dc(1)
        self.buffer = bytearray(self.height * self.width * 2)
        super().__init__(self.buffer, self.width, self.height, framebuf.RGB565)
        self.init_display()
        

        self.WHITE  =   0xFFFF
        self.BLACK  =  0x0000
        self.GREEN  =  0x001F
        self.RED    =  0xF800
        self.BLUE   = 0x07E0
        self.GBLUE = 0X07FF
        self.YELLOW = 0xFFE0
        
    def write_cmd(self, cmd):    
        self.cs(1)
        self.dc(0)
        self.cs(0)
        self.spi.write(bytearray([cmd]))
        self.cs(1)

    def write_data(self, buf):
        self.cs(1)
        self.dc(1)
        self.cs(0)
        self.spi.write(bytearray([buf]))
        self.cs(1)

    def init_display(self):
        """Initialize dispaly"""  
        self.rst(1)
        self.rst(0)
        self.rst(1)
        
        self.write_cmd(0x36);
        self.write_data(0x70);
        
        self.write_cmd(0x3A);
        self.write_data(0x05);

         #ST7735R Frame Rate
        self.write_cmd(0xB1);
        self.write_data(0x01);
        self.write_data(0x2C);
        self.write_data(0x2D);

        self.write_cmd(0xB2);
        self.write_data(0x01);
        self.write_data(0x2C);
        self.write_data(0x2D);

        self.write_cmd(0xB3);
        self.write_data(0x01);
        self.write_data(0x2C);
        self.write_data(0x2D);
        self.write_data(0x01);
        self.write_data(0x2C);
        self.write_data(0x2D);

        self.write_cmd(0xB4); #Column inversion
        self.write_data(0x07);

        #ST7735R Power Sequence
        self.write_cmd(0xC0);
        self.write_data(0xA2);
        self.write_data(0x02);
        self.write_data(0x84);
        self.write_cmd(0xC1);
        self.write_data(0xC5);

        self.write_cmd(0xC2);
        self.write_data(0x0A);
        self.write_data(0x00);

        self.write_cmd(0xC3);
        self.write_data(0x8A);
        self.write_data(0x2A);
        self.write_cmd(0xC4);
        self.write_data(0x8A);
        self.write_data(0xEE);

        self.write_cmd(0xC5); #VCOM
        self.write_data(0x0E);

        #ST7735R Gamma Sequence
        self.write_cmd(0xe0);
        self.write_data(0x0f);
        self.write_data(0x1a);
        self.write_data(0x0f);
        self.write_data(0x18);
        self.write_data(0x2f);
        self.write_data(0x28);
        self.write_data(0x20);
        self.write_data(0x22);
        self.write_data(0x1f);
        self.write_data(0x1b);
        self.write_data(0x23);
        self.write_data(0x37);
        self.write_data(0x00);
        self.write_data(0x07);
        self.write_data(0x02);
        self.write_data(0x10);

        self.write_cmd(0xe1);
        self.write_data(0x0f);
        self.write_data(0x1b);
        self.write_data(0x0f);
        self.write_data(0x17);
        self.write_data(0x33);
        self.write_data(0x2c);
        self.write_data(0x29);
        self.write_data(0x2e);
        self.write_data(0x30);
        self.write_data(0x30);
        self.write_data(0x39);
        self.write_data(0x3f);
        self.write_data(0x00);
        self.write_data(0x07);
        self.write_data(0x03);
        self.write_data(0x10);

        self.write_cmd(0xF0); #Enable test command
        self.write_data(0x01);

        self.write_cmd(0xF6); #Disable ram power save mode
        self.write_data(0x00);
            #sleep out
        self.write_cmd(0x11);
        #Turn on the LCD display
        self.write_cmd(0x29);

    def show(self):
        self.write_cmd(0x2A)
        self.write_data(0x00)
        self.write_data(0x01)
        self.write_data(0x00)
        self.write_data(0x80)
        
        self.write_cmd(0x2B)
        self.write_data(0x00)
        self.write_data(0x02)
        self.write_data(0x00)
        self.write_data(0x82)
        
        self.write_cmd(0x2C)
        
        self.cs(1)
        self.dc(1)
        self.cs(0)
        self.spi.write(self.buffer)
        self.cs(1)
  
if __name__=='__main__':
    pwm = PWM(Pin(BL))
    pwm.freq(1000)
    pwm.duty_u16(32768)#max 65535

    LCD = LCD_1inch44()
    #color BRG
    LCD.fill(LCD.BLACK)
 
    LCD.show()
    
    LCD.fill_rect(15,40,75,12,LCD.YELLOW)
    LCD.rect(15,40,75,12,LCD.YELLOW)
    LCD.text("1in44-LCD",17,42,LCD.WHITE)
    
    LCD.fill_rect(15,60,75,12,LCD.BLUE)
    LCD.rect(15,60,75,12,LCD.BLUE)
    LCD.text("128x128Px ",17,62,LCD.WHITE)
    
    LCD.fill_rect(15,80,75,12,LCD.GREEN)
    LCD.rect(15,80,75,12,LCD.GREEN)
    LCD.text("ST7735S",17,82,LCD.WHITE)

    LCD.hline(5,5,120,LCD.GBLUE)
    LCD.hline(5,125,120,LCD.GBLUE)
    LCD.vline(5,5,120,LCD.GBLUE)
    LCD.vline(125,5,120,LCD.GBLUE)
    
    LCD.show()
   
    key0 = Pin(15,Pin.IN,Pin.PULL_UP) 
    key1 = Pin(17,Pin.IN,Pin.PULL_UP)
    key2 = Pin(2 ,Pin.IN,Pin.PULL_UP)
    key3 = Pin(3 ,Pin.IN,Pin.PULL_UP)
   
    while(1):      
        if(key0.value() == 0):
            LCD.fill_rect(100,100,20,20,LCD.GBLUE)
        else :
            LCD.fill_rect(100,100,20,20,LCD.BLACK)
            LCD.rect(100,100,20,20,LCD.GBLUE)
            
        if(key1.value() == 0):
            LCD.fill_rect(100,70,20,20,LCD.GBLUE)
        else :
            LCD.fill_rect(100,70,20,20,LCD.BLACK)
            LCD.rect(100,70,20,20,LCD.GBLUE)
            
        if(key2.value() == 0):
            LCD.fill_rect(100,40,20,20,LCD.GBLUE)
        else :
            LCD.fill_rect(100,40,20,20,LCD.BLACK)
            LCD.rect(100,40,20,20,LCD.GBLUE)
        if(key3.value() == 0):
            
            LCD.fill_rect(100,10,20,20,LCD.GBLUE)
        else :
            LCD.fill_rect(100,10,20,20,LCD.BLACK)
            LCD.rect(100,10,20,20,LCD.GBLUE) 
                      
        LCD.show()
    time.sleep(1)
    LCD.fill(0xFFFF)






