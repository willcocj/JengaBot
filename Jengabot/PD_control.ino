
void PD_control()
{
  Serial.println("I'm in PD_control.");

  unsigned long cur_time = millis();
  unsigned long prev_time;
  unsigned long delta_time;
  
  int prev_pos_A, prev_pos_B, prev_pos_C, prev_pos_D;
  int delta_pos_A, delta_pos_B, delta_pos_C, delta_pos_D;
  
  cur_pos_A = ads1115.readADC_SingleEnded(feedback_A);
  cur_pos_B = ads1115.readADC_SingleEnded(feedback_B);
  cur_pos_C = ads1115.readADC_SingleEnded(feedback_C);
  cur_pos_D = ads1115.readADC_SingleEnded(feedback_D);

  unsigned long vel_A, vel_B, vel_C, vel_D;

  int dist_to_goal_A = goal_A - cur_pos_A; // check difference to see if continue moving, or stop
  int dist_to_goal_B = goal_B - cur_pos_B;
  int dist_to_goal_C = goal_C - cur_pos_C;
  int dist_to_goal_D = goal_D - cur_pos_D;

  // This will need to be modified during optimization //

  float Kp_A = 0.09; //This worked cery well set to 0.12
  float Kp_B = 6;
  float Kp_C = 0.5; 
  float Kp_D = 0.1;

  float Kd_A = -55; //15 with o.12 worked 10 with 0.12 was no good 2 w/0.12 did not work
  float Kd_B = -1;
  float Kd_C = -1.5;
  float Kd_D = -18; //18 with 0.1 worked 14 w/0.1 was no good

  float pwm_A, pwm_B, pwm_C, pwm_D;

  int min_pwm_A_if = 180; // 180 "worked"
  int min_pwm_A = 160; // 160 "worked"
  
  int min_pwm_B;
  
  int min_pwm_C = 60;

  int min_pwm_D_if = 27; // 28 "worked"
  int min_pwm_D = 27; // 28 "worked"
  int max_pwm_D_if = 90;
  int max_pwm_D = 100;

  /*float Kp_A = 0.03;
  float Kp_B = 10;
  float Kp_C = 0.5;
  float Kp_D = 0.04;

  float Kd_A = -7.50;
  float Kd_B = 1;
  float Kd_C = -0.4;
  float Kd_D = -4.2;

  int pwm_A, pwm_B, pwm_C, pwm_D;

  int min_pwm_A_if = 195;
  int min_pwm_A = 150;
  
  int min_pwm_B;
  
  int min_pwm_C = 55;

  int min_pwm_D_if = 38;
  int min_pwm_D = 28;
  int max_pwm_D_if = 90;
  int max_pwm_D = 100;*/

  // This is the end of what needs to be optimized //
  
  /*//Serial.print("goal_A: "); Serial.println(goal_A);
  //Serial.print("cur_pos_A: "); Serial.println(cur_pos_A);
  //Serial.print("dist_to_goal_A: "); Serial.println(dist_to_goal_A);
  //Serial.print("abs(dist_to_goal_A): "); Serial.println(abs(dist_to_goal_A));
  //Serial.println();
  //Serial.print("goal_B: "); Serial.println(goal_B);
  //Serial.print("cur_pos_B: "); Serial.println(cur_pos_B);
  //Serial.print("dist_to_goal_B: "); Serial.println(dist_to_goal_B);
  //Serial.print("abs(dist_to_goal_B): "); Serial.println(abs(dist_to_goal_B));
  //Serial.println();
  //Serial.print("goal_C: "); Serial.println(goal_C);
  //Serial.print("cur_pos_C: "); Serial.println(cur_pos_C);
  //Serial.print("dist_to_goal_C: "); Serial.println(dist_to_goal_C);
  //Serial.print("abs(dist_to_goal_C): "); Serial.println(abs(dist_to_goal_C));
  //Serial.println();
  //Serial.print("goal_D: "); Serial.println(goal_D);
  //Serial.print("cur_pos_D: "); Serial.println(cur_pos_D);
  //Serial.print("dist_to_goal_D: "); Serial.println(dist_to_goal_D);
  //Serial.print("abs(dist_to_goal_D): "); Serial.println(abs(dist_to_goal_D));
  //Serial.println();
  //Serial.print("precision: "); Serial.println(precision_D); //Serial.println();*/
  
  while (abs(dist_to_goal_A) >= precision_A || abs(dist_to_goal_B) >= precision_B || abs(dist_to_goal_C) >= precision_C || abs(dist_to_goal_D) >= precision_D) // While motors A or C are not within precision window:
  {
    /*//Serial.println("In A, B, C or D are outside of the precsion window while loop."); Serial.println();
    ////Serial.print("abs(dist_to_goal_A) >= precision: "); Serial.println(abs(dist_to_goal_A) >= precision);
    //Serial.print("abs(dist_to_goal_B) >= precision: "); Serial.println(abs(dist_to_goal_B) >= precision);
    //Serial.print("abs(dist_to_goal_C) >= precision: "); Serial.println(abs(dist_to_goal_C) >= precision);
    ////Serial.print("abs(dist_to_goal_D) >= precision: "); Serial.println(abs(dist_to_goal_D) >= precision);
    //Serial.println();
    ////Serial.print("goal_A: "); Serial.println(goal_A);
    ////Serial.print("cur_pos_A: "); Serial.println(cur_pos_A);
    ////Serial.print("dist_to_goal_A: "); Serial.println(dist_to_goal_A);
    ////Serial.print("abs(dist_to_goal_A): ") Serial.println(abs(dist_to_goal_A));
    ////Serial.println();
    //Serial.print("goal_B: "); Serial.println(goal_B);
    //Serial.print("cur_pos_B: "); Serial.println(cur_pos_B);
    //Serial.print("dist_to_goal_B: "); Serial.println(dist_to_goal_B);
    //Serial.print("abs(dist_to_goal_B): "); Serial.println(abs(dist_to_goal_B));
    //Serial.println();
    //Serial.print("goal_C: "); Serial.println(goal_C);
    //Serial.print("cur_pos_C: "); Serial.println(cur_pos_C);
    //Serial.print("dist_to_goal_C: "); Serial.println(dist_to_goal_C);
    //Serial.print("abs(dist_to_goal_C): "); Serial.println(abs(dist_to_goal_C));
    //Serial.println();
    ////Serial.print("goal_D: "); Serial.println(goal_D);
    ////Serial.print("cur_pos_D: "); Serial.println(cur_pos_D);
    ////Serial.print("dist_to_goal_D: "); Serial.println(dist_to_goal_D);
    ////Serial.print("abs(dist_to_goal_D): "); Serial.println(abs(dist_to_goal_D));
    ////Serial.println();*/

////// 4/4 4/4 4/4 4/4 4/4 4/4 ////// All 4 are out of precision. Unique
    if (abs(dist_to_goal_A) >= precision_A && abs(dist_to_goal_B) >= precision_B && abs(dist_to_goal_C) >= precision_C && abs(dist_to_goal_D) >= precision_D)
    {
      ////Serial.println("In A, B, C, D are out of precision If conditional.");
      /*//Serial.print("abs(dist_to_goal_A) >= precision: "); Serial.println(abs(dist_to_goal_A) >= precision);
      //Serial.print("abs(dist_to_goal_B) >= precision: "); Serial.println(abs(dist_to_goal_B) >= precision);
      //Serial.print("abs(dist_to_goal_C) >= precision: "); Serial.println(abs(dist_to_goal_C) >= precision);
      //Serial.print("abs(dist_to_goal_D) >= precision: "); Serial.println(abs(dist_to_goal_D) >= precision);*/

      pwm_A = Kp_A * abs(dist_to_goal_A) + Kd_A * abs (delta_pos_A);
      //Serial.print("PD_control_pwm_A: "); //Serial.println(pwm_A);
      if (goal_A <= 3000 && dist_to_goal_A < 0)
      {
        if (pwm_A >= 42949600) {pwm_A = min_pwm_A_if;}
        else if (pwm_A > 255 && pwm_A < 42949600) {pwm_A = 255;}
        else if (pwm_A < min_pwm_A_if) {pwm_A = min_pwm_A_if;}
        else {pwm_A = pwm_A;}
        precision_A = 25;
      }
      else
      {  
        if (pwm_A >= 42949600) {pwm_A = min_pwm_A;}
        else if (pwm_A > 240 && pwm_A < 42949600) {pwm_A = 240;}
        else if (pwm_A < min_pwm_A) {pwm_A = min_pwm_A;}
        else {pwm_A = pwm_A;}
        precision_A = 25;
      }
      
      pwm_B = 255;
      
      pwm_C = Kp_C * abs(dist_to_goal_C) + Kd_C * abs(delta_pos_C);
      //Serial.print("PD_control_pwm_C: "); //Serial.println(pwm_C);
      if (pwm_C >= 42949600) {pwm_C = min_pwm_C;}
      else if (pwm_C > 255 && pwm_C < 42949600) {pwm_C = 255;}
      else if (pwm_C < min_pwm_C) {pwm_C = min_pwm_C;}
      else {pwm_C = pwm_C;}
      
      

      pwm_D = Kp_D * abs(dist_to_goal_D) + Kd_D * abs (delta_pos_D);
      //Serial.print("PD_control_pwm_D: "); //Serial.println(pwm_D);
      if (goal_D < 6000 && dist_to_goal_D < 0)
      {
        if (pwm_D >= 42949600) {pwm_D = min_pwm_D_if;}
        else if (pwm_D > max_pwm_D && pwm_D < 42949600) {pwm_D = max_pwm_D_if;}
        else if (pwm_D < min_pwm_D_if) {pwm_D = min_pwm_D_if;}
        else {pwm_D = pwm_D;}
        precision_D = 25;
      }
      else
      {  
        if (pwm_D >= 42949600) {pwm_D = min_pwm_D;}
        else if (pwm_D > max_pwm_D && pwm_D < 42949600) {pwm_D = max_pwm_D;}
        else if (pwm_D < min_pwm_D) {pwm_D = min_pwm_D;}
        else {pwm_D = pwm_D;}
        precision_D = 25;
      }
      
      //if (dist_to_goal_B > 0){pwm_C = 95;} // If moving up, because goal_B > cur_pos_B
      //else {pwm_C = 125;}
      
      engage_A(pwm_A);
      engage_B(pwm_B);
      engage_C(pwm_C);
      engage_D(pwm_D);
    }
////// 3/4 3/4 3/4 3/4 3/4 3/4 ////// three are out of precision, while one is in precision. Four combos.
    else if (abs(dist_to_goal_A) >= precision_A && abs(dist_to_goal_B) >= precision_B && abs(dist_to_goal_C) >= precision_C && abs(dist_to_goal_D) < precision_D)
    {
      ////Serial.println("In A, B, C are out and D is in precision else if conditional.");
      /*//Serial.print("abs(dist_to_goal_A) >= precision: "); Serial.println(abs(dist_to_goal_A) >= precision);
      //Serial.print("abs(dist_to_goal_B) >= precision: "); Serial.println(abs(dist_to_goal_B) >= precision);
      //Serial.print("abs(dist_to_goal_C) >= precision: "); Serial.println(abs(dist_to_goal_C) >= precision);
      //Serial.print("abs(dist_to_goal_D) < precision: "); Serial.println(abs(dist_to_goal_D) < precision);*/
      
      pwm_A = Kp_A * abs(dist_to_goal_A) + Kd_A * abs (delta_pos_A);
      //Serial.print("PD_control_pwm_A: "); //Serial.println(pwm_A);
      if (goal_A <= 3000 && dist_to_goal_A < 0)
      {
        if (pwm_A >= 42949600) {pwm_A = min_pwm_A_if;}
        else if (pwm_A > 255 && pwm_A < 42949600) {pwm_A = 255;}
        else if (pwm_A < min_pwm_A_if) {pwm_A = min_pwm_A_if;}
        else {pwm_A = pwm_A;}
        precision_A = 25;
      }
      else
      {  
        if (pwm_A >= 42949600) {pwm_A = min_pwm_A;}
        else if (pwm_A > 240 && pwm_A < 42949600) {pwm_A = 240;}
        else if (pwm_A < min_pwm_A) {pwm_A = min_pwm_A;}
        else {pwm_A = pwm_A;}
        precision_A = 25;
      }
      //if (pwm_A >= 42949600) {pwm_A = 35;}
      //else if (pwm_A > 255 && pwm_A < 42949600) {pwm_A = 255;}
      //else if (pwm_A < 35) {pwm_A = 35;}
      //else {pwm_A = pwm_A;}
      
      pwm_B = 255;
      
      pwm_C = Kp_C * abs(dist_to_goal_C) + Kd_C * abs(delta_pos_C);
      //Serial.print("PD_control_pwm_C: "); //Serial.println(pwm_C);
      if (pwm_C >= 42949600) {pwm_C = min_pwm_C;}       
      else if (pwm_C > 255 && pwm_C < 42949600) {pwm_C = 255;}       
      else if (pwm_C < min_pwm_C) {pwm_C = min_pwm_C;}       
      else {pwm_C = pwm_C;}
      
      
      
      //if (dist_to_goal_B > 0){pwm_C = 95;} // If moving up, because goal_B > cur_pos_B
      //else {pwm_C = 125;}

      stop_D();

      engage_A(pwm_A);
      engage_B(pwm_B);
      engage_C(pwm_C);
    }
    else if (abs(dist_to_goal_A) >= precision_A && abs(dist_to_goal_B) >= precision_B && abs(dist_to_goal_C) < precision_C && abs(dist_to_goal_D) >= precision_D)
    {
      ////Serial.println("In A, B, D are out and C is in precision else if conditional.");
      /*//Serial.print("abs(dist_to_goal_A) >= precision: "); //Serial.println(abs(dist_to_goal_A) >= precision);
      //Serial.print("abs(dist_to_goal_B) >= precision: "); //Serial.println(abs(dist_to_goal_B) >= precision);
      //Serial.print("abs(dist_to_goal_C) < precision: "); //Serial.println(abs(dist_to_goal_C) < precision);
      //Serial.print("abs(dist_to_goal_D) >= precision: "); //Serial.println(abs(dist_to_goal_D) >= precision);*/  
          
      pwm_A = Kp_A * abs(dist_to_goal_A) + Kd_A * abs (delta_pos_A);
      //Serial.print("PD_control_pwm_A: "); //Serial.println(pwm_A);
      if (goal_A <= 3000 && dist_to_goal_A < 0)
      {
        if (pwm_A >= 42949600) {pwm_A = min_pwm_A_if;}
        else if (pwm_A > 255 && pwm_A < 42949600) {pwm_A = 255;}
        else if (pwm_A < min_pwm_A_if) {pwm_A = min_pwm_A_if;}
        else {pwm_A = pwm_A;}
        precision_A = 25;
      }
      else
      {  
        if (pwm_A >= 42949600) {pwm_A = min_pwm_A;}
        else if (pwm_A > 240 && pwm_A < 42949600) {pwm_A = 240;}
        else if (pwm_A < min_pwm_A) {pwm_A = min_pwm_A;}
        else {pwm_A = pwm_A;}
        precision_A = 25;
      }

      pwm_B = 255;
      
      pwm_D = Kp_D * abs(dist_to_goal_D) + Kd_D * abs (delta_pos_D);
      //Serial.print("PD_control_pwm_D: "); //Serial.println(pwm_D);

      if (goal_D < 6000 && dist_to_goal_D < 0)
      {
        if (pwm_D >= 42949600) {pwm_D = min_pwm_D_if;}
        else if (pwm_D > max_pwm_D && pwm_D < 42949600) {pwm_D = max_pwm_D;}
        else if (pwm_D < min_pwm_D_if) {pwm_D = min_pwm_D_if;}
        else {pwm_D = pwm_D;}
        precision_D = 25;
      }
      else
      {  
        if (pwm_D >= 42949600) {pwm_D = min_pwm_D;}
        else if (pwm_D > max_pwm_D && pwm_D < 42949600) {pwm_D = max_pwm_D;}
        else if (pwm_D < min_pwm_D) {pwm_D = min_pwm_D;}
        else {pwm_D = pwm_D;}
        precision_D = 25;
      }

      stop_C();

      engage_A(pwm_A);
      engage_B(pwm_B);
      engage_D(pwm_D);
    }
    else if (abs(dist_to_goal_A) >= precision_A && abs(dist_to_goal_B) < precision_B && abs(dist_to_goal_C) >= precision_C && abs(dist_to_goal_D) >= precision_D)
    {
      ////Serial.println("In A, C, D are out and B is in precision else if conditional.");
      /*//Serial.print("abs(dist_to_goal_A) >= precision: "); //Serial.println(abs(dist_to_goal_A) >= precision);
      //Serial.print("abs(dist_to_goal_B) < precision: "); //Serial.println(abs(dist_to_goal_B) < precision);
      //Serial.print("abs(dist_to_goal_C) >= precision: "); //Serial.println(abs(dist_to_goal_C) >= precision);
      //Serial.print("abs(dist_to_goal_D) >= precision: "); //Serial.println(abs(dist_to_goal_D) >= precision);*/

      pwm_A = Kp_A * abs(dist_to_goal_A) + Kd_A * abs (delta_pos_A);
      //Serial.print("PD_control_pwm_A: "); //Serial.println(pwm_A);
      if (goal_A <= 3000 && dist_to_goal_A < 0)
      {
        if (pwm_A >= 42949600) {pwm_A = min_pwm_A_if;}
        else if (pwm_A > 255 && pwm_A < 42949600) {pwm_A = 255;}
        else if (pwm_A < min_pwm_A_if) {pwm_A = min_pwm_A_if;}
        else {pwm_A = pwm_A;}
        precision_A = 25;
      }
      else
      {  
        if (pwm_A >= 42949600) {pwm_A = min_pwm_A;}
        else if (pwm_A > 240 && pwm_A < 42949600) {pwm_A = 240;}
        else if (pwm_A < min_pwm_A) {pwm_A = min_pwm_A;}
        else {pwm_A = pwm_A;}
        precision_A = 25;
      }
      
      pwm_C = Kp_C * abs(dist_to_goal_C) + Kd_C * abs(delta_pos_C);
      //Serial.print("PD_control_pwm_C: "); //Serial.println(pwm_C);
      if (pwm_C >= 42949600) {pwm_C = min_pwm_C;}
      else if (pwm_C > 255 && pwm_C < 42949600) {pwm_C = 255;}
      else if (pwm_C < min_pwm_C) {pwm_C = min_pwm_C;}
      else {pwm_C = pwm_C;}
      
      

      pwm_D = Kp_D * abs(dist_to_goal_D) + Kd_D * abs (delta_pos_D);
      //Serial.print("PD_control_pwm_D: "); //Serial.println(pwm_D);

      if (goal_D < 6000 && dist_to_goal_D < 0)
      {
        if (pwm_D >= 42949600) {pwm_D = min_pwm_D_if;}
        else if (pwm_D > max_pwm_D && pwm_D < 42949600) {pwm_D = max_pwm_D;}
        else if (pwm_D < min_pwm_D_if) {pwm_D = min_pwm_D_if;}
        else {pwm_D = pwm_D;}
        precision_D = 25;
      }
      else
      {  
        if (pwm_D >= 42949600) {pwm_D = min_pwm_D;}
        else if (pwm_D > max_pwm_D && pwm_D < 42949600) {pwm_D = max_pwm_D;}
        else if (pwm_D < min_pwm_D) {pwm_D = min_pwm_D;}
        else {pwm_D = pwm_D;}
        precision_D = 25;
      }

      //pwm_C = 255;

      stop_B();

      engage_A(pwm_A);
      engage_C(pwm_C);
      engage_D(pwm_D);
    }
    else if (abs(dist_to_goal_A) < precision_A && abs(dist_to_goal_B) >= precision_B && abs(dist_to_goal_C) >= precision_C && abs(dist_to_goal_D) >= precision_D)
    {
      ////Serial.println("In B, C, D are out and A is in precision else if conditional.");
      /*//Serial.print("abs(dist_to_goal_A) < precision: "); //Serial.println(abs(dist_to_goal_A) < precision);
      //Serial.print("abs(dist_to_goal_B) >= precision: "); //Serial.println(abs(dist_to_goal_B) >= precision);
      //Serial.print("abs(dist_to_goal_C) >= precision: "); //Serial.println(abs(dist_to_goal_C) >= precision);
      //Serial.print("abs(dist_to_goal_D) >= precision: "); //Serial.println(abs(dist_to_goal_D) >= precision);*/

      pwm_B = 255;
      
      pwm_C = Kp_C * abs(dist_to_goal_C) + Kd_C * abs(delta_pos_C);
      //Serial.print("PD_control_pwm_C: "); //Serial.println(pwm_C);
      if (pwm_C >= 42949600) {pwm_C = min_pwm_C;}
      else if (pwm_C > 255 && pwm_C < 42949600) {pwm_C = 255;}
      else if (pwm_C < min_pwm_C) {pwm_C = min_pwm_C;}
      else {pwm_C = pwm_C;}
      
      

      pwm_D = Kp_D * abs(dist_to_goal_D) + Kd_D * abs (delta_pos_D);
      //Serial.print("PD_control_pwm_D: "); //Serial.println(pwm_D);

      if (goal_D < 6000 && dist_to_goal_D < 0)
      {
        if (pwm_D >= 42949600) {pwm_D = min_pwm_D_if;}
        else if (pwm_D > max_pwm_D && pwm_D < 42949600) {pwm_D = max_pwm_D;}
        else if (pwm_D < min_pwm_D_if) {pwm_D = min_pwm_D_if;}
        else {pwm_D = pwm_D;}
        precision_D = 25;
      }
      else
      {  
        if (pwm_D >= 42949600) {pwm_D = min_pwm_D;}
        else if (pwm_D > max_pwm_D && pwm_D < 42949600) {pwm_D = max_pwm_D;}
        else if (pwm_D < min_pwm_D) {pwm_D = min_pwm_D;}
        else {pwm_D = pwm_D;}
        precision_D = 25;
      }

      //if (dist_to_goal_B > 0){pwm_C = 95;} // If moving up, because goal_B > cur_pos_B
      //else {pwm_C = 125;}

      stop_A();
      
      engage_B(pwm_B);
      engage_C(pwm_C);
      engage_D(pwm_D);
    }
////// 2/4 2/4 2/4 2/4 2/4 2/4 ////// two are out of precision, while two are in precision. 6 combos.
    else if (abs(dist_to_goal_A) < precision_A && abs(dist_to_goal_B) >= precision_B && abs(dist_to_goal_C) >= precision_C && abs(dist_to_goal_D) < precision_D)
    {
      ////Serial.println("In B and C are out and A and D are in precision else if conditional.");
      /*//Serial.print("abs(dist_to_goal_A) < precision: "); //Serial.println(abs(dist_to_goal_A) < precision);
      //Serial.print("abs(dist_to_goal_B) >= precision: "); //Serial.println(abs(dist_to_goal_B) >= precision);
      //Serial.print("abs(dist_to_goal_C) >= precision: "); //Serial.println(abs(dist_to_goal_C) >= precision);
      ////Serial.print("abs(dist_to_goal_D) < precision: "); //Serial.println(abs(dist_to_goal_D) < precision);*/

      pwm_B = 255;
      
      pwm_C = Kp_C * abs(dist_to_goal_C) + Kd_C * abs(delta_pos_C);
      //Serial.print("PD_control_pwm_C: "); //Serial.println(pwm_C);
      if (pwm_C >= 42949600) {pwm_C = min_pwm_C;}
      else if (pwm_C > 255 && pwm_C < 42949600) {pwm_C = 255;}
      else if (pwm_C < min_pwm_C) {pwm_C = min_pwm_C;}
      else {pwm_C = pwm_C;}
      
      

      //if (dist_to_goal_B > 0){pwm_C = 95;} // If moving up, because goal_B > cur_pos_B
      //else {pwm_C = 125;}

      stop_A();
      stop_D();

      engage_B(pwm_B);
      engage_C(pwm_C);
    }
    else if (abs(dist_to_goal_A) >= precision_A && abs(dist_to_goal_B) >= precision_B && abs(dist_to_goal_C) < precision_C && abs(dist_to_goal_D) < precision_D)
    {
      ////Serial.println("In A and B are out and C and D are in precision else if conditional.");
      /*//Serial.print("abs(dist_to_goal_A) >= precision: "); //Serial.println(abs(dist_to_goal_A) >= precision);
      //Serial.print("abs(dist_to_goal_B) >= precision: "); //Serial.println(abs(dist_to_goal_B) >= precision);
      //Serial.print("abs(dist_to_goal_C) < precision: "); //Serial.println(abs(dist_to_goal_C) < precision);
      //Serial.print("abs(dist_to_goal_D) < precision: "); //Serial.println(abs(dist_to_goal_D) < precision);*/

      pwm_A = Kp_A * abs(dist_to_goal_A) + Kd_A * abs (delta_pos_A);
      //Serial.print("PD_control_pwm_A: "); //Serial.println(pwm_A);
      if (goal_A <= 3000 && dist_to_goal_A < 0)
      {
        if (pwm_A >= 42949600) {pwm_A = min_pwm_A_if;}
        else if (pwm_A > 255 && pwm_A < 42949600) {pwm_A = 255;}
        else if (pwm_A < min_pwm_A_if) {pwm_A = min_pwm_A_if;}
        else {pwm_A = pwm_A;}
        precision_A = 25;
      }
      else
      {  
        if (pwm_A >= 42949600) {pwm_A = min_pwm_A;}
        else if (pwm_A > 240 && pwm_A < 42949600) {pwm_A = 240;}
        else if (pwm_A < min_pwm_A) {pwm_A = min_pwm_A;}
        else {pwm_A = pwm_A;}
        precision_A = 25;
      }

      pwm_B = 255;

      stop_C();
      stop_D();

      engage_A(pwm_A);
      engage_B(pwm_B);
    }
    else if (abs(dist_to_goal_A) < precision_A && abs(dist_to_goal_B) >= precision_B && abs(dist_to_goal_C) < precision_C && abs(dist_to_goal_D) >= precision_D)
    {
      ////Serial.println("In B and D are out and A and C are in precision else if conditional.");
      /*//Serial.print("abs(dist_to_goal_A) < precision: "); //Serial.println(abs(dist_to_goal_A) < precision);
      //Serial.print("abs(dist_to_goal_B) >= precision: "); //Serial.println(abs(dist_to_goal_B) >= precision);
      //Serial.print("abs(dist_to_goal_C) < precision: "); //Serial.println(abs(dist_to_goal_C) < precision);
      //Serial.print("abs(dist_to_goal_D) >= precision: "); //Serial.println(abs(dist_to_goal_D) >= precision);*/

      pwm_B = 255;

      pwm_D = Kp_D * abs(dist_to_goal_D) + Kd_D * abs (delta_pos_D);
      //Serial.print("PD_control_pwm_D: "); //Serial.println(pwm_D);

      if (goal_D < 6000 && dist_to_goal_D < 0)
      {
        if (pwm_D >= 42949600) {pwm_D = min_pwm_D_if;}
        else if (pwm_D > max_pwm_D && pwm_D < 42949600) {pwm_D = max_pwm_D;}
        else if (pwm_D < min_pwm_D_if) {pwm_D = min_pwm_D_if;}
        else {pwm_D = pwm_D;}
        precision_D = 25;
      }
      else
      {  
        if (pwm_D >= 42949600) {pwm_D = min_pwm_D;}
        else if (pwm_D > max_pwm_D && pwm_D < 42949600) {pwm_D = max_pwm_D;}
        else if (pwm_D < min_pwm_D) {pwm_D = min_pwm_D;}
        else {pwm_D = pwm_D;}
        precision_D = 25;
      }

      stop_A();
      stop_C();
      
      engage_B(pwm_B);
      engage_D(pwm_D);
    }
    else if (abs(dist_to_goal_A) >= precision_A && abs(dist_to_goal_B) < precision_B && abs(dist_to_goal_C) >= precision_C && abs(dist_to_goal_D) < precision_D)
    {
      ////Serial.println("In A and C are out and B and D are in precision else if conditional.");
      /*//Serial.print("abs(dist_to_goal_A) >= precision: "); //Serial.println(abs(dist_to_goal_A) >= precision);
      //Serial.print("abs(dist_to_goal_B) < precision: "); //Serial.println(abs(dist_to_goal_B) < precision);
      //Serial.print("abs(dist_to_goal_C) >= precision: "); //Serial.println(abs(dist_to_goal_C) >= precision);
      //Serial.print("abs(dist_to_goal_D) < precision: "); //Serial.println(abs(dist_to_goal_D) < precision);*/

      pwm_A = Kp_A * abs(dist_to_goal_A) + Kd_A * abs (delta_pos_A);
      //Serial.print("PD_control_pwm_A: "); //Serial.println(pwm_A);
      if (goal_A <= 3000 && dist_to_goal_A < 0)
      {
        if (pwm_A >= 42949600) {pwm_A = min_pwm_A_if;}
        else if (pwm_A > 255 && pwm_A < 42949600) {pwm_A = 255;}
        else if (pwm_A < min_pwm_A_if) {pwm_A = min_pwm_A_if;}
        else {pwm_A = pwm_A;}
        precision_A = 25;
      }
      else
      {  
        if (pwm_A >= 42949600) {pwm_A = min_pwm_A;}
        else if (pwm_A > 240 && pwm_A < 42949600) {pwm_A = 240;}
        else if (pwm_A < min_pwm_A) {pwm_A = min_pwm_A;}
        else {pwm_A = pwm_A;}
        precision_A = 25;
      }

      pwm_C = Kp_C * abs(dist_to_goal_C) + Kd_C * abs(delta_pos_C);
      //Serial.print("PD_control_pwm_C: "); //Serial.println(pwm_C);
      if (pwm_C >= 42949600) {pwm_C = min_pwm_C;}
      else if (pwm_C > 255 && pwm_C < 42949600) {pwm_C = 255;}
      else if (pwm_C < min_pwm_C) {pwm_C = min_pwm_C;}
      else {pwm_C = pwm_C;}
      
      

      stop_B();
      stop_D();

      engage_A(pwm_A);
      engage_C(pwm_C);
    }
    else if (abs(dist_to_goal_A) >= precision_A && abs(dist_to_goal_B) < precision_B && abs(dist_to_goal_C) < precision_C && abs(dist_to_goal_D) >= precision_D)
    {
      ////Serial.println("In A and D are out and B and C are in precision else if conditional.");
      /*//Serial.print("abs(dist_to_goal_A) >= precision: "); //Serial.println(abs(dist_to_goal_A) >= precision);
      //Serial.print("abs(dist_to_goal_B) < precision: "); //Serial.println(abs(dist_to_goal_B) < precision);
      //Serial.print("abs(dist_to_goal_C) < precision: "); //Serial.println(abs(dist_to_goal_C) < precision);
      //Serial.print("abs(dist_to_goal_D) >= precision: "); //Serial.println(abs(dist_to_goal_D) >= precision);*/

      pwm_A = Kp_A * abs(dist_to_goal_A) + Kd_A * abs (delta_pos_A);
      //Serial.print("PD_control_pwm_A: "); //Serial.println(pwm_A);
      if (goal_A <= 3000 && dist_to_goal_A < 0)
      {
        if (pwm_A >= 42949600) {pwm_A = min_pwm_A_if;}
        else if (pwm_A > 255 && pwm_A < 42949600) {pwm_A = 255;}
        else if (pwm_A < min_pwm_A_if) {pwm_A = min_pwm_A_if;}
        else {pwm_A = pwm_A;}
        precision_A = 25;
      }
      else
      {  
        if (pwm_A >= 42949600) {pwm_A = min_pwm_A;}
        else if (pwm_A > 240 && pwm_A < 42949600) {pwm_A = 240;}
        else if (pwm_A < min_pwm_A) {pwm_A = min_pwm_A;}
        else {pwm_A = pwm_A;}
        precision_A = 25;
      }

      pwm_D = Kp_D * abs(dist_to_goal_D) + Kd_D * abs (delta_pos_D);
      //Serial.print("PD_control_pwm_D: "); //Serial.println(pwm_D);

      if (goal_D < 6000 && dist_to_goal_D < 0)
      {
        if (pwm_D >= 42949600) {pwm_D = min_pwm_D_if;}
        else if (pwm_D > max_pwm_D && pwm_D < 42949600) {pwm_D = max_pwm_D;}
        else if (pwm_D < min_pwm_D_if) {pwm_D = min_pwm_D_if;}
        else {pwm_D = pwm_D;}
        precision_D = 25;
      }
      else
      {  
        if (pwm_D >= 42949600) {pwm_D = min_pwm_D;}
        else if (pwm_D > max_pwm_D && pwm_D < 42949600) {pwm_D = max_pwm_D;}
        else if (pwm_D < min_pwm_D) {pwm_D = min_pwm_D;}
        else {pwm_D = pwm_D;}
        precision_D = 25;
      }

      stop_B();
      stop_C();

      engage_A(pwm_A);
      engage_D(pwm_D);
    }
    else if (abs(dist_to_goal_A) < precision_A && abs(dist_to_goal_B) < precision_B && abs(dist_to_goal_C) >= precision_C && abs(dist_to_goal_D) >= precision_D)
    {
      ////Serial.println("In C and D are out and A and B are in precision else if conditional.");
      /*//Serial.print("abs(dist_to_goal_A) < precision: "); //Serial.println(abs(dist_to_goal_A) < precision);
      //Serial.print("abs(dist_to_goal_B) < precision: "); //Serial.println(abs(dist_to_goal_B) < precision);
      //Serial.print("abs(dist_to_goal_C) >= precision: "); //Serial.println(abs(dist_to_goal_C) >= precision);
      //Serial.print("abs(dist_to_goal_D) >= precision: "); //Serial.println(abs(dist_to_goal_D) >= precision);*/

      pwm_C = Kp_C * abs(dist_to_goal_C) + Kd_C * abs(delta_pos_C);
      //Serial.print("PD_control_pwm_C: "); //Serial.println(pwm_C);
      if (pwm_C >= 42949600) {pwm_C = min_pwm_C;}
      else if (pwm_C > 255 && pwm_C < 42949600) {pwm_C = 255;}
      else if (pwm_C < min_pwm_C) {pwm_C = min_pwm_C;}
      else {pwm_C = pwm_C;}
      
      

      pwm_D = Kp_D * abs(dist_to_goal_D) + Kd_D * abs (delta_pos_D);
      //Serial.print("PD_control_pwm_D: "); //Serial.println(pwm_D);

      if (goal_D < 6000 && dist_to_goal_D < 0)
      {
        if (pwm_D >= 42949600) {pwm_D = min_pwm_D_if;}
        else if (pwm_D > max_pwm_D && pwm_D < 42949600) {pwm_D = max_pwm_D;}
        else if (pwm_D < min_pwm_D_if) {pwm_D = min_pwm_D_if;}
        else {pwm_D = pwm_D;}
        precision_D = 25;
      }
      else
      {  
        if (pwm_D >= 42949600) {pwm_D = min_pwm_D;}
        else if (pwm_D > max_pwm_D && pwm_D < 42949600) {pwm_D = max_pwm_D;}
        else if (pwm_D < min_pwm_D) {pwm_D = min_pwm_D;}
        else {pwm_D = pwm_D;}
        precision_D = 25;
      }

      //pwm_C = 255;

      stop_A();
      stop_B();

      engage_C(pwm_C);
      engage_D(pwm_D);
    }

////// 1/4 1/4 1/4 1/4 1/4 ////// one is out of precision, while three are in precision. 4 combos.
    else if (abs(dist_to_goal_A) < precision_A && abs(dist_to_goal_B) >= precision_B && abs(dist_to_goal_C) < precision_C && abs(dist_to_goal_D) < precision_D)
    {
      ////Serial.println("In B is out and A, C, D are in precision else if conditional.");
      /*//Serial.print("abs(dist_to_goal_A) < precision: "); //Serial.println(abs(dist_to_goal_A) < precision);
      //Serial.print("abs(dist_to_goal_B) >= precision: "); //Serial.println(abs(dist_to_goal_B) >= precision);
      //Serial.print("abs(dist_to_goal_C) < precision: "); //Serial.println(abs(dist_to_goal_C) < precision);
      //Serial.print("abs(dist_to_goal_D) < precision: "); //Serial.println(abs(dist_to_goal_D) < precision);*/

      pwm_B = 255;

      stop_A();
      stop_C();
      stop_D();

      engage_B(pwm_B);    
    }
    else if (abs(dist_to_goal_A) < precision_A && abs(dist_to_goal_B) < precision_B && abs(dist_to_goal_C) >= precision_C && abs(dist_to_goal_D) < precision_D)
    {
      ////Serial.println("In C is out and A, B, D are in precision else if conditional.");
      /*//Serial.print("abs(dist_to_goal_A) < precision: "); //Serial.println(abs(dist_to_goal_A) < precision);
      //Serial.print("abs(dist_to_goal_B) < precision: "); //Serial.println(abs(dist_to_goal_B) < precision);
      //Serial.print("abs(dist_to_goal_C) >= precision: "); //Serial.println(abs(dist_to_goal_C) >= precision);
      //Serial.print("abs(dist_to_goal_D) < precision: "); //Serial.println(abs(dist_to_goal_D) < precision);*/  
      
      pwm_C = Kp_C * abs(dist_to_goal_C) + Kd_C * abs(delta_pos_C);
      //Serial.print("PD_control_pwm_C: "); //Serial.println(pwm_C);
      if (pwm_C >= 42949600) {pwm_C = min_pwm_C;}
      else if (pwm_C > 255 && pwm_C < 42949600) {pwm_C = 255;}
      else if (pwm_C < min_pwm_C) {pwm_C = min_pwm_C;}
      else {pwm_C = pwm_C;}
      
      

      stop_A();
      stop_B();
      stop_D();

      engage_C(pwm_C);

    }
    else if (abs(dist_to_goal_A) >= precision_A && abs(dist_to_goal_B) < precision_B && abs(dist_to_goal_C) < precision_C && abs(dist_to_goal_D) < precision_D)
    {
      ////Serial.println("In A is out and B, C, D are in precision else if conditional.");
      /*//Serial.print("goal_A: "); //Serial.println(goal_A);
      //Serial.print("cur_pos_A: "); //Serial.println(cur_pos_A);
      //Serial.print("dist_to_goal_A: "); //Serial.println(dist_to_goal_A);
      //Serial.print("abs(dist_to_goal_A): "); //Serial.println(abs(dist_to_goal_A));
      //Serial.println();
      //Serial.print("abs(dist_to_goal_A) >= precision: "); //Serial.println(abs(dist_to_goal_A) >= precision);
      //Serial.print("abs(dist_to_goal_B) < precision: "); //Serial.println(abs(dist_to_goal_B) < precision);
      //Serial.print("abs(dist_to_goal_C) < precision: "); //Serial.println(abs(dist_to_goal_C) < precision);
      //Serial.print("abs(dist_to_goal_D) < precision: "); //Serial.println(abs(dist_to_goal_D) < precision);*/

      pwm_A = Kp_A * abs(dist_to_goal_A) + Kd_A * abs (delta_pos_A);
      //Serial.print("PD_control_pwm_A: "); //Serial.println(pwm_A);
      if (goal_A <= 3000 && dist_to_goal_A < 0)
      {
        if (pwm_A >= 42949600) {pwm_A = min_pwm_A_if;}
        else if (pwm_A > 255 && pwm_A < 42949600) {pwm_A = 255;}
        else if (pwm_A < min_pwm_A_if) {pwm_A = min_pwm_A_if;}
        else {pwm_A = pwm_A;}
        precision_A = 25;
      }
      else
      {  
        if (pwm_A >= 42949600) {pwm_A = min_pwm_A;}
        else if (pwm_A > 240 && pwm_A < 42949600) {pwm_A = 240;}
        else if (pwm_A < min_pwm_A) {pwm_A = min_pwm_A;}
        else {pwm_A = pwm_A;}
        precision_A = 25;
      }

      stop_B();
      stop_C();
      stop_D();

      engage_A(pwm_A);
    }
    else if (abs(dist_to_goal_A) < precision_A && abs(dist_to_goal_B) < precision_B && abs(dist_to_goal_C) < precision_C && abs(dist_to_goal_D) >= precision_D)
    {
      ////Serial.println("In D is out and A, B, C are in precision else if conditional.");
      /*//Serial.print("abs(dist_to_goal_A) < precision: "); //Serial.println(abs(dist_to_goal_A) < precision_A);
      //Serial.print("abs(dist_to_goal_B) < precision: "); //Serial.println(abs(dist_to_goal_B) < precision_B);
      //Serial.print("abs(dist_to_goal_C) < precision: "); //Serial.println(abs(dist_to_goal_C) < precision_C);
      //Serial.print("abs(dist_to_goal_D) >= precision: "); //Serial.println(abs(dist_to_goal_D) >= precision_D);*/

      pwm_D = Kp_D * abs(dist_to_goal_D) + Kd_D * abs (delta_pos_D);
      //Serial.print("PD_control_pwm_D: "); //Serial.println(pwm_D);

      if (goal_D < 6000 && dist_to_goal_D < 0)
      {
        if (pwm_D >= 42949600) {pwm_D = min_pwm_D_if;}
        else if (pwm_D > max_pwm_D && pwm_D < 42949600) {pwm_D = max_pwm_D;}
        else if (pwm_D < min_pwm_D_if) {pwm_D = min_pwm_D_if;}
        else {pwm_D = pwm_D;}
        precision_D = 25;
      }
      else
      {  
        if (pwm_D >= 42949600) {pwm_D = min_pwm_D;}
        else if (pwm_D > max_pwm_D && pwm_D < 42949600) {pwm_D = max_pwm_D;}
        else if (pwm_D < min_pwm_D) {pwm_D = min_pwm_D;}
        else {pwm_D = pwm_D;}
        precision_D = 25;
      }

      stop_A();
      stop_B();
      stop_C();
      
      engage_D(pwm_D);
    }
    else
    {
      ////Serial.println("All four are in precision.");
      stop_A();
      stop_B();
      stop_C();
      stop_D();
    }

    ////Serial.println("I'm at the end of the PD_control while loop.");//Serial.println();

    prev_time = cur_time;
    cur_time = millis();
    delta_time = cur_time - prev_time;

    prev_pos_A = cur_pos_A;
    prev_pos_B = cur_pos_B;
    prev_pos_C = cur_pos_C;
    prev_pos_D = cur_pos_D;

    cur_pos_A = ads1115.readADC_SingleEnded(feedback_A);
    cur_pos_B = ads1115.readADC_SingleEnded(feedback_B);
    cur_pos_C = ads1115.readADC_SingleEnded(feedback_C);
    cur_pos_D = ads1115.readADC_SingleEnded(feedback_D);

    delta_pos_A = cur_pos_A - prev_pos_A;
    delta_pos_B = cur_pos_B - prev_pos_B;
    delta_pos_C = cur_pos_C - prev_pos_C;
    delta_pos_D = cur_pos_D - prev_pos_D;

    vel_A = delta_pos_A / delta_time;
    vel_B = delta_pos_B / delta_time;
    vel_C = delta_pos_C / delta_time;
    vel_D = delta_pos_D / delta_time;

    dist_to_goal_A = goal_A - cur_pos_A;//check difference to see if continue moving, or stop
    dist_to_goal_B = goal_B - cur_pos_B;//check difference to see if continue moving, or stop
    dist_to_goal_C = goal_C - cur_pos_C;//check difference to see if continue moving, or stop
    dist_to_goal_D = goal_D - cur_pos_D;//check difference to see if continue moving, or stop

    /*//Serial.println();
    ////Serial.print("goal_A: "); //Serial.println(goal_A);
    ////Serial.print("cur_pos_A: "); //Serial.println(cur_pos_A);
    ////Serial.print("dist_to_goal_A: "); //Serial.println(dist_to_goal_A);
    ////Serial.print("abs(dist_to_goal_A): ") //Serial.println(abs(dist_to_goal_A));
    ////Serial.println();
    //Serial.print("goal_B: "); //Serial.println(goal_B);
    //Serial.print("cur_pos_B: "); //Serial.println(cur_pos_B);
    //Serial.print("dist_to_goal_B: "); //Serial.println(dist_to_goal_B);
    //Serial.print("abs(dist_to_goal_B): "); //Serial.println(abs(dist_to_goal_B));
    //Serial.println();
    //Serial.print("goal_C: "); //Serial.println(goal_C);
    //Serial.print("cur_pos_C: "); //Serial.println(cur_pos_C);
    //Serial.print("dist_to_goal_C: "); //Serial.println(dist_to_goal_C);
    //Serial.print("abs(dist_to_goal_C): "); //Serial.println(abs(dist_to_goal_C));
    //Serial.println();
    //Serial.print("goal_D: "); //Serial.println(goal_D);
    //Serial.print("cur_pos_D: "); //Serial.println(cur_pos_D);
    //Serial.print("dist_to_goal_D: "); //Serial.println(dist_to_goal_D);
    //Serial.print("abs(dist_to_goal_D): "); //Serial.println(abs(dist_to_goal_D));
    //Serial.println();*/
  } 
  stop_A(); // These might be useful. They were off because we may want them off for scanning the tower. If we need them on, then WE NEED TO DELETE the stop B & C pairings outside of this subroutine.
  stop_B();
  stop_C();
  stop_D();
}
