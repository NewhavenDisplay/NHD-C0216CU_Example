/*****************************************************************************
 * 
/ Program for writing to NHD-C0216CU Series series with the ST7032 Controller.
/ This code is written for the Arduino Uno R3 using 8-bit Parallel Interface
/
/ Newhaven Display invests time and resources providing this open source code,
/ Please support Newhaven Display by purchasing products from Newhaven Display!

* Copyright (c) 2019, Newhaven Display International
*
* This code is provided as an example only and without any warranty by Newhaven Display. 
* Newhaven Display accepts no responsibility for any issues resulting from its use. 
* The developer of the final application incorporating any parts of this 
* sample code is responsible for ensuring its safe and correct operation
* and for any consequences resulting from its use.
* See the GNU General Public License for more details. 
* 
*****************************************************************************/

 /******** INITIAL DEFINITIONS***************/

#define RST   8
#define RS    9
#define RW    10
#define E     11


/************************ CHAR STRING**********/

char const text1[] = ("XXXXXXXXXXXXXXXX");
char const text2[] = ("ZZZZZZZZZZZZZZZZ");
char const text3[] = ("HHHHHHHHHHHHHHHH");

/************ Functions************/

void command(int c){
  digitalWrite(RW, LOW);
  digitalWrite(RS, LOW);
  digitalWrite(E, HIGH);
  PORTD = c;
  digitalWrite(E, LOW);
  delay(1);
}


void data(int d){
  digitalWrite(RW, LOW);
  digitalWrite(RS, HIGH);
  digitalWrite(E, HIGH);
  PORTD = d;
  digitalWrite(E, LOW);
  delay(1);
}


void init1(){
  DDRD = 0xFF;
  digitalWrite(RST, LOW);
  delay(2);
  digitalWrite(RST, HIGH);
  delay(20);
  command(0x30);
  delay(2);
  command(0x30); //wake up
  command(0x30); //wake up
  command(0x39); //function set
  command(0x14); //internal osc frequency
  command(0x55); //power control
  command(0x6D); //follower control
  command(0x79); //contrast
  command(0x0C); //display on
  command(0x06); //entry mode
  command(0x01); //clear
  delay(10);
}

void disp(){                            // DISPLAY TEXT
  command(0x01);
  command(0x02); 
  command(0x80); // Brings back to First Line
  for( int i = 0; i< 16; i++){
    data('X');
  }
  command(0xc0);                              // Second Line
  for (int i = 0; i<16; i++){
    data('X');
  }
  delay(1500);
  command(0x01);
  command(0x02); 
  command(0x80); // Brings back to First Line
  for( int i = 0; i< 16; i++){
    data('H');
  }
  command(0xc0);                              // Second Line
  for (int i = 0; i<16; i++){
    data('H');
  }
  delay(1500);
  command(0x01);
  command(0x02); 
  command(0x80); // Brings back to First Line
  for( int i = 0; i< 16; i++){
    data('Z');
  }
  command(0xc0);                              // Second Line
  for (int i = 0; i<16; i++){
    data('Z');
  }
  delay(1500);
}
void setup() {
  // put your setup code here, to run once:
  DDRD = 0xFF;
  DDRB = 0xFF;
  digitalWrite(13, HIGH);
  init1();
  
}

void loop() {
  disp();
}
