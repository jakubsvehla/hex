#include <ncurses.h>

#include "editor.h"
#include "cmd_mode.h"
#include "normal_mode.h"
#include "insert_mode.h"

Editor::Editor ()
{
}

Editor::~Editor ()
{

  delete m_CmdLineView;
  delete m_FileView;
  delete m_File;
  delete m_CmdMode;
  delete m_NormalMode;
  delete m_InsertMode;
  delete m_Config;

  endwin();
}

void Editor::Init ()
{
  // Initialize curses
  initscr(); noecho(); cbreak();

  m_Config      = new Config();
  m_Config      -> LoadFromFile(".hexrc");

  m_File        = new File();
  m_FileView    = new FileView(LINES - 1);
  m_CmdLineView = new CmdLineView();
  m_CmdMode     = new CmdMode(this);
  m_NormalMode  = new NormalMode(this);
  m_InsertMode  = new InsertMode(this);

  m_FileView    -> Configure(m_Config);

  m_Mode        = m_NormalMode;

}

void Editor::OpenFile (char * name)
{
  m_File        -> Open(name);
  m_FileView    -> Bind(m_File);
}

void Editor::Run ()
{
  m_Run = true;

  while (m_Run) {
    m_Mode -> Run();
  }
}

void Editor::Exit ()
{
  m_Run = false;
}
