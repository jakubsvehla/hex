#ifndef INSERT_MODE_H_
#define INSERT_MODE_H_

#include "mode.h"
#include "editor.h"

/// In insert mode the text you type is inserted into
/// the buffer.
class InsertMode : public Mode
{
public:

  /// Constructor.
  InsertMode (Editor * editor);

  /// Runs the mode
  virtual void Run ();
};

#endif // INSERT_MODE_H_
