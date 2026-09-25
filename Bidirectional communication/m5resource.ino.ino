//jan israel charrez gomez
#include "M5Unified.h"
#include "M5GFX.h"

M5Canvas canvas(&M5.Display);

#pragma pack(1)
typedef struct {
  uint16_t cpu;
  uint8_t mem;
  uint8_t battery;
} StatsPacket;

void setup() {
  M5.begin();
  Serial.begin(115200);
  M5.Display.setRotation(1);
  canvas.createSprite(M5.Display.width(),M5.Display.height());
  canvas.setTextSize(2);
}
void loop() {
  M5.update();
  if(Serial.available() > sizeof(StatsPacket)){
    StatsPacket pkt;
    Serial.readBytes((uint8_t*)&pkt, sizeof(pkt));
    canvas.setCursor(0, 20);
    canvas.printf("CPU: %u", pkt.cpu);
    canvas.setCursor(0, 40);
    canvas.printf("Mem: %u", pkt.mem);
    canvas.setCursor(0, 60);
    canvas.printf("Battery: %u", pkt.battery);
  }
  if (M5.BtnA.wasPressed()) {
    Serial.write(0x01);
    canvas.setCursor(0,80);
    if(Serial.available() > sizeof(StatsPacket)){
      StatsPacket pkt;
      Serial.readBytes((uint8_t*)&pkt, sizeof(pkt));
      Serial.write(0x01);
      Serial.printf("CPU: %u", pkt.cpu);
      Serial.printf("Mem: %u", pkt.mem);
      Serial.printf("Batery: %u", pkt.battery);
      Serial.print("Button A Pressed");
    }
  }
  if (M5.BtnA.wasReleased()) {
    canvas.clear();
    Serial.write(0x02);
    canvas.setCursor(0, 80);
    canvas.print("Button A Released");
  }
  if (M5.BtnB.isPressed()) {
    canvas.clear();
    Serial.write(0xFF);
    canvas.setCursor(0, 80);
    canvas.print("Quit Pressed");
  }
  canvas.pushSprite(0,0);
}
