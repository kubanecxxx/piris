#ifndef PMASTER_H
#define PMASTER_H

namespace piris
{

class PPortingAbstract;
class PScreen;
class PKeyEvent;
class PTouchEvent;

class PMaster
{
public:
    PMaster(PPortingAbstract * port);
    PMaster(PKeyEvent * k, PTouchEvent * t);

private:
    PPortingAbstract * hw;
    PScreen * activeScreen;
    PMaster(const PMaster &);

    PKeyEvent * key;
    PTouchEvent * touch;

public:
    void setActiveScreen(PScreen * screen);
    void printScreen();
    void main();
    inline void setHW(PPortingAbstract * port) {hw = port;}

    PScreen * getActiveScreen() const {return activeScreen;}

};

}

#endif // PMASTER_H
