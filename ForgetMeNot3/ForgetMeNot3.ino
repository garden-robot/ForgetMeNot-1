

enum gameState_t {
  SETUP,                // Waiting for someone (possibly me) to become center
                        // All tiles full green
                        // Exit when either we detect we are center or we get a message from a center

                        // Here the tile remembers if it is center (it has 6 neighboors)

  ESTABLISH_CENTER,     // We have 6 nieghboors, now wait for them all to ack us as the center
                        // Exit when we get VOTE_CENTER message on all Faces                        
                        
  BLOOM,                // Show that we are getting ready to start a level
                        // Center animate green to yellow, petals animate full green to just one green pixel facing center
                        // Exit at end of animation

  READY,                // Ready to start playing when user pushes center button
                        // Center yellow sparkle
                        // Exit on button press on center

  PUZZLE,               // Show the puzzle
                        // Exit at end of timeout
  
  PAUSE,                // Pause to make them forget what they saw
                        // Center yellow, petals green dot towards center
                        // Exit at end of timeout
  
  CHANGED,              // Show the puzzle but changed from the last PUZZLE state
                        // Center yellow?
                        // Exit when user pushes one of the petals

  // Jump to ANSWER is user selects wrong tile
  
  CORRECT,              // User found change. 
                        // 
  // Return to BLOOM which will show all tiles full GREEN and then animate to ready for next round
  
  SHOW_ANSWER,          // User picked wrong change, show them the right one
                        // All petals red except the one that change which is full green.
                        // Center stays yellow
                        // All petals fade to black, center stays yellow
                        // Exit at end of timeout
  
  SCOREBOARD,           // Show what level they got to with a full screen animation
                        // Exit on button press on center

  // Jump to SETUP
};


// A long press anytime jumps to BLOOM if this tile has 6 neighbors
// Anytime a leaf goes too long without seeing any messages, it will go back to SETUP
// Anytime a center sees a RESET, it will become a leaf

// Messages sent over the IR link

enum messages_t {

  // Sent by Center

  CENTER_REQUEST,     // We are asking everyone to vote us to be center
  SHOW_PUZZLE,        // Pick a random puzzle to show based on puzzle type for level
  SHOW_PAUSE,         // Show green on face pointing to center
  SHOW_CHANGED,       // Change your display based on current puzzle type and difficulty (only sent to faces that should change)
  SHOW_CORRECT,       // When user makes correct pick, all tiles get this (currently green).
  SHOW_WRONG_MISSED,  // When user makes a wrong pick, this is shown on the missed tile (currently green)
  SHOW_WRONG_OTHERS,  // When user makes a wrong pick, this is shown on all but the missed tile (currently red)

  SHOW_SCORE_STEP_EVEN,  // Show the next step in a score progression. Message alternates between even and odd on each step.
  SHOW_SCORE_STEP_ODD,   // First 4 steps are 0-3 red LEDs on permitier, then middle LED lights and starts progresion over. 

  // Sent by Petals

  ACK_CENTER,            // Ack the center_request. Reset to level 0.
  IDLE,                  // Default sent by a petal (including a tile that is in SETUP waiting for center to be found)
  PRESSED,               // Button pressed since last transition. Cleared whenever the petal gets a message from center.
  ACK_SCORE_STEP_EVEN,   // Sent after getting SHOW_SCORE_STEP_EVEN to enable ping-pong acking
  ACK_SCORE_STEP_ODD     // Sent after getting SHOW_SCORE_STEP_ODD to enable ping-pong acking   
  
};



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


// Current game state
gameState_t gameState = SETUP;

// Are we currently the center?
bool centerFlag;

// The face of our current cenrter (if centerFlag==0)
byte centerFace;

// Next time we change state (for states that have time-based exit condition)
Timer nextStateChangeTimer;

// We remember the durration of the current timer so we can calculate our progress into it.
// (There really should be a Timer.getProgress() )
word currentTimerDurration; 

// Current play level
byte currentLevel;


void setup() {
  // put your setup code here, to run once:
}


// From colorwheel here...https://learnui.design/blog/the-hsb-color-system-practicioners-primer.html
const byte GREEN_HUE = (90/360) * 255;
const byte YELLOW_HUE = (60/360) * 255;

// Progress is 0-255 indicating how far along in current animation we are

void display( const gameState_t gameState , const bool centerFlag , const byte progress ) {

  switch (gameState) {

    case SETUP: {
      // Everything is always green durring setup
      setColor( GREEN );      
    } break;


    case BLOOM: {
      if (centerFlag) {
        
        // Durring bloom animation we change color from GREEN to YELLOW
        byte hue = ( ( (YELLOW_HUE/2) * progress ) + ( (GREEN_HUE/2) * (255-progress)) ) / 255;
        setColor( makeColorHSB(  hue , 255 , 255 ) );
        // With a sparkle
        setColorOnFace( WHITE , random(FACE_COUNT-1) );
      } else {
        // Not center
        setColor( GREEN ); 
      }
      
    } break;
      
  }
  
}

const word BLOOM_TIME_MS=2000;


void loop() {

  // First we update our state based on outside world and time 

  // Read messages from all faces

  bool anyExpiredFacesFlag = false;   // Keep track if there are any empty faces so we can tell if we are a center

  FOREACH_FACE(f) {
    if (!isValueReceivedOnFaceExpired(f)) {
      
      // Active neighboor

      const byte m=valueReceivedOnFace(f);

      if (centerFlag) {
        // We are the center, update our state as nessisary

        if (gameState==

      } else {
        // We are not the center...
        // so we always accept the new state of the center
        if (m!=gameSatet && m!=SETUP) {
          gameState = m;
          centerFace=f;

          switch (gameState) {

            case BLOOM: {
              nextStateTimer.set(BLOOM_TIME_MS);
            } break;
            
          }
        }          
      }
    } else {
      anyExpiredFacesFlag=true;
    }
    
  }

  if (!anyExpiredFacesFlag){

    // Unconditionally reset if we are a center and there is a long press
    
    if (buttonLongPressed()) {
        state = SETUP;
    }

    // If we are at a center and are currently in SETUP mode, then we are good to start the game

    if (state == SETUP ) {
      // We ae in a proper game state arrangement
      state = BLOOM;
      nextStateChangeTimer = BLOOM_TIME_MS;
      centerFlag=true; 
    }
    
  }


  


  // Next update our display based on current state


  void display( gameState , centerFlag , const byte progress ) {
  
  }

  
}
