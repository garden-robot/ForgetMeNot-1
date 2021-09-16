
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


// Are we currently the center?
bool weAreCenter=false;

// The current game state, only valid when weAreCenterFlag is true

enum gameState_t {
  
  BLOOM,                // Show that we are getting ready to start next level
                        // Center animate green to yellow, petals animate full green to just one green pixel facing center
                        // Exit on button press on center
                        
  PUZZLE,               // Show the puzzle
                        // Exit at end of timeout
  
  PAUSE,                // Pause to make them forget what they saw
                        // Center yellow, petals green dot towards center
                        // Exit at end of timeout
  
  CHANGED,              // Show the puzzle but changed from the last PUZZLE state
                        // Center yellow?
                        // Exit when user pushes one of the petals

  // Jump to ANSWER if user selects wrong tile
  
  CORRECT,              // User found change. 
                        // Exit at end of timeout.

  
  // Jump to BLOOM
  
  SHOW_ANSWER,          // User picked wrong change, show them the right one
                        // All petals red except the one that change which is full green.
                        // Center stays yellow
                        // All petals fade to black, center stays yellow
                        // Exit at end of timeout
  
  SCOREBOARD,           // Show what level they got to with a full screen animation
                        // Exit on button press on center

  // Jump to SETUP
};

const word BLLOM_TIMER_MS = 2000;   // How long to show bloom animation


// A long press anytime jumps to BLOOM if this tile has 6 neighbors
// Anytime a leaf goes too long without seeing any messages, it will go back to SETUP
// Anytime a center sees a RESET, it will become a leaf

// Messages sent over the IR link

enum messages_t {

  // Sent by Center

  SHOW_BLOOM_0,       // Show single green pixel pointing to center. Reset level to 0.
  SHOW_BLOOM,         // Show single green pixel pointing to center. Increment level. 
  
  SHOW_PUZZLE,        // Pick a random puzzle to show based on puzzle type for current level.
  SHOW_PAUSE,         // Show green on face pointing to center
  SHOW_CHANGED,       // Change your display based on current puzzle type and difficulty (only sent to faces that should change)
  SHOW_CORRECT,       // When user makes correct pick, all tiles get this (currently green).
  SHOW_WRONG_MISSED,  // When user makes a wrong pick, this is shown on the missed tile (currently green)
  SHOW_WRONG_OTHERS,  // When user makes a wrong pick, this is shown on all but the missed tile (currently red)

  SHOW_SCORE_STEP_EVEN,  // Show the next step in a score progression. Message alternates between even and odd on each step.
  SHOW_SCORE_STEP_ODD,   // First 4 steps are 0-3 red LEDs on permitier, then middle LED lights and starts progresion over. 

  // Sent by Petals

  IDLE,                  // Sent by default
  PRESSED,               // Button pressed since last transition. Cleared whenever the petal gets a new message from center.
  
  ACK_SCORE_STEP_EVEN,   // Sent after getting SHOW_SCORE_STEP_EVEN to enable ping-pong acking
  ACK_SCORE_STEP_ODD     // Sent after getting SHOW_SCORE_STEP_ODD to enable ping-pong acking   
  
};


// Current play level
byte currentLevel;


// From colorwheel here...https://learnui.design/blog/the-hsb-color-system-practicioners-primer.html
const byte GREEN_HUE = (90/360) * 255;
const byte YELLOW_HUE = (60/360) * 255;


struct stateTimer_t {

  Timer timer;
  
  // We remember the durration of the current timer so we can calculate our progress into it.
  // (There really should be a Timer.getProgress() )
  word initialDurration; 
    
  void set( word t ) {
    timer.set( t );
    initialDurration = t;  
  }

  // Returns 0-255 to indicate how far along the timer we are (255=expired)
  byte progress() {
    if (timer.isExpired()) {
      return 255;
    }

    return ( timer.getRemaining() * 255 ) / initialDurration;
    
  }

};

stateTimer_t stateTimer;


// How long to show the bloom animation at the start of each round
const word BLOOM_TIME_MS=2000;  


void setup() {
  // Default display at power up
  // TODO: Do we want to also start here after waking from sleep?
  setColor( GREEN );
  setValueSentOnAllFaces( IDLE );
}


// Control puzzle show and pause times based on level
// TODO: TUNE THESE
const word MAX_SHOW_TIME=5000;    // 5 seconds on
const word MIN_SHOW_TIME=3000;    // 3 seconds on
const word MIN_PAUSE_TIME=1500;    // 1.5 second  off
const word MAX_PAUSE_TIME=3000;    // 3 seconds off
const byte CURVE_BEGIN_LEVEL=1;
const byte CURVE_END_LEVEL=10;

