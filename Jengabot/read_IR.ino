
float read_IR()
{
  int analog_thresh = 190;                                                        // This is the threshold that must be crossed before the analog sensor is accurately detecting a block's presence
  int analog_IR_pins[4] = {62, 64, 66, 68};                                       // IR sensors [1, 2, 4, 5] in pins [A8, A10, A12, A14]; [62, 64, 66, 68]
  int digital_IR_pins[2] = {42, 45};                                              // IR sensors [3, 6] in digital pins [?, ?]

  ////// IR_0 , ANALOG//////
  for (int k = 1; k < 13; k++)                                                   // This for loop makes 8 iterations for the first analog IR sensor (IR_0)
  {
    float_IR_values[0] = (float_IR_values[0]*(k-1) + float(analogRead(analog_IR_pins[0])))/(k);   // This provides a running avearge of 8 IR sensor analog values for the first analog IR sensor (IR_0); [prev_avg * (k-1) + 1000 * new_value] / k
  }
  if (float_IR_values[0] < analog_thresh) {IR_values[0] = 0;}                               // If the analog value is lower than the threshold, then no block is there, so we assign it HIGH to match the digital pin value
  else {IR_values[0] = 1;}

  ////// IR_1, DIGITAL //////
  for (int k = 1; k < 13; k++)                                                           // This for loop makes 8 iterations for each of the 4 analog IR sensors
  {
    float_IR_values[1] = (float_IR_values[1]*(k-1) + float(digitalRead(digital_IR_pins[0])))/(k);  // This provides a running avearge of 8 IR sensor analog values for each of the four analog IR sensors
  }
  if (float_IR_values[1] >= 0.2) {IR_values[1] = 0;}  
  else {IR_values[1] = 1;}

  /*float_IR_values[1] = digitalRead(digital_IR_pins[0]);
  if (float_IR_values[1] == 1) {IR_values[1] = 0;}  
  else {IR_values[1] = 1;}*/

  ////// IR_2, ANALOG //////
  for (int k = 1; k < 13; k++)                                                   // This for loop makes 8 iterations for the first analog IR sensor (IR_0)
  {
    float_IR_values[2] = (float_IR_values[2]*(k-1) + float(analogRead(analog_IR_pins[1])))/(k);   // This provides a running avearge of 8 IR sensor analog values for the first analog IR sensor (IR_0); [prev_avg * (k-1) + 1000 * new_value] / k
  }
  if (float_IR_values[2] < analog_thresh) {IR_values[2] = 0;}                               // If the analog value is lower than the threshold, then no block is there, so we assign it HIGH to match the digital pin value
  else {IR_values[2] = 1;} 

  ////// IR_3, ANALOG //////
  for (int k = 1; k < 13; k++)                                                   // This for loop makes 8 iterations for the first analog IR sensor (IR_0)
  {
    float_IR_values[3] = (float_IR_values[3]*(k-1) + float(analogRead(analog_IR_pins[2])))/(k);   // This provides a running avearge of 8 IR sensor analog values for the first analog IR sensor (IR_0); [prev_avg * (k-1) + 1000 * new_value] / k
  }
  if (float_IR_values[3] < analog_thresh) {IR_values[3] = 0;}                               // If the analog value is lower than the threshold, then no block is there, so we assign it HIGH to match the digital pin value
  else {IR_values[3] = 1;}

  ////// IR_4, DIGITAL //////
  for (int k = 1; k < 13; k++)                                                   // This for loop makes 8 iterations for each of the 4 analog IR sensors
  {
    float_IR_values[4] = (float_IR_values[4]*(k-1) + float(digitalRead(digital_IR_pins[1])))/(k);  // This provides a running avearge of 8 IR sensor analog values for each of the four analog IR sensors
  }
  if (float_IR_values[4] >= 0.2) {IR_values[4] = 0;}  
  else {IR_values[4] = 1;}
  
  ////// IR_5, ANALOG //////
  for (int k = 1; k < 13; k++)                                                   // This for loop makes 8 iterations for each of the 4 analog IR sensors
  {
    float_IR_values[5] = (float_IR_values[5]*(k-1) + float(analogRead(analog_IR_pins[3])))/(k);  // This provides a running avearge of 8 IR sensor analog values for each of the four analog IR sensors
  }
  if (float_IR_values[5] < analog_thresh) {IR_values[5] = 0;}
  else {IR_values[5] = 1;}
}



