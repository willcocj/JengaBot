
void extract_target()
{
  Serial.println("I'm in the extract target subroutine.");

  tower[targets[0]] = 0;

  goal_A = target_row_pots[0];
  goal_B = target_row_pots[1];
  goal_C = target_row_pots[2];
  goal_D = target_row_pots[3];


  //Serial.print("goal_A: "); Serial.println(target_row_pots[0]);
  //Serial.print("goal_B: "); Serial.println(target_row_pots[1]);
  //Serial.print("goal_C: "); Serial.println(target_row_pots[2]);
  //Serial.print("goal_D: "); Serial.println(target_row_pots[3]);

  //Serial.print("goal_A: "); Serial.println(goal_A);
  //Serial.print("goal_B: "); Serial.println(goal_B);
  //Serial.print("goal_C: "); Serial.println(goal_C);
  //Serial.print("goal_D: "); Serial.println(goal_D);

  move_vert();
  delay(200);
  PD_control();
  delay(200);

  goal_A = mod_target_pots[0];
  goal_D = mod_target_pots[3];
  move_vert();
  delay(200);
  PD_control();
  delay(200);
  
  goal_B = mod_target_pots[1];
  goal_C = mod_target_pots[2];
  move_vert();
  delay(200);
  PD_control();
  delay(200);
 
  //Serial.print("goal_A: "); Serial.println(goal_A);
  //Serial.print("goal_B: "); Serial.println(goal_B);
  //Serial.print("goal_C: "); Serial.println(goal_C);
  //Serial.print("goal_D: "); Serial.println(goal_D);

  move_vert();
  delay(200);
  PD_control();
  delay(200);
  
  /*goal_A = mod_target_pots[0];
  Serial.print("goal_A: "); Serial.println(goal_A);
  PD_control();
  delay(200);
  
  goal_B = mod_target_pots[1];
  goal_C = mod_target_pots[2];
  Serial.print("goal_B: "); Serial.println(goal_B);
  Serial.print("goal_C: "); Serial.println(goal_C);
  PD_control();
  delay(200);
  
  goal_D = mod_target_pots[3];
  Serial.print("goal_D: "); Serial.println(goal_D);
  PD_control();
  delay(200);*/

  cur_pos_A = ads1115.readADC_SingleEnded(feedback_A);
  cur_pos_B = ads1115.readADC_SingleEnded(feedback_B);
  cur_pos_C = ads1115.readADC_SingleEnded(feedback_C);
  cur_pos_D = ads1115.readADC_SingleEnded(feedback_D);

  Serial.print("goal_A: "); Serial.println(goal_A);
  Serial.print("goal_B: "); Serial.println(goal_B);
  Serial.print("goal_C: "); Serial.println(goal_C);
  Serial.print("goal_D: "); Serial.println(goal_D); Serial.println();  
  Serial.print("cur_pos_A: "); Serial.println(cur_pos_A);
  Serial.print("cur_pos_B: "); Serial.println(cur_pos_B);
  Serial.print("cur_pos_C: "); Serial.println(cur_pos_C);
  Serial.print("cur_pos_D: "); Serial.println(cur_pos_D); Serial.println();

  PD_control();

  Serial.println("                                                           Extract Block."); Serial.println();
  digitalWrite(punch_pin, HIGH);
  delay(200);
  digitalWrite(punch_pin, LOW);
  delay(200);

  goal_A = target_row_pots[0];
  goal_B = target_row_pots[1];
  goal_C = target_row_pots[2];
  goal_D = target_row_pots[3];
  //move_vert();                                // Move vertically, only. (This engages motors 2 and 3).
  PD_control();                               // use PD_control to move in
  delay(200);

  
  Serial.println("Move to top position."); Serial.println();
  if (tower_pos == 0)
  {
    if (target_side == 0)
    {
      goal_A = T_0_S_0_top[0];
      goal_B = T_0_S_0_top[1];
      goal_C = T_0_S_0_top[2];
      goal_D = T_0_S_0_top[3];
    }
    else if (target_side == 1)
    {
      goal_A = T_0_S_1_top[0];
      goal_B = T_0_S_1_top[1];
      goal_C = T_0_S_1_top[2];
      goal_D = T_0_S_1_top[3];
    }
  }
  else if (tower_pos == 1)
  {
    if (target_side == 0)
    {
      goal_A = T_1_S_0_top[0];
      goal_B = T_1_S_0_top[1];
      goal_C = T_1_S_0_top[2];
      goal_D = T_1_S_0_top[3];
    }
    else if (target_side == 1)
    {
      goal_A = T_1_S_1_top[0];
      goal_B = T_1_S_1_top[1];
      goal_C = T_1_S_1_top[2];
      goal_D = T_1_S_1_top[3];
    }
  }

  move_vert();
  delay(200);
  PD_control();
  delay(200);

  Serial.println("Move to start position."); Serial.println();
  goal_A = start_pos[0]; goal_B = start_pos[1]; goal_C = start_pos[2]; goal_D = start_pos[3];

  move_vert();
  delay(200);
  PD_control();                       // use PD_contol to move into final extraction position
  delay(200);


  Serial.println("Move to dump position."); Serial.println();
  goal_A = dump_pos[0]; goal_B = dump_pos[1]; goal_C = dump_pos[2]; goal_D = dump_pos[3];

  move_vert();
  delay(200);
  PD_control();
  delay(200);

  catch_servo.write(130);
  delay(2000);
  catch_servo.write(78);


  Serial.println("Move to start position."); Serial.println();
  goal_A = start_pos[0]; goal_B = start_pos[1]; goal_C = start_pos[2]; goal_D = start_pos[3];

  move_vert();
  delay(200);
  PD_control();                       // use PD_contol to move into final extraction position
  delay(200);
  
}

