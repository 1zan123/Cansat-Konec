#include <SoftwareSerial.h>
#include <DHT.h>
#include <Adafruit_BMP280.h>
#include <Wire.h>
#include <Adafruit_HMC5883_U.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <TinyGPS++.h>

// APC220 moduli (TX1/RX1 = 8/9)
SoftwareSerial APC220_1(8, 9);    // Prvi APC220


// DHT22 senzor
#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// BMP280
#define BMP280_ADDRESS 0x77
Adafruit_BMP280 bmp;

// HMC5883L magnetometer
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

// MPU6050
Adafruit_MPU6050 mpu;

// GPS
SoftwareSerial gpsSerial(4, 3);
TinyGPSPlus gps;

// Napetost baterije
#define BATTERY_PIN A0
#define VOLTAGE_DIVIDER_FACTOR 2.0
#define BATTERY_MIN_VOLTAGE 5.5
#define BATTERY_MAX_VOLTAGE 9.0

// Ostalo
const int ledPin = 13;
unsigned long lastUpdate = 0;
const unsigned long updateInterval = 500;
int counter = 0;

// Magnetometer filter
#define FILTER_SIZE 5
float magX_array[FILTER_SIZE] = {0}, magY_array[FILTER_SIZE] = {0}, magZ_array[FILTER_SIZE] = {0};
int filterIndex = 0;

// Kalibracija magnetometra
float offsetX = 10.0, offsetY = -5.0, offsetZ = 3.0;

float readBatteryVoltage() {
    int sensorValue = analogRead(BATTERY_PIN);
    return sensorValue * (5.0 / 1023.0) * VOLTAGE_DIVIDER_FACTOR;
}

int batteryVoltageToPercentage(float voltage) {
    return constrain(((voltage - BATTERY_MIN_VOLTAGE) / (BATTERY_MAX_VOLTAGE - BATTERY_MIN_VOLTAGE)) * 100.0, 0, 100);
}

void updateMagnetometerData(float x, float y, float z) {
    magX_array[filterIndex] = x;
    magY_array[filterIndex] = y;
    magZ_array[filterIndex] = z;
    
    filterIndex = (filterIndex + 1) % FILTER_SIZE;

    float avgX = 0, avgY = 0, avgZ = 0;
    for (int i = 0; i < FILTER_SIZE; i++) {
        avgX += magX_array[i];
        avgY += magY_array[i];
        avgZ += magZ_array[i];
    }
    avgX /= FILTER_SIZE;
    avgY /= FILTER_SIZE;
    avgZ /= FILTER_SIZE;

    magX_array[filterIndex] = avgX;
    magY_array[filterIndex] = avgY;
    magZ_array[filterIndex] = avgZ;
}

void setup() {
    pinMode(ledPin, OUTPUT);
    Serial.begin(115200);
    gpsSerial.begin(115200);
    APC220_1.begin(115200);
    APC220_2.begin(115200);

    dht.begin();
    Wire.begin();

    if (!bmp.begin(BMP280_ADDRESS)) {
        Serial.println("BMP280 ni zaznan!");
        while (1);
    }

    if (!mag.begin()) {
        Serial.println("HMC5883L ni zaznan!");
        while (1);
    }

    if (!mpu.begin()) {
        Serial.println("MPU6050 ni zaznan!");
        while (1);
    }

    bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,
                    Adafruit_BMP280::SAMPLING_X2,
                    Adafruit_BMP280::SAMPLING_X16,
                    Adafruit_BMP280::FILTER_X16,
                    Adafruit_BMP280::STANDBY_MS_500);

    Serial.println("Vsi senzorji inicializirani.");
}

void loop() {
    while (gpsSerial.available() > 0) {
        gps.encode(gpsSerial.read());
    }

    if (millis() - lastUpdate >= updateInterval) {
        lastUpdate = millis();

        float temperature = dht.readTemperature();
        float humidity = dht.readHumidity();
        float pressure = bmp.readPressure() / 100.0;

        sensors_event_t magEvent;
        mag.getEvent(&magEvent);
        float magX = magEvent.magnetic.x - offsetX;
        float magY = magEvent.magnetic.y - offsetY;
        float magZ = magEvent.magnetic.z - offsetZ;
        updateMagnetometerData(magX, magY, magZ);

        sensors_event_t a, g, temp;
        mpu.getEvent(&a, &g, &temp);  // Pospeškometer in žiroskop

        double latitude = gps.location.lat();
        double longitude = gps.location.lng();

        float batteryVoltage = readBatteryVoltage();
        int batteryPercentage = batteryVoltageToPercentage(batteryVoltage);

        digitalWrite(ledPin, HIGH);

        // Pošiljanje podatkov prek APC220_1 (oddajnik)
        SoftwareSerial* apc = &APC220_1;  // ali zamenjaj z &APC220_2 po potrebi
        apc->print(counter); apc->print(",");
        apc->print(temperature, 1); apc->print(",");
        apc->print(humidity, 1); apc->print(",");
        apc->print(batteryPercentage); apc->print(",");
        apc->print(pressure, 2); apc->print(",");
        apc->print(magX_array[filterIndex]); apc->print(",");
        apc->print(magY_array[filterIndex]); apc->print(",");
        apc->print(magZ_array[filterIndex]); apc->print(",");
        apc->print(a.acceleration.x); apc->print(",");
        apc->print(a.acceleration.y); apc->print(",");
        apc->print(a.acceleration.z); apc->print(",");
        apc->print(g.gyro.x); apc->print(",");
        apc->print(g.gyro.y); apc->print(",");
        apc->print(g.gyro.z); apc->print(",");
        apc->print(latitude, 6); apc->print(",");
        apc->println(longitude, 6);

        Serial.println("Podatki poslani.");

        digitalWrite(ledPin, LOW);
        counter++;
    }
}


