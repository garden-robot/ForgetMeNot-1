
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
  
  CORRECT,              // User found the change. 
                        // Exit at end of timeout.

  
  // Jump to BLOOM if there is another level
  // Jump to WIN if no more levels
  
  SHOW_ANSWER,          // User picked wrong change, show them the right one
                        // All petals red except the one that change which is full green.
                        // Center stays yellow
                        // All petals fade to black, center stays yellow
                        // Exit at end of timeout
  
  SCOREBOARD,           // Show what level they got to with a full screen animation
                        // Exit on button press on center

  // Jump to SETUP


  WIN,                  // They beat all the levels!
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

  SHOW_WIN,           // When user beats all levels (currently animated rainbow)

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
const byte GREEN_HUE = (90 * 255)/360;
const byte YELLOW_HUE = (60 * 255)/360;


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

// How long to show the "you are correct" display after a correct changed petal selection
const word CORRECT_TIME_MS=2000;

// How long to show the "you are wrong" display after an  incorrect changed petal selection
const word WRONG_TIME_MS=2000;


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
      
    } break;
    

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
      
    } break;

    case PAUSE:{
      if (progress==255) {   // Done with pause?

        // Only now, at the very last second do we actually pick which petal changed. Seems wrong, right?
        changedPetal = random( FACE_COUNT- 1) ;

        // Have the petals display either the orginal or changed version of thier puzzle
        FOREACH_FACE(f) {
          if (f==changedPetal) {                        // TODO: Condense with `x?y:z` if we need space 
            setValueSentOnFace( SHOW_CHANGED , f );
          } else {
            setValueSentOnFace( SHOW_PUZZLE , f );            
          }
        }
        
        gameState=CHANGED;               
      }
      
    } break;

   case CHANGED: {
      
      boolean wrongFlag=false;    // We need this for the very edge case if they try to cheat by pressig two petlas at EXACTLY the same moment.
                                  // TODO: This is not really a practical concern, so remove if we need space
      FOREACH_FACE(f) {
        if (!isValueReceivedOnFaceExpired(f) && getLastValueReceivedOnFace(f)==PRESSED ) {
          // This petal had its button pressed

          if (f==changedPetal && !wrongFlag) {
            // They picked the right petal and only the right petal!
            gameState = CORRECT;
            setValueSentOnAllFaces( SHOW_CORRECT );
            stateTimer.set( CORRECT_TIME_MS );
            setColor(GREEN);             
          } else {
            // They pressed the wrong petal :(
            wrongFlag = true;
            setValueSentOnFace( SHOW_WRONG_MISSED , changedPetal );     // Show them the one they _should_ have pressed. 
            setValueSentOnAllFaces(  SHOW_WRONG_OTHERS );                
            stateTimer.set( WRONG_TIME_MS );
            setColor(RED);                          // I like RED here better than YELLOW, don't you? 
          }          
        }
              
      }
    } break;

    case CORRECT: {
      setColor( GREEN ); 

      // They got it right, I think they deserve little excitment with some fading sparkles
      if (random(255) < progress) {
        setColorOnFace( WHITE , random( FACE_COUNT -1 ) );
      }

      if (progress == 255) {
        // Ready for next round.
        currentLevel+=1;

        if (currentLevel==MAX_LEVEL) {

          // WE HAVE A WINNER!

          gameState=WIN;
          setValueSentOnAllFaces( SHOW_WIN );    // A spectacular flurish
          
        } else {
                  
          setValueSentOnAllFaces( SHOW_BLOOM );    // Get petals ready for next round. Ths will increment thier level
          
        }
      }
    } break;
  }
}

#define PETAL_COLOR_COUNT 6

Color petalColors[6] = {
  makeColorHSB( 30,200,255),  // SALMON
  makeColorHSB(255,200,255),  // PINK
  makeColorHSB(220,200,255),  // LIGHT PINK
  makeColorHSB(180,200,255),  // VIOLET
  makeColorHSB(150,200,255),  // INDIGO
  makeColorHSB(120, 50,255),  // PERIWINKLE/WHITE
};

byte getRandomPetalColorIndex() {
  return random( PETAL_COLOR_COUNT -1 );
}

// This find a different color, and how hard it is to see it is different is determined by the difficulty
  /*
     NOTE: difficulty distance should be thought of from the midpoint
     i.e. the easiest difference in color will be 180º away in the spectrum
     and the easiest difference in direction will be 180º opposite
  */

