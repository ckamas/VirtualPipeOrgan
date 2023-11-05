


class TabStopsEngine {
public:

  // drive all tabs to the "off" position
  TabStopsEngine()=default;

  // turn all drivers off, leave in their current position.
  ~TabStopsEngine();

  void init();
  // update the tab data base
  // looking for tabs that are being driven and are wating for their timeout to
  // stop driving
  void loop();

  // command  TAB on or off
  void tabOn(int tab);
  void tabOff(int tab);

  TabStopsEngine(const TabStopsEngine&) = delete;             // no copy constructor
  TabStopsEngine& operator=(const TabStopsEngine&) = delete;  // no copy assignment
  TabStopsEngine(TabStopsEngine&&) = delete;                  // no move operations
  TabStopsEngine& operator=(TabStopsEngine&&) = delete;       // no move assignment

private:
  const int TABOFF = 0;
  const int TABON = 1;
};