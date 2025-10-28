/*Author: Oday A. Rabaiah*/

// Libraries (see platformio.ini for info)
#include <Arduino.h> // For serial monitor
#include <WiFi.h> // For Server
#include <Wire.h> // For OLED
#include <Servo.h>
// #include <Adafruit_GFX.h>     // OLED Screen
// #include <Adafruit_SSD1306.h> // OLED Screen
// #include <FastLED.h> // To control on-board RGB

/*----------WiFi----------*/
#define SSID "INNTEGRAL"
#define PASSWORD "1234567890"

WiFiServer server(8080); // wifi server init. (port 8080)

/*----------OLED Screen----------*/
// #define SCREEN_WIDTH 128 // OLED width,  in pixels
// #define SCREEN_HEIGHT 32 // OLED height, in pixels
//
// Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

/*----------On-Board RGB----------*/
// #define LED_PIN 48
// #define NUM_LEDS 1
//
// CRGB leds[NUM_LEDS]; // On-Board RGB

/*----------Servo Motor----------*/
const int servo_pin_1 = 41;
const int servo_pin_2 = 42;

int angle_1;
int angle_2;

Servo servo = Servo();

/*LiquidCrystal_I2C lcd(0x27, 16, 2); //LCD init. (address 0x27)*/

void setup() {
    Serial.begin(115200); // Start monitor at 115200 baud

    // FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS); // Init LEDs on board
    //
    // leds[0] = CRGB(0, 0, 0);
    // FastLED.show();

    // Wire.setPins(1, 2); 
    Wire.begin();

    // if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    //     Serial.println("Failed to start OLED");
    //     while (1);
    // }

    // Web server config.
    Serial.println("SETTING ACCESS POINT...");
    WiFi.softAP(SSID, PASSWORD);

    IPAddress IP = WiFi.softAPIP();
    Serial.print("ACCESS POINT IP ADDRESS: ");
    Serial.println(IP);

    server.begin(); // Start server
    
    // oled.clearDisplay(); // clear display
    // oled.setTextSize(2);         // set text size
    // oled.setTextColor(WHITE);    // set text color
    // oled.setCursor(0, 0);       // set position to display
    // oled.println(IP); // set text
    // oled.display();

    servo.write(servo_pin_1, 0);
    servo.write(servo_pin_2, 0);
    
    Serial.println("------------------------------"); 
}

// Loop (repeat forever)
void loop() {
    WiFiClient client = server.available(); // Set client

    if (client) {
        Serial.println("CLIENT FOUND"); // Confirm client

        while (client.connected()) {
            char c = client.read(); // Get data from client (1 character)

            Serial.print("RECIEVED MESSAGE:"); // Confirm message
            Serial.println(c);

            // Test commands (CAN BE REPLACED)
            if (c == '0') {
                // oled.clearDisplay();
                // oled.println("SERVO RESET");

                angle_1 = 0;
                // angle_2 = 0; 

                Serial.println("LCD PROMPTED, 0");
            } else if (c == '1') { // Set servo 1 to move positive
                // oled.clearDisplay();
                // oled.println("SERVO 1 POS +");

                angle_1 = 45;

                Serial.println("LCD PROMPTED, 1");
            } else if (c == '2') { // Set servo 2 to move positive
                // oled.clearDisplay();
                // oled.println("SERVO 2 POS +");

                angle_2 = 45;

                Serial.println("LCD PROMPTED, 2");
            } else if (c == '3') { // Set servo 1 to move negative
                // oled.clearDisplay();
                // oled.println("SERVO 1 POS -");

                angle_1 = 90;

                Serial.println("LCD PROMPTED, 3");
            } else if (c == '4') { // Set servo 2 to move negative
                // oled.clearDisplay();
                // oled.println("SERVO 2 POS -");

                angle_2 = 180;

                Serial.println("LCD PROMPTED, 4");
            }
            servo.write(servo_pin_1, angle_1);
            servo.write(servo_pin_2, angle_2);
        }
    }

    client.stop(); // Stop client after disconnection
    Serial.println("CLIENT DISCONNECTED"); // Confirm
    Serial.println("------------------------------"); // Pretty CLI
}
