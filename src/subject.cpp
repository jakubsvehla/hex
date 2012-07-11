#include "subject.h"

Subject::~Subject ()
{
}

void Subject::NotifyObservers () // FIXME: should be const
{
  std::vector<Observer *>::const_iterator iter;

  for (iter = m_Observers.begin(); iter != m_Observers.end(); iter ++) {
    (*iter) -> Notify(this);
  }
}

void Subject::RegisterObserver (Observer * observer)
{
  m_Observers.push_back(observer);
}
