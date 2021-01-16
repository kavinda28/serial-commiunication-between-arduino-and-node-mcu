#include <FirebaseArduino.h>
#include <DHT.h>
//#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
//#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>
//#include <SimpleTimer.h>

//pin tx-2,rx-3

String myString; // complete message from arduino, which consistors of snesors data
char rdata; // received charactors

int firstVal, secondVal,thirdVal; // sensors 
// This function sends Arduino's up time every second to Virtual Pin (1).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.

//firebase code.......
#define FIREBASE_HOST "mys01-dd445.firebaseio.com"
#define FIREBASE_AUTH "FNFkRN9Kh0GhnwEDm25IT7JRC7CxpntdyebR1IWx"
#define WIFI_SSID "Dialog 4G" // Change the name of your WIFI
#define WIFI_PASSWORD "E7741EE3" // Change the password of your WIFI

#define DHTPIN 14    // Data Pin of DHT 11 , for NodeMCU D5 GPIO no. is 14

#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);
int c=0,p1=0,p2=0,k1=0;
float n1;

void setup()
{
  // Debug console
  Serial.begin(9600);

WiFi.begin (WIFI_SSID, WIFI_PASSWORD);
   while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
   dht.begin();
  Serial.println ("");
  Serial.println ("WiFi Connected!");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  
}

void loop()
{

  
  if (Serial.available() > 0 ) 
  {
    rdata = Serial.read(); 
    myString = myString+ rdata; 
   // Serial.print(rdata);
    if( rdata == '\n')
    {
   //  Serial.println(myString); 
  // Serial.println("fahad");
// new code
String l = getValue(myString, ',', 0);
String m = getValue(myString, ',', 1);
String n = getValue(myString, ',', 2); 
String k = getValue(myString, ',', 3); 
Serial.println("value 1= ");
Serial.println(l);
Serial.println("value 2= ");
Serial.println(m);
Serial.println("value 3= ");
Serial.println(n);
Serial.println("value 4= ");
Serial.println(k);
n1=n.toFloat();
k1=k.toFloat();
    if(n1>=2 && n1 <=10){
                   digitalWrite(13,HIGH);
                 Serial.println("01 parked");
                 p1=1000;
                      
            }else{
              Serial.println("free 01");
              p1=1001;
              } 
            
            if(k1>=2 && k1<=10){
                    digitalWrite(13,LOW);
                  Serial.println("02 parked..");
                   p2=2000;
                        }else{
              Serial.println("free 02");
              
              } 

  myString = "";
// end new code
    }
  }

  //float h = dht.readHumidity();
  //Serial.println (h);
  //float t = dht.readTemperature();  // Reading temperature as Celsius (the default)
  //Serial.println (t);
//  Firebase.setFloat("Temp",t);
  //Firebase.setFloat("Humidity",h);
  Firebase.setFloat("COUNT",c);
  Firebase.setString("parking01","+hello+");
  Firebase.setFloat("parking02",p2);
  c++;
 // delay(200);

}



String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
