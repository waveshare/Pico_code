/*****************************************************************************
* | File      	:   Readme_EN.txt
* | Author      :   
* | Function    :   Help with use
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2021-02-04
* | Info        :   Here is an English version of the documentation for your quick use.
******************************************************************************/
This file is to help you use this routine.
Since our ink screens are getting more and more, it is not convenient for our maintenance, so all the ink screen programs are made into one project.
A brief description of the use of this project is here:

1. Basic information:
This routine is verified using the corresponding module with the PICO. 
You can see the corresponding test routine in the examples\ of the project.

2. Pin connection:
Pin connection You can look at dev_config.c/h in \lib\Config. Again, here:
LCD  1.14
LCD    =>    Pico
VCC    ->    VSYS
GND    ->    GND
DIN    ->    11
CLK    ->    10
CS     ->    9
DC     ->    8
RST    ->    12
BL     ->    13

LCD 1.3 
LCD    =>    Pico
VCC    ->    VSYS
GND    ->    GND
DIN    ->    11
CLK    ->    10
CS     ->    9
DC     ->    8
RST    ->    12
BL     ->    13
A       ->   15
B       ->    17
X       ->    19
Y       ->    21
UP     ->    2
DOWM ->    18
LEFT   ->    16
RIGHT ->    20
CTRL  ->    3


OLED 1.3
OLED =>    Pico
VCC    ->    VSYS
GND    ->    GND
DIN    ->    11
CLK    ->    10
CS     ->    9
DC     ->    8
RST    ->    12

LCD  1.44
LCD    =>    Pico
VCC    ->    VSYS
GND    ->    GND
DIN    ->    11
CLK    ->    10
CS     ->    9
DC     ->    8
RST    ->    12
BL     ->    13

LCD 1.8 
LCD    =>    Pico
VCC    ->    VSYS
GND    ->    GND
DIN    ->    11
CLK    ->    10
CS     ->    9
DC     ->    8
RST    ->    12
BL     ->    13

OLED 2.23
OLED    =>    Pico
VCC    ->    VSYS
GND    ->    GND
DIN    ->    11
CLK    ->    10
CS     ->    9
DC     ->    8
RST    ->    12
SDA    ->     6
SCL     ->     7

LCD 2 
LCD    =>    Pico
VCC    ->    VSYS
GND    ->    GND
DIN    ->    11
CLK    ->    10
CS     ->    9
DC     ->    8
RST    ->    12
BL     ->    13
KEY0  ->   15
KEY1  ->    17
KEY2  ->    2
KEY3  ->    3
3. Basic use:
You need to execute:
    If the directory already exists, you can go directly. If there is no build directory, execute
         mkdir build
     Enter the build directory and type in the terminal:
         cd build
         export PICO_SDK_PATH=../../pico-sdk
     Where ../../pico-sdk is your installed SDK directory
     Execute cmake, automatically generate Makefile file, enter in the terminal:
         cmake ..
     Execute make to generate an executable file, and enter in the terminal:
         make
     Copy the compiled uf2 file to pico

4. Directory structure (selection):

If you use our products frequently, we will be very familiar with our program directory structure. We have a copy of the specific function.
The API manual for the function, you can download it on our WIKI or request it as an after-sales customer service. Here is a brief introduction:
Config\: This directory is a hardware interface layer file. You can see many definitions in DEV_Config.c(.h), including:
   type of data;
    GPIO;
    Read and write GPIO;
    Delay: Note: This delay function does not use an oscilloscope to measure specific values.
    Module Init and exit processing:
        void DEV_Module_Init(void);
        void DEV_Module_Exit(void);
             
\lib\GUI\: This directory is some basic image processing functions, in GUI_Paint.c(.h):
    Common image processing: creating graphics, flipping graphics, mirroring graphics, setting pixels, clearing screens, etc.
    Common drawing processing: drawing points, lines, boxes, circles, Chinese characters, English characters, numbers, etc.;
    Common time display: Provide a common display time function;
    Commonly used display pictures: provide a function to display bitmaps;
    
\lib\Fonts\: for some commonly used fonts:
    Ascii:
        Font8: 5*8
        Font12: 7*12
        Font16: 11*16
        Font20: 14*20
        Font24: 17*24
    Chinese:
        font12CN: 16*21
        font24CN: 32*41
        
\lib\e-paper\: This directory is the LCD driver function;
examples\: This directory is the test program of LCD, you can see the specific usage method in it;