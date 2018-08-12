#include <Button.h>

#define hallSW0 14 // выключатель в холе кнопка 0

#define hallSW1 2   // выключатель в холе кнопка 1
#define hallLight 3 // коридор свет
bool bhallLight = false;

#define bathroomSW0 4   // ванная выключатель
#define bathroomLight 5 // ванная свет
bool bbathroomLight = false;
#define bathroomFan 6 // ванная вентилятор
bool bbathroomFan = false;
int ibathroomFan = 0;
#define bathroomBrace 7 // ванная бра
bool bbathroomBrace = false;

#define wcSW0 8   // туалет выключатель
#define wcLight 9 // теалет свет
bool bwcLight = false;
#define wcFan 10 // туалет выключатель
bool bwcFan = false;
int iwcFan = 0;
#define wcBrace 11 // туалет бра
bool bwcBrace = false;

#define kitchenSW0_0 15 // кухня выключатель кнопка 0
#define kitchenSW0_1 16 // кухня выключатель кнопка 1
#define kitchenSW1_0 17 // кухня выключатель кнопка возле поверхности кнопка 0
#define kitchenLight 18
bool bkitchenLight = false;
#define kitchenLight1 16
bool bkitchenLight1 = false;
#define kitchenLight2 17
bool bkitchenLight2 = false;
#define kitchenLightDots 18
bool bkitchenLightDots = false;

#define balconySW0 19
#define balconyLight 20
bool bbalconyLight = false;

#define livingRoomSW0 21
#define livingRoomSW1 22
#define livingRoomLight 23
bool blivingRoomLight = false;
#define livingRoomBrace 24
bool blivingRoomBrace = false;

#define bedRoomSW0_0 25
#define bedRoomSW0_1 26
#define bedRoomSW1_0 27
#define bedRoomSW1_1 28
#define bedRoomSW2_0 29
#define bedRoomSW2_1 30
#define bedRoomLight 31
bool bbedRoomLight = false;
#define bedRoomBrace0 32
bool bbedRoomBrace0 = false;
#define bedRoomBrace1 33
bool bbedRoomBrace1 = false;

#define childRoomSW0_0 34
#define childRoomSW0_1 35
#define childRoomSW1_0 36
#define childRoomSW1_1 37
#define childRoomLight 38
bool bchildRoomLight = false;
#define childRoomBrace 39
bool bchildRoomBrace = false;

#define inOutDoorSensor  12 // TODO не забуть установить сенсор дверей

Button hButton;

int HallTimeOff=0;

#define ON LOW
#define OFF HIGH

void setup()
{
   Serial.begin(9600);
  pinMode(inOutDoorSensor, INPUT);
  hButton.NO(); // N.O. Normal Open
  // hButton.NC(); // N.C. Normal Closed
  //hButton.pullUp();
  hButton.pullDn(); // - подтяжка пинов кнопок к GND
  hButton.duration_bounce(50);
  hButton.duration_click_Db(250);
  hButton.duration_inactivity_Up(5000);
  hButton.duration_inactivity_Dn(1000);
  hButton.duration_press(500);
  hButton.button(hallSW0, hallSW1, bathroomSW0, wcSW0, kitchenSW0_0, kitchenSW0_1, kitchenSW1_0, balconySW0, livingRoomSW0, livingRoomSW1, bedRoomSW0_0, bedRoomSW0_1, bedRoomSW1_0, bedRoomSW1_1, bedRoomSW2_0, bedRoomSW2_1, childRoomSW0_0, childRoomSW0_1, childRoomSW1_0, childRoomSW1_1); // arduino pins connected to button

  //pinMode(inOutDoorSensor, INPUT); // подключение

  pinMode(hallLight, OUTPUT);  
  digitalWrite(hallLight, OFF);
  
  pinMode(bathroomLight, OUTPUT);  
  pinMode(bathroomFan, OUTPUT);
  digitalWrite(bathroomLight,OFF);
  digitalWrite(bathroomFan, OFF);
  
  pinMode(wcLight, OUTPUT);
  pinMode(wcFan, OUTPUT);
  digitalWrite(wcLight, OFF);
  digitalWrite(wcFan, OFF);
  
  //digitalWrite(wcLight, LOW);
  pinMode(kitchenLight, OUTPUT);  
  digitalWrite(kitchenLight,OFF);

  pinMode(livingRoomLight, OUTPUT);
  digitalWrite(livingRoomLight,OFF);

  pinMode(bedRoomLight, OUTPUT);
  digitalWrite(bedRoomLight,OFF);

  pinMode(childRoomLight, OUTPUT);
  digitalWrite(childRoomLight,OFF);
  // put your setup code here, to run once:

 
}

