#ifndef IOBSERVER_H_
#define IOBSERVER_H_

#include <string>
/**
 * @class IObserver
 * @brief this interface class represents an observer which
 * will be notified of events
 */
class IObserver {
 public:
  /**
  * @brief a method through which the observer can be notified
  * by the publisher with a message
  * @param message type string containing 
  * the message the observer is to be notified of
  */
  virtual void notify(const std::string &message) const = 0;
};

#endif  // IOBSERVER_H_
