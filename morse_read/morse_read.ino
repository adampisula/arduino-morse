#include <Timer.h>
#include <Event.h>

#define input A0
#define btnpin 8

int prev = 1;
int zero = 0;
int one = 0;

int wait = 50;
int unit = 350 / wait;

String morse = "";
boolean checked = 0;

Timer t;

char alphabet[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0' };
String morsecode[] = { 
  ".-", //A
  "-...", //B
  "-.-.", //C
  "-..", //D
  ".", //E
  "..-.", //F
  "--.", //G
  "....", //H
  "..", //I
  ".---", //J
  "-.-", //K
  ".-..", //L
  "--", //M
  "-.", //N
  "---", //O
  ".--.", //P
  "--.-", //Q
  ".-.", //R
  "...", //S
  "-", //T
  "..-", //U
  "...-", //V
  ".--", //W
  "-..-", //X
  "-.--", //Y
  "--..", //Z
  ".----", //1
  "..---", //2
  "...--", //3
  "....-", //4
  ".....", //5
  "-....", //6
  "--...", //7
  "---..", //8
  "----.", //9
  "-----" //0  
};

//IF ARRAY CONTAINS
char letter(String code)
{
  for(int i = 0; i < sizeof(morsecode); i++)
  {
    if(morsecode[i] == code)
      return alphabet[i];
  }

  return NULL;
}

String morseToASCII(String morsec)
{
  String w = "";
  String ret = "";

  for(int i = 0; i < morsec.length(); i++)
  {
    if(morsec[i] != '/')
      w += morsec[i];
    else
    {
      if(morsec[i - 1] == '/')
        ret += " ";
      else
        ret += letter(w);
      
      w = "";
    }
  }

  return ret;
}

bool readState(int pin) {
  int value = analogRead(pin);
  
  if(value < 600)
    return true;
  
  return false;
}

void checkState() {
  boolean state = !readState(input);

  if(prev != state)
  { 
    if(one > unit - 100 / wait && one < unit + 100 / wait)
      morse += ".";
    else if(one > 3 * unit - 100 / wait && one < 5 * unit + 100 / wait)
      morse += "-";
    else if(zero > 1.5 * unit - 100 / wait && zero < 1.5 * unit + 100 / wait)
      morse += "";
    else if(zero > 3 * unit - 100 / wait && zero < 5 * unit + 100 / wait)
    {
      if(morse != "")
        morse += "/"; 
    }
    else if(zero > 7 * unit - 100 / wait && zero < 9 * unit + 100 / wait)
    {
      if(morse != "")
        morse += "//"; 
    }
    
    zero = 0;
    one = 0;

    prev = state;
  }

  else
  {
    if(prev == 0)
      one++;
    else
      zero++;
  }
}

void clearMorse() {
  morse += "///";
  
  if(morse != "/" && morse != "//" && morse != "///" && morse != "" && morse != " ")
  {
    if(morse.length() < 40)
      Serial.println(morse + " -> " + morseToASCII(morse));
    else
      Serial.println(morseToASCII(morse));
  }

  morse = "";
}

void setup() {
  Serial.begin(9600);

  pinMode(input, INPUT);
  pinMode(btnpin, INPUT_PULLUP);

  t.every(wait, checkState);
}

bool prevbtn = false;
bool btn = false;

void loop() {
  t.update();

  btn = !digitalRead(btnpin);

  if(btn != prevbtn)
  {
    clearMorse();

    prev = btn;
  }
}
