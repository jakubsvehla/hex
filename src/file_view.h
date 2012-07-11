#ifndef FILE_VIEW_H_
#define FILE_VIEW_H_

#include "view.h"
#include "config.h"

/// View the file in hexadecimal and ASCII.
class FileView : public View
{
public:

  /// Constructs a file view.
  /// @param [in] lines Number of lines. Defaults to height of the screen.
  /// @param [in] cols Number of columns. Defaults to the width of the screen.
  /// @param [in] y0 Top-left corner.
  /// @param [in] x0 Top-left corner.
  FileView (int lines = 0,
            int cols = 0,
            int y0 = 0,
            int x0 = 0);

  virtual ~FileView ();

  /// Configures the file view.
  void Configure (Config * config = NULL);

  /// Notifies the view about the subject change.
  virtual void Notify (Subject * s);

  /// Renders a hexadecimal view of the binded file.
  /// Optionally it can also render an ASCII view of the file and offset of every line.
  void Render ();

  /// Scrolls the screen down or up if neccessary.
  void Scroll (int pos);

  /// Calculates the position of the cursor in the view based on |pos| in the file
  /// and moves it to that position.
  void MoveCursor (int pos);

  /// Renders the hexadecima view.
  /// @param [in] buffer The file buffer to be rendered.
  void RenderHexadecimal (unsigned char * buffer,
                          int size);

  /// Renders the ASCII view.
  /// @param [in] buffer The file buffer to be rendered.
  void RenderASCII (unsigned char * buffer,
                    int size);
  
  /// Renders line numbers.
  void RenderLineNums ();

  int BytesPerLine () const;

  /// Binds a given file to the view.
  void Bind (File * file);

private:

  /// Calculates how many blocks of _n_ bytes will fit into the view (together with line numbers and ACSII view).
  int CalculateBlockCnt () const;

  /// Cached result of CalculateBlockCnt().
  int m_BlockCnt;

  /// How many bytes are grouped into one block. Default value is 4.
  int m_BlockSize;

  /// Offset of the first line rendered in the view.
  int m_Offset;

  /// Number of bytes which will fit into the view.
  /// Caches the value not to have to calculate it every time the view is rendered.
  int m_BytesPerScreen;

  /// Number of bytes which will fit into one line
  /// Caches the value not to have to calculate it every time the view is rendered.
  int m_BytesPerLine;

  bool m_ShowNums;

  int m_HexOffset;

  bool m_ShowASCII;
  int m_ASCIIOffset;

  /// Pointer to the file bounded to the view.
  File * m_File;

  /// Tracks the file version in order to rerender the view
  /// only when the file has been changed.
  int m_FileVersion;


};

#endif // FILE_VIEW_H_
