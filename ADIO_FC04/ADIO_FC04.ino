//-----------voice-sensor------------
int sensorVoice = 2;
int sensorJidianqi = 13; // 
void setup() 
{ 
pinMode(sensorJidianqi, OUTPUT); 
pinMode(sensorVoice, INPUT); 
Serial.begin(115200); 
}
void loop() 
{
  if (digitalRead(sensorVoice) ==0) 
  {
    delay(100); 
    if (digitalRead(sensorVoice) ==0) 
    {
      Serial.println(digitalRead(sensorVoice));
    }
  }
  else
  {
  digitalWrite(sensorJidianqi, LOW);
  }
}
