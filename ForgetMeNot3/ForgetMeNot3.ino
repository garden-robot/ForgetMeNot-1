

enum gameStates_t {
  SETUP,                // Waiting for someone (possibly me) to become center
                        // Exit when either we detect we are center or we get a message from a center

                        // Here the tile remembers if it is center (it has 6 neighboors)
                        
  BLOOM,                // Show that we are getting ready to start the game
                        // Exit at end of timeout

  READY,                // Ready to start playing when user pushes center button
                        // Exit on button press on center

  PUZZLE,               // Show the initial puzzle state
                        // Exit at end of timeout
  
  PAUSE                 // Show black to make them forget what they saw
                        // Exit at end of timeout
  
  CHANGED,              // Show the puzzle with one thing changed. 
                        // Exit at end of timeout

  // Jump to ANSWER is user selects wrong tile
  
  CORRECT,              // User found change. 
  // Return to SHOW_PUZZLE
  
  SHOW_ANSWER,          // User picked wrong change, show them the right one
                        // Exit at end of timeout
  
  SCOREBOARD,           // Show what level they got to
                        // Exit on button press on center

  // Jump to BLOOM
};


// A long press anytime jumps to BLOOM if this tile has 6 neighbors

// Messages sent over the IR link

enum center_messages_t {

  // Sent by CENTER

  ENTER_BLOOM,        // Enter the bloom animation
  STEP_GENERAL,       // Step to the next state 
  STEP_CHANGED,       // Step to the next state, but *you* are the changed tile (only sent in PAUSED state)
  STEP_WRONG          // User picked wrong tile, so jump to ANSWER (only sent in CHANGED state)
};

// Each petal remembers which face it last saw a center_message_t on, and only sends
// petal_message_t messages on that face.

enum petal_messages_t {

  // Sent by petal
  
  NOT_CLICKED,        // I have not been clicked since last state change
  CLICKED             // I have been clicked since last state change
}

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
