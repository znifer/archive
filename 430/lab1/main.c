#include <msp430.h> 
#include "stdio.h"
#include "system_define.h"
#include "system_variable.h"
#include "function_prototype.h"
#include "main.h"
#include "lcd.h"

char symbol[8] = { 0b00011111,
                   0b00001010,
                   0b00000100,
                   0b00001010,
                   0b00011111,
                   0b00010001,
                   0b00010001,
                   0b00011111
};

void main(void) {
    WDTCTL = WDTPW + WDTHOLD;      //Отключение ждущего таймера
    Init_System_Clock();
    Init_System();
    LCD_init();

    char text[40] = "Ковалёв И.Д.";
    LCD_set_pos(0, 0);
    char lowertext[40] = "Группа ВТ-31";
    LCD_set_pos(1, 0);
    LCD_message(lowertext);
	
	wait_1ms(1);
	
    int i;
    for (i = 0; i < 8; i++){
        LCD_WriteCommand(0x40 + i);
        LCD_WriteData(symbol[i]);
    }
    while (1){}
}
