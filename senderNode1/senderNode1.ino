/*
  this code is for the master sender node 1

  it revieces instruction from the master python program and send the instruction to the corresponding slave node
*/

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  if(Serial.available()>0){
    // do stuff
  }
}
