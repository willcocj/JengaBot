
// The First two lines must be set to declare our player order and position of the tower relative to our home corner.
boolean tower_pos = 1;         // Set to 0 if the zeroth row is parallel to our long side, 1 if it is perpendicular to it.

int Start = 1;                  
                  // Set to 0 if we go first, 1 if we go second.

int targets[3] = {20, 30, 30};           // Initiate and set the 1 x 3 target arrary. This contains the block numbers [0:53] for the three potential targets
int target_rows[3] = {6, 10, 10};       // Initiate and set the 1x 3 target row array. This contains the row numbers [0:17] for the three potential targets
boolean target_side = 0;              // Target side is 0 for the zeroth/evens side and 1 for the ones/odds side

// Include libraries
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <Adafruit_ADS1015.h>

Adafruit_ADS1115 ads1115;    // Construct an ads1115 at the default address: 0x48

int Round = 0;                  // Set a round counter to 0.

int start_pos[4] = {2000, 11000, 18800, 2500};  // Set start position values to return to at the end of each turn in preperation for the next turn.

int T_0_S_0_top[4] = {15789, 10572, 17575, 13862};     // Pot values and servo angle for the top position, ready to descend the tower attacking the zeroth face.
int T_0_S_1_top[4] = {23683, 10457, 18391, 2750};     // Pot values and servo angle for the top position, ready to descend the tower attacking the zeroth face.
int T_1_S_0_top[4] = {23683, 10457, 18391, 2750};     // Pot values and servo angle for the top position, ready to descend the tower attacking the zeroth face.
int T_1_S_1_top[4] = {15789, 10572, 17575, 13862};
// Setting gloabal goal potentiometer values to the top position.
int goal_A = start_pos[0];                  // Motor A provides Yaw about the Z at the origin.
int goal_B = start_pos[1];                  // Motor B is used only for vertical translation at the origin. Is used with Motor C to maintain 0 lateral traslation.
int goal_C = start_pos[2];                  // Motor C is used for horizontal and lateral translation. It engages alone for lateral and is synchronized with Motor B for vertical translation.
int goal_D = start_pos[3];                  // Motor D provides yaw about the z axis of the rlative origin at the end effector.

int dump_pos[4] = {2000, 5000, 12700, 2500};

int tower[54];                        // Initiatte the 1 x 54 tower arrary. This is for mapping

int target_row_pots[4];
int mod_target_pots[4];               // Initialize a 1 x 4 array to fill with target pot values to be replaced with modified target pot values


int row_drop_flag = 0;                // Define a flag to use in case a row may be completely dropped.

float float_IR_values[6] = {0.00, 0.00, 0.00, 0.00, 0.00, 0.00};       // Initiate a 1x6 array for IR sensor average float values and fill it with zeros.
int IR_values[6] = {0, 0, 0, 0, 0, 0};                     // Initiate a 1x6 array for IR sensor average values and fill it with ones. This is used to map the tower. elements are temporarily assigned values of 1 when a block is absent.
float targets_IR_values[3][6];

int it_0[4] = {24100, 5000, 12700, 15060}; //This is a test target for development
int it_1[4] = {23150, 5000, 12700, 15060}; //This is a test target for development

////////FOR MOTOR CONTROL////////

int precision_A = 25;              //how close to final value to get
const int precision_B = 25;
const int precision_C = 25;
int precision_D = 25;

float slow_down_dist = 625;       // Threshold difference between goal and current position in which once below this value, speed is a function of this difference.

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Initializing motor B
Adafruit_DCMotor *motor_B = AFMS.getMotor(1);

// Initializing motor C
Adafruit_DCMotor *motor_C = AFMS.getMotor(2);

// Initializing motor D
Adafruit_DCMotor *motor_D = AFMS.getMotor(3);

// Initialize wrist servo by creating a servo object
Servo catch_servo;
int catch_pin = 50;

// Initializing motor A
const int dir_pin_A = 2;        // Set Direction pin to digital pin 2
const int vel_pin_A = 3;        // Set PWM (speed) pin to digital pin 3

// Initialize motor potentiometer pins for motor feedback

int16_t  cur_pos_A, cur_pos_B, cur_pos_C, cur_pos_D;

const int feedback_A = 0;      //pot_A sensing pin
const int feedback_B = 1;      //pot_B sensing pin
const int feedback_C = 2;      //pot_C sensing pin
const int feedback_D = 3;      //pot_D sensing

////////END FOR MOTOR CONTROL////////

const int punch_pin = 26;

const int start_turn = 5;

const int end_turn = 6;

///////////FOR USER INPUT///////////
int opp_move;
int tens;
int ones;
int extras;
int counter = 0;
/////////END FOR USER INPUT/////////

////////// SETUP SETUP SETUP SETUP SETUP SETUP SETUP SETUP SETUP SETUP SETUP SETUP SETUP SETUP SETUP SETUP SETUP SETUP SETUP SETUP SETUP SETUP SETUP SETUP SETUP SETUP //////////

void setup()
{
  Serial.begin(115200);         // Initialize Serial connection at a baud rate of 115200

  ads1115.begin();  // Initialize 16-bit ADC

  AFMS.begin();  // create with the default frequency 1.6KHzt

  for (int i = 0; i <= 41; i++) // Populate tower array with ones indicting they are all present
  {
    tower[i] = 1;       // This list includes the out-of-play zeroth row of blocks
  }
  for (int i = 42; i < 54; i++) // Populate tower array with ones indicting they are all present
  {
    tower[i] = 0;       // This list includes the out-of-play zeroth row of blocks
  }

  // Initialize motor control pins on Motorshield 2
  pinMode(dir_pin_A, OUTPUT); // sets D2 to output
  pinMode(vel_pin_A, OUTPUT); // sets D3 to output

  // Initialize servo pin and set servo starting position
  catch_servo.attach(catch_pin);
  catch_servo.write(78); // This is the catch's closed position. The open position is 130
  int a = catch_servo.read();
  Serial.print("catch_servo: "); Serial.println(a);

  pinMode(punch_pin, OUTPUT);
  pinMode(start_turn, INPUT);            // Set digital pin 5 as INPUT to initialize MOVE INPUT SIGNAL.
  pinMode(end_turn, OUTPUT);            // Set digital pin 6 as OUTPUT to indicate when we are finished with our turn.
  pinMode(13, OUTPUT);
}

////////// LOOP LOOP LOOP LOOP LOOP LOOP LOOP LOOP LOOP LOOP LOOP LOOP LOOP LOOP LOOP LOOP LOOP LOOP LOOP LOOP LOOP LOOP LOOP LOOP LOOP LOOP LOOP LOOP LOOP LOOP LOOP //////////

void loop()
{
  //if (Round == 0)                   // Tests to see if this is the first time we've reeived a signal, indicating the start of the match.
  //{


  wait_for_start_signal();        // (TYP wait) Initializes a flag and enters while loop until that flag is flipped by the turn signal.
  //wait_for_turn_signal();       // This loop waits for the signal indicating the start of the match.

  if (Round == 1 && Start == 0)
  {
    scan_tower();
    extract_target();
    Round ++;
    determine_targets();
  }
  else
  {
    //determine_targets();
    scan_tower();
    extract_target();
    Round++;
    determine_targets();
  }
}//////// END LOOP ////////
