#include <msp430.h> 
#include "stdio.h"
#include "system_define.h"
#include "system_variable.h"
#include "function_prototype.h"
#include "main.h"

#define SIZE 200

/*����������� ��������� �������� 200 ����� (�� 0 �� 199) ��
���������������� MSP430F1611 � ���� �� ���������� USB �
������������ � ����������:
������ USART0,
�������� ������ ������� 38400 ���/�,
����� ������ �����������,
8 ����� ������ ��� ���� ��������.*/

void main(void) {
    //���������� ������� �������
    WDTCTL = WDTPW + WDTHOLD;
    //�������������� �������
    Init_System();
    Init_System_Clock();
    //�������������� UART
    char speed = 2;     // 0 - 38400, 1 - 57600, 2 - 115200 - �������� ������
    char databits = 8;  // 7, 8 - ������ �������
    char stopbits = 1;  // 1, 2 - ���-�� ������������ �������� ���
    char parity = 0;    // 0 - ��� �������� ��������, 1 - �������� ��������, �������, 2 - ������
    char iface = 0;     // 0 - USB, 1 - ������



    //�������� ������
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
