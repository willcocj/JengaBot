

////////MOTOR A CONTROL//////// A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A A

void engage_A(int pwm_A)
{
  boolean dir_A;
  int temp_pos_A = ads1115.readADC_SingleEnded(feedback_A); // analogRead(feedback_A);
  float dist_to_goal_A = goal_A - temp_pos_A;
  //float speed_factor_A = 1; // abs(dist_to_goal_A / slow_down_dist);
  
  //float speed_factor_A = abs(dist_to_goal_A / slow_down_dist);
  
  if (dist_to_goal_A >= 0) {dir_A = HIGH;}                       // If the goal is further forward (goal A is larger than current pot A value): 
  else                     {dir_A =LOW;}                       // Otherwise:

  digitalWrite(dir_pin_A, dir_A); // Set direction of motor A
  analogWrite(vel_pin_A, pwm_A); // Set motor A speed
  
  /*//Serial.println("In engage_A");
  //Serial.print("goal_A: "); //Serial.println(goal_A);
  //Serial.print("cur_pos_A: "); //Serial.println(temp_pos_A);
  //Serial.print("dist_to_goal_A: "); //Serial.println(dist_to_goal_A);
  //Serial.print("Direction of Rot_A: "); //Serial.println(dir_A);
  ////Serial.print("speed_factor_A: "); //Serial.println(speed_factor_A);*/
  //Serial.print("motor_control_pwm_A: "); //Serial.println(pwm_A); //Serial.println();
}//end engage_A

void stop_A()
{
  ////Serial.println("In stop_A"); ////Serial.println();
  analogWrite(vel_pin_A, 0); // Set motor A speed to 0
  }//end stop_A*/


////////MOTOR B CONTROL//////// B B B B B B B B B B B B B B B B B B B B B B B B B B B B B B B B B B B B B B B B B B B B B B B 

void engage_B(int pwm_B)
{
  String dir_B;
  int temp_pos_B = ads1115.readADC_SingleEnded(feedback_B); //analogRead(feedback_B);
  float dist_to_goal_B = goal_B - temp_pos_B;
  int slow_down_dist_B = 400;
  float speed_factor_B = abs(dist_to_goal_B / slow_down_dist_B);
  
  if (dist_to_goal_B > 0)                        // If the goal is further forward (goal B is larger than current pot B value): 
  {
    motor_B->run(FORWARD);                                 // Drive motor B forward
    dir_B = "Forward";
    ////Serial.println("I'm going to move up.");
  }
  else                                            // Otherwise:
  {
    motor_B->run(BACKWARD);                                  // Drive motor B in Reverse
    dir_B = "Backward";
    ////Serial.println("I'm going to move down.");
  }

  if (abs(dist_to_goal_B) > slow_down_dist_B)       // If magnitude of distance to goal is greater than slow down distace:
  {
    pwm_B = pwm_B;                                  // Drive motor C with max pwm.
  }
  else                                            // Otherwise:
  {
    pwm_B = (pwm_B - 190) * speed_factor_B + 190;                 // Drive motor C at a rate proportional to the distance to goal.
  }

  motor_B->setSpeed(pwm_B);
  
  //Serial.println("In engage_B");
  //Serial.print("goal_B: "); Serial.println(goal_B);
  //Serial.print("cur_pos_B: "); Serial.println(temp_pos_B);
  //Serial.print("dist_to_goal_B: "); Serial.println(dist_to_goal_B);
  //Serial.print("Direction of Rot_B: "); Serial.println(dir_B);
  ////Serial.print("speed_factor_B: "); Serial.println(speed_factor_B);
  //Serial.print("motor_control_pwm_B: "); Serial.println(pwm_B); Serial.println();
}//end engage_B

void stop_B()
{
  ////Serial.println("In stop_B"); ////Serial.println();
  motor_B->run(RELEASE);
  motor_B->run(FORWARD);
  motor_B->setSpeed(30);
  //digitalWrite(brake_B, HIGH); // Engage brake for motor B
}//end stop_B