void allOFF(bool withHall=false)
{
    if (withHall)
    {
      digitalWrite(hallLight, OFF);
    }
    digitalWrite(bathroomLight, OFF);
    digitalWrite(bathroomFan, OFF);
    digitalWrite(wcLight, OFF);
    digitalWrite(wcFan, OFF);
    digitalWrite(kitchenLight, OFF);
    digitalWrite(childRoomLight, OFF);
}

void loop()
{
  bool val = digitalRead(inOutDoorSensor);
  if ((!val)&&(digitalRead(hallLight)==OFF))
  {
    digitalWrite(hallLight, ON);
  }  
  if ((digitalRead(hallLight)==ON)&&(HallTimeOff>0)&&(millis()-HallTimeOff>0))
  {
    HallTimeOff = 0;
    allOFF(true);

  }


  hButton.read();
//
#pragma region hall
#pragma region hallSW0
  if (hButton.event_click_Dn(0) == 1)
  {
     Serial.println("hallSW0");
    bhallLight = digitalRead(hallLight);
    digitalWrite(hallLight, !bhallLight);
  }
  if (hButton.event_click_Db(0) == 1)
  {
  }
  if (hButton.event_press_short(0) == 1)
  {
  }
  if (hButton.event_press_long(0) == 1)
  {
  }
#pragma endregion

#pragma region hallSW1
  if (hButton.event_click_Dn(1) == 1)
  {
    HallTimeOff = millis()+60000;
    Serial.println("hallSW1");
    allOFF(false);
    //digitalWrite(hallLight, OFF);
    // digitalWrite(bathroomLight, OFF);
    // digitalWrite(bathroomFan, OFF);
    // digitalWrite(wcLight, OFF);
    // digitalWrite(wcFan, OFF);
    // digitalWrite(kitchenLight, OFF);    
    // digitalWrite(childRoomLight, OFF);
  }
  if (hButton.event_click_Db(1) == 1)
  {
    bhallLight = digitalRead(hallLight);
    digitalWrite(hallLight, !bhallLight);
  }
  if (hButton.event_press_short(1) == 1)
  {
  }
  if (hButton.event_press_long(1) == 1)
  {
  }
#pragma endregion
#pragma endregion

#pragma region bathroom
  if (hButton.event_click_Dn(2) == 1)
  {
    Serial.println("bathroomSW0");
    bbathroomLight = digitalRead(bathroomLight);
    Serial.println(bbathroomLight);
    digitalWrite(bathroomLight, !bbathroomLight);
    digitalWrite(bathroomFan, !bbathroomLight);    
  }
  if (hButton.event_click_Db(2) == 1)
  {
  }
  if (hButton.event_press_short(2) == 1)
  {
  }
  if (hButton.event_press_long(2) == 1)
  {
  }
#pragma endregion

#pragma region WC
  if (hButton.event_click_Dn(3) == 1)
  {
    Serial.println("WCSW0");
    bwcLight = digitalRead(wcLight);
    Serial.println(bwcLight);
    digitalWrite(wcLight, !bwcLight);
    digitalWrite(wcFan, !bwcLight);
  }
  if (hButton.event_click_Db(3) == 1)
  {
  }
  if (hButton.event_press_short(3) == 1)
  {
  }
  if (hButton.event_press_long(3) == 1)
  {
  }
#pragma endregion

#pragma region kitchen
#pragma region kitchenSW0_0
  if (hButton.event_click_Dn(4) == 1)
  {
    Serial.println("kitchenLight");
    bkitchenLight = digitalRead(kitchenLight);
    digitalWrite(kitchenLight, !bkitchenLight);
  }
  if (hButton.event_click_Db(4) == 1)
  {
  }
  if (hButton.event_press_short(4) == 1)
  {
  }
  if (hButton.event_press_long(4) == 1)
  {
  }
#pragma endregion

#pragma region kitchenSW0_1
  if (hButton.event_click_Dn(5) == 1)
  {
  }
  if (hButton.event_click_Db(5) == 1)
  {
    bkitchenLight = digitalRead(kitchenLight);
    digitalWrite(kitchenLight, !bkitchenLight);
  }
  if (hButton.event_press_short(5) == 1)
  {
  }
  if (hButton.event_press_long(5) == 1)
  {
  }
#pragma endregion

#pragma region kitchenSW0_1
  if (hButton.event_click_Dn(6) == 1)
  {
  }
  if (hButton.event_click_Db(6) == 1)
  {
    bkitchenLight = digitalRead(kitchenLight);
    digitalWrite(kitchenLight, !bkitchenLight);
  }
  if (hButton.event_press_short(6) == 1)
  {
  }
  if (hButton.event_press_long(6) == 1)
  {
  }
#pragma endregion
#pragma endregion

#pragma region livingRoom
#pragma region livingRoomSW0
  if (hButton.event_click_Dn(7) == 1)
  {
    blivingRoomLight = digitalRead(livingRoomLight);
    digitalWrite(livingRoomLight, !blivingRoomLight);
  }
  if (hButton.event_click_Db(7) == 1)
  {
  }
  if (hButton.event_press_short(7) == 1)
  {
  }
  if (hButton.event_press_long(7) == 1)
  {
  }
#pragma endregion

#pragma region livingRoomSW1
  if (hButton.event_click_Dn(8) == 1)
  {
    
  }
  if (hButton.event_click_Db(8) == 1)
  {
    blivingRoomLight = digitalRead(livingRoomLight);
    digitalWrite(livingRoomLight, !blivingRoomLight);
  }
  if (hButton.event_press_short(8) == 1)
  {
  }
  if (hButton.event_press_long(8) == 1)
  {
  }
#pragma endregion

#pragma endregion

#pragma region bedRoom
#pragma region bedRoomSW0_0
 if (hButton.event_click_Dn(9) == 1)
  {
    bbedRoomLight = digitalRead(bedRoomLight);
    digitalWrite(bedRoomLight, !bbedRoomLight);
  }
  if (hButton.event_click_Db(9) == 1)
  {
  }
  if (hButton.event_press_short(9) == 1)
  {
  }
  if (hButton.event_press_long(9) == 1)
  {
  }
#pragma endregion

#pragma region bedRoomSW0_1
  if (hButton.event_click_Dn(10) == 1)
  {
    bhallLight = digitalRead(hallLight);;
    digitalWrite(hallLight, !bhallLight);
  }
  if (hButton.event_click_Db(10) == 1)
  {
  }
  if (hButton.event_press_short(10) == 1)
  {
  }
  if (hButton.event_press_long(10) == 1)
  {
  }
#pragma endregion

#pragma endregion

#pragma region childRoom
#pragma region childRoomSW0_0
 if (hButton.event_click_Dn(16) == 1)
  {
    Serial.println("childRoomSW0_0");
    bchildRoomLight = digitalRead(childRoomLight);
    digitalWrite(childRoomLight, !bchildRoomLight);
  }
  if (hButton.event_click_Db(16) == 1)
  {
  }
  if (hButton.event_press_short(16) == 1)
  {
  }
  if (hButton.event_press_long(16) == 1)
  {
  }
#pragma endregion

#pragma region childRoomSW0_1
  if (hButton.event_click_Dn(17) == 1)
  {
    Serial.println("childRoomSW0_1");
    //bchildRoomLight = !bchildRoomLight;
    //digitalWrite(childRoomLight, bchildRoomLight);
  }
  if (hButton.event_click_Db(17) == 1)
  {
  }
  if (hButton.event_press_short(17) == 1)
  {
  }
  if (hButton.event_press_long(17) == 1)
  {
  }
#pragma endregion

#pragma endregion




  if (hButton.event_click_Dn() == 1) // - событие нажатия                          кнопки
  {
  }
  if (hButton.event_click_Db() == 1) // - событие двойного щелчка                  кнопки
  {
  }
  if (hButton.event_press_short() == 1) // - событие короткого нажатия                кнопки
  {
  }
  if (hButton.event_press_long() == 1) // - событие длинного  нажатия                кнопки
  {
  }
}
