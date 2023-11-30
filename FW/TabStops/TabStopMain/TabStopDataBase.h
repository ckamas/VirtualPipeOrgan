
enum State {
  standby,
  start_on,
  start_off,
  wait_on,
  wait_off
};

typedef struct {
  // for the tab stop solenoids
  const int SPIaddress;           // for driving the tabstop to a particular state
  State MyState;                  // driving state
  unsigned long DriveTimeStamp;   // how long to leave the solenoid energized
  
  // for reading the state of the tabstops
  const int I2C_BIT;              // for reading the tapstop's current state.
  bool tabReadSet;                // current state driven out on midi
  unsigned long ReadTimeStamp;    // when to start reading the i2c again

  const char *TabStop;            // human readable name
} TabStops;

extern TabStops stops[];
extern const int stopsSize;
