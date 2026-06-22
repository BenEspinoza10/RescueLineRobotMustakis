// ============================================================
//  Red Neuronal - Clasificador de Color Verde
//  ESP32 + Arduino IDE
//  Arquitectura: 3 → 6 → 4 → 1
//  Activación: ReLU (capas ocultas), Sigmoid (salida)
// ============================================================

// ---------- Hiperparámetros ---------------------------------
#define INPUT_SIZE   3
#define HIDDEN1_SIZE 6
#define HIDDEN2_SIZE 4
#define OUTPUT_SIZE  1
#define LEARNING_RATE 0.05f
#define EPOCHS        2000
#define PRINT_EVERY   200   // Imprime loss cada N épocas

// ---------- Pesos y biases ----------------------------------
// Capa 1: INPUT → HIDDEN1
float w1[INPUT_SIZE][HIDDEN1_SIZE];
float b1[HIDDEN1_SIZE];
// Capa 2: HIDDEN1 → HIDDEN2
float w2[HIDDEN1_SIZE][HIDDEN2_SIZE];
float b2[HIDDEN2_SIZE];
// Capa 3: HIDDEN2 → OUTPUT
float w3[HIDDEN2_SIZE][OUTPUT_SIZE];
float b3[OUTPUT_SIZE];

// ---------- Activaciones (forward pass) ---------------------
float a1[HIDDEN1_SIZE];   // salida capa oculta 1
float a2[HIDDEN2_SIZE];   // salida capa oculta 2
float a3[OUTPUT_SIZE];    // salida final

// ---------- Gradientes (backward pass) ----------------------
float d3[OUTPUT_SIZE];
float d2[HIDDEN2_SIZE];
float d1[HIDDEN1_SIZE];

// ---------- Dataset de entrenamiento ------------------------
// Formato: {R, G, B, es_verde?}
// Valores normalizados 0.0–1.0  (divide por 255 al ingresar)
// Ajusta o amplía este dataset según tu sensor / necesidades
const float X[][3] = {
  // ---- Verdes ----
  {0.00f, 1.00f, 0.00f},   // verde puro
  {0.13f, 0.55f, 0.13f},   // forest green
  {0.24f, 0.70f, 0.44f},   // medium sea green
  {0.56f, 0.93f, 0.56f},   // pale green
  {0.00f, 0.50f, 0.00f},   // dark green
  {0.60f, 0.98f, 0.60f},   // honeydew-ish
  {0.20f, 0.80f, 0.20f},   // lime-ish
  {0.18f, 0.55f, 0.34f},   // sea green
  // ---- No verdes ----
  {1.00f, 0.00f, 0.00f},   // rojo
  {0.00f, 0.00f, 1.00f},   // azul
  {1.00f, 1.00f, 0.00f},   // amarillo
  {1.00f, 0.65f, 0.00f},   // naranja
  {0.50f, 0.00f, 0.50f},   // morado
  {1.00f, 1.00f, 1.00f},   // blanco
  {0.00f, 0.00f, 0.00f},   // negro
  {0.50f, 0.50f, 0.50f},   // gris
};
const float Y[] = {
  1,1,1,1,1,1,1,1,   // verdes
  0,0,0,0,0,0,0,0    // no verdes
};
const int N_SAMPLES = sizeof(Y) / sizeof(Y[0]);

// ============================================================
//  Funciones de activación
// ============================================================
float relu(float x)    { return x > 0.0f ? x : 0.0f; }
float relu_d(float x)  { return x > 0.0f ? 1.0f : 0.0f; }
float sigmoid(float x) { return 1.0f / (1.0f + expf(-x)); }

// ============================================================
//  Inicialización de pesos (Xavier simplificado)
// ============================================================
float randWeight(int fan_in) {
  float limit = sqrtf(2.0f / fan_in);
  // Genera un número aleatorio en [-limit, limit]
  return ((float)random(-1000, 1000) / 1000.0f) * limit;
}

