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
const int LDR = A0;  // Sensor LDR na porta analógica A0
const int LM35 = A1; // Sensor de temperatura LM35 na porta analógica A1
const int potenciometro = A2; // Potenciômetro na porta analógica A2

unsigned long previousMillisLM35 = 0;
unsigned long previousMillisLDR = 0;
unsigned long previousMillisPOT = 0;

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

  if (millis() - previousMillisLM35 >= 1000)
  {
    LM35();
    previousMillisLM35 = millis();
  }
    

  if (millis() - previousMillisLDR >= 500)
  {
    LDR();
    previousMillisLDR = millis();
  }
    
  
  if (millis() - previousMillisPOT >= 400)
  {
    POT();
    previousMillisPOT = millis();
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

void LM35()
{
  //
}

void LDR()
{
  //
}

void POT()
{
  // 
}
