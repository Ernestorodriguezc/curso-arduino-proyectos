// Pruebas de variso sensores DHT11 de temperatura/humedad
// Ha requerido las siguientes librerias de Arduino:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

#include "DHT.h"

#define DHTPINA 2     // El pin digital elegido para el DHT sensor 1
#define DHTPINB 4     // El pin digital elegido para el DHT sensor 2

#define DHTTYPE DHT11   // El tipo de sensores elegidos son DHT 11

// Initialize DHT sensor.

DHT dht1(DHTPINA, DHTTYPE);
DHT dht2(DHTPINB, DHTTYPE);


void setup() {
  Serial.begin(115200);
  Serial.println(F("Media temperaturas y humedad de dos sensores DHT11"));

  dht1.begin();
  dht2.begin();
}

void loop() {
  // Espero 4 segundos para cada una de las medidas.
  delay(4000);

// no se ha considerado ningún bucle del tipo for (float j = 0; j <= 1; j++) por tener unicamente dos sensores
// Tomar las lecturas de la temperatura lleva unos 250 milliseconds!

  float h1 = dht1.readHumidity();
  float h2 = dht2.readHumidity();
  // Leermos la temperatura en grados centigrados (the default)
  float t1 = dht1.readTemperature();
  float t2 = dht2.readTemperature();

// Chequeamos las lecturas por si hay algún error.
  if (isnan(h1) || isnan(t1)) {
    Serial.println(F("Error al leer desde el sensor DHT1!"));
    return;
  }
  
  if (isnan(h2) || isnan(t2)) {
    Serial.println(F("Error al leer desde el sensor DHT2!"));
    return;
  }
  
  // Sensación termica en Celsius (isFahreheit = false)
  float hic1 = dht1.computeHeatIndex(t1, h1, false);
  float hic2 = dht2.computeHeatIndex(t2, h2, false);
  
  Serial.print(F("Humidity 1: ")); 
  Serial.print(h1);
  Serial.print(F("%  Humidity 2: ")); 
  Serial.print(h2); 
  Serial.println(F("% "));
  
  Serial.print(F("Temperature 1: ")); 
  Serial.print(t1);
  Serial.print(F("°C  Temperatura 2: ")); 
  Serial.print(t2);
  Serial.println(F("°C "));
  Serial.print(F("Sensación Térmica 1: "));
  Serial.print(hic1); Serial.print(F("°C "));
  Serial.print(F("Sensación Térmica 2: "));
  Serial.print(hic2); Serial.println(F("°C "));

  Serial.println("=================================");
 // calculamos la media de sensación termica entre los dos sensores

  float m = ( hic1 + hic2 )/ 2;
  Serial.println("Sensación termica media: ");
  Serial.print((int)m); 
  Serial.println(" ºC, ");
  Serial.println("=================================");
  Serial.println(" ");
}
