# Controle de Servo Motor com Raspberry Pi Pico

#Vídeo explicação do projeto


## Sobre o Projeto
Este projeto foi desenvolvido no âmbito do **EmbarcaTech**, como parte do curso de **Formação Básica em Software Embarcado**. 

O objetivo do projeto é controlar um **servo motor** utilizando o **Raspberry Pi Pico W** e a interface **PWM (Pulse Width Modulation)**. 

## Requisitos
Para compilar e executar o projeto, é necessário ter instalado:
- **Visual Studio Code** com as seguintes extensões:
  - CMake
  - CMake Tools
  - Raspberry Pi Pico Project
  - Wokwi (para simulação)
- **SDK do Raspberry Pi Pico** corretamente configurado

## Hardware Utilizado
- **Raspberry Pi Pico W**
- **Servo Motor**

## Como Funciona
1. O código inicia configurando o **PWM** no pino definido para controle do servo motor.
2. O servo é posicionado inicialmente em **180°**, depois em **90°** e, por fim, em **0°**, com um intervalo de 5 segundos entre cada posição.
3. Em seguida, entra em um loop onde o servo oscila suavemente entre **0° e 180°**.

## Funcionamento do Loop Principal
O **loop principal** controla o movimento oscilatório do **servo motor** entre 0° e 180°. Ele opera da seguinte forma:

1. **Definição Inicial**
   - O código inicia com `servo_level = servo_0`, correspondente à posição de 0°.
   - A variável `up_down` é inicializada como `1`, indicando que o servo começará aumentando o ângulo.

2. **Execução Contínua (`while (true)`)**
   O loop principal roda indefinidamente, controlando o movimento do servo motor com os seguintes passos:

   a) **Atualização do PWM**
      ```c
      pwm_set_gpio_level(PWM_SERVO, servo_level);
      ```
      - Define o nível do **PWM**, que controla o **duty cycle** do sinal enviado ao servo.

   b) **Verifica Direção do Movimento**
      - Se `up_down == 1`, o servo **aumenta** o ângulo (`servo_level` cresce).
      - Se `up_down == 0`, o servo **diminui** o ângulo (`servo_level` reduz).

   c) **Movimentação Gradual**
      ```c
      servo_level += SERVO_STEP; // Incremento de 5μs
      sleep_ms(10); // Aguarda 10ms entre cada ajuste
      ```
      - O ângulo do servo aumenta gradualmente até atingir **180°**.
      - Se `servo_level >= servo_180`, a direção inverte (`up_down = 0`).

      **Quando diminuindo:**
      ```c
      servo_level -= SERVO_STEP;
      sleep_ms(10);
      ```
      - O ângulo diminui até **0°**.
      - Ao atingir **servo_0**, a direção inverte (`up_down = 1`).



## Código-Fonte
O programa está implementado em **C** e utiliza a biblioteca **pico/stdlib.h** para manipulação de GPIOs e a biblioteca **hardware/pwm.h** para controle do PWM.

### Configuração do PWM
- **Período**: 20ms (50Hz)
- **Divisor de Clock**: 125
- **WRAP PERIOD**: 20000
- **Duty Cycle**:
  - 0°  -> 0.5ms (~2.5% do período)
  - 90° -> ~1.47ms (~7.35% do período)
  - 180° -> 2.4ms (~12% do período)

## Como Compilar e Executar
1. Configure o ambiente de desenvolvimento para o Raspberry Pi Pico.
2. Compile o projeto utilizando o **CMake**.
3. Transfira o binário gerado para o Pico e reinicie o dispositivo.

## Testes adicionais
Pode-se ainda substituir o a variavel "PWM_SERVO" pelo valor 12 para observar o PWM operando no terminal da cor azul do LED RBG presente na placa BitDogLab e observar a mudança do brilho
do led correspondente a cada Duty Cycle.

## Simulação
Para testar o funcionamento do código sem um hardware físico, é possível utilizar a extensão **Wokwi** do Visual Studio Code para simulação do comportamento do servo motor.

## Autor
**Davi Bezerra Cavalcanti**