byte getContraColorIndex( const byte startColorIndex , const byte difficulty ) {

  byte endColorIndex;

  bool goRight = (random(1)==0);      // Go right around the color wheel (clockwise)? 

  // TODO: We should just code this distance directly into the levels struct?

  byte distance = 5 - difficulty;

  // TODO: Am I reading this right? Seems like the values for `difficulty` in levels should start at 3 and then go down to 1 as levels go up? 0 and 4 really don't make sense. 
  // TODO: Yea, a difficulty of 1 now turns into a distance of 4, which is harder than a difficulty of 2 which is a distance of 3. 
  
  if (goRight) {
    endColorIndex = startColorIndex + distance;
  } else {    
    endColorIndex = startColorIndex + (PETAL_COLOR_COUNT - distance);
  }

  // Normalize the color back into range
  if (endColorIndex>=PETAL_COLOR_COUNT) {
    endColorIndex-=PETAL_COLOR_COUNT;
  }


  return endColorIndex;
  
}

// Bring f down to 0<=f<FACE_COUNT
// Assumes that f<((FACE_COUNT*2)-1)

byte normalizeFace( byte f ) {
  if (f>=FACE_COUNT) {
    f-=FACE_COUNT;
  }
  return f;
}

// Find opostie face

byte opositeFace( byte f ) {
  return normalizeFace( f + (FACE_COUNT/2) );
}

// Set the 3 faces pointing towards directionFace to c 

void setColorIndexOnSide( byte colorIndex , byte directionFace ) {
    Color c =  petalColors[colorIndex ];
    setColorOnFace( c , directionFace );
    setColorOnFace( c , normalizeFace( (directionFace+FACE_COUNT)-1 ) );
    setColorOnFace( c , normalizeFace( directionFace+1 ) );          
}

void swap( byte &a , byte &b ) {
  byte t=a;
  a=b;
  b=t;
}

const byte ROTATION_MS_PER_STEP = 50;   // 50ms per step * 6 steps per rotation = 300ms per rotation = ~3 rotations per second
 
struct puzzle_t {

  puzzleType_t type;   // Set based on the current level
  byte difficulty;           // Set based on the current level

  // I know this union seems like overkill, but it makes this complicated code read simple
  // Hey, I could have made a polymorphic puzzle class!

  union {                // We use this to remember the data used to make the current puzzle (and it's changed version)
    
    struct {
      byte index;    // Index of the current color in petalColors
    } color;

    struct {
      byte interiorIndex;    // Index of the current color in petalColors that points to the center
      byte exteriorIndex;    // Index of the current color in petalColors that points away from center. We could compute this deterministically, but more efficient to remember it once.      
    } dicromic;

    struct {
      byte face;              // Which face it lit
    } direction;

    struct {
      boolean clockwise;
    } rotation;
  
  } data;

  byte level;     // We remeber the currentl level we are playing to create an interlock for incrementing to the next level
  
  void set( const level_t &level ) {    // Set the current puzzle

    // Save these, we might need them again
    type = level.type;
    difficulty = level.difficulty; 

    switch (type) {
      
      case COLOR:         // Each petal is a single color
        data.color.index = getRandomPetalColorIndex();
        break;
        
      case DIRECTION:     // Each petal is lit a single direction
        data.direction.face = random( FACE_COUNT -1 );
        break;
        
      case DICHROMIC:     // Each petal is a pair of colors
        data.dicromic.interiorIndex = getRandomPetalColorIndex();
        data.dicromic.exteriorIndex = getContraColorIndex( data.dicromic.interiorIndex , difficulty );
        break;
                
      case ROTATION:      // Each petal animates rotation CW or CCW      
        data.rotation.clockwise = (random(1)==0);
        break;
      
    }
    
  }

