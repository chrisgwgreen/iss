#ifndef parser_h
#define parser_h

class Parser
{

private:
public:
  Parser();

  void parseISSLocation(String &);
  void parseGEOCoder(String &lat, String &lng, String &line);
};

extern Parser parser;

#endif
