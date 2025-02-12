#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define SERVO_PIN 22  // GPIO para o sinal PWM do servomotor

float calculaCiclo(int larg, int per){
    float ciclo;
    ciclo = larg / per *100;
}

// Função para definir o ângulo do servomotor
void set_servo_angle(uint pin, float pulse_us) {
    uint slice_num = pwm_gpio_to_slice_num(pin);
    uint duty = (pulse_us / 20000.0f) * 25000;  // Convertendo microsegundos para ciclo PWM
    pwm_set_gpio_level(pin, duty);
}

int main() {
    stdio_init_all();

    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(SERVO_PIN);
    
    // Configuração da frequência do PWM para aproximadamente 50Hz
    pwm_set_wrap(slice_num, 25000);  // 125MHz / 25000 = 50Hz
    pwm_set_clkdiv(slice_num, 1.0f); // Divisor de clock
    pwm_set_enabled(slice_num, true);
    
    while (true) {
        printf("Movendo para 180 graus\n");
        set_servo_angle(SERVO_PIN, 2400);
        sleep_ms(5000);
        
        printf("Movendo para 90 graus\n");
        set_servo_angle(SERVO_PIN, 1470);
        sleep_ms(5000);
        
        printf("Movendo para 0 graus\n");
        set_servo_angle(SERVO_PIN, 500);
        sleep_ms(5000);

        // Movimento suave de 0 a 180 graus
        printf("Movendo suavemente de 0 a 180 graus\n");
        for (float pulse = 500; pulse <= 2400; pulse += 5) {
            set_servo_angle(SERVO_PIN, pulse);
            sleep_ms(10);
        }

        // Movimento suave de 180 a 0 graus
        printf("Movendo suavemente de 180 a 0 graus\n");
        for (float pulse = 2400; pulse >= 500; pulse -= 5) {
            set_servo_angle(SERVO_PIN, pulse);
            sleep_ms(10);
        }
    }
}
