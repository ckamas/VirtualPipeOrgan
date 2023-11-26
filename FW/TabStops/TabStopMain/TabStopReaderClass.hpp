


class TabStopsReadingEngine {
public:

  TabStopsReadingEngine() = default;

  ~TabStopsReadingEngine() = default;

  void init();
  void loop();


  TabStopsReadingEngine(const TabStopsReadingEngine&) = delete;             // no copy constructor
  TabStopsReadingEngine& operator=(const TabStopsReadingEngine&) = delete;  // no copy assignment
  TabStopsReadingEngine(TabStopsReadingEngine&&) = delete;                  // no move operations
  TabStopsReadingEngine& operator=(TabStopsReadingEngine&&) = delete;       // no move assignment

private:
  void MidiSendTabOff(uint8_t tab);
  void MidiSendTabOn(uint8_t tab);



  typedef struct {
    uint8_t mux;
    uint8_t chip;
    uint8_t value;
  } TabStopReaderElement_t;
#define NumDevices 10
  TabStopReaderElement_t myDatabase[NumDevices];
};
