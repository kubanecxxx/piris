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

};

}

#endif // PMASTER_H
