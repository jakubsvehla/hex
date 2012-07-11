#include "cmd_line_view.h"

CmdLineView::CmdLineView (int lines, int cols, int y0, int x0)
: View(lines, cols, y0, x0)
{
}

CmdLineView::~CmdLineView ()
{
}

void CmdLineView::Render ()
{
}

void CmdLineView::Render (const char * str)
{
  Erase();
  Print(str);
  Refresh();
}

void CmdLineView::Notify (Subject * s)
{
}
