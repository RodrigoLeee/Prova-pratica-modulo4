#include <WiFi.h>
#include <HTTPClient.h>

#define led_yellow 9 // Pin used to control yellow led
#define led_green 2 // Pin used to control green led
#define led_red 40 // Pin used to control red led

const int buttonPin = 18;  // the number of the pushbutton pin
int buttonState = 0;  // variable for reading the pushbutton status

const int ldrPin = 4;  // the number of the pushbutton pin
int threshold=600;

void setup() {

  // Initial configuration of the pins to control the leds as OUTPUTS
  pinMode(led_yellow,OUTPUT);
  pinMode(led_green,OUTPUT);
  pinMode(led_red,OUTPUT);

  // Initiates INPUTS
  pinMode(buttonPin, INPUT); // Initialize the pushbutton pin as an input

  digitalWrite(led_yellow, LOW);
  digitalWrite(led_green, LOW);
  digitalWrite(led_red, LOW);

  Serial.begin(9600);   // Configuration to debug through serial interface between ESP and computer, with a baud rate of 9600

  WiFi.begin("Wokwi-GUEST", ""); // Connect to the open wifi network with the SSID Wokwi-GUEST

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println("Connected the the wifi successfully!");   // Considering that the loop above ended, the ESP32 is now conected to the WiFi (another option is to put this commant inside the if bellow)

  // Verifies button state
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    Serial.println("Button pressed!");
  } else {
    Serial.println("Button not pressed!");
  }

  if(WiFi.status() == WL_CONNECTED){ // Checks if the ESP is connected to the internet
    HTTPClient http;

    String serverPath = "http://www.google.com.br/"; // Endpoint of the HTTP Request

    http.begin(serverPath.c_str());

    int httpResponseCode = http.GET(); // HTTP Request Result

    if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      //String payload = http.getString();
      //Serial.println(payload);
      }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
      }
      http.end();
    }

  else {
    Serial.println("WiFi Disconnected");
  }
}

void loop() {
  int ldrstatus=analogRead(ldrPin);
  Serial.println(ldrstatus);
  if(ldrstatus<=threshold){
    //Serial.print("its dark turn on led");

    digitalWrite(led_yellow, HIGH);
    delay(1000);
    digitalWrite(led_yellow, LOW);

  }else{
    //Serial.print("its bright turn off light");
    //Serial.println(ldrstatus);
    digitalWrite(led_green, HIGH);
    delay(3000);
    digitalWrite(led_green, LOW);

    digitalWrite(led_yellow, HIGH);
    delay(3000);
    digitalWrite(led_yellow, LOW);

    digitalWrite(led_red, HIGH);
    buttonState = digitalRead(buttonPin);
    if (buttonState == HIGH) {
      delay(1000)
    }
    else {
      delay(5000);
    }
    digitalWrite(led_red, LOW);
  }
}