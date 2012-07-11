#ifndef CMD_LINE_VIEW_H_
#define CMD_LINE_VIEW_H_

#include "view.h"

/// A command line view.
class CmdLineView : public View
{
public:

  /// Creates a new command line view.
  /// By default this view is one line height and is situated at the bottom of the screen.
  /// @param [in] lines Number of lines. Defaults to 1.
  /// @param [in] cols Number of columns. Defaults to the width of the screen.
  /// @param [in] y0 Top-left corner.
  /// @param [in] x0 Top-left corner.
  CmdLineView (int lines = 1,
               int cols  = 0,
               int y0    = LINES - 1,
               int x0    = 0);

  virtual ~CmdLineView ();

  virtual void Render ();

  virtual void Render (const char * str);

  virtual void Notify (Subject * s);

};

#endif // CMD_LINE_VIEW_H_