/*
   returns a duration in milliseconds that the puzzle will show for
*/
word getShowDuration(byte level) {
  if (level < CURVE_BEGIN_LEVEL) {
    return MAX_SHOW_TIME; // max time is easier i.e. lower level
  }
  else if (level > CURVE_END_LEVEL) {
    return MIN_SHOW_TIME; // min time is harder i.e. higher level
  }
  else {
    // everything in between
    return MAX_SHOW_TIME - (level - CURVE_BEGIN_LEVEL) * (MAX_SHOW_TIME - MIN_SHOW_TIME) / ( CURVE_END_LEVEL - CURVE_BEGIN_LEVEL);
  }

}

/*
   returns a duration in milliseconds that the puzzle will show for
*/
word getPauseDuration(byte level) {

  if (level < CURVE_BEGIN_LEVEL) {
    return MIN_PAUSE_TIME; // max time is easier i.e. lower level
  }
  else if (level > CURVE_END_LEVEL) {
    return MAX_PAUSE_TIME; // min time is harder i.e. higher level
  }
  else {
    // everything in between
    return MIN_PAUSE_TIME + (level - CURVE_BEGIN_LEVEL) * (MAX_PAUSE_TIME - MIN_PAUSE_TIME) / ( CURVE_END_LEVEL - CURVE_BEGIN_LEVEL);
  }
}

boolean doWeHave6Neighboors() {
  FOREACH_FACE(f) {
    if (isValueReceivedOnFaceExpired(f)) {
      return false;
    }
  }
  return true;
}

// Current game state (only valid if weAreCenterFlag==true)
gameState_t gameState;

// Which petal changed? (only valid in CHANGED state)
byte changedPetal;

// We are the center, update our state

void updateStateCenter() {

  byte progress = stateTimer.progress();
  
  switch (gameState) {

    case BLOOM: {
      // Durring bloom animation we change color from GREEN to YELLOW. Ends with YELLOW after timer expires.
      byte hue = ( ( (YELLOW_HUE) * progress ) + ( (GREEN_HUE) * (255-progress)) ) / 255;
      setColor( makeColorHSB(  hue , 255 , 255 ) );
      // With a sparkle
      setColorOnFace( WHITE , random(FACE_COUNT-1) );

      if (progress==255 && buttonPressed()) {
        // Pressing the button now will start the round and show the puzzle on the petals. 
        // Note that the petals decide what to show since they know what level we are on
        setColor(YELLOW);   // Clear the sparkle
        setValueSentOnAllFaces( SHOW_PUZZLE );    
        gameState=PUZZLE;
        stateTimer.set( getShowDuration(currentLevel) );  
      }
      break;
    }

    case PUZZLE: {
      // Durring this time, the user gets to study the puzzle. 
      // TODO: Delete this little countdown stopwatch animation here for fun that is not in the orginal game. 

      if (progress < 255 ) {
        // Animation running, show center face ticking down to full black...
        // TODO: Does this look right?
        byte darkface = (byte) ((progress * (FACE_COUNT-1)) / 255);
        setColorOnFace( OFF , darkface );
      } else {
        // Your time to study the puzzle is up! Go black!
        setColor(OFF);
        setValueSentOnAllFaces( SHOW_PAUSE );    
        gameState=PAUSE;
        stateTimer.set( getPauseDuration(currentLevel) );
      }
    }
        
  }
  
  
}

// The face of our current center (only valid if areWeCenterFlag==false)
byte centerFace;

void updateStatePetal() {


  
}

void loop() {

  // Check for resets to the global state machine first

  // First check if we should become a center
  // If we have neighboors on all 6 sides, then we will become center and start a new game
  // We also start a new game if we have neighboors on all sides and the button is long pressed

  if (!weAreCenter || buttonLongPressed()  ) {
    if (doWeHave6Neighboors()) {
      weAreCenter=true;      
      gameState=BLOOM;
      stateTimer.set( BLOOM_TIME_MS );
      currentLevel=0;
      setColor(YELLOW);
      setValueSentOnAllFaces( SHOW_BLOOM_0 );   // Reset all petals to level 0
      return;
    }
  }

  // Next check if we should recognize a new center and reset

  FOREACH_FACE(f) {
    if (!isValueReceivedOnFaceExpired(f) && getLastValueReceivedOnFace(f)==SHOW_BLOOM_0) {
      weAreCenter=false; 
      centerFace=f;
      currentLevel=0;
      setValueSentOnAllFaces( IDLE );
      setColor( OFF );
      setColorOnFace( GREEN , f );
      return;
    }
  }


  // OK, if we get here then we are in stable gameplay so handle normal stuff

  if (weAreCenter) {
    updateStateCenter();
  } else {
    updateStatePetal();    
  }
  
}
