const int inputPin = 2; // D2 pini

void setup() {
  Serial.begin(9600); // Seri portu başlat
  pinMode(inputPin, INPUT); // Giriş pini olarak ayarla
}

void loop() {
  // 32 bitlik giriş sinyalini okuma
  unsigned long inputSignal = digitalReadSignal();

  // D31 ile D14 arasındaki 18 biti ayıklama
  unsigned int extractedBits = (inputSignal >> 14) & 0x0003FFFF;

  // Ayıklanan bitleri seri portta gösterme
  Serial.println(extractedBits);

  delay(1000); // İşlem arasında 1 saniye gecikme
}

unsigned long digitalReadSignal() {
  unsigned long signal = 0;
  for (int i = 0; i < 32; i++) {
    int bitValue = digitalRead(inputPin); // D2 pinden bit değerini oku
    signal = (signal << 1) | bitValue; // Okunan biti sinyale ekle
    delayMicroseconds(1); // Küçük bir gecikme
  }
  return signal;
}

