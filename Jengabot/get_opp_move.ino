
void get_opp_move()
{  
  while (Serial.available()) 
  {  
    //Serial.println("Entering while loop.");
    if (counter == 0)
    {
      if (Serial.available() > 0) 
      {
        tens = (int)Serial.read() - 48;
        //Serial.print("tens: ");
        //Serial.println(tens); 
        counter = 1;
      }
      else {Serial.println("no serial available.");}
    }
    else if (counter == 1)
    {
      if (Serial.available() > 0) 
      {
        // read the incoming byte:
        ones = (int)Serial.read() - 48;
        //Serial.print("ones: ");
        //Serial.println(ones);        
        opp_move = 10 * tens + ones;
        Serial.print("opp_move: ");
        Serial.println(opp_move);
        Serial.println();
        Serial.println("Hit clicker.");
        Serial.println();
        counter = 2;
      }
       else {Serial.println("no serial available.");}
    }
    else
    {
      //Serial.println("Heading back to main loop!");
      counter = 0; 
    }
  }
}
