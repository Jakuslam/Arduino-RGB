//pin 10- blue
//pin 9 - Red
//pin 8 - GREEN
//pin 7 - diode
//pin 6 - schwitch

#include <SoftwareSerial.h>
#include <IRremote.h>

#define RX 12
#define TX 11

const int IRPin = 7; // číslo pinu tlačítka přijímače

IRrecv irrecv(IRPin); // vytvořeme objekt typu IRrecv
decode_results results; // definujeme proměnnou



SoftwareSerial bluetooth(TX, RX);

  int red;
  int green;
  int blue;

  int pauza = 10;

  int coPrislo;

  int PrichodZname = 0;
  bool BR = false;
  bool BG = false;
  bool RG = false;
  bool ALL = false;
  
  bool zapnuto = false;

  float dilek; //desetiné číslo
  
byte BluetoothData;

void setup() {
  
  //start pinů  
  pinMode(8, OUTPUT); //Green
  pinMode(9, OUTPUT); //Red
  pinMode(10, OUTPUT);  // Blue


  pinMode(6, OUTPUT);  // prepinac
  
Serial.begin(9600); // spustit sériový monitor na 9600 bps
irrecv.enableIRIn(); // zapnout infračervený přijímač
  
  //strart bluethoot

  bluetooth.begin(9600);
  bluetooth.println("Arduino zapnuto, test Bluetooth..");


}

void loop() {
  
  PrichodZname = 0;
  
  
//sem pak dej tu duodu (-:
if (irrecv.decode(&results)) { // jestli přijímač (dioda) přijal data
    irrecv.resume(); // přijat další data

    Serial.print("něco přišlo");
    
    
    if(results.value == 0xFFC23D){
      
      if(zapnuto == true){
        zapnuto = false;
        Serial.print("vypnuto");
      }
      else if(zapnuto == false){
        zapnuto = true;
        Serial.print("zapnuto");
      }
    }
    else if(results.value == 0xFF30CF){//1
      blue = 1;
      red = 0;
      green = 0;
      
    }
    else if(results.value == 0xFF18E7){ //2
      blue = 5;
      red = 7;
      green = 5;
      
    }
    else if(results.value == 0xFF7A85){ //3
      blue = 0;
      red = 0;
      green = 8;
      
    }
    else if(results.value == 0xFF10EF){ //4
      blue = 0;
      red = 9;
      green = 0;
      
    }
    else if(results.value == 0xFF38C7){ //11
      blue = 9;
      red = 2;
      green = 2;
      
    }
    else if(results.value == 0xFF5AA5){ //6
      blue = 9;
      red = 9;
      green = 0;
      
    }
    else if(results.value == 0xFF42BD){ //7
      blue = 1;
      red = 9;
      green = 1;
      
    }
    else if(results.value == 0xFF4AB5){ //8
      blue = 6;
      red = 9;
      green = 6;
      
    }
    else if(results.value == 0xFF52AD){ //10
      pauza = 10;
      blue = 3;
      red = 3;
      green = 0;
      
    }
    else{
      Serial.print("Žádný příjem z diody");
      
    }
    Serial.print("\n");
    Serial.print(red);
    Serial.print("\n");
    Serial.print(green);
    Serial.print("\n");
    Serial.print(blue);
    Serial.print("\n");
}


if(bluetooth.available() > 0){
    
  BluetoothData=bluetooth.read();
  Serial.print(BluetoothData);
  switch(BluetoothData){
      
      case  42 + 48: //1
      Serial.print("1");
      blue = 1;
      red = 0;
      green = 0;
      
      break;
      
      case  41 + 48: //2
      Serial.print("2");
      blue = 5;
      red = 7;
      green = 5;
      
      break;
      
      case  40 + 48: //3
      Serial.print("3");
      blue = 0;
      red = 0;
      green = 8;
      
      break;
      
      case  39 + 48: //4
      Serial.print("4");
      blue = 0;
      red = 9;
      green = 0;
      break;
      
      case  38 + 48: //5
      Serial.print("5");
      blue = 0;
      red = 9;
      green = 1;
      
      break;
      
      case  37 + 48: //6
      Serial.print("6");
      blue = 9;
      red = 9;
      green = 0;
      
      break;
      
      case  36 + 48: //7
      Serial.print("7");
      blue = 1;
      red = 9;
      green = 1;
      break;
      
      case  35 + 48: //8
      Serial.print("8");
      blue = 6;
      red = 9;
      green = 6;
      break;
      
      case  33 + 48: //9
      Serial.print("9");
      blue = 0;
      red = 6;
      green = 3;
      break;
      
      case  32 + 48: //10
  Serial.print("10?");
      pauza = 10;
      blue = 3;
      red = 3;
      green = 0;
      
      break;
      
      case  31 + 48: //11
  Serial.print("11?");
      pauza = 10;

      blue = 9;
      red = 2;
      green = 2;
      
      break;

      case 82:
      
      coPrislo = 1;
      Serial.print("red"); 
      pauza = 10; 
      break;
        
      case 71:
      
      coPrislo = 2;
      Serial.print("green"); 
      pauza = 10; 
      break;

      case 66:

      coPrislo = 3;
      Serial.print("blue");
      pauza = 10; 
      break;
      
      case  30 + 48:
  
      zapnuto = true;
      Serial.print("ON");
      pauza = 10;
      break;
      
      case  22 + 48:
  
      zapnuto = false;
      Serial.print("OFF");
      pauza = 10; 
      break;

      case  49:
      Serial.print("Y");
      digitalWrite(6,HIGH);
      break;

      case  50:
      Serial.print("M");
      digitalWrite(6,LOW);
      break;

      default:

      Serial.print("default");
      
      if(coPrislo == 1){
        red = BluetoothData - 48;
        PrichodZname = 0;
        Serial.print(red);
        Serial.print("- r \n");
      }
      else if(coPrislo == 2){
        green = BluetoothData  - 48;
        PrichodZname = 0;
        Serial.print(green);
        Serial.print("- g\n");
      }
      else if(coPrislo == 3){
        blue = BluetoothData - 48;
        PrichodZname = 0;
        Serial.print(blue);
        Serial.print("- b \n");
      }
      else if(coPrislo == 0){

      }
      
      break;

  }
    
}

 
if(zapnuto == true){
 RGBprint();
 }
    
}


