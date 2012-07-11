#ifndef SUBJECT_H_
#define SUBJECT_H_

#include <vector>

#include "observer.h"

/// Represents a subject in observer pattern.
/// All subject should inherit form this class.
class Subject
{
public:
  virtual ~Subject ();

  /// Registers a new observer.
  void RegisterObserver (Observer * observer);

protected:

  /// Notifies all its observers.
  void NotifyObservers ();

private:
  std::vector<Observer *> m_Observers;
};

#endif // SUBJECT_H_
