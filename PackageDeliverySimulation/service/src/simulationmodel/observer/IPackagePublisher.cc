#include "IPackagePublisher.h"

void IPackagePublisher::addPackageObserver(IPackageObserver* o) {
packageObservers.insert(o); }

void IPackagePublisher::removePackageObserver(IPackageObserver* o) {
packageObservers.erase(o); }

void IPackagePublisher::notifyPackageObservers(Package* package) {
  for (auto& o : packageObservers) o->notify(package);
}