  void show(byte centerFace, bool changed) {       // Show the puzzle on our pixels. if changed==true, the then alternate version is shown


    switch (type) {
      
      case COLOR: {         // Show the indicated color index on all pixels

        byte showColorIndex =data.color.index;; 
        
        if (changed) {
          // Change the color to a different one, and how different is based on the difficulty
          showColorIndex =  getContraColorIndex( showColorIndex , difficulty );
        }
      
        setColor( petalColors[ showColorIndex ] ); 
      } break;
        
      case DIRECTION: {    // Show selected petal as white

        byte showDirectionFace=data.direction.face; 

        if (changed) {
          // make the direction point the other way
          // TODO: Should there also be other ways it can pint at harder levels? 
          showDirectionFace = opositeFace( showDirectionFace );
        }
        
        setColor(OFF);
        setColorOnFace( WHITE , showDirectionFace );
      } break;
                
      case DICHROMIC: {     // Show inner on 3 faces pointing to center, outer on other 3 faces

        Color interiorColor = petalColors[ data.dicromic.interiorIndex];
        Color exteriorColor = petalColors[ data.dicromic.exteriorIndex];

        byte showFaceDirection = centerFace;
        byte showFaceOtherDirection = opositeFace(showFaceDirection);

        if (changed) {
          // swap inner and outer colors
          swap( showFaceDirection , showFaceOtherDirection );
        }

        setColorIndexOnSide( data.dicromic.interiorIndex , showFaceDirection );
        setColorIndexOnSide(  data.dicromic.exteriorIndex , showFaceOtherDirection );       
      } break;
                
      case ROTATION: {  // Show a single white pixel rotating based on millis so they will be out of sync as show in instructions 

        // TODO: This will be huge code size, replace if we run out of room. 
        byte rotationFace = (millis() / ROTATION_MS_PER_STEP) % FACE_COUNT;

        if (changed) {
          // Revese direction
          rotationFace = FACE_COUNT - 1 - rotationFace;
        }

        setColor( OFF );
        setColorOnFace( WHITE , rotationFace );     
      } break;
      
    }    
    
  }

};

puzzle_t puzzle; 


// The face of our current center (only valid if areWeCenterFlag==false)
byte centerFace;

// This makes sure we only update the level once per cycle though the states
bool levelUpdatedInterlock;

void updateStatePetal() {

  if (!isValueReceivedOnFaceExpired(centerFace)) {    
    byte messageFromCenter = getLastValueReceivedOnFace(centerFace);

    switch (messageFromCenter) {

      case SHOW_BLOOM_0:        // Show single green pixel pointing to center. Reset level to 0.
        /* FALL THOUGH */       // BLOOM_) is just a specical case of BLOOM, and that is handled in main loop. 
      case SHOW_BLOOM:          // Show single green pixel pointing to center. Increment level.         

        // Note here that we call puzzle.set() repeatedly while the bloom animation is running. This adds some entorpy. 
        puzzle.set( levels[currentLevel] ); 
        
        setColor( OFF );
        setColorOnFace( GREEN , centerFace );

        return;

      case SHOW_PUZZLE:        // Show the current puzzle on our pixels
        puzzle.show(centerFace , false );     // Show a current puzzle, not changed
        return;

      case SHOW_PAUSE:        // The pause between showing the unchanged and changed version
        setColor(OFF);        // This is an editorial decision. I like it all going dark here. 
        return;
        
      case SHOW_CHANGED:        // Show the current puzzle on our pixels, but in the "changed" version
        puzzle.show(centerFace , true );     // Show a current puzzle, changed
        return;

      case SHOW_CORRECT:             // Indicate to the user they picked the right peice

        // I pick now as a good time to increment the petal to the next level. 
        // We check if the currentLevel variable matches the level of the current puzzle to make sure we only
        // increment once per pass though the sequence. 
        if (puzzle.level==currentLevel) {
          currentLevel++;
        }
        
        setColor( GREEN );      // TODO: we can be more creative here! 
        setColorOnFace( WHITE , random( FACE_COUNT - 1) );    // We need some sparkle here - they got it right, lets celibrate!
        break;

      case SHOW_WRONG_MISSED:   // Show user they made the wrong choice and this tile was the changed one
        setColor( GREEN );      // TODO: we can be more creative here! 
        break;
            
      case SHOW_WRONG_OTHERS:   // Show user they made the wrong choice and this tile was the not changed one
        setColor( RED );        // TODO: we can be more creative here! 
        break;

      case SHOW_WIN:            // Show a pretty winning flurish.         
        uint32_t m = millis(); 
        setColor( makeColorHSB( ( m >> 8 ) & 0xff , 0xff , m & 0xff ) );     // TODO: We owe them better than this. 
        break;
      
    }

    // Reset the button flag each time the message from the center changes
    if (didValueOnFaceChange(centerFace)) {
      setValueSentOnFace( IDLE , centerFace ); 
    }

    // Note we only bother sending the button pressed message to the center face
    if (buttonPressed()) {
      setValueSentOnFace( PRESSED , centerFace ); 
    }

        
  } else {
    // TODO: Might be nice to have a timeout here where if a petal has not seen a center for a few seconds it then forgets the current game.
  }
  
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
    }
  }

  // OK, if we get here then we are in stable gameplay so handle normal stuff

  if (weAreCenter) {
    updateStateCenter();
  } else {
    updateStatePetal();    
  }
  
}
