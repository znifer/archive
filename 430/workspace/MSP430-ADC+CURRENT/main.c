#include <msp430.h> 
#include "stdio.h"
#include "system_define.h"
#include "system_variable.h"
#include "function_prototype.h"
#include "main.h"

const float INA_RS1 = 0.21;              // ������������� �������������, ��
const float INA_RL1 = 30.1;              // ������������� ��������, ��

void init(){
    // ������������� ������
    TACTL = TASSEL0 + MC0;          // ��������� �� ACLK � ������ �����
    TACCTL1 = OUTMOD_3;// + CCIE;      // OUT1 � ����� ���������/�����
    TACCR1 = 250;                   // ����� ���������������
    TACCR0 = 328;                   // ����� ������������

    // ������������� ���
    P6SEL |= BIT0 + BIT1;                       // �������� ��� ADC1, � �������� ��������� ������ ����
    ADC12CTL1 = SHP + CSTARTADD_0               // ������ ������� � ��������� ����� �������������� - ADC12MEM1
    ADC12CTL1 |= CONSEQ1 + CONSEQ0 + SHS_0;     // ����� ������������� ������������������ ������� � ������������� �� ������ 1 ������� �

    // ����� �������� ���������� - Vr+ = V�REF+ = 3.3�, Vr- = AVss = 0�
    //    � �������� ������ ADC1 ��� ������ ������ ADC12MEM1
    ADC12MCTL0 = SREF_3 + INCH_1;
    ADC12MCTL1 = SREF_3 + INCH_1 + EOS;
    ADC12IE |= BIT1;                 // �������� ���������� �� ���
    ADC12CTL0 |= ENC;                // ��������� ��������������
    ADC12CTL0 |= ADC12ON;            // �������� ���
}

float curr = 0;
// �������� ��� ����������
// ��� � ������ ������ �������
// 10ms
// ������������ �������
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
        sprintf(text, "����. ��� = %f", curr);
        LCD_set_pos(0, 0);
        LCD_message(text);
        LED_invert();           // ��������/��������� ����, ����� �������� �����������
        wait_1ms(2000);

    }
}

#pragma vector = ADC12_VECTOR
__interrupt void ADC_interrupt(void){
    //ADC12CTL0 &= ~ENC;      // ��������� ��������������
    curr = (ADC12MEM1 * 3.3) / (4095.0 * INA_RS1 * INA_RL1);
    //ADC12CTL0 |= ENC;       // ��������� ��������������
}
