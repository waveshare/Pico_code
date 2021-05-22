/*****************************************************************************
* | File      	:   Readme_CN.txt
* | Author      :   
* | Function    :   Help with use
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2021-03-31
* | Info        :   在这里提供一个中文版本的使用文档，以便你的快速使用
******************************************************************************/
这个文件是帮助您使用本例程。
在这里简略的描述本工程的使用：

1.基本信息：
本例程使用相对应的模块搭配Pico进行了验证，你可以在工程的中查看对应的测试例程;

2.管脚连接：
管脚连接你可以在Pico-LCD-0.96.py查看，这里也再重述一次：
LCD 0.96
LCD    =>    Pico
VCC    ->    VSYS
GND    ->    GND
DIN    ->    11
CLK    ->    10
CS     ->    9
DC     ->    8
RST    ->    12
BL     ->    13
-----------------------------
(KEY)		Pico	
UP：	->	2
DOWN：	->	18
LEFT：	->	16
RIGHT：	->	20
CTRL：	->	3
A：	->	15
B:	->	17

3.基本使用：
    1): 按住Pico板上的按键，将pico通过Micro USB线接到树莓派的USB接口，然后松开按键。
        接入之后，电脑会自动识别到一个可移动盘（RPI-RP2）
        
    2): 将python目录中pico_micropython_20210121.uf2 文件复制到识别的可移动盘（RPI-RP2）中
    
    3): 更新Thonny IDE
        sudo apt upgrade thonny
        
    4): 打开Thonny IDE （点击树莓logo -> Programming -> Thonny Python IDE ）
        选择Tools -> Options... -> Interpreter
        选择MicroPython(Raspberry Pi Pico 和ttyACM0端口
        
    5): 在Thonny IDE中打开python/Pico-LCD-0.96/Pico-LCD-0.96.py文件
        然后运行当前脚本（绿色小三角）即可

4.例程中像素画板的使用说明：
    例程中会显示一个8*16大小的方格（方格大小10*10 pixels）
    摇杆：
   上	->	画笔上移
   下	->	画笔下移
   左	->	画笔左移
   右	->	画笔右移
   ctrl(摇杆中心键)	->	更换画笔颜色
   A	->	按住A按键不放，在画笔位置填充实心像素块，颜色为当前画笔颜色，此时可操作摇杆连续填充
   B	->	清空像素画板
		


    