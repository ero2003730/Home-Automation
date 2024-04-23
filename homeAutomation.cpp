// Declaração das portas dos pinos como constantes
const int pino1 = 3;   // Porta PWM
const int pino2 = 5;   // Porta PWM
const int pino3 = 6;   // Porta PWM
const int pino4 = 9;   // Porta PWM
const int botao1 = 2;  // Porta digital
const int botao2 = 4;  // Porta digital
const int botao3 = 7;  // Porta digital
const int buzzer = 10; // Porta PWM
const int servomotor = 11; // Porta PWM

// Portas analógicas
const int LDR = 0;  // Sensor LDR na porta analógica A0
const int LM35 = 1; // Sensor de temperatura LM35 na porta analógica A1
const int potenciometro = 2; // Potenciômetro na porta analógica A2

unsigned long previousMillisLM35 = 0;
unsigned long previousMillisLDR = 0;
unsigned long previousMillisPOT = 0;
unsigned long previousMillisBuzzer = 0;

// Variáveis de debounce para cada botão
unsigned long lastDebounceTime1 = 0;
unsigned long lastDebounceTime2 = 0;
unsigned long lastDebounceTime3 = 0;
const long debounceDelay = 50; // debounce delay de 50 milissegundos

int buttonState1 = LOW;
int lastButtonState1 = LOW;
int button1;

int buttonState2 = LOW;
int lastButtonState2 = LOW;
int button2;

int buttonState3 = LOW;
int lastButtonState3 = LOW;
int button3;

struct Temperatura
{
  int temp;
};

Temperatura temperaturas[20];
int contadorTemp = 0;

int tempMedia;
int tempMax;
int tempMin;

bool buzzerState = LOW; // Estado inicial do buzzer
unsigned long buzzerTimer = 0; // Para guardar a última vez que o buzzer mudou de estado
const unsigned long buzzerInterval = 1000; // Intervalo de tempo para ligar/desligar o buzzer

void setup() 
{
  // Configuração dos pinos PWM como saída
  pinMode(pino1, OUTPUT);
  pinMode(pino2, OUTPUT);
  pinMode(pino3, OUTPUT);
  pinMode(pino4, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(servomotor, OUTPUT);

  // Configuração dos botões como entrada
  pinMode(botao1, INPUT);
  pinMode(botao2, INPUT);
  pinMode(botao3, INPUT);
  
  // Configuração dos pinos analógicos 
  pinMode(LDR, INPUT);
  pinMode(LM35, INPUT);
  pinMode(potenciometro, INPUT);

  Serial.begin(9600);
}

void loop() 
{

  // Verificação de debounce para cada botão
  debounceButton1();
  debounceButton2();
  debounceButton3();

  if (button1)
  {
    // logica
    button1 = false;
  }

  if (button2)
  {
    // logica
    button2 = false;
  }

  if (button3)
  {
    // logica
    button3 = false;
  }

  if ((millis() - previousMillisLM35) > 1000)
  {
    funcLM35();
    previousMillisLM35 = millis();
  }
    

  if (millis() - previousMillisLDR >= 500)
  {
    funcLDR();
    previousMillisLDR = millis();
  }
    
  
  if (millis() - previousMillisPOT >= 400)
  {
    funcPOT();
    previousMillisPOT = millis();
  }
    
}

void funcLM35() 
{
  // Ler temperatura do sensor 
  int tempAtual = lerTemperaturaTC(); //tinkercad
  //int tempAtual = lerTemperaturaAD(); //arduino

  Serial.println(tempAtual);
  
  // Armazenar a leitura atual no array e atualizar o contadorTemp
  temperaturas[contadorTemp].temp = tempAtual;
  
  contadorTemp = (contadorTemp + 1) % 20; // Isso fará o contador girar de 0 a 19

  // Calcular média, máximo e mínimo
  for (int i = 0; i < 20; ++i) 
  {
    int temp = temperaturas[i].temp;
    
    tempMedia += temp; // Somando para calcular média depois
    
    if (temp > tempMax) 
    {
      tempMax = temp; // Atualiza o máximo
    }
    if (temp < tempMin) 
    {
      tempMin = temp; // Atualiza o mínimo
    }
  }

  // Finalizar cálculo da média
  tempMedia = tempMedia / 20;

  // Verifica se a temperatura atual é maior que o limite
  controlBuzzer(tempAtual);
}

void funcLDR()
{

}

void funcPOT()
{
  // 
}

// ----------------------------------------------------------------------------------------------------------------
// Funções utilizadas para o sensor de temperatura

// Função para ler a temperatura no Tinkercad
int lerTemperaturaTC() 
{
  int valorADC = analogRead(LM35); // Substitua LM35 pelo seu pino de leitura ADC
  float tensao = valorADC * (5.0 / 1023.0); // Converte o valor ADC para tensão
  int temperaturaC = (tensao - 0.5) * 100; // Converte a tensão para temperatura
  return temperaturaC;
}

// Função para ler a temperatura no Arduino com tensão de referência de 1.1V
int lerTemperaturaAD() 
{
  int valorADC = analogRead(LM35); // Substitua LM35 pelo seu pino de leitura ADC
  float tensao = valorADC * (1.1 / 1023.0); // Converte o valor ADC para tensão com base na tensão de referência de 1.1V
  int temperaturaC = tensao / 0.01; // Converte a tensão para temperatura
  return temperaturaC;
}

// Função para verificar se esta acima do limite de temperatura para o buzzer
void controlBuzzer(int tempAtual) 
{
  // Se a temperatura for maior que 25 graus e o buzzer estiver desligado
  if (tempAtual > 30 && buzzerState == LOW && (millis() - buzzerTimer > buzzerInterval)) 
  {
    buzzerState = HIGH; // Liga o buzzer
    buzzerTimer = millis(); // Reinicia o timer
    analogWrite(buzzer, 1); // Aciona o buzzer
  } 
  // Se o buzzer estiver ligado e o tempo de 1 segundo passou
  else if (buzzerState == HIGH && (millis() - buzzerTimer > buzzerInterval)) 
  {
    buzzerState = LOW; // Desliga o buzzer
    buzzerTimer = millis(); // Reinicia o timer
    analogWrite(buzzer, 0); // Desaciona o buzzer
  }
}


void debounceButton1()
{
  int reading = digitalRead(botao1);

  if (reading != lastButtonState1)
    lastDebounceTime1 = millis();

  if ((millis() - lastDebounceTime1) > 50)
  {
    if (reading != buttonState1)
    {
      buttonState1 = reading;

      if (buttonState1 == HIGH)
      {
        button1 = 1;
      }
    }
  }

  lastButtonState1 = reading;
}

void debounceButton2()
{
  int reading = digitalRead(botao2);

  if (reading != lastButtonState2)
    lastDebounceTime2 = millis();

  if ((millis() - lastDebounceTime2) > 50)
  {
    if (reading != buttonState2)
    {
      buttonState2 = reading;

      if (buttonState2 == HIGH)
      {
        button2 = 1;
      }
    }
  }

  lastButtonState2 = reading;
}

void debounceButton3()
{
  int reading = digitalRead(botao3);

  if (reading != lastButtonState3)
    lastDebounceTime3 = millis();

  if ((millis() - lastDebounceTime3) > 50)
  {
    if (reading != buttonState3)
    {
      buttonState3 = reading;

      if (buttonState3 == HIGH)
      {
        button3 = 1;
      }
    }
  }

  lastButtonState3 = reading;
}
