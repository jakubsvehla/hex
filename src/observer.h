#ifndef OBSERVER_H_
#define OBSERVER_H_

class Subject;

/// Represents an observer in the observer pattern.
class Observer
{
public:

  /// Handles a notification.
  virtual void Notify (Subject * s) = 0;
};

#endif // OBSERVER_H_
