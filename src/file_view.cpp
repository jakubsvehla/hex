#include <cctype>
#include <typeinfo>

#include "file_view.h"

// A helper function
// Does what you expect.
inline int min(int x, int y)
{
  return x < y ? x : y;
}

FileView::FileView (int lines, int cols, int y0, int x0)
: View (lines, cols, y0, x0)
{
  m_Offset = 0; // FIXME: rename offset to base

  m_File = NULL;
  m_FileVersion = 0;

  Configure();

}

FileView::~FileView ()
{
}

void FileView::Configure (Config * config)
{

  if (config != NULL) {
    m_ShowNums      = config -> m_Number;
    m_ShowASCII     = config -> m_ShowASCII;
    m_BlockSize     = config -> m_Group;
  }
  else {
    m_ShowNums      = true;
    m_ShowASCII     = true;
    m_BlockSize     = 4; // block size is 4 bytes by default    
  }

  if (m_ShowNums)
    m_HexOffset     = 10;
  else
    m_HexOffset     = 0;

  m_BlockCnt        = CalculateBlockCnt();

  m_BytesPerLine    = m_BlockSize * m_BlockCnt;
  m_BytesPerScreen  = m_BytesPerLine * m_Height;

  m_ASCIIOffset     = m_Width - m_BytesPerLine;

}

void FileView::Notify (Subject * s)
{
  int pos;

  if (typeid(*s) == typeid(File)) {
    pos = m_File -> Tell();

    if (m_File -> Version() > m_FileVersion ||
        pos < m_Offset ||
        pos >= m_Offset + m_BytesPerScreen)
      Render();

    else
      MoveCursor(pos);
  }
}

void FileView::Render ()
{
  int     pos;
  int     size;
  unsigned char  * buffer;

  // FIXME: check if file is not NULL

  // Get the position of the cursor in the file
  pos = m_File -> Tell();

  Scroll(pos);

  buffer = new unsigned char [m_BytesPerScreen];
  size = m_File -> Read(m_Offset, m_BytesPerScreen, buffer);

  Erase();

  // Render line numbers
  if (m_ShowNums)
    RenderLineNums();

  // Render hexadecimal
  RenderHexadecimal(buffer, size);

  // Render ASCII
  if (m_ShowASCII)
    RenderASCII(buffer, size);

  // Place the cursor at the right place
  MoveCursor(pos);

  // Refresh the screen
  Refresh();

  // Deallocate the buffer
  delete [] buffer;

}

void FileView::Scroll (int pos)
{
  // Scroll up if the cursor is above the screen
  while (pos < m_Offset) {
    m_Offset -= m_BytesPerLine;
  }

  // Scroll down if the cursor is below the screen
  while (pos >= m_Offset + m_BytesPerScreen) {
    m_Offset += m_BytesPerLine;
  }
}

void FileView::MoveCursor (int pos)
{
  pos = pos - m_Offset;
  Move(pos / m_BytesPerLine, m_HexOffset + (pos % m_BytesPerLine * 3) + (pos % m_BytesPerLine / m_BlockSize));
}

void FileView::RenderHexadecimal (unsigned char * buffer, int size)
{
  unsigned char * line = buffer;
  int i, j;

  for (i = 0; i < m_Height; i++) {

    Move(i, m_HexOffset);

    for (j = 0; j < min(m_BytesPerLine, size); j ++) {

      Print("%02X ", line[j]);

      // Print one space after every block
      if ((j + 1) % m_BlockSize == 0) Put(' ');

    }

    line += m_BytesPerLine;
    size -= m_BytesPerLine;
  }
}

void FileView::RenderASCII (unsigned char * buffer, int size)
{
  unsigned char * line = buffer;
  int i, j;

  for (i = 0; i < m_Height; i++) {

    Move(i, m_ASCIIOffset);

    for (j = 0; j < min(m_BytesPerLine, size); j ++) {
      if (isprint(line[j]))
        Put(line[j]);
      else
        Put('.');
    }

    line += m_BytesPerLine;
    size -= m_BytesPerLine;
  }

}

void FileView::RenderLineNums ()
{
  int i;

  for (i = 0; i < m_Height; i ++) {
    Move(i, 0);
    Print("%08lX", m_Offset + (i * m_BytesPerLine));
  }
}

int FileView::CalculateBlockCnt () const
{
  int actual_block_size;
  int col_width;
  int tmp;
  int width;
  int block_cnt;

  block_cnt = 0;

  // Actual width of the block when it's rendered (with spaces).
  actual_block_size = (m_BlockSize * 3) + 1;

  width = m_Width - m_HexOffset;

  if (m_ShowASCII)
    col_width = actual_block_size + m_BlockSize;
  else
    col_width = actual_block_size;

  tmp = col_width;

  while (tmp <= width) {
    block_cnt ++;
    tmp += col_width;
  }

  return block_cnt;
}

int FileView::BytesPerLine () const
{
  return m_BytesPerLine;
}

void FileView::Bind (File * file)
{
  m_File = file;
  m_File -> RegisterObserver(this);
  Render();
}
