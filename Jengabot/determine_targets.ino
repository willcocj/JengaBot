

void determine_targets() // Modifies the target array based on the two pieces on the same side with the highest score of the most high value neighbor blocks present above and below y
{
  Serial.println("I'm going to determine my next target block");
  int row = 2; // Start at row 2 for ease of calculating score and not wanting dummy 0s above the zeroth row (leaves row 1 unneccessarily inaccessible)
  int block = 0; // This value is shifted +1 to allow for easy division of three as a means to track row position.

  int scores[54];                       // Initiatte the 1 x 54 scores arrary. This is for target selection.

  for (int k = 0; k < 6; k++) {scores[k] = 0;}

  int temp_array[12];// initialize array for temporary target neighbor data
  int temp_block; // initialize 

  int c_0 = 1; // Multiplier for 1 row below potential target
  int c_1 = 2; // Multiplier for 1 row above potential target
  int c_2 = 1; // Multiplier for 2 rows above potential target

  int tough_spot = 3;
  int sweet_spot = 3;
  
  int lone_block_bonus = 0; // initilaize variable to use as LBB value
  int dbl_block_bonus = 0; // initilaize variable to use as DBB value
  
  int odd_top_pos = 0;
  int odd_top_row = 0;
  int odd_top_score = 0; 

  int odd_not_top_pos = 0;
  int odd_not_top_row = 0;
  int odd_not_top_score = 0;

  int odd_third_pos = 0;
  int odd_third_row = 0;
  int odd_third_score = 0; 

  
  int even_top_pos = 0;
  int even_top_row = 0;
  int even_top_score = 0; 
  
  int even_not_top_pos = 0;
  int even_not_top_row = 0;
  int even_not_top_score = 0;

  int even_third_pos = 0;
  int even_third_row = 0;
  int even_third_score = 0;

  Serial.println("                                                     This is the current tower map.");
  Serial.print("["); Serial.print(tower[0]);  Serial.print(", "); Serial.print(tower[1]);  Serial.print(", "); Serial.print(tower[2]);  Serial.println("]  row 0");  Serial.println();
  Serial.print("["); Serial.print(tower[3]);  Serial.print(", "); Serial.print(tower[4]);  Serial.print(", "); Serial.print(tower[5]);  Serial.println("]  row 1");  Serial.println();
  Serial.print("["); Serial.print(tower[6]);  Serial.print(", "); Serial.print(tower[7]);  Serial.print(", "); Serial.print(tower[8]);  Serial.println("]  row 2");  Serial.println();
  Serial.print("["); Serial.print(tower[9]);  Serial.print(", "); Serial.print(tower[10]); Serial.print(", "); Serial.print(tower[11]); Serial.println("]  row 3");  Serial.println();
  Serial.print("["); Serial.print(tower[12]); Serial.print(", "); Serial.print(tower[13]); Serial.print(", "); Serial.print(tower[14]); Serial.println("]  row 4");  Serial.println();
  Serial.print("["); Serial.print(tower[15]); Serial.print(", "); Serial.print(tower[16]); Serial.print(", "); Serial.print(tower[17]); Serial.println("]  row 5");  Serial.println();
  Serial.print("["); Serial.print(tower[18]); Serial.print(", "); Serial.print(tower[19]); Serial.print(", "); Serial.print(tower[20]); Serial.println("]  row 6");  Serial.println();
  Serial.print("["); Serial.print(tower[21]); Serial.print(", "); Serial.print(tower[22]); Serial.print(", "); Serial.print(tower[23]); Serial.println("]  row 7");  Serial.println();
  Serial.print("["); Serial.print(tower[24]); Serial.print(", "); Serial.print(tower[25]); Serial.print(", "); Serial.print(tower[26]); Serial.println("]  row 8");  Serial.println();
  Serial.print("["); Serial.print(tower[27]); Serial.print(", "); Serial.print(tower[28]); Serial.print(", "); Serial.print(tower[29]); Serial.println("]  row 9");  Serial.println();
  Serial.print("["); Serial.print(tower[30]); Serial.print(", "); Serial.print(tower[31]); Serial.print(", "); Serial.print(tower[32]); Serial.println("]  row 10"); Serial.println();
  Serial.print("["); Serial.print(tower[33]); Serial.print(", "); Serial.print(tower[34]); Serial.print(", "); Serial.print(tower[35]); Serial.println("]  row 11"); Serial.println();
  Serial.print("["); Serial.print(tower[36]); Serial.print(", "); Serial.print(tower[37]); Serial.print(", "); Serial.print(tower[38]); Serial.println("]  row 12"); Serial.println();
  Serial.print("["); Serial.print(tower[39]); Serial.print(", "); Serial.print(tower[40]); Serial.print(", "); Serial.print(tower[41]); Serial.println("]  row 13"); Serial.println();
  Serial.print("["); Serial.print(tower[42]); Serial.print(", "); Serial.print(tower[43]); Serial.print(", "); Serial.print(tower[44]); Serial.println("]  row 14"); Serial.println();
  Serial.print("["); Serial.print(tower[45]); Serial.print(", "); Serial.print(tower[46]); Serial.print(", "); Serial.print(tower[47]); Serial.println("]  row 15"); Serial.println();
  Serial.print("["); Serial.print(tower[48]); Serial.print(", "); Serial.print(tower[49]); Serial.print(", "); Serial.print(tower[50]); Serial.println("]  row 16"); Serial.println();
  Serial.print("["); Serial.print(tower[51]); Serial.print(", "); Serial.print(tower[52]); Serial.print(", "); Serial.print(tower[53]); Serial.println("]  row 17"); Serial.println();

  
  //Serial.println();
  //Serial.print("block:");
  //Serial.print(block);
  //Serial.print(", row: ");
  //Serial.println(row);

  for (int row = 2; row <= 17; row++)
  { 
    for (int b = 0; b <= 2; b++) // Iterate through blocks 6 through 41. Blocks 42-53 are inaccessible due to our extraction method.
    {
      block = 3 * row + b;
      //Serial.print("row: "); Serial.println(row);
      //Serial.print("row_block: "); Serial.println(b);
      //Serial.print("block: "); Serial.println(block);
      //Serial.print("Block Status: "); Serial.println(tower[block]);

      if (tower[block] == 0) // If there is no block in this position:
      {
        scores[block] = 0; // Give it a score of 0
      }
    
      else if (tower[block] == 1) // If there is a block present:
      { 
        if (b == 1) //  If block is the middle block:
        {
          if (tower[block - 1] == 0 && tower[block + 1] == 0) // If the middle block is alone in its row:
          {
            //Serial.println("MIDDLE BLOCK IS ALONE.");
            lone_block_bonus = -100; // Set score so high it is at the top of the list.
            row_drop_flag = 1; // Raise flag indicating potential to drop a row.
          }
        }      
      
      int score_2_up = 0;
      for (int k = 0; k <= 2; k++)
      {
        int row_2_up = row - 2;
        temp_block = (row_2_up * 3 + k);
        temp_array[k] = tower[temp_block];
        score_2_up = score_2_up + tower[temp_block]*c_2;
      }
      
      int score_1_up = 0;
      for (int k = 0; k <= 2; k++)
      {
        int row_1_up = row - 1;
        temp_block = (row_1_up * 3 + k);
        temp_array[k+3] = tower[temp_block];
        score_1_up = score_1_up + tower[temp_block]*c_1;
      }

      int score_0 = 0;
      for (int k = 0; k <= 2; k++)
      {
        temp_block = (row * 3 + k);
        temp_array[k+6] = tower[temp_block];
        score_0 = score_0 + tower[temp_block];
      }
      
      int score_1_dwn = 0;
      for (int k = 0; k <= 2; k++)
      {
        int row_1_dwn = row + 1;
        temp_block = (row_1_dwn * 3 + k);
        temp_array[k+9] = tower[temp_block];
        score_1_dwn = score_1_dwn + tower[temp_block]*c_0;
      }

      if (score_0 == 2)
      {
        if (tower[row * 3 + 1] == 1)
        {
          if (block == row * 3 + 1)
          {
            dbl_block_bonus = -500; // Ensure we don't try to extract the middle block when it's one of two in a row
          }
          else
          {
            dbl_block_bonus = 10;  
          }
        }
        else if (tower[row * 3 + 1] == 0)
        {
          dbl_block_bonus = -500;
          //Serial.println("MIDDLE BLOCK IS GONE. THIS ROW IS DEAD.");
        }
      }

      scores[block] = score_2_up + score_1_up + score_0 + score_1_dwn + lone_block_bonus + dbl_block_bonus;

      if (row >= 4 && row <= 11)
      {
        scores[block] = scores[block] + sweet_spot;
      }
      else if (row < 4)
      {
        scores[block] = scores[block] - tough_spot;
      }
      else {scores[block] = scores[block];}    
      
      lone_block_bonus = 0; //Reset LBB value holder.
      dbl_block_bonus = 0; //Reset DBB value holder.

      //Serial.print("score: "); Serial.println(scores[block]); Serial.println();

      //Serial.print("block:");
      //Serial.print(block);
      //Serial.print(", row: ");
      //Serial.println(row);
      }
    }
  }
  // Score array is noww full
  // Fill target array with the top two moves
  int odd_score = 0;
  int even_score = 0;
  for (int row = 2; row <= 17; row++)
  {
    if (row % 2 == 1) // If row is odd:
    {
      for (int b = 0; b <= 2; b++)
      {
        int temp_block = row * 3 + b;
        int temp_score = scores[temp_block];
        if (temp_score > odd_top_score)
        {
          odd_top_pos = temp_block;
          odd_top_row = row; 
          odd_top_score = temp_score;
        }
        else if(temp_score <= odd_top_score && temp_score > odd_not_top_score)
        {
          odd_not_top_pos = temp_block;
          odd_not_top_row = row;
          odd_not_top_score = temp_score;
        }
        else if(temp_score <= odd_not_top_score && temp_score > odd_third_score)
        {
          odd_third_pos = temp_block;
          odd_third_row = row;
          odd_third_score = temp_score;
        }
        else
        {
          continue; // continue if temp_score is lower tham either current best options
        }
      }
    }
    
    if (row % 2 == 0) // If row is even:
    {
      for (int b = 0; b <= 2; b++)
      {
        int temp_block = row * 3 + b;
        int temp_score = scores[temp_block];
        if (temp_score > even_top_score)
        {
          even_top_pos = temp_block;
          even_top_row = row;
          even_top_score = temp_score;
        }
        else if(temp_score <= even_top_score && temp_score > even_not_top_score)
        {
          even_not_top_pos = temp_block;
          even_not_top_row = row;
          even_not_top_score = temp_score;
        }
        else if(temp_score <= even_not_top_score && temp_score > even_third_score)
        {
          even_third_pos = temp_block;
          even_third_row = row;
          even_third_score = temp_score;
        }
        else
        {
          continue; // continue if temp_score is lower tham all three current best options
        }
      }
    }
  }

  odd_score = odd_top_score + odd_not_top_score + odd_third_score;
  even_score = even_top_score + even_not_top_score + even_third_score;

  //Serial.print("odd_score: ");Serial.println(odd_score);
  //Serial.print("even_score: "); Serial.println(even_score); Serial.println();
  
  if (odd_score > even_score)
  {
    target_side = 1;
    targets[0] = odd_top_pos;
    targets[1] = odd_not_top_pos;
    targets[2] = odd_third_pos;
    target_rows[0] = odd_top_row;
    target_rows[1] = odd_not_top_row;
    target_rows[2] = odd_third_row;
    /*Serial.println("The odd side has been targeted.");
    Serial.print("Our target blocks are: ");
    Serial.print("[");
    Serial.print(targets[0]);
    Serial.print(", ");
    Serial.print(targets[1]);
    Serial.print(", ");
    Serial.print(targets[2]);
    Serial.println("]");
    Serial.println();  
    Serial.print("Our target rows are: ");
    Serial.print("[");
    Serial.print(target_rows[0]);
    Serial.print(", ");
    Serial.print(target_rows[1]);
    Serial.print(", ");
    Serial.print(target_rows[2]);
    Serial.println("]");
    Serial.println(); */  
  } 

  else
  {
    target_side = 0;
    targets[0] = even_top_pos;
    targets[1] = even_not_top_pos;
    targets[2] = even_third_pos;
    target_rows[0] = even_top_row;
    target_rows[1] = even_not_top_row;
    target_rows[2] = even_third_row;
    /*Serial.println("The even side has been targetd.");
    Serial.print("Our target blocks are: ");
    Serial.print("[");
    Serial.print(targets[0]);
    Serial.print(", ");
    Serial.print(targets[1]);
    Serial.print(", ");
    Serial.print(targets[2]);
    Serial.println("]");
    Serial.println();
    Serial.print("Our target rows are: ");
    Serial.print("[");
    Serial.print(target_rows[0]);
    Serial.print(", ");
    Serial.print(target_rows[1]);
    Serial.print(", ");
    Serial.print(target_rows[2]);
    Serial.println("]");
    Serial.println();  */
  }
}
