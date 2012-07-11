#include <fstream>
#include <cstring>
#include <cstdlib>

#include "config.h"

using namespace std;

Config::Config ()
{
  // Initialize all values
  m_Number       = true;
  m_ShowASCII    = true;
  m_Group        = 4;
}

bool Config::LoadFromFile (const char * name)
{
  fstream filestr;
  string  line;

  filestr.open(name, fstream::in);

  if (filestr.fail()) return false;

  while (true) {

    if (filestr.eof()) break;

    if (filestr.fail()) {
      filestr.close();
      return false;
    }

    getline(filestr, line);

    if (line.length() == 0) continue;

    ParseOption(line);

  }

  filestr.close();

  return true;
}

void Config::ParseOption (string line)
{
  string tokens[TOKEN_NUM];
  bool   boolean;

  Tokenize(line, tokens);

  boolean = true;
  if (tokens[0].find("no") == 0) {
    boolean = false;
    tokens[0] = tokens[0].substr(2);
  }

  if (tokens[0].compare("ascii") == 0) {
    m_ShowASCII = boolean;
  }
  if (tokens[0].compare("number") == 0) {
    m_Number = boolean;
  }
  if (tokens[0].compare("group") == 0) {
    if (!boolean) ; // FIXME: raise an exception

    m_Group = atoi(tokens[1].c_str());
  }

  // ...

}

void Config::Tokenize (string line, string tokens [TOKEN_NUM])
{
  char * str;
  char * p;
  char   delim[] = " ";
  int    i = 0;

  str = new char [line.size()+1];
  strcpy(str, line.c_str());

  p = strtok(str, delim);
  for (i = 0; i < TOKEN_NUM; i ++) {
    if (p != NULL)
      tokens[i] = p;
    p = strtok(NULL, delim);
  }

  delete [] str;
}
