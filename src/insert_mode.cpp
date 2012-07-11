#include "insert_mode.h"

InsertMode::InsertMode (Editor * editor)
: Mode(editor)
{
}

void InsertMode::Run ()
{
  int c;

  m_Editor -> m_CmdLineView -> Render("-- INSERT MODE --");
  m_Editor -> m_FileView -> Refresh();

  try {
    while (m_Editor -> m_FileView -> GetHex(c)) {
      m_Editor -> m_File -> Ins(c);
    }    
  }
  catch (NotHexadecimalValue) {
    m_Editor -> m_FileView -> Beep();    
  }

  m_Editor -> m_Mode = m_Editor -> m_NormalMode;
}
