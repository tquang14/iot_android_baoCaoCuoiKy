#include <Arduino.h>
#include <DHT.h>
#include <BH1750.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <FirebaseArduino.h>

DHT dht(D3, DHT11);
float t = 0;
float h = 0;
float doAm_dat = 0;
int percent_doAm_dat = 0;
float light = 0;
String bom_state = "off";
String phunSuong_state = "off";
String den_state = "off";
String mua = "false";
BH1750 lightMeter(0x23);
#define FIREBASE_HOST "testmyled-aa8f7.firebaseio.com"
#define FIREBASE_AUTH "gn0qcrclXBS7gVjNSNpOaULUn17H4cssN2kRxhie"

void control_relay(String relay1, String relay2, String relay3, String relay4);
void get_state_control();
void set_to_firebase(String anhSang, String doAmDat, String doAmKK, String nhietDo, String mua);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();
  pinMode(D7, INPUT);
  pinMode(D4, OUTPUT);
  pinMode(D0, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  Wire.begin(D2, D1);
  
  if (lightMeter.begin()) {
    Serial.println("dusaduasdsa");    
  } else {
     Serial.println("loi");
  }
  WiFi.begin("Kieu Mai", "0947311163");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  //doc va gui thong tin len firebase
  h = dht.readHumidity();
  t = dht.readTemperature();
  doAm_dat = analogRead(A0);
  percent_doAm_dat = 100 - map(doAm_dat,0, 1024, 0, 100);
  light = lightMeter.readLightLevel();
  Serial.println(h);
  Serial.println(t);
  Serial.println(percent_doAm_dat);
  Serial.print("anh sang: ");
  Serial.println(light);
  // kiem tra mua
  if (!digitalRead(D7)) {
    mua = "true";
    Serial.println("mua");
  } else {
    mua = "false";
    Serial.println("ko mua");
  }
  
  set_to_firebase(String(light), String(percent_doAm_dat), String(h), String(t), mua);
  // lay trang thai cac relay tren firebase
  get_state_control();
  // dieu khien bom
  control_relay(bom_state, phunSuong_state, den_state, "off"); // relay 4 ko dung
  if (bom_state)
  delay(5000);
}

void set_to_firebase(String anhSang, String doAmDat, String doAmKK, String nhietDo, String mua) {
  Firebase.setString("iot_android/anhSang", String(anhSang));
  Firebase.setString("iot_android/doAmDat", String(doAmDat));
  Firebase.setString("iot_android/doAmKK", String(doAmKK));
  Firebase.setString("iot_android/nhietDo", String(nhietDo));
  Firebase.setString("iot_android/mua", mua);
}
void get_state_control() {
  bom_state = Firebase.getString("iot_android_control/bom");
  phunSuong_state = Firebase.getString("iot_android_control/phunSuong");
  den_state = Firebase.getString("iot_android_control/den");
}

void control_relay(String relay1, String relay2, String relay3, String relay4) {
  // relay1
  if (relay1 == "on") {
    digitalWrite(D4, 0);
  } else if (relay1 == "off") {
    digitalWrite(D4, 1);
  }
  // relay 2
  if (relay2 == "on") {
    digitalWrite(D5, 0);
  } else if (relay3 == "off") {
    digitalWrite(D5, 1);
  }
  //relay 3
  if (relay3 == "on") {
    digitalWrite(D6, 0);
  } else if (relay3 == "off") {
    digitalWrite(D6, 1);
  }
  //relay 4
  if (relay4 == "on") {
    digitalWrite(D0, 0);
  } else if (relay4 == "off") {
    digitalWrite(D0, 1);
  }
}
