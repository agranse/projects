#ifndef IPUBLISHER_H_
#define IPUBLISHER_H_

#include <set>
#include <string>

#include "IObserver.h"

/**
 * @class IPublisher
 * @brief this class represents a publisher which
 * will notify relevant parties of events
 */
class IPublisher {
 public:
  /**
  * @brief a method through which the observer can be added
  * to the publisher's list of objects to be notified
  * @param o type IObserver* that contains the observer that is to be added
  */
  void addObserver(const IObserver* o);
  /**
  * @brief a method through which the observer can be removed
  * from the publisher's list of objects to be notified
  * @param o type IObserver* that contains the observer that is to be removed
  */
  void removeObserver(const IObserver* o);
  /**
  * @brief a method through which the publisher can notify
  * all observers on the publisher's list of objects to be notified
  * @param message type string& containing
  * the message that is to be sent
  */
  void notifyObservers(const std::string& message) const;

 private:
  std::set<const IObserver*> observers;
};

#endif  // IPUBLISHER_H_
