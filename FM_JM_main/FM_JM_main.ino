 //FM JAMMER BY ISSOUPEWD

//************************************************************************************************
#include <Wire.h>              // I2C: A4(SDA), A5(SCL)
#include <Adafruit_GFX.h>      // OLED
#include <Adafruit_SSD1306.h>  // OLED
#include <BfButton.h>          // Encoder
#include <Adafruit_Si4713.h>



//************************************************************************************************
// si4713
#define RESETPIN 12
float frequency = 9800;  // Initial frequency
#define MIN_FREQ 8800    // 88.00 MHz
#define MAX_FREQ 10800   // 108.00 MHz
float stations[13] = { 8840, 8920, 9100, 9150, 9470, 9560, 9600, 9800, 10050, 10090, 10150, 10460, 10510 };

int stationNum = 0;
Adafruit_Si4713 radio = Adafruit_Si4713(RESETPIN);


//************************************************************************************************
//Encoder KY-040
#define KyCLK 5                                                 // Encoder CLK pin
#define kyDT 4                                                  // Encoder DT pin
#define KySW 3                                                  // Encoder SW pin
BfButton KyBtn(BfButton::STANDALONE_DIGITAL, KySW, true, LOW);  // Encoder button setup
// Encoder variables
int currentStateCLK;   // Encoder CLK state
int previousStateCLK;  // Encoder CLK state
int prs = 1;
int presbandcahn = 1;
int turnon = 1;

//************************************************************************************************
// OLED0.96
#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels
#define OLED_RESET -1     // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3c
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
bool firsttime = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // fixing the problem the rst of si4713
  pinMode(RESETPIN, OUTPUT);
  digitalWrite(RESETPIN, LOW);  // turn off
  delay(1000);
  digitalWrite(RESETPIN, HIGH);  // turn on
  delay(1000);
  // Encoder pins
  pinMode(KyCLK, INPUT);
  pinMode(kyDT, INPUT);

  // Encoder button settings
  KyBtn.onPress(pressHandler)
    .onDoublePress(pressHandler)
    .onPressFor(pressHandler, 500);  // Custom timeout for 0.5 second

  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);  //oled init
  radio.begin();                                        //oled init
  radio.setTXpower(115);

  oledstart();

  // Read the initial state of KyCLK
  // previousStateCLK = digitalRead(KyCLK);
}

void loop() {
  // put your main code here, to run repeatedly:
  //encoder pushbutton
  KyBtn.read();
  if (turnon == 1) {  // no click
    oledhome();
  } else {  // two clicks
    KyBtn.read();
    //encoder frequency val
    handleEncoder();
    if (presbandcahn == 2) {  // one clcik
      firstall();
    }
  }
  //*********
  //   UwU  *
  //*********
}
