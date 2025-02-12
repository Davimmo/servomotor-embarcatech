#include <stdio.h> //biblioteca padrão da linguagem C
#include "pico/stdlib.h" //subconjunto central de bibliotecas do SDK Pico
#include "hardware/pwm.h" //biblioteca para controlar o hardware de PWM

//Ajustes nécessarios para colocar o clock em 50Hz que corresponde ao périodo de 20ms

#define PWM_SERVO 22 //pino do LED conectado a GPIO como PWM
//Altere o valor para 12 para testar no terminal da cor azul do LED RGB da BitDogLab

const uint16_t WRAP_PERIOD = 20000; //valor máximo do contador - WRAP
const float PWM_DIVISER = 125.f; //divisor do clock para o PWM
const uint16_t SERVO_STEP = 5; //passo de incremento/decremento para o duty cycle que corresponde a 5μs
uint16_t servo_180 = WRAP_PERIOD*0.12f; //nível inicial do pwm (duty cycle)
uint16_t servo_90 = WRAP_PERIOD*0.0735f;
uint16_t servo_0 = WRAP_PERIOD*0.025f;
uint16_t servo_level = WRAP_PERIOD*0.025f;


//função para configurar o módulo PWM

void pwm_setup()
{
    gpio_set_function(PWM_SERVO, GPIO_FUNC_PWM); //habilitar o pino GPIO como PWM
    uint slice = pwm_gpio_to_slice_num(PWM_SERVO); //obter o canal PWM da GPIO
    pwm_set_clkdiv(slice, PWM_DIVISER); //define o divisor de clock do PWM
    pwm_set_wrap(slice, WRAP_PERIOD); //definir o valor de wrap
    pwm_set_gpio_level(PWM_SERVO,servo_180);
    pwm_set_enabled(slice, true); //habilita o pwm no slice correspondente
}


//função principal
int main(){
    stdio_init_all(); //inicializa o sistema padrão de I/O
    
    pwm_setup(); //configura o PWM
    sleep_ms(5000); //Aguarda 5 segundos na posição inicial de 180°

    pwm_set_gpio_level(PWM_SERVO,servo_90);
    sleep_ms(5000); //Aguarda 5 segundos em 90°

    pwm_set_gpio_level(PWM_SERVO,servo_0);
    sleep_ms(5000); //Aguarda 5 segundos na posição de 0°
    
    uint up_down = 1; //variável para controlar se o nível do LED aumenta ou diminui

    //loop principal
    while (true) {
        
        // printf("Ciclo ativo:%d\n", led_level);//imprimir ciclo ativo do PWM - valor máximo é 2000
        pwm_set_gpio_level(PWM_SERVO, servo_level); //define o nível atual do PWM (duty cycle)


        if (up_down) 
        {
            servo_level += SERVO_STEP; // Incrementa a posição do servo
            sleep_ms(10);
            if (servo_level >= servo_180)
                up_down = 0; // Muda direção para diminuir quando atingir o período máximo
        }
        else
        {
            servo_level -= SERVO_STEP; // Decrementa a posição do servo
            sleep_ms(10);
            if (servo_level <= servo_0)
                up_down = 1; // Muda direção para aumentar quando atingir o mínimo
        }

    }
}