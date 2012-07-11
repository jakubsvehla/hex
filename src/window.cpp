#include <cctype>
#include <sstream>
#include <iomanip>

using namespace std;

#include "window.h"

#ifndef ESC
#define ESC 27
#endif

Window::Window (int lines, int cols, int y0, int x0)
{
  m_Win = newwin(lines, cols, y0, x0);
  m_Y0 = y0;
  m_X0 = x0;
  getmaxyx(m_Win, m_Height, m_Width);

  keypad(m_Win, TRUE);
}

Window::~Window ()
{
  delwin(m_Win);
}

void Window::Put (const int c)
{
  waddch(m_Win, c);
}

void Window::Del ()
{
  wdelch(m_Win);
}

void Window::Print (const char * format, ...)
{
  va_list args;
  va_start(args, format);
  vwprintw(m_Win, format, args);
  va_end(args);
}

bool Window::Get (int & c) const
{
  if ((c = wgetch(m_Win)) != ERR) {
    return true;
  }
  else {
    return false;
  }  
}

bool Window::GetHex (int & c) const
{
  stringstream buffer;
  int x;
  int i;

  for (i = 0; i < 2; i ++) {
    Get(x);
    if (x == ESC) return false;
    if (isxdigit(x)) {
      buffer << hex << (char) x;
    }
    else {
      throw NotHexadecimalValue();
    }    
  }

  buffer >> hex >> c;

  return true;
}

void Window::Move (int y, int x)
{
  wmove(m_Win, y, x);
}

void Window::Refresh ()
{
  wrefresh(m_Win);
}

void Window::Erase ()
{
  werase(m_Win);
}

void Window::Beep () const
{
  beep();
}
