#ifndef SYSTEMCOLORS_H
#define SYSTEMCOLORS_H

#include <QColor>
#include "windows.h"
#include "wchar.h"
/* COLOR_BTNHIGHLIGHT, COLOR_INACTIVECAPTION, COLOR_SCROLLBAR*/
class SystemColors{
public:
    SystemColors();
    static QColor getColor(int index);
    static void setColor(int index, QColor color);

};

#endif // SYSTEMCOLORS_H
