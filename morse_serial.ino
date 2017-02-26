int outputPin = 5;

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

String ASCIIToMorse(String text)
{
  String ret = "";
  
  for(int i = 0; i < text.length(); i++)
  {
    for(int j = 0; j < sizeof(alphabet); j++)
    {
      if(text[i] == alphabet[j])
      {
        ret += morse[j];
        
        break;
      }
    }

    ret += "/";
  }

  return ret;
}

String toUppercase(String text)
{
  String ret = "";
  char c;

  for(int i = 0; i < text.length(); i++)
  {
    char c = toupper(text[i]);
    
    ret += c;
  }

  return ret;
}

void procMorse(String morse, int unit)
{
  for(int i = 0; i < morse.length(); i++)
  {
    tone(outputPin, 300);
    
    if(morse[i] == '.')
      delay(unit); 
    else if(morse[i] == '-')
      delay(3 * unit);

    noTone(outputPin);
    delay(unit);
    
    if(morse[i] == '/' && morse[i - 1] != '/')
      delay(2 * unit);
    if(morse[i] == '/' && morse[i + 1] == '/')
    {
      delay(3 * unit);      
      i++;
    }
  }
}

void setup() {
  pinMode(outputPin, OUTPUT);
  
  Serial.begin(9600);
  
  while(Serial.available()) {}
}

void loop() {
  String sread = Serial.readString();
  
  if(sread != "")
  {
    String morse = ASCIIToMorse(toUppercase(sread));
    
    Serial.println(sread + " -> " + morse);
    procMorse(morse, 350);
  }
}
