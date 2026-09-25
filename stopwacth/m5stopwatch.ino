//ELEE2045
//Instructor Kyle Johnsen
//Jan Israel Charrez Gomez
#include <M5Unified.h>
#include <M5GFX.h>

bool buttonPressed = false;
unsigned long start_timer = 0;
bool buttonStop = false;

unsigned long time_mili_stop = 0;
unsigned long time_sec_stop = 0;
unsigned long time_min_stop = 0;

void setup() {
  M5.begin();
  M5.Display.setRotation(1);
  M5.Speaker.setVolume(255);
  M5.Display.setCursor(0,0);
}

void loop() {
  M5.delay(100);
  M5.update();

  unsigned long time_mili=0;
  M5.Display.setCursor(180,50);
  M5.Display.print(time_mili);
  M5.Display.println(" ms.");

  unsigned long time_sec=0;
  M5.Display.setCursor(100,50);
  M5.Display.print(time_sec);
  M5.Display.println(" sec. --- ");

  unsigned long time_min=0;
  M5.Display.setCursor(30, 50);
  M5.Display.print(time_min);
  M5.Display.println(" min. --- ");

  unsigned long time_mili1 = millis()-start_timer;
  unsigned long time_sec1 = time_mili1/1000;
  unsigned long time_min1 = time_sec1/60;

  if(M5.BtnA.wasPressed()) {
    if (!buttonPressed){
      buttonPressed = true;
      buttonStop = false;
      start_timer = millis();
      M5.Display.clear();
    } else {
      if (!buttonStop){
        buttonStop = true;
        time_mili_stop = time_mili1 % 1000 ;
        time_sec_stop = time_sec1 % 60;
        time_min_stop = time_min1;
        M5.Display.clear();
      } else {
        buttonStop = false;
        start_timer = millis()- (time_mili_stop + (time_sec_stop * 1000) + (time_min_stop * 60000));
        M5.Display.clear();
      }
    }
  }
  if(M5.BtnB.wasPressed()){
    M5.Display.setCursor(0,0);
    M5.Display.clear();
    M5.Speaker.tone(4400.0, 100, 0, true);
    buttonPressed = false;
    buttonStop = false;
    M5.Display.drawCenterString("CLEARED", M5.Display.width()/2, M5.Display.height()/2);
    M5.delay(1000);
    M5.Display.clear();
  }

  if(buttonPressed && !buttonStop){
    time_mili1= time_mili1 % 1000;
    M5.Display.setCursor(180,50);
    M5.Display.print(time_mili1);
    M5.Display.println(" ms.");

    time_sec1 = time_sec1 % 60;
    M5.Display.setCursor(100,50);
    M5.Display.print(time_sec1);
    M5.Display.println(" sec. --- ");

    M5.Display.setCursor(30 , 50);
    M5.Display.print(time_min1);
    M5.Display.println(" min. --- ");
  }
  if (buttonStop){
    M5.Display.setCursor(180,50);
    M5.Display.print(time_mili_stop);
    M5.Display.println(" ms.");

    M5.Display.setCursor(100,50);
    M5.Display.print(time_sec_stop);
    M5.Display.println(" sec. ---");

    M5.Display.setCursor(30,50);
    M5.Display.print(time_min_stop);
    M5.Display.println(" min. ---");
  }
}
