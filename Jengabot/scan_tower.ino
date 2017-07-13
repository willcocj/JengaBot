
void scan_tower()
{
  ////// The first three arrays are the potentiometer values associated with the tower being in the Zeroth position
  int T_0_target_pot_values[42][4] = // Potentiometer values for all blocks in the Zeroth tower position. These values are to be gotten empirically.
  {
    {15634, 7857, 19598, 13980}, {14750, 7858,15543, 14228},  {14117, 7857, 15112, 14117}, // row  0  ; blocks  0,  1,  2
    {22290, 7598, 15172, 3301},  {23040, 7598, 14820, 3110},  {23975, 7597, 14529, 2940}, // row  1  ; blocks  3,  4,  5  //####// block 5 pot 4 needs to be checked
    {15933, 7204, 15062, 13824}, {15093, 7204, 14524, 13881}, {14117, 7204, 14075, 14117}, // row  2  ; blocks  6,  7,  8  changed
    {22348, 6848, 14378, 3353},  {23216, 6848, 14089, 3044},  {24119, 6848, 13826, 2651}, // row  3  ; blocks  9, 10, 11 changed
    {15933, 6424, 14264, 13708}, {15152, 6424, 13874, 13859}, {14117, 6424, 13401, 14117}, // row  4  ; blocks 12, 13, 14 changed
    {22497, 6072, 13675, 3206},  {23236, 6072, 13400, 3002},  {24050, 6072, 13065, 2745}, // row  5  ; blocks 15, 16, 17 changed
    {15989, 5665, 13530, 13690}, {15097, 5665, 13204, 14016}, {14117, 5605, 12523, 14117}, // row  6  ; blocks 18, 19, 20 changed
    {22507, 5331, 12941, 3141},  {23235, 5331, 12665, 2940},  {24055, 5331, 12346, 2655}, // row  7  ; blocks 21, 22, 23 chnaged
    {15960, 4912, 12824, 13816}, {15117, 4912, 12355, 13935}, {14117, 4912, 11795, 14117}, // row  8  ; blocks 24, 25, 26 changed
    {22493, 4541, 12153, 3215},  {23293, 4541, 11872, 2976},  {24170, 4541, 11595, 2596}, // row  9  ; blocks 27, 28, 29 changed
    {15922, 4110, 12074, 13877}, {15083, 4110, 11700, 14040}, {14117, 4110, 11300, 14117}, // row 10  ; blocks 30, 31, 32 changed
    {22433, 3752, 11420, 3247},  {23205, 3752, 11092, 3036},  {24149, 3752, 10844, 2669}, // row 11  ; blocks 33, 34, 35 changed
    {15790, 3325, 11392, 14018}, {14939, 3325, 10900, 14137}, {14117, 3325, 10525, 14117}, // row 12  ; blocks 36, 37, 38 changed
    {22536, 3013, 10759, 3097},  {23202, 3013, 10372, 3032},  {24142, 3013, 10113, 2691}, // row 13  ; blocks 39, 40, 41 changed
  };
  int T_O_target_row_pot_values[14][4] = 
  {
    {15449, 7860,  15125, 14045}, // row 0
    {23530, 7600,  15412, 2836},  // row 1
    {15342, 7078,  14363, 14092}, // row 2
    {23512, 6816,  14533, 2838},  // row 3
    {15333, 6288,  13610, 14093}, // row 4
    {23340, 6040,  13863, 2979},  // row 5
    {15376, 5538,  12880, 14135}, // row 6
    {23626, 5289,  13185, 2757},  // row 7
    {15290, 4776,  12095, 14108}, // row 8
    {23585, 4498,  12405, 2749},  // row 9
    {15515, 3969,  11295, 14048}, // row 10
    {23663, 3704,  11509, 2681},  // row 11
    {15470, 3210,  10448, 14005}, // row 12
    {23774, 2955,  10906, 2619}   // row 13
  };
  int T_0_S_0_scan_pot_values[14][4] = // Only motors B and C will change; [1] and [2], respectively. These are not extraction positions.
  { // These are Tower Zeros, Zeroth side center positions of every row.
    {15546, 8658, 15727, 14011}, // row  0
    {15534, 8292, 15394, 14000}, // row  1
    {15515, 7912, 15022, 13988}, // row  2
    {15520, 7513, 14582, 13992}, // row  3
    {15535, 7120, 14237, 13996}, // row  4
    {15527, 6722, 13953, 14077}, // row  5
    {15410, 6334, 13592, 14126}, // row  6
    {15374, 5957, 13148, 14052}, // row  7
    {15434, 5587, 12758, 14010}, // row  8
    {15474, 5206, 12320, 13929}, // row  9
    {15424, 4824, 11874, 13879}, // row 10
    {15530, 4428, 11508, 13892}, // row 11
    {15498, 4020, 11164, 13889}, // row 12
    {15471, 3635, 10805, 14008} // row 13
  };
  int T_0_S_1_scan_pot_values[14][4] = // Only motors B and C will change; [1] and [2], respectively. These are not extraction positions.
  { // These are Tower Zeros, Ones side center positions of every row.
    {23812, 8650, 16525, 2612}, // row  0
    {23812, 8420, 16296, 2612}, // row  1
    {23646, 7978, 15810, 2789}, // row  2 changed
    {23665, 7587, 15340, 2759}, // row  3 changed
    {23731, 7193, 15028, 2757}, // row  4 changed
    {23654, 6858, 14642, 2716}, // row  5 changed
    {23764, 6474, 14242, 2745}, // row  6 changed
    {23706, 6099, 13896, 2760}, // row  7 changed 
    {23754, 5725, 13556, 2706}, // row  8 changed
    {23673, 5354, 13056, 2830}, // row  9 changed
    {23644, 4967, 12766, 2873}, // row 10 changed
    {23759, 4573, 12456, 2671}, // row 11 changed
    {23728, 4163, 12053, 2667}, // row 12 changed
    {23691, 3784, 11632, 2794}  // row 13 changing
  };

  ////// The following three arrays are the potentiometer values associated with the tower being in the Ones position
  int T_1_target_pot_values[42][4] = // Potentiometer values for all blocks in the Ones tower position. These values are to be gotten empirically.
  {
    {15589, 7511, 15455, 13900}, {14670, 7511, 15030, 14099}, {13789, 7511, 14605, 14268}, // row  0  ; blocks  0,  1,  2
    {15589, 7511, 15455, 13900}, {14670, 7511, 15030, 14099}, {13789, 7511, 14605, 14268}, // row  1  ; blocks  3,  4,  5
    {22703, 7247, 14857, 3017},  {23493, 7247, 14531, 2794},  {24354, 7247, 14305, 2600},  // row  2  ; blocks  6,  7,  8 changed
    {15766, 6801, 14832, 14065}, {14988, 6801, 14294, 14101}, {14148, 6801, 13916, 14328}, // row  3  ; blocks  9,  10, 11 changed
    {22656, 6470, 14122, 3062},  {23496, 6470, 13884, 2765},  {24300, 6470, 13538, 2595},  // row  4  ; blocks  12, 13, 14 changed
    {15811, 6044, 14020, 14002}, {14984, 6044, 13545, 14100}, {14171, 6044, 13166, 14307}, // row  5  ; blocks  15, 16, 17 changed
    {22650, 5714, 13385, 2976},  {23512, 5714, 13149, 2673},  {24341, 5714, 12865, 2476},  // row  6  ; blocks  18, 19, 20 changed
    {15788, 5289, 13242, 13976}, {14926, 5289, 12819, 14093}, {14158, 5290, 12348, 14240}, // row  7  ; blocks  21, 22, 23 changed
    {22746, 4956, 12639, 2967},  {23422, 4956, 12306, 2867},  {23424, 4956, 12305, 2867},  // row  8  ; blocks  24, 25, 26 changed
    {15789, 4509, 12495, 13905}, {15023, 4509, 12019, 14080}, {14140, 4509, 11580, 14331}, // row  9  ; blocks  27, 28, 29 changed
    {22595, 4154, 11825, 3161},  {23433, 4154, 11556, 2797},  {24262, 4154, 11289, 2603},  // row  10 ; blocks  30, 31, 32 changed
    {15853, 3716, 11726, 13986}, {14940, 3716, 11358, 14180}, {14163, 3716, 10855, 14240}, // row  11 ; blocks  33, 34, 35 changed
    {22646, 3385, 11095, 3073},  {23412, 3385, 10840, 2821},  {24262, 3385, 10560, 2556},  // row  12 ; blocks  36, 37, 38 changed
    {15824, 2964, 10972, 13962}, {14938, 2964, 10623, 14224}, {14122, 2964, 10291, 14494}, // row  13 ; blocks  39, 40, 41 changed
  };
  int T_1_target_row_pot_values[14][4] = 
  {
    {23509, 7900, 15000, 2800},  // row 0
    {15400, 7511, 14645, 13977}, // row 1
    {23509, 7190, 14916, 2832},  // row 2
    {15411, 6721, 13930, 13970}, // row 3
    {23507, 6410, 14195, 2812},  // row 4
    {15372, 5962, 13144, 13963}, // row 5
    {23589, 5662, 13432, 2761},  // row 6
    {15462, 5205, 12360, 13843}, // row 7
    {23618, 4906, 12669, 2748},  // row 8
    {15371, 4420, 11600, 14042}, // row 9
    {23533, 4105, 12010, 2656},  // row 10
    {15475, 3636, 10864, 13879}, // row 11
    {23608, 3336, 11226, 2744},  // row 12
    {15375, 2888, 10054, 13980}  // row 13
  };
  int T_1_S_0_scan_pot_values[18][4] = // Only motors B and C will change. These are not extraction positions.
  { // These are Tower Ones, Zeroth side center positions of every row.
    {23812, 8850, 16605, 2612}, // row  0 // {23812, 8650, 16525, 2612}, // row  0
    {23812, 8620, 16376, 2612}, // row  1 // {23812, 8420, 16296, 2612}, // row  1
    {23795, 8105, 15702, 2844}, // row  2 // {23795, 7905, 15622, 2844}, // row  2
    {23640, 7860, 15447, 2786}, // row  3 // {23640, 7660, 15367, 2786}, // row  3
    {23631, 7336, 14946, 2785}, // row  4 // {23631, 7136, 14866, 2785}, // row  4
    {23628, 7081, 14733, 2757}, // row  5 // {23628, 6881, 14653, 2757}, // row  5
    {23764, 6539, 14280, 2660}, // row  6 // {23764, 6339, 14200, 2660}, // row  6
    {23782, 6311, 14171, 2583}, // row  7 // {23782, 6111, 14091, 2583}, // row  7
    {23667, 5806, 13666, 2612}, // row  8 // {23762, 5598, 13572, 2612}, // row  8
    {23779, 5554, 13425, 2633}, // row  9 // {23779, 5354, 13345, 2633}, // row  9
    {23809, 5029, 12897, 2598}, // row 10 // {23809, 4829, 12817, 2598}, // row 10
    {23759, 4773, 12646, 2639}, // row 11 // {23759, 4573, 12566, 2639}, // row 11
    {23807, 4219, 12069, 2623}, // row 12 // {23807, 4019, 11989, 2623}, // row 12
    {23747, 3968, 11833, 2586}  // row 13 // {23747, 3768, 11753, 2586}   // row 13
  };
  int T_1_S_1_scan_pot_values[18][4] = // Only motors B and C will change. These are not extraction positions.
  { // These are Tower Ones, Ones side center positions of every row.
    {15546, 8658, 15727, 14011}, // row  0
    {15534, 8292, 15394, 14000}, // row  1
    {15515, 7912, 15022, 13988}, // row  2
    {15520, 7513, 14582, 13992}, // row  3
    {15535, 7120, 14237, 13996}, // row  4
    {15527, 6722, 13953, 14077}, // row  5
    {15410, 6334, 13592, 14126}, // row  6
    {15374, 5957, 13148, 14052}, // row  7
    {15434, 5587, 12758, 14010}, // row  8
    {15474, 5206, 12320, 13929}, // row  9
    {15424, 4824, 11874, 13879}, // row 10
    {15530, 4428, 11508, 13892}, // row 11
    {15498, 4020, 11164, 13889}, // row 12
    {15471, 3635, 10805, 14008} // row 13
  };

  //float float_IR_values[6] = {0.00, 0.00, 0.00, 0.00};       // Initiate a 1x6 array for IR sensor average float values and fill it with zeros.
  //int IR_values[6] = {0, 0, 0, 0, 0, 0};                     // Initiate a 1x6 array for IR sensor average values and fill it with ones. This is used to map the tower. elements are temporarily assigned values of 1 when a block is absent.
  //float targets_IR_values[3][6];

  int cur_side = target_side;

  ////// SCAN SCAN SCAN SCAN SCAN SCAN SCAN SCAN SCAN SCAN SCAN SCAN SCAN SCAN SCAN SCAN SCAN SCAN SCAN SCAN SCAN SCAN SCAN SCAN //////

  Serial.println("I am now going to scan the tower.");

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

  //****// Move into position above the tower //****//
  move_vert();
  delay(200);
  PD_control();
  delay(200);
  //move_in_plane();

  //****// move into target position

  if (Round == 1 && Start == 0)   // If it is the start of the match and we are the Zeroth player, We have a fresh to extract the first block from.
  {
    Serial.println("We start this match as the zeroth player");
    
    ////// Get target row's pot values and store them in target_row_pots array for extract_return subroutine to use //////
    Serial.println("I'm getting target_row_pot values");
    
    if (tower_pos == 0)                     // TYP. If tower is in the zeroth position, in which the top row is parallel with our longest side
    {
      target_row_pots[0] = T_O_target_row_pot_values[target_rows[0]][0];
      target_row_pots[1] = T_O_target_row_pot_values[target_rows[0]][1];
      target_row_pots[2] = T_O_target_row_pot_values[target_rows[0]][2];
      target_row_pots[3] = T_O_target_row_pot_values[target_rows[0]][3];
    }
    else if (tower_pos == 1)
    {
      target_row_pots[0] = T_1_target_row_pot_values[target_rows[0]][0];
      target_row_pots[1] = T_1_target_row_pot_values[target_rows[0]][1];
      target_row_pots[2] = T_1_target_row_pot_values[target_rows[0]][2];
      target_row_pots[3] = T_1_target_row_pot_values[target_rows[0]][3];
    }

    ////// Get target block's pot values and store them in mod_target_blocks array for extract_return subroutine to use //////
    Serial.println("I'm getting target_block_pot values");
    if (tower_pos == 0)           // if the tower is in the zereoth position
    {
      mod_target_pots[0] = T_0_target_pot_values[targets[0]][0];
      mod_target_pots[1] = T_0_target_pot_values[targets[0]][1];
      mod_target_pots[2] = T_0_target_pot_values[targets[0]][2];
      mod_target_pots[3] = T_0_target_pot_values[targets[0]][3];
    }
    else if  (tower_pos == 1)     // else if the tower iss in the ones position
    {
      mod_target_pots[0] = T_1_target_pot_values[targets[0]][0];
      mod_target_pots[1] = T_1_target_pot_values[targets[0]][1];
      mod_target_pots[2] = T_1_target_pot_values[targets[0]][2];
      mod_target_pots[3] = T_1_target_pot_values[targets[0]][3];
    }
  }

  else                                        // Else if it is not the start of the match or we are the First player, At least one block has been removed. Must scan tower to determine opponents move.
  {
    //****// The following script iterates through the rows to scan each row with IR sensors //****//
    for (int r = 1; r <= 13; r++)             // Move down the tower one row at a time taking sensor readings at each row. Will slow to zero on approach and will delay before engaging again.
    {
      if (tower_pos == 0)                     // TYP. If tower is in the zeroth position, in which the top row is parallel with our longest side
      {
        if (target_side == 0)                 // TYP. If our target blocks are on the zeroth side, which is the side in which we can extract blocks from the zeroth/even rows
        {
          goal_B = T_0_S_0_scan_pot_values[r][1];  // TYP. set goal_B to pot value for each row on the Zeroth Tower's Zeroth side
          goal_C = T_0_S_0_scan_pot_values[r][2];  // TYP. set goal_B to pot value for each row on the Zeroth Tower's Zeroth side
        }
        else if (target_side == 1)            // TYP. Else if the target blocks are on the ones side, which is the side we can extrat the blocks from the ones/odd rows   
        {
          goal_B = T_0_S_1_scan_pot_values[r][1];
          goal_C = T_0_S_1_scan_pot_values[r][2];
        }
      }
      else if (tower_pos == 1)
      {
        if (target_side == 0)
        {
          goal_B = T_1_S_0_scan_pot_values[r][1];
          goal_C = T_1_S_0_scan_pot_values[r][2];
        }
        else if (target_side == 1)
        {
          goal_B = T_1_S_1_scan_pot_values[r][1];
          goal_C = T_1_S_1_scan_pot_values[r][2];
        }
      }

      move_vert();                            // with goals set, move into position at the center of each row
      delay(200);
      PD_control();
      digitalWrite(13, HIGH);
      delay(500);
      read_IR();                              // call IR subroutine to modify the IR arrays with new data
      digitalWrite(13, LOW);

      Serial.println(); Serial.print("row: "); Serial.println(r); Serial.println();
      Serial.print("IR_0: "); Serial.println(float_IR_values[0]);
      Serial.print("IR_1: "); Serial.println(float_IR_values[1]);
      Serial.print("IR_2: "); Serial.println(float_IR_values[2]);
      Serial.print("IR_3: "); Serial.println(float_IR_values[3]);
      Serial.print("IR_4: "); Serial.println(float_IR_values[4]);
      Serial.print("IR_5: "); Serial.println(float_IR_values[5]);
      Serial.print("IR_0: "); Serial.println(IR_values[0]);
      Serial.print("IR_1: "); Serial.println(IR_values[1]);
      Serial.print("IR_2: "); Serial.println(IR_values[2]);
      Serial.print("IR_3: "); Serial.println(IR_values[3]);
      Serial.print("IR_4: "); Serial.println(IR_values[4]);
      Serial.print("IR_5: "); Serial.println(IR_values[5]);

      //****// The following script analyzes the IR sensor values, which is used  
      
      if (r == target_rows[0] || r == target_rows[1] || r == target_rows[2])  // if we are on one of our three target rows
      {
        if (r == target_rows[0])                                              // if our current row is our primary target
        {
          for (int i = 0; i < 6; i++)                                         // TYP. use for loop to iterate through the 6 IR sensor values
          {
            targets_IR_values[0][i] = float_IR_values[i];                     // assign the current row's average IR values to the primary targets IR values
          }
        }

        else if (r == target_rows[1])                                         // else if our current row is our Secondary target
        {
          for (int i = 0; i < 6; i++)
          {
            targets_IR_values[1][i] = float_IR_values[i];                     // assign the current row's average IR values to the secondary targets IR values
          }
        }

        else if (r == target_rows[2])                                         // else if our current row is our tertiary target
        {
          for (int i = 0; i < 6; i++)
          {
            targets_IR_values[2][i] = float_IR_values[i];                     // assign the current row's avearge IR values to the tertiary targets IR values
          }
        }
      }

      //****// The following portion of this script is specific to each block within the current row //****//

      for (int b = 0; b < 3; b++)           // for each of the 3 blocks on this row
      {
        int block = 3 * r + b;              // calculate the absolute block number


        if (target_side == 0)               // if target side is the zeroth/even side
        {
          if (r % 2 == 0)                   // and if we are at an even for, sensors 0,1,2 are for detection
          {
            if (IR_values[b] == 0)          // If the "IR values" for pins 0,1 or 2 are zero
            { 
              tower[block] = 0;             // this block is not present
            }
          }
 
          else                              // else, we are at an odd row, sensors 4,5,6 are for detection
          {
            if (IR_values[b + 3] == 0)      // If the "IR values" for pins 3,4 or 5 are zero
            { 
              tower[block] = 0;             // this block is not present
            }
          }
        }
        
        else if (target_side == 1)          // if target side is the ones/odd side
        {
          if (r % 2 == 0)                   // and if we are at an even for, sensors 3, 4 ,5 are for detection
          {
            if (IR_values[b+3] == 0)        // If the "IR values" for pins 3,4 or 5 are zero
            { 
              tower[block] = 0;             // this block is not present
            }
          }
          else                              // else, we are at an odd row, sensors 0, 1, 2 are for detection
          {
            if (IR_values[b] == 0)          // If the "IR values" for pins 0, 1, or 2 are zero
            { 
              tower[block] = 0;             // this block is not present
            }
          }
        }
        
       /*if (block == targets[1] && tower[block] == 0)                         // if the current block is the target block and the target block is absenit
        {
          targets[1] = targets[2];                                            // redefine the target block to be the secondary target
          for (int i = 0; i < 6; i++)
          {
            targets_IR_values[1][i] = targets_IR_values[2][i];                // replace the primary target block's IR readings with those of the secondary target for the 
          }
        }

        if (block == targets[0] && tower[block] == 0)                         // if the current block is the target block and the target block is absenit
        {
          targets[0] = targets[1];                                            // redefine the target block to be the secondary target
          for (int i = 0; i < 6; i++)
          {
            targets_IR_values[0][i] = targets_IR_values[1][i];                // replace the primary target block's IR readings with those of the secondary target for the 
          }
        }*/
      }// end of b "block" for loop 
    }// end of row for loop

    //determine_targets();

    if (cur_side != target_side)
    {
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

  //****// Move into position above the tower //****//
  move_vert();
  delay(200);
  PD_control();
  delay(200);
    }

  if (tower[targets[1]] == 0)                         // if the current block is the target block and the target block is absenit
  {
    targets[1] = targets[2];
    target_rows[1] = target_rows[2];
    // redefine the target block to be the secondary target
    for (int i = 0; i < 6; i++)
    {
      targets_IR_values[1][i] = targets_IR_values[2][i];                // replace the primary target block's IR readings with those of the secondary target for the 
    }
  }

  if (tower[targets[0]] == 0)                         // if the current block is the target block and the target block is absenit
  {
    targets[0] = targets[1];                                           // redefine the target block to be the secondary target
    target_rows[0] = target_rows[1];
    for (int i = 0; i < 6; i++)
    {
      targets_IR_values[0][i] = targets_IR_values[1][i];                // replace the primary target block's IR readings with those of the secondary target for the 
    }
  }

    ////// Get target row's pot values and store them in target_row_pots array for extract_return subroutine to use //////
    Serial.println("I'm getting target_row_pot values");
    
    if (tower_pos == 0)                     // TYP. If tower is in the zeroth position, in which the top row is parallel with our longest side
    {
      target_row_pots[0] = T_O_target_row_pot_values[target_rows[0]][0];
      target_row_pots[1] = T_O_target_row_pot_values[target_rows[0]][1];
      target_row_pots[2] = T_O_target_row_pot_values[target_rows[0]][2];
      target_row_pots[3] = T_O_target_row_pot_values[target_rows[0]][3];
    }
    else if (tower_pos == 1)
    {
      target_row_pots[0] = T_1_target_row_pot_values[target_rows[0]][0];
      target_row_pots[1] = T_1_target_row_pot_values[target_rows[0]][1];
      target_row_pots[2] = T_1_target_row_pot_values[target_rows[0]][2];
      target_row_pots[3] = T_1_target_row_pot_values[target_rows[0]][3];
    }

    ////// Get target block's pot values and store them in mod_target_blocks array for extract_return subroutine to use //////
    if (tower_pos == 0)           // if the tower is in the zereoth position
    {
      mod_target_pots[0] = T_0_target_pot_values[targets[0]][0];
      mod_target_pots[1] = T_0_target_pot_values[targets[0]][1];
      mod_target_pots[2] = T_0_target_pot_values[targets[0]][2];
      mod_target_pots[3] = T_0_target_pot_values[targets[0]][3];
    }
    else if  (tower_pos == 1)     // else if the tower iss in the ones position
    {
      mod_target_pots[0] = T_1_target_pot_values[targets[0]][0];
      mod_target_pots[1] = T_1_target_pot_values[targets[0]][1];
      mod_target_pots[2] = T_1_target_pot_values[targets[0]][2];
      mod_target_pots[3] = T_1_target_pot_values[targets[0]][3];
    }
  }// end of else (not round 0 or not player 0 condition conditional) 
}// end scan tower

      ///// I now need to determine what to do with the IR sensor values. For each row, three of the IR sensors are used to determine what blocks are still present, while the other two analog sensors are used to determine misalignment.
      ///// The misalignment needs to be stored for the target rows. Once the opponents last move has been determined and the target block has been finalized, the pot values for the target block needs to be calculated from the misalignment of the target row
      ///////////////////////////////////////////////////////////////////////////////////////THIS IS WHER I"M AT???????????????????????????????????????????????????????????????????????????????????????????
