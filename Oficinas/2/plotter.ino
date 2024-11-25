// Definição dos pinos do teclado 4x3
#define ROW1 12
#define ROW2 A0
#define ROW3 A1
#define ROW4 A2
#define COL1 A3
#define COL2 A4
#define COL3 A5

// Pinos dos motores 0, 1, 2, 3 e outros
int pins1[] = {0, 1, 2, 3};  // Pinos conectados ao driver do motor1
int pins2[] = {4, 5, 6, 7};  // Pinos conectados ao driver do motor2
int pins3[] = {8, 9, 10, 11}; // Pinos conectados ao driver do motor3

// Sequência de meio passo para o motor 28BYJ-48
const int halfStepSequence[8][4] = {
  {1, 0, 0, 0},
  {1, 1, 0, 0},
  {0, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 1, 0},
  {0, 0, 1, 1},
  {0, 0, 0, 1},
  {1, 0, 0, 1}
};

int velocidade = 1;          // Velocidade do motor (delay mínimo entre passos)
int movimentoAnterior = 1;   // Alterna entre sentido horário e anti-horário

// Configura os pinos
void setup() {
  // Configura os pinos dos motores como saída
  for (int i = 0; i < 4; i++) {
    pinMode(pins1[i], OUTPUT);
    pinMode(pins2[i], OUTPUT);
    pinMode(pins3[i], OUTPUT);
  }

  // Configura os pinos do teclado como entrada com pull-up
  pinMode(ROW1, INPUT_PULLUP);
  pinMode(ROW2, INPUT_PULLUP);
  pinMode(ROW3, INPUT_PULLUP);
  pinMode(ROW4, INPUT_PULLUP);
  pinMode(COL1, INPUT_PULLUP);
  pinMode(COL2, INPUT_PULLUP);
  pinMode(COL3, INPUT_PULLUP);
}

void loop() {
  // Verifica se alguma tecla foi pressionada
  if (digitalRead(ROW1) == LOW) {
    debounceKey(COL1, '1');
    debounceKey(COL2, '2');
    debounceKey(COL3, '3');
  } else if (digitalRead(ROW2) == LOW) {
    debounceKey(COL1, '4');
    debounceKey(COL2, '5');
    debounceKey(COL3, '6');
  } else if (digitalRead(ROW3) == LOW) {
    debounceKey(COL1, '7');
    debounceKey(COL2, '8');
    debounceKey(COL3, '9');
  } else if (digitalRead(ROW4) == LOW) {
    debounceKey(COL1, '*');
    debounceKey(COL2, '0');
    debounceKey(COL3, '#');
  }
}

// Função para evitar múltiplas leituras (debounce)
void debounceKey(int col, char tecla) {
  if (digitalRead(col) == LOW) {
    delay(50); // Delay para debounce
    if (digitalRead(col) == LOW) {
      teclaPressionada(tecla);
    }
  }
}

// Função chamada quando uma tecla é pressionada
void teclaPressionada(char tecla) {
  if (tecla == '1' || tecla == '3') {
    rotateMotors(1); // Sentido horário
  } else if (tecla == '2') {
    rotateMotors(2); // Sentido anti-horário
  } else {
    // Alterna entre sentido horário e anti-horário
    if (movimentoAnterior == 1) {
      rotateMotors(2); // Sentido anti-horário
      movimentoAnterior = 2;
    } else {
      rotateMotors(1); // Sentido horário
      movimentoAnterior = 1;
    }
  }
  delay(500); // Evita múltiplas leituras
}

// Função para girar os motores
void rotateMotors(int direction) {
  unsigned long startTime = millis();
  unsigned long duration = 3000; // 3 segundos

  while (millis() - startTime < duration) {
    if (direction == 1) {
      for (int step = 0; step < 8; step++) {
        setMotorStep(step, pins1);
        setMotorStep(step, pins2);
        setMotorStep(step, pins3);
        delay(velocidade);
      }
    } else if (direction == 2) {
      for (int step = 7; step >= 0; step--) {
        setMotorStep(step, pins1);
        setMotorStep(step, pins2);
        setMotorStep(step, pins3);
        delay(velocidade);
      }
    }
  }
  stopMotors(pins1);
  stopMotors(pins2);
  stopMotors(pins3);
}

// Define os passos dos motores
void setMotorStep(int step, int pins[]) {
  for (int i = 0; i < 4; i++) {
    digitalWrite(pins[i], halfStepSequence[step][i]);
  }
}

// Para os motores
void stopMotors(int pins[]) {
  for (int i = 0; i < 4; i++) {
    digitalWrite(pins[i], LOW);
  }
}
