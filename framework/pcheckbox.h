#ifndef PCHECKBOX_H
#define PCHECKBOX_H

#include "pwidget.h"

namespace piris
{

class PCheckBox : public PWidget
{
public:
    PCheckBox(PWidget * par = 0);
    PCheckBox(PWidgetProperties_t & props, PWidget *par = NULL);
    PCheckBox(const PWidgetProperties_t & props, PWidget *par = NULL);

protected:
    virtual void draw(PPortingAbstract *disp) const;
    virtual void processEvent(PKeyEvent *key, PTouchEvent *touch);

private:
    bool checked;

public:
    inline bool Checked() const {return checked;}
    inline void setChecked(bool checked) {this->checked = checked;}

    void recomputeGeometry();
};

}

#endif // PCHECKBOX_H
