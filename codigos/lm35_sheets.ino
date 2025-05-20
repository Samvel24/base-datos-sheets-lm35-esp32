#include <HTTPClient.h>
#include <WiFi.h>

#define adcVrefmV 3300.0
#define resolucionADC 4096.0 // entrada analógica = 12 bits = rango de lectura 0-4095.
#define LM35 36 // El pin GPIO36 (ADC1_0) del ESP32 está conectado al LM35
int lecturaAnalogica = 0;

const char* ssid = "SSID";
const char* password = "Contrasenia_SSID";
const char* serverName = "URL_Google_Sheets";

float milliVolts;
float tempC;
float tempF;
unsigned long timeRead = 0;

void setup() {
  // put your setup code here, to run once:
  initWifi(); // Inicialización de Wi-fi

  Serial.begin(9600);
  
  analogSetAttenuation(ADC_11db);// Se establece la atenuación del ADC a 11 dB (hasta una entrada de ~3,3 V)
}

void loop() {
  // put your main code here, to run repeatedly:
   if (millis() - timeRead > 2000) { // millis devuelve el número de milisegundos transcurridos desde que la placa Arduino comenzó a ejecutar el programa actual
    lecturaAnalogica = analogRead(LM35);

    milliVolts = lecturaAnalogica * (adcVrefmV / resolucionADC);

    tempC = milliVolts / 10;

    tempF = tempC * 9 / 5 + 32;

    Serial.print("Temperatura - ");
    Serial.print(tempC);
    Serial.write("\xC2\xB0");  // Simbolo de grado
    Serial.println("C");
    Serial.print(" - ");
    Serial.print(tempF);
    Serial.println("\xC2\xB0"); // Simbolo de grado
    Serial.println("F");

    enviarAGoogleSheets();

    timeRead = millis();
  }
}

void initWifi() {
  Serial.print("Conectando a: ");
  Serial.print(ssid);

  WiFi.begin(ssid, password); // Inicializa la configuración de red 

  int timeout = 10 * 4;  // Se configura un tiempo de 10 segundos de conexión
  while (WiFi.status() != WL_CONNECTED && (timeout-- > 0)) {
    delay(250); // 250 milisegundos; 1 segundo = 1000 ms // se necesita un total de 40 iteraciones de este ciclo while para esperar la conexión Wi-Fi
    Serial.print(".");
  }
  Serial.println("");

  if (WiFi.status() != WL_CONNECTED) { // Si después de los 10 segundos no se realiza la conexión
    Serial.println("Ha fallado la conexión al Wi-Fi"); // entonces se muestra un mensaje de fallo
  }

  Serial.print("WiFi conectado a la siguiente dirección IP: ");
  Serial.println(WiFi.localIP()); // se muestra la IP que tiene la placa ESP32
}

void enviarAGoogleSheets() {
  if (WiFi.status() == WL_CONNECTED) { // Si la conexión Wi-Fi se realizó correctamente
    HTTPClient http;
    http.begin(serverName); // Analiza una url a la cual se debe conectar
    http.addHeader("Content-Type", "application/json"); // Se agrega una cabecera para compartir información adicional entre el cliente y el servidor, en este caso se indica que se va enviar información en formato JSON

    String jsonData = "{\"tempC\":\"" + String(tempC) + "\", \"tempF\":\"" + String(tempF) + "\"}"; // Cadena JSON a enviar al servidor

    int httpResponseCode = http.POST(jsonData); //  Envía una solicitud de tipo POST (realiza modificaciones en un recurso) al servidor (Proyecto de Google Sheets)

    if (httpResponseCode > 0) {
      String response = http.getString(); // Se obtiene el conjunto de los datos transmitidos útiles (excluyendo otros datos o metadatos que son enviados para facilitar la entrega del mensaje) em forma de cadena
      Serial.println(httpResponseCode);
      Serial.println(response); // Se imprime el conjunto de los datos transmitidos útiles (respuesta del servidor)
    } else {
      Serial.print("Wrong request POST: ");
      Serial.println(httpResponseCode);
    }

    http.end(); // Cuando el conjunto de los datos transmitidos útiles (carga útil) se ha obtenido, entonces esta función se debe llamar.
  }
}
