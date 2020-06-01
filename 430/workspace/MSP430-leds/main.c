#include <msp430.h> 
#include "system_define.h"
#include "system_variable.h"
#include "function_prototype.h"
#include "main.h"

/*
����������� ���������, ����������� ������� ������ 3, 7 � 0 ���������
���������� ���������� ����������� 1, 2 � 3 ��������������. ����� ��
����� ������ �������������� ��� ������� ������� #. ������� ��������
��������� �� ����� SCL � 70 ���.
 */

char interrupted = 0;

#pragma vector=PORT1_VECTOR
__interrupt void ISR_p1int(void){
  P1IFG &= ~BIT7;
  interrupted = 1;
}

void interrupt_ready(){
    I2C_WriteByte(0x03, 0x0F, 0x73);
    I2C_WriteByte(0x01, 0x0F, 0x73);
}

void poll_ready(){
    I2C_WriteByte(0x03, 0x0F, 0x73);
    I2C_WriteByte(0x01, 0xFF, 0x73);
}
// ������������� ������ UART0 ��� ������ � ������ I2C
void Init_I2C_70hz(){
  P3SEL |= 0x0A;           // ����� �������������� ������� ��� ����� ����� P3
                           // � ������ I2C SDA->P3.1, SCL->P3.3
  U0CTL |= I2C + SYNC;     // ������� ����� I2C ��� USART0
  U0CTL &= ~I2CEN;         // ��������� ������ I2C
  // ������������ ������ I2C
  //f_scl = fI2C / (I2CPSC + 1) * (I2CSCLH + 2 + I2CSCLL + 2)
  I2CTCTL=I2CSSEL_2;      // SMCLK
  I2CSCLH = 0x21;         // High period of SCL
  I2CSCLL = 0x21;         // Low period of SCL
  U0CTL |= I2CEN;         // �������� ������ I2C
  // ������������ ������ ������ I2C-��������� PCA9538 - RST_RG1->P3.1 � RST_RG2->P3.2
  P3DIR |= 0x05;            // ����������� ��� ����� ����� �� �����,
  P3SEL &= ~0x05;           //   �������� ������� �����-������ ��� ���
  P3OUT &= ~0x05;           //   � ��������� ����� ������ �� 1 ��
  wait_1ms(1);
  P3OUT |= 0x05;
}

void main(void) {
    WDTCTL = WDTPW + WDTHOLD;
    //P1DIR &= ~BIT7;
    P1IE |= BIT7;
    P1IFG &= ~BIT7;
    P1IES |= BIT7;

    _enable_interrupt();
    Init_System_Clock();
    Init_System();
    Init_I2C();
    interrupt_ready();

    char symbol = 0, octPressed = 0;

    while (1){
        if(interrupted){
            // �������� �� �����?
            P1IE &= ~BIT7;
            interrupted = 0;
            symbol = KEYS_scannow();
            if (!octPressed){
                switch (symbol){
                    case '3':
                        LED_set(1);
                        wait_1ms(100);
                        LED_reset(1);
                        break;
                    case '7':
                        LED_set(2);
                        wait_1ms(100);
                        LED_reset(2);
                        break;
                    case '0':
                        LED_set(3);
                        wait_1ms(100);
                        LED_reset(3);
                        break;
                    case '#':
                        octPressed = 1;
                        break;
                }
            }
            interrupt_ready();
            // ������� �� �����
            P1IE |= BIT7;
        }
    }
}
