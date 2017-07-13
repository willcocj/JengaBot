
void wait_for_start_signal()
{
  Serial.println("Going to wait for start signal.");
  delay(5000);
  int S_P_S = digitalRead(5);
  Serial.print("S_P_S: ");
  Serial.println(S_P_S);
  boolean flag = 0;

  while (flag == 0)
  {
    int temp_S_P_S = digitalRead(5);
    //Serial.print("temp_S_P_S: ");
    //Serial.println(temp_S_P_S);
    if (temp_S_P_S == S_P_S)
    {
      continue;
    }
    else if (temp_S_P_S != S_P_S)
    {
      Serial.print("temp_S_P_S: ");
      Serial.println(temp_S_P_S);
      Round++;
      flag = 1;
      if (Start == 0)
      {
        Serial.println("MATCH HAS BEGUN!!");
        Serial.println("OUR TURN HAS BEGUN!!");
        Serial.println();
        Serial.print("Round: ");
        Serial.print(Round);
        Serial.println(".1");
        Serial.println();

      }
      else if (Start == 1)
      {
        Serial.println("MATCH HAS BEGUN!!");
        Serial.println("THEIR TURN HAS BEGUN!!");
        Serial.println();
        Serial.print("Round: ");
        Serial.print(Round);
        Serial.println(".1");
        Serial.println();
      }
    }
  }
}

