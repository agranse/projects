#ifndef IPACKAGEPUBLISHER_H_
#define IPACKAGEPUBLISHER_H_

#include <set>
#include <string>

#include "IPackageObserver.h"

class Package;
/**
 * @class IPackagePublisher
 * @brief this class represents a publisher which
 * notify observers of specifically package events
 */
class IPackagePublisher {
 public:
   /**
  * @brief a method through which the package observer can be added
  * to the publisher's list of objects to be notified
  * @param o type IPackageObserver* of the
  * observer that is to be added
  */
  void addPackageObserver(IPackageObserver* o);
   /**
  * @brief a method through which the package observer can be removed
  * from the publisher's list of objects to be notified
  * @param o type IPackageObserver* of the
  * observer that is to be removed
  */
  void removePackageObserver(IPackageObserver* o);
  /**
  * @brief a method through which the publisher can notify
  * all observers on the package list
  * @param package type Package* that contains the package to notify observers about
  */
  void notifyPackageObservers(Package* package);

 private:
  std::set<IPackageObserver*> packageObservers;
};

#endif  // IPACKAGEPUBLISHER_H_
