#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <DHT.h>
#include <NewPing.h>  // Include the NewPing library for HC-SR04 sonar sensor

#define DHTPIN D5
#define DHTTYPE DHT22
#define TRIGGER_PIN D6   // Define the pin for the sonar sensor trigger
#define ECHO_PIN D7      // Define the pin for the sonar sensor echo

DHT dht(DHTPIN, DHTTYPE);
WiFiClient client;
String URL = "http://192.168.0.110/env_project/test_data.php";

const char* ssid = "FARHADET_2.4GHz@unifi";
const char* password = "11sambungan";

int temperature = 0;
int humidity = 0;
int distance = 0;

NewPing sonar(TRIGGER_PIN, ECHO_PIN);  // Initialize sonar sensor

void setup() {
    Serial.begin(115200);
    dht.begin();
    connectWiFi();
}

void loop() {
    if (WiFi.status() != WL_CONNECTED) {
        connectWiFi();
    }

    Load_DHT22_Data();
    readSonarData();

    String postData = "temperature=" + String(temperature) + "&humidity=" + String(humidity) + "&distance=" + String(distance);

    HTTPClient http;
    http.begin(client, URL);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    int httpCode = http.POST(postData);
    String payload = "";

    if (httpCode > 0) {
        if (httpCode == HTTP_CODE_OK) {
            payload = http.getString();
            Serial.println("Server response: " + payload);  // Print server response
        } else {
            Serial.printf("[HTTP] POST... code: %d\n", httpCode);
        }
    } else {
        Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();

    Serial.print("URL : "); Serial.println(URL); 
    Serial.print("Data: "); Serial.println(postData);
    Serial.print("httpCode: "); Serial.println(httpCode);
    Serial.println("--------------------------------------------------");

    delay(10000);
}

void Load_DHT22_Data() {
    temperature = dht.readTemperature();
    humidity = dht.readHumidity();

    if (isnan(temperature) || isnan(humidity)) {
        Serial.println("Failed to read from DHT sensor!");
        temperature = 0;
        humidity = 0;
    }

    Serial.printf("Temperature: %d °C\n", temperature);
    Serial.printf("Humidity: %d %%\n", humidity);
}

void readSonarData() {
    unsigned int uS = sonar.ping();
    distance = sonar.convert_cm(uS);

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
}

void connectWiFi() {
    WiFi.mode(WIFI_OFF);
    delay(1000);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.println("Connecting to WiFi");

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}
