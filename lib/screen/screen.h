#ifndef screen_h
#define screen_h

class Screen
{

private:
public:
  Screen();

  void setup();
  void println(String &);
  void drawImage();
};

extern Screen screen;

#endif
