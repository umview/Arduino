#include <SoftwareSerial.h>
#include <MsTimer2.h>

//SIM800 TX is connected to Arduino D8
#define SIM800_TX_PIN 8
//SIM800 RX is connected to Arduino D7
#define SIM800_RX_PIN 9
SoftwareSerial mySerial(SIM800_TX_PIN,SIM800_RX_PIN);
void setup(){
  //delay(10000);
    Serial.begin(9600);
    SIM800Init();
    bitSet(DDRB,5);
    MsTimer2::set(1000,getData_ISR);
    MsTimer2::start();
}
char cmd[10]={0};
char sign=0;
void loop(){
  //getData();
  delay(500);
  char i=0;
  for(i=0;i<=9;i++)Serial.write(cmd[i]);
  Serial.println();
  if(cmd[1]=='1')bitSet(PINB,5);
  
}
void SIM800Init(){
  mySerial.begin(9600);
  delay(1000);
  Serial.println("Setup Complete!");
  mySerial.write("AT\r");
  while(mySerial.available())Serial.write(mySerial.read());
  mySerial.write("AT+SAPBR=3,1,\"APN\",\"CMNET\"\r");
  delay(500);
  while(mySerial.available())Serial.write(mySerial.read());
  mySerial.write("AT+SAPBR=3,1,\"PHONENUM\",\"15100000000\"\r");
  delay(500);
  while(mySerial.available())Serial.write(mySerial.read());
  mySerial.write("AT+SAPBR=4,1\r");
  delay(500);
  while(mySerial.available())Serial.write(mySerial.read());
  mySerial.write("AT+SAPBR=1,1\r");
  delay(1000);
  while(mySerial.available())Serial.write(mySerial.read());
  mySerial.write("AT+SAPBR=2,1\r");
  delay(1000);
  while(mySerial.available())Serial.write(mySerial.read());
  mySerial.write("AT+HTTPINIT\r");
  delay(1000);
  while(mySerial.available())Serial.write(mySerial.read());
  mySerial.write("AT+HTTPPARA=\"CID\",\"1\"\r");
  delay(500);
  while(mySerial.available())Serial.write(mySerial.read());
  mySerial.write("AT+HTTPPARA=\"URL\",\"http://test.umview.com/\"\r");
  delay(500);
  while(mySerial.available())Serial.write(mySerial.read());
  mySerial.write("AT+HTTPACTION=0\r");
  delay(1000);
  while(mySerial.available())mySerial.read();
  mySerial.write("AT+HTTPREAD=1,14\r");
  delay(1000);
  while(mySerial.available())Serial.write(mySerial.read());
}

void getData(){
  char cnt=0;
   /*
while(mySerial.available()){
    char c=mySerial.read();
    if(c=='#'){
//      if((c=mySerial.read())!='1')goto restart;
    while((c=mySerial.read())!='#')cmd[cnt]=c,cnt++;
    }
    //if(cmd[0]!='1')loop();
  mySerial.read();
}
*/
while(mySerial.available()){
    char c=mySerial.read();
    if(c=='#'){
//      if((c=mySerial.read())!='1')goto restart;
    for(cnt=0;cnt<=9;cnt++)cmd[cnt]=mySerial.read();
    }
    //if(cmd[0]!='1')loop();
  mySerial.read();
  }
}
void requestDataStep1(){
  mySerial.write("AT+HTTPACTION=0\r");
}
void requestDataStep2(){
    while(mySerial.available())mySerial.read();
    mySerial.write("AT+HTTPREAD=1,14\r");
}
void getData_ISR(){ 
  if(sign==0)requestDataStep1(),sign++;
  else if(sign==1)requestDataStep2(),sign++;
  else getData(),sign=0,Serial.println("getData");
}
