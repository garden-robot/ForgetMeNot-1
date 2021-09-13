

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
  
  PAUSE,                // Show black to make them forget what they saw
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
};




// Current game state
gameStates_t gameState = SETUP;

// Are we currently the center?
bool centerFlag;

// Next time we change state (for states that have time-based exit condition)
//Timer nextStateChangeTimer;

// Current play level
byte currentLevel;



enum puzzleType_t {
  COLOR,        // Each petal is a single color
  DIRECTION,    // Each petal is lit a single direction
  DICHROMIC,    // Each petal is a pair of colors
  ROTATION      // Each petal animates rotation CW or CCW
};


// Info about a level

struct level_t {
  puzzleType_t type:2;  
  byte difficulty:3;    // Higher difficulty = smaller roation angles
  byte changes:3;       // Number of tiles that change in this round
};

level_t levels {
  
   
};


#define MAX_LEVEL 72

byte puzzleArray[MAX_LEVEL] =     {0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 2, 2, 1, 0, 2, 3, 3, 2, 0, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3};
byte difficultyArray[MAX_LEVEL] = {1, 1, 1, 1, 2, 1, 1, 2, 1, 2, 1, 1, 1, 2, 2, 1, 1, 2, 3, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(1000000);
  Serial.println("begin");
}


void loop() {
  // put your main code here, to run repeatedly:
  for( int i =0; i<MAX_LEVEL; i++ ) {
    Serial.print(  "    { ");

    const char *x;

    switch (puzzleArray[i]) {
      case 0: x="COLOR    "; break;
      case 1: x="DIRECTION"; break;
      case 2: x="DICHROMIC"; break;
      case 3: x="ROTATION "; break;
    }

    Serial.print( x );
    Serial.print( " , ");

    Serial.print( difficultyArray[i]);
    Serial.print( " , ");
    
    Serial.print( "1");
    
    Serial.print( "  }, // Level  ");
    Serial.println(i);    
    
  }
  while (1);
}
