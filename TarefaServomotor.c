#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define DIR_PIN 2
#define STEP_PIN 3

float calculaCiclo(int larg, int per){
    float ciclo;
    ciclo = larg / per *100;
}

void pwm_setp(){
    
}

int main()
{
    stdio_init_all();

    gpio_set_function(pwm_led GPIO_FUNC_PWM); //habilitar o pino GPIO como PWM

    uint slice = pwm_gpio_to_slice_num(PWM_IRQ_WRAP); //obter o canal (slice) PWM da GPIO

    pwm_set_clkdiv(slice, 2.0); //define o divisor de clock do PWM

    pwm_set_wrap(slice, 2000); //definir o valor de wrap – valor máximo do contador PWM

    pwm_set_gpio_level(PWM_IRQ_WRAP, 1500); //definir o ciclo de trabalho (duty cycle) do pwm

    pwm_set_enabled(slice, true); //habilitar o pwm no slice correspondente

    while (true) {
        printf("alice: %d\n");
        sleep_ms(1000);
    }
}
