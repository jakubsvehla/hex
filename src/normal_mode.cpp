#include <sstream>

#include "normal_mode.h"

NormalMode::NormalMode (Editor * editor)
: Mode(editor)
{
}

void NormalMode::Run ()
{
  int c;
  int offset = 1;
  int jmp = 1;
  int i;
  int whence = SEEK_CUR;
  bool clear = true;
  std::stringstream buffer;

  m_Editor -> m_File -> Seek(0, whence);

  while (true) {

    m_Editor -> m_FileView -> Get(c);

    if (clear) {
      m_Editor -> m_CmdLineView -> Erase();
      m_Editor -> m_CmdLineView -> Refresh();
      m_Editor -> m_FileView -> Refresh();

      clear = false;
    }

    if (isdigit(c)) {
      buffer << (char) c;
      continue;
    }

    buffer >> jmp;

    switch (c) {

      case 'x':
        offset = 0;
        for (i = 0; i < jmp; i ++) {
          m_Editor -> m_File -> Del();
        }
        break;

      case 'r':
        offset = 0;

        try {
          if (m_Editor -> m_FileView -> GetHex(c)) {
            m_Editor -> m_File -> Put(c);
          }
        }
        catch (NotHexadecimalValue) {
          m_Editor -> m_FileView -> Beep();
        }
        break;

      case KEY_LEFT:
      case 'h':
        offset = -1;
        offset *= jmp;
        break;

      case KEY_RIGHT:
      case 'l':
        offset = 1;
        offset *= jmp;
        break;

      case KEY_DOWN:
      case 'j':
        offset = m_Editor -> m_FileView -> BytesPerLine();
        offset *= jmp;
        break;

      case KEY_UP:
      case 'k':
        offset = m_Editor -> m_FileView -> BytesPerLine();
        offset = -offset;
        offset *= jmp;
        break;

      case 'i':
        m_Editor -> m_Mode = m_Editor -> m_InsertMode;
        return;

      case ':':
        m_Editor -> m_Mode = m_Editor -> m_CmdMode;
        return;

      case ESC:
        jmp = 1;
        buffer.clear();
        buffer.str("");
        return;

      default:
        continue;
    }

    jmp = 1;
    buffer.clear();
    buffer.str("");

    if (!m_Editor -> m_File -> Seek(offset, whence)) {
      m_Editor -> m_FileView -> Beep();
    }

  }
}
