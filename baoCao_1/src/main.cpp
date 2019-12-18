#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <BH1750.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <FirebaseArduino.h>

DHT dht(D3, DHT11);
// khai bao cac bien luu gia tri cam bien va cac bien chua gia tri de bat tat thiet bi
float t = 0, t_auto = 0;
float h = 0, h_auto = 0;
float doAm_dat = 0;
int percent_doAm_dat = 0, percent_doAm_dat_auto = 0;
float light = 0, light_auto = 0;
// cac bien trang thai
String bom_state = "off";
String phunSuong_state = "off";
String den_state = "off";
String mua = "false";
String mode = "manual";

BH1750 lightMeter(0x23);
#define FIREBASE_HOST "testmyled-aa8f7.firebaseio.com"
#define FIREBASE_AUTH "gn0qcrclXBS7gVjNSNpOaULUn17H4cssN2kRxhie"

void control_relay(String relay1, String relay2, String relay3, String relay4);
void get_state_control();
void set_to_firebase(String anhSang, String doAmDat, String doAmKK, String nhietDo, String mua);
void get_auto_val();

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
  // kiem tra mua
  if (!digitalRead(D7)) {
    mua = "true";
  } else {
    mua = "false";
  }
  set_to_firebase(String(light), String(percent_doAm_dat), String(h), String(t), mua);
  
  // neu che do hoat dong la auto
  if (mode == "auto") {
    // lay cac gia tri dk tu dong
    get_auto_val();
    // kiem tra nhiet do kk
    if (t_auto > t) { 
      Firebase.setString("iot_android_control/den", "on");
    } else {
      Firebase.setString("iot_android_control/den", "off");
    }
    // kiem tra do am dat
    if (percent_doAm_dat_auto > percent_doAm_dat) {
      Firebase.setString("iot_android_control/bom", "on");
    } else {
      Firebase.setString("iot_android_control/bom", "off");
    }
    // kiem tra do am kk
    if (h_auto > h) {
      Firebase.setString("iot_android_control/phunSuong", "on");
    } else {
      Firebase.setString("iot_android_control/phunSuong", "off");
    }
    // neu anh sang cai dat < anh sang hien tai => dong mai nha
    if (light < light_auto) {
      // sang led
      Serial.println("sang led");
    } else {
      // tat led
      Serial.println("tat led");
    }
    delay(5000);
  }
  // lay trang thai cac relay tren firebase
  get_state_control();
  // dieu khien bom
  control_relay(bom_state, phunSuong_state, den_state, "off"); // relay 4 ko dung
  delay(1000);
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
  mode = Firebase.getString("iot_android_control/mode");
}

void get_auto_val() {
  // lay thong tin tu firebase va ep sang kieu float
  light_auto = Firebase.getString("auto_val/anhSang").toFloat();
  percent_doAm_dat_auto = Firebase.getString("auto_val/doAmDat").toInt();
  h_auto = Firebase.getString("auto_val/doAmKK").toFloat();
  t_auto = Firebase.getString("auto_val/nhietDo").toFloat();
  Serial.println(light_auto);
  Serial.println(percent_doAm_dat_auto);
  Serial.println(h_auto);
  Serial.println(t_auto);
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