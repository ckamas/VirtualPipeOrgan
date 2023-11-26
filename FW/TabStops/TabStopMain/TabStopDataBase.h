
enum State {
  standby,
  start_on,
  start_off,
  wait_on,
  wait_off
};

typedef struct {
  const int SPIaddress;
  const int I2C_BIT;
  bool tabReadSet;
  unsigned long timestamp;
  State MyState;
  const char *TabStop;
} TabStops;

extern TabStops stops[];
extern const int stopsSize;
