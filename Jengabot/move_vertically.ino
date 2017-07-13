
// Moving vertically up engages Motors B and C in opposite directions.
// UP:   Motor B forward (HIGH), Motor C Forward (HIGH)
// DOWN: Motor B Reverse (LOW), Motor C Reverse (LOW)

void move_vert()
{
  Serial.println("I'm in move_vert");
  float pwm_B;
  float pwm_C;
  ////Serial.println("I'm going to move only vertically.");
  int cur_pos_B = ads1115.readADC_SingleEnded(feedback_B); // analogRead(feedback_B);
  int dist_to_goal_B = goal_B - cur_pos_B;//check difference to see if continue moving, or stop

  int cur_pos_C =  ads1115.readADC_SingleEnded(feedback_C); // analogRead(feedback_C);
  int dist_to_goal_C = goal_C - cur_pos_C;//check difference to see if continue moving, or stop

  float float_goal_C = float(goal_C);
  float temp_pos_C = ads1115.readADC_SingleEnded(feedback_C); // analogRead(feedback_C);
  float float_dist_to_goal_C = float_goal_C - temp_pos_C;
  float speed_factor_C = abs(float_dist_to_goal_C / float(slow_down_dist));

  /*//Serial.print("goal_B: "); //Serial.println(goal_B);
  //Serial.print("cur_pos_B: "); //Serial.println(cur_pos_B);
  //Serial.print("dist_to_goal_B: "); //Serial.println(dist_to_goal_B);
  //Serial.print("abs(dist_to_goal_B): "); //Serial.println(abs(dist_to_goal_B));
  //Serial.print("goal_C: "); //Serial.println(goal_C);
  //Serial.print("cur_pos_C: "); //Serial.println(cur_pos_C);
  //Serial.print("dist_to_goal_C: "); //Serial.println(dist_to_goal_C);
  //Serial.print("abs(dist_to_goal_C): "); //Serial.println(abs(dist_to_goal_C));
  //Serial.print("precision: "); //Serial.println(precision); //Serial.println();*/
  
  while (abs(dist_to_goal_B) > precision_B || abs(dist_to_goal_C) > precision_C) // While motors B or C are not within precision window:
  {
    /*//Serial.println("In B or C are outside of the precsion window while loop.");
    //Serial.print("abs(dist_to_goal_B) >= precision"); //Serial.println(abs(dist_to_goal_B) >= precision);
    //Serial.print("abs(dist_to_goal_C) >= precision"); //Serial.println(abs(dist_to_goal_C) >= precision); //Serial.println();*/

    if (abs(dist_to_goal_B) > precision_B && abs(dist_to_goal_C) > precision_C) // While motors B and C are not within precision window:
    {      
      ////Serial.println("In B and C are out if conditional.");
      /*//Serial.print("abs(dist_to_goal_B) >= precision"); //Serial.println(abs(dist_to_goal_B) >= precision);
      //Serial.print("abs(dist_to_goal_C) >= precision"); //Serial.println(abs(dist_to_goal_C) >= precision); //Serial.println();*/
      pwm_B = 255;
      if (dist_to_goal_B > 0){pwm_C = 88;} // If moving up, because goal_B > cur_pos_B
      else {pwm_C = 130;}

      //Serial.print("B_C_out_move_vert_pwm_C: "); //Serial.println(pwm_C);

      if (abs(dist_to_goal_C) > slow_down_dist)       // If magnitude of distance to goal is greater than slow down distace:
      {
        pwm_C = pwm_C;                                  // Drive motor C with max pwm.
      }
      else                                            // Otherwise:
      {
        pwm_C = (pwm_C - 55) * speed_factor_C + 55;                 // Drive motor C at a rate proportional to the distance to goal.
      }

      ////Serial.print("dist_to_goal_C: "); //Serial.println(float_dist_to_goal_C);
      ////Serial.print("slow_down_dist: "); //Serial.println(slow_down_dist);
      ////Serial.print("speed_factor: "); //Serial.println(speed_factor_C);
      //Serial.print("B_C_out_move_vert_pwm_C: "); //Serial.println(pwm_C);
      
      engage_B(pwm_B); // engage B because it is out of precision window.
      engage_C(pwm_C); // engage C because it is out of precision window.
    }
 
    else if (abs(dist_to_goal_B) > precision_B && abs(dist_to_goal_C) <= precision_C) // While motors B is not within precision window CND motor C is:
    {
      ////Serial.println("In B is out and C is in else if conditional.");
      /*//Serial.print("abs(dist_to_goal_B) >= precision"); //Serial.println(abs(dist_to_goal_B) >= precision);
      //Serial.print("abs(dist_to_goal_C) < precision"); //Serial.println(abs(dist_to_goal_C) < precision); //Serial.println();*/
      stop_C();
      pwm_B = 255;
      engage_B(pwm_B); // engage B because it is out of precision window.
    }

    else if (abs(dist_to_goal_B) <= precision_B && abs(dist_to_goal_C) > precision_C) // While motors C is not within precision window AND motor A is:
    {      
      ////Serial.println("In B is in and C is out else if conditional.");
      /*//Serial.print("abs(dist_to_goal_B) < precision"); //Serial.println(abs(dist_to_goal_B) < precision);
      //Serial.print("abs(dist_to_goal_C) >= precision"); //Serial.println(abs(dist_to_goal_C) >= precision); //Serial.println();*/
      stop_B();
      pwm_C = 180;

      if (abs(dist_to_goal_C) > slow_down_dist)       // If magnitude of distance to goal is greater than slow down distace:
      {
        pwm_C = pwm_C;                                  // Drive motor C with max pwm.
      }
      else                                            // Otherwise:
      {
        pwm_C = (pwm_C - 55) * speed_factor_C + 55;                 // Drive motor C at a rate proportional to the distance to goal.
      }

      ////Serial.print("dist_to_goal_C: "); //Serial.println(float_dist_to_goal_C);
      ////Serial.print("slow_down_dist: "); //Serial.println(slow_down_dist);
      ////Serial.print("speed_factor: "); //Serial.println(speed_factor_C);
      //Serial.print("C_out_move_vert_pwm_C: "); //Serial.println(pwm_C);

      engage_C(pwm_C); // engage C because it is out of precision window.
    }

    else
    {
      stop_B();
      stop_C();
    }

    ////Serial.println("I'm at the end of move vert while loop.");      
    cur_pos_B =  ads1115.readADC_SingleEnded(feedback_B); // analogRead(feedback_B);
    dist_to_goal_B = goal_B - cur_pos_B;//check difference to see if continue moving, or stop

    cur_pos_C = ads1115.readADC_SingleEnded(feedback_C); // analogRead(feedback_C);
    dist_to_goal_C = goal_C - cur_pos_C;//check difference to see if continue moving, or stop

    /*//Serial.print("goal_B: "); //Serial.println(goal_B);
    //Serial.print("cur_pos_B: "); //Serial.println(cur_pos_B);
    //Serial.print("dist_to_goal_B: "); //Serial.println(dist_to_goal_B);
    //Serial.print("abs(dist_to_goal_B): "); //Serial.println(abs(dist_to_goal_B));
    //Serial.print("goal_C: "); //Serial.println(goal_C);
    //Serial.print("cur_pos_C: "); //Serial.println(cur_pos_C);
    //Serial.print("dist_to_goal_C: "); //Serial.println(dist_to_goal_C);
    //Serial.print("abs(dist_to_goal_C): "); //Serial.println(abs(dist_to_goal_C));
    //Serial.print("precision: "); //Serial.println(precision); //Serial.println();*/
  }  
  stop_B(); //These might be useful. They are off because we may want them off for scanning the tower. If we need them on, then we should delete the stop B & C pairiings elsewhere.
  stop_C();
}
