#define G40 196  //5 Sol
#define G402 208  //#5 #Sol
#define A40 220  //6 La
#define B40 247  //7 Si
#define C41 262  //1 Do
#define D41 294  //2 Re
#define E41 330  //3 Mi
#define F41 349  //4 Fa
#define G41 392  //5 Sol
#define G42 415  //#5 #Sol
#define A41 440  //6 La
#define B41 494  //7 Si
#define C51 523  //1 Do_h
#define D51 587  //2 Re_h
#define D52 622  //#2 #Re_h
#define E51 659  //3 Mi_h
#define F51 698  //4 Fa_h
#define G51 784  //5 Sol_h
#define A51 880  //6 La_h
#define B51 988  //7 Si_h
#define O1 000  //0
int scale[]={A40,B40,C41,D41,F41,E41,E41,E41,A41,A41,E41,E41,D41,D41,D41,F41,E41,D41,D41,C41,C41
,C41,B40,A40,G402,A40,A40,D41,E41,C41,E41,B40,E41,A40,E41,D41,E41,C41,E41,B40,E41,A40};  //輸入歌曲音調
int time[]={1,1,1,1,1,1,2,1,1,1,1,1,1,2,1,1,1,1,1,1,2,
1,1,1,1,2,2,2,1,2,1,2,1,2,1,2,1,2,1,3,3,2};//輸入節拍,設定聲響時間長度
int length;//--->>>>以上設定 音樂
#include <LiquidCrystal.h>      // 包含LiquidCrystal.h標頭檔
LiquidCrystal LCD(12,11,10 ,5,4,3,2);   // 建構LiquidCrystal物件
#define trigP 6 
#define echoP 7
const int samplePeriod = 50;  // 每50ms取樣一次(頻率為20Hz)
const int T25=29; // 25度時之音速比例(1/0.0346)
unsigned long t0 = 0;
int Distance, Duration ;
int count = 0; //計數
int set_count = 0; //設定次數
int set_count_3 = set_count ;  //設定次數三組
const int control_1 = A5;  //設定模式
const int control_2 = A2;  //計數歸零
const int buzzer = 13;      // 宣告蜂鳴器位置
#define PB0 A4  //按鈕 次屬增加
#define PB1 A3 //按鈕 次數減少
int ON = 1 ,OFF = 1;  
void setup() {
    pinMode(trigP, OUTPUT);
    pinMode(echoP, INPUT);
    LCD.begin(16,2);
    Serial.begin(9600);
    pinMode(control_1 ,INPUT);
    pinMode(PB0 ,INPUT);
    pinMode(PB1 ,INPUT);
    pinMode(buzzer, OUTPUT); 
    length=sizeof(scale)/sizeof(scale[0]);
}
void loop() {
   if(!digitalRead(control_1)){ // 模式一 設定次數
    OFF = digitalRead(PB0);
    if(OFF == 0){
      set_count = set_count - 1;
      set_count_3 = (set_count * 3);
      Serial.print("set_count : ");
      Serial.print(set_count);
      delay(100); //防斗
    }//增加 按鈕的程式
    ON = digitalRead(PB1);
    if(ON == 0){
       set_count = set_count + 1;
       set_count_3 = (set_count * 3);
      Serial.print("set_count : ");
      Serial.print(set_count);
      delay(100); //防斗
    }//減少 按鈕的程式
    LCD.print("set_count : ");
    LCD.print(set_count);
    LCD.setCursor(0,1);
    LCD.print("s_c * 3 : ");
    LCD.print(set_count_3);
    LCD.setCursor(0,2);
    delay(500);      // 暫停1秒
    LCD.clear();
   }
else if(!digitalRead(control_2)){ //模式二 歸零程式
  count = 0;
   LCD.print("count : ");
   LCD.print(count);
   delay(1000);      // 暫停5秒
   LCD.clear();
}
else{ //模式三_偵測模式
    if(millis()-t0 >= samplePeriod) {
        usonicRead(); // 量測距離
        t0 = millis();  // 紀錄時間
        Serial.print("Distance:  ");
        Serial.print(Distance);
        Serial.println("  cm");
        LCD.print("Distance:");
        LCD.print(Distance);
        LCD.print("cm");
        LCD.setCursor(0,1);
      if(Distance <= 6 ){
      count = count + 1;
    }
     LCD.print("count : ");
      LCD.print(count);
      LCD.setCursor(0,2);
    }
    if(set_count == count){
      tone(buzzer, 1000, 500);// 播音0.1秒
      delay(100);       // 靜音0.1秒
    }
  if(set_count_3 == count){
     beep1(buzzer,1);
     delay(1000);       // 靜音1秒
  }
   
    delay(5000);      // 暫停5秒
    LCD.clear();
}
}
//=== 超音波函式 ======
void usonicRead() {
    digitalWrite(trigP, HIGH);    // 持續送出超音波
    delayMicroseconds(10);    // 等待10微秒
    digitalWrite(trigP, LOW);     // 停止送出超音波
    Duration = pulseIn(echoP, HIGH)/2;  // 單趟時間
    Distance = Duration/T25;  // 距離
}
//=== 恭喜音樂函式 ======
void beep1(int pin, int counts) {
  for(int i=0;i<length;i++){
    tone(pin,scale[i]);
 
    if(time[i]>0)                        //判斷時間是否為不發聲的0,如果不是發聲
      delay(time[i]*250);
    else{                                 //判斷時間是否為不發聲的0,如果是不發聲
      noTone(pin);
      delay(250);
      }
    noTone(pin);
    delay(0);
  }
  delay(1000);
}//播報恭喜恭喜
