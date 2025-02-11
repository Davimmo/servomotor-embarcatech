#include <stdio.h> //biblioteca padrão da linguagem C
#include "pico/stdlib.h" //subconjunto central de bibliotecas do SDK Pico
#include "hardware/pwm.h" //biblioteca para controlar o hardware de PWM

#define PWM_servo 22 //pino do LED conectado a GPIO como PWM
const uint16_t WRAP_PERIOD = 24999; //valor máximo do contador - WRAP
const float PWM_DIVISER = 100.0; //divisor do clock para o PWM
const uint16_t SERVO_STEP = 5000; //passo de incremento/decremento para o duty cycle do LED
uint16_t servo_level = 625; //nível inicial do pwm (duty cycle)

//função para configurar o módulo PWM
void pwm_setup()
{
    gpio_set_function(PWM_servo, GPIO_FUNC_PWM); //habilitar o pino GPIO como PWM
    uint slice = pwm_gpio_to_slice_num(PWM_servo); //obter o canal PWM da GPIO
    pwm_set_clkdiv(slice, PWM_DIVISER); //define o divisor de clock do PWM
    pwm_set_wrap(slice, WRAP_PERIOD); //definir o valor de wrap
    pwm_set_enabled(slice, true); //habilita o pwm no slice correspondente
}


//função principal
int main()
{
    sleep_ms(2000);
    stdio_init_all(); //inicializa o sistema padrão de I/O
    
    pwm_setup(); //configura o PWM

    uint up_down = 1; //variável para controlar se o nível do LED aumenta ou diminui

    //loop principal
    while (true) {
        
        pwm_set_gpio_level(PWM_servo, servo_level); //define o nível atual do PWM (duty cycle)
        printf("Ciclo ativo:%d\n", servo_level); // Imprime o duty cycle atual
        // sleep_ms(1000); // Atraso de 1 segundo

        // if (up_down) 
        // {
        //     servo_level += SERVO_STEP; // Incrementa o nível do LED
        //     if (servo_level >= WRAP_PERIOD)
        //         up_down = 0; // Muda direção para diminuir quando atingir o período máximo
        // }
        // else
        // {
        //     servo_level -= SERVO_STEP; // Decrementa o nível do LED
        //     if (servo_level <= SERVO_STEP)
        //         up_down = 1; // Muda direção para aumentar quando atingir o mínimo
        // }

    }
}