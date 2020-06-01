#include <msp430.h> 
#include "stdio.h"
#include "system_define.h"
#include "system_variable.h"
#include "function_prototype.h"
#include "main.h"

const float INA_RS1 = 0.21;              // измерительное сопротивление, Ом
const float INA_RL1 = 30.1;              // сопротивление нагрузки, Ом

void init(){
    // Конфигурируем таймер
    TACTL = TASSEL0 + MC0;          // Тактуемся от ACLK в режиме вверх
    TACCTL1 = OUTMOD_3;// + CCIE;      // OUT1 в режим установка/сброс
    TACCR1 = 250;                   // Выход устанавливается
    TACCR0 = 328;                   // Выход сбрасывается

    // Конфигурируем АЦП
    P6SEL |= BIT0 + BIT1;                       // Выбираем АЦП ADC1, к которому подключен датчик тока
    ADC12CTL1 = SHP + CSTARTADD_0               // таймер выборки и стартовый адрес преобразования - ADC12MEM1
    ADC12CTL1 |= CONSEQ1 + CONSEQ0 + SHS_0;     // режим повторяющаяся последовательность каналов и синхронизация по выходу 1 таймера А

    // выбор опорного напряжения - Vr+ = VеREF+ = 3.3В, Vr- = AVss = 0В
    //    и входного канала ADC1 для ячейки памяти ADC12MEM1
    ADC12MCTL0 = SREF_3 + INCH_1;
    ADC12MCTL1 = SREF_3 + INCH_1 + EOS;
    ADC12IE |= BIT1;                 // Включить прерывания от АЦП
    ADC12CTL0 |= ENC;                // Разрешить преобразования
    ADC12CTL0 |= ADC12ON;            // Включить АЦП
}

float curr = 0;
// Включить все светодиоды
// ацп в режиме послед выборки
// 10ms
// Длительность выборки
void main(void) {
    WDTCTL = WDTPW + WDTHOLD;
    Init_System_Clock();
    Init_System();
    Init_I2C();
    LCD_init();
    LCD_set_pos(0, 0);
    _enable_interrupt();
    init();
    char text[40] = "";
    while(1){
        sprintf(text, "Потр. ток = %f", curr);
        LCD_set_pos(0, 0);
        LCD_message(text);
        LED_invert();           // включаем/выключаем свет, чтобы менялось потребление
        wait_1ms(2000);

    }
}

#pragma vector = ADC12_VECTOR
__interrupt void ADC_interrupt(void){
    //ADC12CTL0 &= ~ENC;      // Запрещаем преобразование
    curr = (ADC12MEM1 * 3.3) / (4095.0 * INA_RS1 * INA_RL1);
    //ADC12CTL0 |= ENC;       // Разрешаем преобразование
}
