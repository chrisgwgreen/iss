#ifndef network_h
#define network_h

class Network
{

private:
public:
  Network();

  void setup();
  void fetchISSLocation();
  void fetchGeocode(String lat, String lng);
};

extern Network network;

#endif
