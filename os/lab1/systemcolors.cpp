#include "systemcolors.h"

SystemColors::SystemColors(){}

QColor SystemColors::getColor(int index){
    QColor color;
    DWORD winColor;
    winColor = GetSysColor(index);
    color.setRgb(GetRValue(winColor), GetGValue(winColor), GetBValue(winColor));
    return color;
}

void SystemColors::setColor(int index, QColor color){
    int r = color.red();
    int g = color.green();
    int b = color.blue();
    DWORD winColor = RGB(r, g, b);
    SetSysColors(1, &index, &winColor);
}
