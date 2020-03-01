#include <M5Stack.h>
#include <Wire.h>

#define I2C_SDA 21
#define I2C_SCL 22

#define S11059_ADDR 0x2A

void setup() {
  //Serial.begin(115200);
  //Serial.println("start---");

  // initialize the M5Stack object
  M5.begin();
  M5.Lcd.fillScreen(WHITE);

  // Init I2C 
  Wire.begin(I2C_SDA, I2C_SCL);

  // 0x00 = Control 
  // 0x8B = ADC-Reset + High Gain + 179.2ms
  Wire.beginTransmission(S11059_ADDR);
  Wire.write(0x00);
  Wire.write(0x89);
  Wire.endTransmission();

  // 0x00 = Control 
  // 0x0B = ADC-Run + High Gain + 179.2ms
  Wire.beginTransmission(S11059_ADDR);
  Wire.write(0x00);
  Wire.write(0x09);
  Wire.endTransmission();

  M5.Lcd.setCursor(0, 0);
  M5.Lcd.setTextColor(BLACK);
  M5.Lcd.setTextSize(2);
  M5.Lcd.printf("Display Test!");
}

void loop() {
  delay(6);

  M5.Lcd.fillScreen(WHITE);
  M5.Lcd.setCursor(0, 0);
  int h,l ,r,g,b,a;
  // 0x03 Read Data
  Wire.beginTransmission(S11059_ADDR);
  Wire.write(0x03);
  Wire.endTransmission();

  Wire.requestFrom(S11059_ADDR,8);
  if(Wire.available()){
    // Red
    h = Wire.read();
    l = Wire.read();
    r = h << 8|l;
    M5.Lcd.print(" r:");
    M5.Lcd.println(r);
    // Green
    h = Wire.read();
    l = Wire.read();
    g = h << 8|l;
    M5.Lcd.print(" g:");
    M5.Lcd.println(g);
    // Blue
    h = Wire.read();
    l = Wire.read();
    b = h << 8|l;
    M5.Lcd.print(" b:");
    M5.Lcd.println(b);
    // Infra red
    h = Wire.read();
    l = Wire.read();
    a = h << 8|l;
    M5.Lcd.print(" a:");
    M5.Lcd.println(a);

/*
    // It converted to RGB?
    int rr, gg, bb;
    M5.Lcd.println(" ");
    rr = map(r, 30, 56000, 0, 255);
    gg = map(g, 30, 41000, 0, 255);
    bb = map(b, 30, 56000, 0, 255);
    M5.Lcd.print(rr, HEX);
    M5.Lcd.print(" ");
    M5.Lcd.print(gg, HEX);
    M5.Lcd.print(" ");
    M5.Lcd.print(bb, HEX);
    M5.Lcd.println("");
*/
  }
  Wire.endTransmission();

}