////////MOTOR C CONTROL//////// C C C C C C C C C C C C C C C C C C C C C C C C C C C C C C C C C C C C C C C C C C C C C C C

void engage_C(int pwm_C)
{
  String dir_C;
  int temp_pos_C = ads1115.readADC_SingleEnded(feedback_C); // analogRead(feedback_C);
  float dist_to_goal_C = goal_C - temp_pos_C;
  float speed_factor_C = abs(dist_to_goal_C / slow_down_dist);
  
  if (dist_to_goal_C >= 0)                        // If the goal is further forward  (goal C is larger than current pot C value):
  {
    motor_C->run(FORWARD);                                 // Drive motor C forward
    dir_C = "Forward";
    ////Serial.println("I'm going to move laterally forward or up.");
  }
  else                                            // Otherwise:
  {
    motor_C->run(BACKWARD);                                  // Drive motor C in Reverse
    dir_C = "Backward";
    ////Serial.println("I'm going to move laterally backwards or down.");
  }
   
  if (abs(dist_to_goal_C) > slow_down_dist)       // If magnitude of distance to goal is greater than slow down distace:
  {
    pwm_C = pwm_C;                                  // Drive motor C with max pwm.
  }
  else                                            // Otherwise:
  {
    pwm_C = (pwm_C - 60) * speed_factor_C + 60;                 // Drive motor C at a rate proportional to the distance to goal.
  }

  motor_C->setSpeed(pwm_C);
  
  //Serial.println("In engage_C");
  //Serial.print("goal_C: "); Serial.println(goal_C);
  //Serial.print("cur_pos_C: "); Serial.println(temp_pos_C);
  //Serial.print("dist_to_goal_C: "); Serial.println(dist_to_goal_C);
  //Serial.print("Direction of Rot_C: "); Serial.println(dir_C);
  ////Serial.print("speed_factor_C: "); Serial.println(speed_factor_C);
  //Serial.print("motor_control_pwm_C: "); Serial.println(pwm_C); //Serial.println();
}//end engage_C

void stop_C()
{
  ////Serial.println("In stop_C"); ////Serial.println();
  motor_C->run(RELEASE);
}//end stop_C


////////MOTOR D CONTROL//////// D D D D D D D D D D D D D D D D D D D D D D D D D D D D D D D D D D D D D D D D D D D D D D D

void engage_D(int pwm_D)
{
  String dir_D;
  int temp_pos_D = ads1115.readADC_SingleEnded(feedback_D);
  int dist_to_goal_D = goal_D - temp_pos_D;
  //float speed_factor_D = abs(dist_to_goal_D / slow_down_dist);
  
  if (dist_to_goal_D > 0)                        // If the goal is further forward (goal D is larger than current pot D value): 
  {
    motor_D->run(FORWARD);                                 // Drive motor D forward
    dir_D = "Forward";
    ////Serial.println("I'm going to rotate the wrist CCW.");
  }
  else                                            // Otherwise:
  {
    motor_D->run(BACKWARD);                                  // Drive motor D in Reverse
    dir_D = "Backward";
    ////Serial.println("I'm going to rotate wrist CW.");
  }
  
  motor_D->setSpeed(pwm_D);
  
  //Serial.println("In engage_D");
  //Serial.print("goal_D; "); Serial.println(goal_D);
  //Serial.print("temp_pos_D: "); Serial.println(temp_pos_D);
  //Serial.print("dist_to_goal_D: "); Serial.println(dist_to_goal_D);
  //Serial.print("Direction of Rot_D: "); Serial.println(dir_D);
  ////Serial.print("speed_factor_D: "); Serial.println(speed_factor_D);
  //Serial.print("motor_control_pwm_D: "); Serial.println(pwm_D); //Serial.println();
}//end engage_D

void stop_D()
{
  ////Serial.println("In stop_D"); //Serial.println();
  motor_D->run(RELEASE);
}//end stop_D
