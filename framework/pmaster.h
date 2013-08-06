#ifndef PMASTER_H
#define PMASTER_H

namespace piris
{

class PPortingAbstract;
class PWidget;

class PMaster
{
public:
    PMaster(PPortingAbstract * port);

private:
    PPortingAbstract * hw;
    PWidget * activeScreen;
    PMaster(const PMaster &);

public:
    void setActiveScreen(PWidget * screen);
    void printScreen();
    void main();
};

}

#endif // PMASTER_H
