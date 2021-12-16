#include <WebServer.h>
#include <WiFi.h>
#include <WiFiUdp.h>


#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;


// the IP of the machine to which you send msgs - this should be the correct IP in most cases (see note in python code)
#define CONSOLE_IP "192.168.1.2 " //.2
#define CONSOLE_PORT 4210
const char* ssid = "ESP32";
const char* password = "12345678";
WiFiUDP Udp;
IPAddress local_ip(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
WebServer server(80);

void setup()
{
  Serial.begin(115200);
  
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  server.begin();

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");
  
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }

mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }  
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }
}

void loop()
{
  Udp.beginPacket(CONSOLE_IP, CONSOLE_PORT);
  // Just test touch pin - Touch0 is T0 which is on GPIO 4.
   /* Udp.printf(String(touchRead(T0)).c_str()); */ 
  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  /* Print out the values */
  Udp.printf("Acceleration X: ");
  Udp.printf("%f", a.acceleration.x);
  Udp.printf(", Y: ");
  Udp.printf("%f", a.acceleration.y);
  Udp.printf(", Z: ");
  Udp.printf("%f", a.acceleration.z);
  Udp.printf(" m/s^2 ");

  Udp.printf("Rotation X: ");
  Udp.printf("%f", g.gyro.x);
  Udp.printf(", Y: ");
  Udp.printf("%f", g.gyro.y);
  Udp.printf(", Z: ");
  Udp.printf("%f", g.gyro.z);
  Udp.printf(" rad/s");
  
  delay(500);
  Udp.endPacket();

  checker(a.acceleration.x, a.acceleration.y, a.acceleration.z);
  
}

static void checker(double AcX, double AcY, double AcZ){
  
  if ((AcX == 0.00) || (AcY == 0.00) && (AcZ == 0.00)){
 WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  server.begin();

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
    
    }
  }
