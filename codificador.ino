const int ledPin0 = 2; // Pin del LED 0 (0 bit)
const int ledPin1 = 3; // Pin del LED 1 (1 bit)
const int ledPinSpace = 4; // Pin del LED para espacio
const int ledPinEnd = 5; // Pin del LED para finalizar mensaje

// Variables para almacenar el estado actual y anterior de cada LED
bool lastStateLed0 = HIGH;
bool lastStateLed1 = HIGH;
bool lastStateLedSpace = HIGH;
bool lastStateLedEnd = HIGH;

int bitIndex = 0; // Índice para la matriz de bits
int bitArray[8] = {0}; // Matriz de 8 bits para almacenar los bits introducidos
String mensaje = ""; // Variable para almacenar el mensaje final

void setup() {
    Serial.begin(9600); // Inicia la comunicación serie
    pinMode(ledPin0, INPUT_PULLUP);
    pinMode(ledPin1, INPUT_PULLUP);
    pinMode(ledPinSpace, INPUT_PULLUP);
    pinMode(ledPinEnd, INPUT_PULLUP);
}

void loop() {
    // Lee el estado actual de cada LED
    bool currentStateLed0 = digitalRead(ledPin0);
    bool currentStateLed1 = digitalRead(ledPin1);
    bool currentStateLedSpace = digitalRead(ledPinSpace);
    bool currentStateLedEnd = digitalRead(ledPinEnd);

    if (currentStateLed0 == LOW && lastStateLed0 == HIGH) {
        Serial.println("0");
        bitArray[bitIndex] = 0;
        bitIndex++;
    }

    
    if (currentStateLed1 == LOW && lastStateLed1 == HIGH) {
        Serial.println("1");
        bitArray[bitIndex] = 1;
        bitIndex++;
    }

    // Verifica si se han recibido 8 bits
    if (bitIndex == 8) {
        char letra = convertirBitsALetra(bitArray);
        mensaje += letra; // Almacena la letra en el mensaje
        Serial.print("Letra detectada: ");
        Serial.println(letra);
        bitIndex = 0; 
    }

    
    
    if (currentStateLedSpace == LOW && lastStateLedSpace == HIGH) {
    Serial.println("S"); // Envía 'S' para indicar un espacio
    }
    if (currentStateLedEnd == LOW && lastStateLedEnd == HIGH) {
    Serial.println("E"); // Envía 'E' para indicar el final del mensaje
    }
    
    lastStateLed0 = currentStateLed0;
    lastStateLed1 = currentStateLed1;
    lastStateLedSpace = currentStateLedSpace;
    lastStateLedEnd = currentStateLedEnd;

    delay(50); // Pequeño retardo para reducir el ruido y los rebotes
}

char convertirBitsALetra(int bits[8]) {
    int valorDecimal = 0;
    for (int i = 0; i < 8; i++) {
        valorDecimal = (valorDecimal << 1) | bits[i]; 
    }
    return char(valorDecimal); 
}