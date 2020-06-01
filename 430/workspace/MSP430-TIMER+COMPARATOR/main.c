#include <msp430.h> 
#include "stdio.h"
#include "system_define.h"
#include "system_variable.h"
#include "function_prototype.h"
#include "main.h"

/*Разработать программу, которая обеспечивает измерение сопротивления переменного резистора и выводит
рассчитанное значение на ЖКИ. Для решения задачи необходимо использовать встроенный компаратор и таймер А в режиме захвата.*/

void main(void) {
    WDTCTL = WDTPW + WDTHOLD;      //Отключение ждущего таймера
    Init_System_Clock();
    Init_System();
    LCD_init();
    _enable_interrupt();
    char text[40] = "Получилось!";
    LCD_set_pos(0, 0);
    LCD_message(text);
    wait_1ms(1000);
    LCD_clear();
    unsigned res = 0;
    while (1){
        res = R22_get_resistance();
        LCD_clear();
        sprintf(text, "%i Ом", res);
        LCD_message(text);
        wait_1ms(1000);
    }
}
