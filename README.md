# Arduino With SIM800L can get information from Internet, all those complete via GPRS
Function for Arduino
SIM800Init() is function of initializing SIM800l 
After initialize ,module can get information form Internet,via command :
  mySerial.write("AT+HTTPACTION=0\r");
  mySerial.write("AT+HTTPREAD=1,14\r");
the delay() function is necessary and the" while(mySerial.available())mySerial.read(); "is also important.
Identify the information via '#':
Starting from '#'
End from '#'
the information length is 10 (char)
//SIM800 TX is connected to Arduino D8
#define SIM800_TX_PIN 8
//SIM800 RX is connected to Arduino D7
#define SIM800_RX_PIN 9
