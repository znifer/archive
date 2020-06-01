#include <msp430.h> 
#include "stdio.h"
#include "system_define.h"
#include "system_variable.h"
#include "function_prototype.h"
#include "main.h"

#define SIZE 200

/*Разработать программу передачи 200 чисел (от 0 до 199) из
микроконтроллера MSP430F1611 в ПЭВМ по интерфейсу USB в
соответствие с протоколом:
модуль USART0,
скорость обмена данными 38400 бит/с,
режим обмена асинхронный,
8 битов данных без бита четности.*/

void main(void) {
    //Отключение ждущего таймера
    WDTCTL = WDTPW + WDTHOLD;
    //Инициализируем систему
    Init_System();
    Init_System_Clock();
    //Инициализируем UART
    char speed = 2;     // 0 - 38400, 1 - 57600, 2 - 115200 - скорость обмена
    char databits = 8;  // 7, 8 - длинна символа
    char stopbits = 1;  // 1, 2 - кол-во передаваемых стоповых бит
    char parity = 0;    // 0 - без контроля четности, 1 - контроль четности, нечетый, 2 - четный
    char iface = 0;     // 0 - USB, 1 - оптика



    //Передаем данные
    char i;
    UART_init(speed, databits, stopbits, parity, iface);
    while (1){
        for (i = 0; i < SIZE; i++){
            UART_sendbyte(i);
        }
        wait_1ms(1000);
    }
    UART_off();
}
