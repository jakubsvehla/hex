#ifndef WINDOW_H_
#define WINDOW_H_

#include <ncurses.h>

/// Not a hexadecimal value exception
class NotHexadecimalValue {};

/// A thin convenience wrapper around ncurses windows.
/// It doesn't handle ncurses initialization and you have to do it yourself manually. 
class Window
{
public:

  /// Creates a |cols| wide and |lines| high window at a given position (|x0|, |y0|).
  Window (int lines = 0,
          int cols  = 0,
          int y0    = 0,
          int x0    = 0);

  /// Deallocates the window.
  virtual ~Window ();

  /// Prints a given charatcter at the current position in the window.
  void Put (const int c);

  /// Deletes a character under the cursor
  void Del ();

  /// Prints a sequence of data formatted as the |format| argument specifies.
  /// After the |format| parameter, the method expects at least as many additional
  /// arguments as specified in |format|
  void Print (const char * format, ...);

  /// Reads a character.
  bool Get (int & c) const;

  /// Reads a character hexadecimally.
  bool GetHex (int & c) const;

  /// Moves the window cursor.
  void Move (int y, int x);

  /// Refreshes the window.
  void Refresh ();

  /// Clears out the window.
  void Erase ();

  /// Alerts the terminal user.
  void Beep () const;

protected:

  /// Height of the window.
  int m_Height;

  /// Width of the window.
  int m_Width;

private:

  // Top-left corner Y position.
  int m_Y0;

  // Top-left corner X position.
  int m_X0;
  
  /// Pointer to the ncurses window.
  WINDOW * m_Win;

};

#endif // WINDOW_H_