void RGBprint(){

  BR = false;
  BG = false;
  RG = false;
  ALL = false;
  
  digitalWrite(8,HIGH);
  digitalWrite(9,HIGH);
  digitalWrite(10,HIGH);
  
  porovnej();
  
  dilek = pauza / (blue + red + green); 

  
  
  if(ALL == true){    
    delay(pauza);
    digitalWrite(8,LOW);
    digitalWrite(9,LOW);
    digitalWrite(10,LOW);
  }
  else if(BG == true){
    
    dilek = pauza / (blue + red);
    
    if(blue < red){
      
      delay(blue * dilek);
      digitalWrite(8,LOW);
      digitalWrite(10,LOW);
      
      delay(red * dilek);
      digitalWrite(9,LOW);
    }
    else{
      
      delay(red * dilek);
      digitalWrite(9,LOW);
      
      delay(blue * dilek);
      digitalWrite(8,LOW);
      digitalWrite(10,LOW);      
    }
  }
  else if(BR == true){
    
    dilek = pauza / (blue + green);
    
    if(blue < green){
      
      delay(blue * dilek);
      digitalWrite(9,LOW);
      digitalWrite(10,LOW);
      
      delay(green * dilek);
      digitalWrite(8,LOW);
    }
    else{
      
      delay(green * dilek);
      digitalWrite(8,LOW);
      
      delay(blue * dilek);
      digitalWrite(9,LOW);
      digitalWrite(10,LOW);
    }
  }
  else if(RG == true){
    
    dilek = pauza / (blue + green);
    
    if(blue > green){
      
      delay(green * dilek);
      digitalWrite(9,LOW);
      digitalWrite(8,LOW);
      
      delay(blue * dilek);
      digitalWrite(10,LOW);
      
    }
    else{
      
      delay(blue * dilek);
      digitalWrite(10,LOW);
      
      delay(blue * dilek);
      digitalWrite(9,LOW);
      digitalWrite(8,LOW);
      
    }
  }
  else{
      
    dilek = pauza / (blue + red + green); 
  
    if(blue > red && blue > green){ //blue největší
    
      if(red > green){
      
        delay(green * dilek);
        digitalWrite(8,LOW);
      
        delay(red * dilek);
        digitalWrite(9,LOW);
      
        delay(blue * dilek);
        digitalWrite(10,LOW);
      }
      else{
      
        delay(red * dilek);
        digitalWrite(9,LOW);
      
        delay(green * dilek);
        digitalWrite(8,LOW);
      
        delay(blue * dilek);
        digitalWrite(10,LOW);
      }

      Serial.print(red);
      Serial.print("___BLUE__");
      Serial.print(green);
      Serial.print("___");
      Serial.print(blue);
      Serial.print("\n");
      
    }
    else if(red < green && blue < green){ // green největší
    
      if(red > blue){
      
        delay(blue * dilek);
        digitalWrite(10,LOW);
      
        delay(red * dilek);
        digitalWrite(9,LOW);
      
        delay(green * dilek);
        digitalWrite(8,LOW);
      }
      else{
      
        delay(red * dilek);
        digitalWrite(9,LOW);
      
        delay(blue * dilek);
        digitalWrite(10,LOW);
      
        delay(green * dilek);
        digitalWrite(8,LOW);
      }
      Serial.print(red);
      Serial.print("___GREEN__");
      Serial.print(green);
      Serial.print("___");
      Serial.print(blue);
      Serial.print("\n");
    }
    else if(red > green && blue < red){ // red nejvědší
    
      if(green > blue){
      
        delay(blue * dilek);
        digitalWrite(10,LOW);
      
        delay(green * dilek);
        digitalWrite(8,LOW);
      
        delay(red * dilek);
        digitalWrite(9,LOW);
      }
      else{
      
        delay(green * dilek);
        digitalWrite(8,LOW);
      
        delay(blue * dilek);
        digitalWrite(10,LOW);
      
        delay(red * dilek);
        digitalWrite(9,LOW);
      }
      Serial.print(red);
      Serial.print("___RED__");
      Serial.print(green);
      Serial.print("___");
      Serial.print(blue);
      Serial.print("\n");
    }
  }
}

void porovnej(){
  
  if(green == blue && green == red){
    ALL = true;
  }
  else if(blue == red){
    BR = true;
  }
  else if(blue == green){
    BG = true;
  }
  else if(red == green){
    RG = true;
  }
}