void initWeights() {
  randomSeed(42);  // Semilla fija para reproducibilidad; cámbiala si quieres variedad
  for (int i = 0; i < INPUT_SIZE;   i++)
    for (int j = 0; j < HIDDEN1_SIZE; j++)
      w1[i][j] = randWeight(INPUT_SIZE);
  for (int j = 0; j < HIDDEN1_SIZE; j++) b1[j] = 0.0f;

  for (int i = 0; i < HIDDEN1_SIZE; i++)
    for (int j = 0; j < HIDDEN2_SIZE; j++)
      w2[i][j] = randWeight(HIDDEN1_SIZE);
  for (int j = 0; j < HIDDEN2_SIZE; j++) b2[j] = 0.0f;

  for (int i = 0; i < HIDDEN2_SIZE; i++)
    for (int j = 0; j < OUTPUT_SIZE; j++)
      w3[i][j] = randWeight(HIDDEN2_SIZE);
  for (int j = 0; j < OUTPUT_SIZE; j++) b3[j] = 0.0f;
}

// ============================================================
//  Forward pass
// ============================================================
void forward(const float* x) {
  // --- Capa 1 ---
  for (int j = 0; j < HIDDEN1_SIZE; j++) {
    float z = b1[j];
    for (int i = 0; i < INPUT_SIZE; i++) z += x[i] * w1[i][j];
    a1[j] = relu(z);
  }
  // --- Capa 2 ---
  for (int j = 0; j < HIDDEN2_SIZE; j++) {
    float z = b2[j];
    for (int i = 0; i < HIDDEN1_SIZE; i++) z += a1[i] * w2[i][j];
    a2[j] = relu(z);
  }
  // --- Capa salida ---
  for (int j = 0; j < OUTPUT_SIZE; j++) {
    float z = b3[j];
    for (int i = 0; i < HIDDEN2_SIZE; i++) z += a2[i] * w3[i][j];
    a3[j] = sigmoid(z);
  }
}

// ============================================================
//  Backward pass + actualización de pesos
// ============================================================
void backward(const float* x, float y_true) {
  // --- Delta salida (BCE loss derivada × sigmoid derivada) ---
  // dL/dz3 = (a3 - y_true)
  for (int j = 0; j < OUTPUT_SIZE; j++)
    d3[j] = a3[j] - y_true;

  // --- Delta capa 2 ---
  for (int i = 0; i < HIDDEN2_SIZE; i++) {
    float sum = 0.0f;
    for (int j = 0; j < OUTPUT_SIZE; j++) sum += d3[j] * w3[i][j];
    d2[i] = sum * relu_d(a2[i]);
  }

  // --- Delta capa 1 ---
  for (int i = 0; i < HIDDEN1_SIZE; i++) {
    float sum = 0.0f;
    for (int j = 0; j < HIDDEN2_SIZE; j++) sum += d2[j] * w2[i][j];
    d1[i] = sum * relu_d(a1[i]);
  }

  // --- Actualizar w3, b3 ---
  for (int i = 0; i < HIDDEN2_SIZE; i++)
    for (int j = 0; j < OUTPUT_SIZE; j++)
      w3[i][j] -= LEARNING_RATE * d3[j] * a2[i];
  for (int j = 0; j < OUTPUT_SIZE; j++)
    b3[j] -= LEARNING_RATE * d3[j];

  // --- Actualizar w2, b2 ---
  for (int i = 0; i < HIDDEN1_SIZE; i++)
    for (int j = 0; j < HIDDEN2_SIZE; j++)
      w2[i][j] -= LEARNING_RATE * d2[j] * a1[i];
  for (int j = 0; j < HIDDEN2_SIZE; j++)
    b2[j] -= LEARNING_RATE * d2[j];

  // --- Actualizar w1, b1 ---
  for (int i = 0; i < INPUT_SIZE; i++)
    for (int j = 0; j < HIDDEN1_SIZE; j++)
      w1[i][j] -= LEARNING_RATE * d1[j] * x[i];
  for (int j = 0; j < HIDDEN1_SIZE; j++)
    b1[j] -= LEARNING_RATE * d1[j];
}

