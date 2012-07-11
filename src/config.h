#ifndef CONFIG_H_
#define CONFIG_H_

#include <string>

using namespace std;

#define TOKEN_NUM 2

/// Holds entire configuration of the editor.
/// Configuration is read from the .hexrc file in the current working directory.
struct Config
{

  /// A constructor.
  /// Initializes all values.
  Config ();

  /// Loads the configuration from a file.
  /// Raises an exception if there's an invalid option in the config.
  bool LoadFromFile (const char * name);

  /// Parses a given option.
  /// Raises an exception if the option is invalid.
  void ParseOption (string line);

  // bool m_Color;
  // bool m_ShowCmd;
  // bool m_Downcase;

  bool m_Number;
  bool m_ShowASCII;
  int  m_Group;

private:

  void Tokenize (string line, string tokens [TOKEN_NUM]);

//   void Lowercase (char *p)
//   {
//     for (;*p;p++)
//       *p = tolower(*p);
//   }

};

#endif // CONFIG_H_
