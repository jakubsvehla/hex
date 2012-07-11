#include <iostream>
#include <sstream>
#include <cstring>

#include "cmd_mode.h"

#define MAX_SIZE 20

CmdMode::CmdMode (Editor * editor)
: Mode(editor)
{
}

CmdMode::~CmdMode ()
{
}

void CmdMode::Run ()
{
  int   c;
  char  buffer [MAX_SIZE + 1];
  int   i = 0;

  m_Editor -> m_CmdLineView -> Erase();
  m_Editor -> m_CmdLineView -> Put(':');

  while (i < MAX_SIZE) {
    m_Editor -> m_CmdLineView -> Get(c);

    // Exit the command line mode
    if (c == ESC) {
      m_Editor -> m_CmdLineView -> Erase();
      Exit();
      return;
    }

    // Execute the command
    else if (c == '\n') {
      break;
    }
    else if (c == KEY_BACKSPACE && i > 0) {
      m_Editor -> m_CmdLineView -> Move(0, i--);
      m_Editor -> m_CmdLineView -> Del();
    }
    else if (isprint(c)) {
      buffer[i++] = c;
      m_Editor -> m_CmdLineView -> Put(c);
    }
  }

  buffer[i] = '\0';

  // quit cmd
  if (strcmp("quit", buffer) == 0 || strcmp("q", buffer) == 0) {
    if (m_Editor -> m_File -> IsSaved()) {
      m_Editor -> Exit();      
    }
    else {
      m_Editor -> m_CmdLineView -> Render("No write since last change (add ! to overwrite)");
      m_Editor -> m_FileView -> Refresh(); 
    }
  }

  // quit! cmd
  else if (strcmp("quit!", buffer) == 0 || strcmp("q!", buffer) == 0) {
    m_Editor -> Exit();
  }

  // write
  else if (strcmp("write", buffer) == 0 || strcmp("w", buffer) == 0) {
    m_Editor -> m_File -> Save();
  }
  else {
    m_Editor -> m_CmdLineView -> Erase();
    m_Editor -> m_CmdLineView -> Print("Not an editor command: %s", buffer);
    m_Editor -> m_CmdLineView -> Refresh();
    m_Editor -> m_FileView -> Refresh();
  }

  Exit();

}

void CmdMode::Exit ()
{
  m_Editor -> m_Mode = m_Editor -> m_NormalMode;
}
