#include "wiringPi.h"
#include "time.h"

//Autor: Hemerson Rafael
//Data: 28/07/17

//Fun��o que calcular o per�odo a partir da frequ�ncia (Hz)
float Period(float frequency){

    return (1.00/frequency);

}

//Fun��o respons�vel pela gera��o de sinais PWM, possui os seguintes par�metros frequ�ncia (Hz), duty cycle (%), pino de sa�da e tempo de execu��o (s).
void SignalGenerator(float frequency, float duty_cycle, int pin_out, float time_execution){

    float time_on, time_off, time_stop;
    if((duty_cycle >= 0) && (duty_cycle <= 100) && (time_execution > 0)){
        // c�lculo do tempo do pulso em baixa
        time_off = Period(frequency) - time_on;

        // c�lculo do tempo do pulso em alta (de acordo com valor do ciclo ativo )
        float time_on = Period(frequency) * (duty_cycle/100.00);

        clock_t t1, t2;
        //Salva o n�mero de clock inicial
        t1 = clock();

        // Loop para controle do tempo de execu��o
        do{
            // fun��o da biblioteca wiringPi que instruir GPIO que mantenha o n�vel l�gico do pin_out em alta (HIGH ou 1)
            digitalWhite(pin_out, 1);
            //Tempo em que o sinal estar� em alta
            delay(time_on);
            // fun��o da biblioteca wiringPi que instruir GPIO que mantenha o n�vel l�gico do pin_out em baixa (LOW ou 0)
            digitalWhite(pin_out, 0);
            //Tempo em que o sinal estar� em baixa
            delay(time_off);
            //Salva o n�mero de clock inicial
            t2 = clock();

            //C�lculo do tempo de execu��o em segundos
            time_stop = (float)(t2 - t1)/CLOCKS_PER_SEC;
        //While para testa se o tempo de parada foi atingido e finalizar o la�o
        }while(time_stop < time_execution);
    }

}

int main(){

}
