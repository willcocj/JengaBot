

void wait_for_turn_signal()
{
  Serial.println("Going to wait for start signal.");
  delay(5000);
  int S_P_S = digitalRead(5);
  Serial.print("S_P_S: ");
  Serial.println(S_P_S);

  while (S_P_S == 0)
  {
    S_P_S = digitalRead(5);
    if (S_P_S == 1)
    {
      Round++;
    }
  }
}
