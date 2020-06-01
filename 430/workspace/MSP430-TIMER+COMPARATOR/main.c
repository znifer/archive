#include <msp430.h> 
#include "stdio.h"
#include "system_define.h"
#include "system_variable.h"
#include "function_prototype.h"
#include "main.h"

/*����������� ���������, ������� ������������ ��������� ������������� ����������� ��������� � �������
������������ �������� �� ���. ��� ������� ������ ���������� ������������ ���������� ���������� � ������ � � ������ �������.*/

void main(void) {
    WDTCTL = WDTPW + WDTHOLD;      //���������� ������� �������
    Init_System_Clock();
    Init_System();
    LCD_init();
    _enable_interrupt();
    char text[40] = "����������!";
    LCD_set_pos(0, 0);
    LCD_message(text);
    wait_1ms(1000);
    LCD_clear();
    unsigned res = 0;
    while (1){
        res = R22_get_resistance();
        LCD_clear();
        sprintf(text, "%i ��", res);
        LCD_message(text);
        wait_1ms(1000);
    }
}
