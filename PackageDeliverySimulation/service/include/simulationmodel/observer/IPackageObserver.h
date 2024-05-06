#ifndef IPACKAGEOBSERVER_H_
#define IPACKAGEOBSERVER_H_

#include <string>

class Package;
/**
 * @class IPackageObserver
 * @brief this class represents an observer which
 * will be notified of specifically package events
 */
class IPackageObserver {
 public:
  /**
  * @brief a method through which the package observer can be notified
  * by the publisher with a message
  * @param package type Package* that contains a package to notify about.
  */
  virtual void notify(Package* package) = 0;
};

#endif  // IPACKAGEOBSERVER_H_
