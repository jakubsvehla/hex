#ifndef NORMAL_MODE_H_
#define NORMAL_MODE_H_

#include "mode.h"
#include "editor.h"

/// In normal mode you can enter all the normal editor
/// commands. If you start the editor you are in this mode.
class NormalMode : public Mode
{
public:

  /// A constructor.
  NormalMode (Editor * editor);

  /// Runs the mode.
  virtual void Run ();
};

#endif // NORMAL_MODE_H_
