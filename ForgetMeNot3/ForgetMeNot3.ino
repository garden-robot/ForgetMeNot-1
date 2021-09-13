

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

#define MAX_LEVEL 72

// Make PROGMEM if we run out of RAM
level_t levels[MAX_LEVEL] {
  { COLOR     , 1 , 1  }, // Level  0
  { COLOR     , 1 , 1  }, // Level  1
  { COLOR     , 1 , 1  }, // Level  2
  { COLOR     , 1 , 1  }, // Level  3
  { COLOR     , 2 , 1  }, // Level  4
  { DIRECTION , 1 , 1  }, // Level  5
  { DIRECTION , 1 , 1  }, // Level  6
  { COLOR     , 2 , 1  }, // Level  7
  { DIRECTION , 1 , 1  }, // Level  8
  { DIRECTION , 2 , 1  }, // Level  9
  { DICHROMIC , 1 , 1  }, // Level  10
  { DICHROMIC , 1 , 1  }, // Level  11
  { DIRECTION , 1 , 1  }, // Level  12
  { COLOR     , 2 , 1  }, // Level  13
  { DICHROMIC , 2 , 1  }, // Level  14
  { ROTATION  , 1 , 1  }, // Level  15
  { ROTATION  , 1 , 1  }, // Level  16
  { DICHROMIC , 2 , 1  }, // Level  17
  { COLOR     , 3 , 1  }, // Level  18
  { ROTATION  , 1 , 1  }, // Level  19
  { COLOR     , 2 , 1  }, // Level  20
  { DIRECTION , 2 , 1  }, // Level  21
  { DICHROMIC , 2 , 1  }, // Level  22
  { ROTATION  , 2 , 1  }, // Level  23
  { COLOR     , 2 , 1  }, // Level  24
  { DIRECTION , 2 , 1  }, // Level  25
  { DICHROMIC , 2 , 1  }, // Level  26
  { ROTATION  , 2 , 1  }, // Level  27
  { COLOR     , 2 , 1  }, // Level  28
  { DIRECTION , 2 , 1  }, // Level  29
  { DICHROMIC , 2 , 1  }, // Level  30
  { ROTATION  , 2 , 1  }, // Level  31
  { COLOR     , 2 , 1  }, // Level  32
  { DIRECTION , 3 , 1  }, // Level  33
  { DICHROMIC , 3 , 1  }, // Level  34
  { ROTATION  , 3 , 1  }, // Level  35
  { COLOR     , 3 , 1  }, // Level  36
  { DIRECTION , 3 , 1  }, // Level  37
  { DICHROMIC , 3 , 1  }, // Level  38
  { ROTATION  , 3 , 1  }, // Level  39
  { COLOR     , 3 , 1  }, // Level  40
  { DIRECTION , 3 , 1  }, // Level  41
  { DICHROMIC , 3 , 1  }, // Level  42
  { ROTATION  , 3 , 1  }, // Level  43
  { COLOR     , 3 , 1  }, // Level  44
  { DIRECTION , 3 , 1  }, // Level  45
  { DICHROMIC , 4 , 1  }, // Level  46
  { ROTATION  , 4 , 1  }, // Level  47
  { COLOR     , 4 , 1  }, // Level  48
  { DIRECTION , 4 , 1  }, // Level  49
  { DICHROMIC , 4 , 1  }, // Level  50
  { ROTATION  , 4 , 1  }, // Level  51
  { COLOR     , 4 , 1  }, // Level  52
  { DIRECTION , 4 , 1  }, // Level  53
  { DICHROMIC , 4 , 1  }, // Level  54
  { ROTATION  , 4 , 1  }, // Level  55
  { COLOR     , 4 , 1  }, // Level  56
  { DIRECTION , 4 , 1  }, // Level  57
  { DICHROMIC , 4 , 1  }, // Level  58
  { ROTATION  , 4 , 1  }, // Level  59
  { COLOR     , 4 , 1  }, // Level  60
  { DIRECTION , 4 , 1  }, // Level  61
  { DICHROMIC , 4 , 1  }, // Level  62
  { ROTATION  , 4 , 1  }, // Level  63
  { COLOR     , 4 , 1  }, // Level  64
  { DIRECTION , 4 , 1  }, // Level  65
  { DICHROMIC , 4 , 1  }, // Level  66
  { ROTATION  , 4 , 1  }, // Level  67
  { COLOR     , 4 , 1  }, // Level  68
  { DIRECTION , 4 , 1  }, // Level  69
  { DICHROMIC , 4 , 1  }, // Level  70
  { ROTATION  , 4 , 1  }, // Level  71   
};


void setup() {
  // put your setup code here, to run once:
}


void loop() {
}
