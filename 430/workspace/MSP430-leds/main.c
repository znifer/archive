#include <msp430.h> 
#include "system_define.h"
#include "system_variable.h"
#include "function_prototype.h"
#include "main.h"

/*
Разработать программу, фиксирующую нажатия клавиш 3, 7 и 0 матричной
клавиатуры включением светодиодов 1, 2 и 3 соответственно. Выход из
цикла опроса осуществляется при нажатии клавиши #. Частота тактовых
импульсов на линии SCL – 70 кГц.
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
// Инициализация модуля UART0 для работы в режиме I2C
void Init_I2C_70hz(){
  P3SEL |= 0x0A;           // Выбор альтернативной функции для линий порта P3
                           // в режиме I2C SDA->P3.1, SCL->P3.3
  U0CTL |= I2C + SYNC;     // Выбрать режим I2C для USART0
  U0CTL &= ~I2CEN;         // Выключить модуль I2C
  // Конфигурация модуля I2C
  //f_scl = fI2C / (I2CPSC + 1) * (I2CSCLH + 2 + I2CSCLL + 2)
  I2CTCTL=I2CSSEL_2;      // SMCLK
  I2CSCLH = 0x21;         // High period of SCL
  I2CSCLL = 0x21;         // Low period of SCL
  U0CTL |= I2CEN;         // Включить модуль I2C
  // формирование строба сброса I2C-регистров PCA9538 - RST_RG1->P3.1 и RST_RG2->P3.2
  P3DIR |= 0x05;            // переключаем эти ножки порта на вывод,
  P3SEL &= ~0x05;           //   выбираем функцию ввода-вывода для них
  P3OUT &= ~0x05;           //   и формируем строб сброса на 1 мс
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
            // Отключим на время?
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
            // Включим на время
            P1IE |= BIT7;
        }
    }
}
