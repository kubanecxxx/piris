# Piris

This project is a basic widget toolkit for embedded devices written in C++. I chose object oriented approach with all those inheritance and virtual methods stuff. It is really usefull for future - new widgets can be easilly added.

It abstracts:
- Touch panel events
- Keys event
- Screens management
- Widgets rendering
- Widget events callbacks / virtual methods which could be overriden

All the hardware specific part is abstracted out in a single abstract class called `PPortingAbstract` located in file [pportingabstract.cpp](framework/pportingabstract.cpp). You only need to inherit this class and implement these pure virtual methods.

The best thing - everything can be developed/tested on a PC - no hardware is needed. The project also contains porting to a Qt widget and simple testing software for development.

My other projects also contains this framework in real world - STM32F4 with SSD1289 LCD with touch.

Build
-----

To build PC development software you just need to import [piris.pro] into Qt Creator and you can try for yourself. If you want to use the framework on an embedded device check this [PirisPort.cpp](https://github.com/kubanecxxx/homeautomation/blob/master/gui/fw/handle/porting/PirisPort.cpp) in my homeautomation repository 
