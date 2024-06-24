const int sensorTempPin = A0;
const int sensorLightPin = A1;
const int ledPin = 13;
const int buzzerPin = 12;
const int numSamples = 30;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  lcd.begin(16, 2);
  lcd.print("Blueshield");
}

void loop() {
  float tempSum = 0;
  float lightSum = 0;
  
  for (int i = 0; i < numSamples; i++) {
    tempSum += analogRead(sensorTempPin);
    lightSum += analogRead(sensorLightPin);
    delay(2000); 
  }
  
  float tempAvg = tempSum / numSamples;
  float lightAvg = lightSum / numSamples;

  float tempCelsius = (tempAvg * 5.0 / 1024.0) * 100.0;
  float lightPercent = (lightAvg / 1024.0) * 100.0;

  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(tempCelsius);
  lcd.print("C ");
  lcd.print("Light: ");
  lcd.print(lightPercent);
  lcd.print("%");

  if (tempCelsius > 23.0) {
    digitalWrite(ledPin, HIGH);
    tone(buzzerPin, 1000, 500);
    logData(tempCelsius, lightPercent);
  } else {
    digitalWrite(ledPin, LOW);
  }
}
