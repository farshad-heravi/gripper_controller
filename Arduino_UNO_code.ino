#define directionPin_M1 4     // right finger
#define stepPin_M1 5
#define directionPin_M2 2     // prismatic joint
#define stepPin_M2 3          
#define directionPin_M3 6
#define stepPin_M3 7

#define stepPerRevolution 2700

int cur_rot1 = 0, cur_rot2 = 0, cur_pos = 0;
const double deg2ticks_rev = 5400./180.;
const double ticks2deg_rev = 1.0/deg2ticks_rev;

const double mm2ticks_pris = 0.5 * 7.69;
const double ticks2mm_pris = 1.0/mm2ticks_pris;


void control_command_callback(float value1, float value2, float value3) {
    // Access positions for the joints
    float position1 = value1;  // Position for prismatic joint in mm
    float position2 = -1*value2;  // Position for revolute 1 in deg
    float position3 = -1*value3;  // Position for revolute 2 in deg

    

    // convert these positions into motor steps or other control signals
    int steps1 = convertPositionToSteps_Prismatic(position1);
    int steps2 = convertPositionToSteps_Revolute(position2);
    int steps3 = convertPositionToSteps_Revolute(position3);
    
    move_gripper(steps1, steps2, steps3);
}

void move_gripper(int pos1, int pos2, int pos3){
    int dir = 1;
    int steps = abs( cur_pos - pos1 );
    if ( cur_pos > pos1 ){
      dir = -1;
    }
    stepper_move_prismatic(steps, dir);
    cur_pos = pos1;

    // rotate both fingers
    rotate_fingers(pos2, pos3);
    cur_rot1 = pos2;
    cur_rot2 = pos3;
}

void rotate_fingers(int target_finger1, int target_finger2){
  if ( cur_rot1 != target_finger1  ){
    // rotate both simultaneously
    if ( target_finger1 > cur_rot1 ){
      stepper_move_rotation( abs(target_finger1 - cur_rot1), HIGH);
    } else {
      stepper_move_rotation( abs(target_finger1 - cur_rot1), LOW);
    }
  }
}

int convertPositionToSteps_Prismatic(double position){     // convert mm to degree
  return (int) (position * mm2ticks_pris);
}

int convertPositionToSteps_Revolute(double position){     // convert ticks to degree
  return (int) (position * deg2ticks_rev);
}

int convertStepsToPosition_Prismatic(int step){     // convert ticks to mm
  return step * ticks2mm_pris;
}

int convertStepsToPosition_Revolute(int step){     // convert ticks to degree
  return step * ticks2deg_rev;
}


// Function to control the first two stepper motors
void stepper_move_prismatic(int steps, int direction) {   // direction 1 for opening; -1 for closing
  // high to close; LOW to open
  if( direction == 1 ){
    direction = LOW;
  } else {
    direction = HIGH;
  }
  for (int i=0; i < steps; i++){
      digitalWrite(directionPin_M2, direction);
      digitalWrite(stepPin_M2, HIGH);
      delayMicroseconds(4000);
      digitalWrite(stepPin_M2, LOW);
      delayMicroseconds(4000);
  }
}

// Function to control the third stepper motor
void stepper_move_rotation(int steps, int direction) {  // direction 1 for opening; -1 for closing
    // high to open; LOW to close
    if( direction == 1 ){
      direction = HIGH;
    } else {
      direction = LOW;
    }
    for (int i=0; i < steps; i++){
        digitalWrite(directionPin_M1, direction);
        digitalWrite(directionPin_M3, direction);
        digitalWrite(stepPin_M1, HIGH);
        digitalWrite(stepPin_M3, HIGH);
        delayMicroseconds(400);
        digitalWrite(stepPin_M1, LOW);
        digitalWrite(stepPin_M3, LOW);
        delayMicroseconds(400);
    }
}


//////////////////////////////////////// 
// SETUP
////////////////////////////////////////
void setup() {
  Serial.begin(9600);
  
  pinMode(directionPin_M1, OUTPUT);
  pinMode(stepPin_M1, OUTPUT);
  pinMode(directionPin_M2, OUTPUT);
  pinMode(stepPin_M2, OUTPUT);
  pinMode(directionPin_M3, OUTPUT);
  pinMode(stepPin_M3, OUTPUT);
}

//////////////////////////////////////// 
// LOOP
////////////////////////////////////////
void loop() {
  if (Serial.available()) {
    // Read the incoming string until a newline is encountered
    String incomingData = Serial.readStringUntil('\n');

    // Split the incoming string by commas
    int firstComma = incomingData.indexOf(',');
    int secondComma = incomingData.indexOf(',', firstComma + 1);

    // Extract the numbers from the string
    String value1_str = incomingData.substring(0, firstComma);
    String value2_str = incomingData.substring(firstComma + 1, secondComma);
    String value3_str = incomingData.substring(secondComma + 1);

    // Convert the strings to doubles
    double val1 = value1_str.toDouble();
    double val2 = value2_str.toDouble();
    double val3 = value3_str.toDouble();

    // Print the received values (debug purpose)
    // Serial.print("Received values: ");
    // Serial.print(val1, 4);  // Print with 4 decimal places
    // Serial.print(", ");
    // Serial.print(val2, 4);
    // Serial.print(", ");
    // Serial.println(val3, 4);

    control_command_callback(val1, val2, val3);
    Serial.println("Feedback: Values received successfully!");
  }

  delay(1);
}
