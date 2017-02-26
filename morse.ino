int dashPin = 2;
int dotPin = 3;
int buttonPin = 4;
int ledPin = 13;
bool dashState = false;
bool dotState = false;
bool buttonState = false;
bool dashPrevState = false;
bool dotPrevState = false;
bool buttonPrevState = false;
String text = "";
String serialRead = "";

char alphabet[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0' };
String morse[] = { 
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
  for(int i = 0; i < sizeof(morse); i++)
  {
    if(morse[i] == code)
      return alphabet[i];
  }

  return NULL;
}

String morseToASCII(String morse)
{
  String w = "";
  String ret = "";

  for(int i = 0; i < morse.length(); i++)
  {
    if(morse[i] != '/')
      w += morse[i];
    else
    {
      if(morse[i - 1] == '/')
        ret += " ";
      else
        ret += letter(w);
      
      w = "";
    }
  }

  return ret;
}

void setup()
{
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(dashPin, INPUT_PULLUP);
  pinMode(dotPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  
  Serial.begin(9600);
}

void loop()
{
  digitalWrite(ledPin, LOW);
  
  buttonState = !digitalRead(buttonPin);
  dashState = !digitalRead(dashPin);
  dotState = !digitalRead(dotPin);
  
  if(buttonState != buttonPrevState)
  {
    if(buttonPrevState)
    {
      text += "/"; 
      Serial.print("/"); 
      
      digitalWrite(ledPin, HIGH);
    }
      
    buttonPrevState = buttonState;
  }
  
  if(dashState != dashPrevState)
  {
    if(dashPrevState)
    {
      text += "-"; 
      Serial.print("-"); 
      
      digitalWrite(ledPin, HIGH);
    }
      
    dashPrevState = dashState;
  }
  
  if(dotState != dotPrevState)
  {
    if(dotPrevState)
    {
      text += "."; 
      Serial.print("."); 

      digitalWrite(ledPin, HIGH);
    }
      
    dotPrevState = dotState;
  }

  if(text[text.length() - 3] == '/' && text[text.length() - 2] == '/' && text[text.length() - 1] == '/')
  {
    Serial.println();
    Serial.println(text + " -> " + morseToASCII(text));
    text = "";
  }

  delay(100); 
}