// ============================================================
//  Entrenamiento completo
// ============================================================
void trainModel() {
  Serial.println("=== Iniciando entrenamiento ===");
  for (int epoch = 1; epoch <= EPOCHS; epoch++) {
    float loss = 0.0f;
    for (int s = 0; s < N_SAMPLES; s++) {
      forward(X[s]);
      backward(X[s], Y[s]);
      // Binary cross-entropy: -[y·log(p) + (1-y)·log(1-p)]
      float p = a3[0];
      p = constrain(p, 1e-7f, 1.0f - 1e-7f);  // evita log(0)
      loss += -(Y[s] * logf(p) + (1.0f - Y[s]) * logf(1.0f - p));
    }
    loss /= N_SAMPLES;

    if (epoch % PRINT_EVERY == 0 || epoch == 1) {
      Serial.printf("Época %4d / %d  |  Loss: %.4f\n", epoch, EPOCHS, loss);
    }
  }
  Serial.println("=== Entrenamiento finalizado ===\n");
}

// ============================================================
//  Predicción (entrada en 0–255)
// ============================================================
bool predictColor(int r, int g, int b) {
  float input[3] = {r / 255.0f, g / 255.0f, b / 255.0f};
  forward(input);
  return a3[0] >= 0.5f;
}

float predictProb(int r, int g, int b) {
  float input[3] = {r / 255.0f, g / 255.0f, b / 255.0f};
  forward(input);
  return a3[0];
}

// ============================================================
//  Evaluación sobre el dataset
// ============================================================
void evaluateModel() {
  int correct = 0;
  Serial.println("--- Evaluación sobre datos de entrenamiento ---");
  for (int s = 0; s < N_SAMPLES; s++) {
    forward(X[s]);
    bool pred = a3[0] >= 0.5f;
    bool real = Y[s] > 0.5f;
    if (pred == real) correct++;
    Serial.printf("  RGB(%.0f,%.0f,%.0f) → prob=%.3f  pred=%s  real=%s  %s\n",
      X[s][0]*255, X[s][1]*255, X[s][2]*255,
      a3[0],
      pred ? "VERDE" : "NO",
      real ? "VERDE" : "NO",
      pred == real ? "✓" : "✗");
  }
  Serial.printf("\nPrecisión: %d / %d (%.1f%%)\n\n", correct, N_SAMPLES,
                100.0f * correct / N_SAMPLES);
}

// ============================================================
//  Lectura del monitor serial (modo interactivo)
//  Formato esperado: "R,G,B"  ej: "0,200,50"
// ============================================================
void handleSerial() {
  if (!Serial.available()) return;
  String line = Serial.readStringUntil('\n');
  line.trim();
  if (line.length() == 0) return;

  int r, g, b;
  if (sscanf(line.c_str(), "%d,%d,%d", &r, &g, &b) == 3) {
    r = constrain(r, 0, 255);
    g = constrain(g, 0, 255);
    b = constrain(b, 0, 255);
    float prob = predictProb(r, g, b);
    bool es_verde = prob >= 0.5f;
    Serial.printf("RGB(%d,%d,%d) → %.3f → %s\n",
                  r, g, b, prob, es_verde ? "*** VERDE ***" : "no es verde");
  } else {
    Serial.println("Formato incorrecto. Usa: R,G,B  (ej: 0,200,50)");
  }
}

// ============================================================
//  Setup & Loop
// ============================================================
void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n=============================================");
  Serial.println("  Clasificador de Color Verde - ESP32 NN");
  Serial.println("=============================================");

  initWeights();
  trainModel();
  evaluateModel();

  Serial.println("Ingresa un color como R,G,B para clasificarlo:");
  Serial.println("Ejemplo: 0,180,40");
}

void loop() {
  handleSerial();
  delay(10);
}
