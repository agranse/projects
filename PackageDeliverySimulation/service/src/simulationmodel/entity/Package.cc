#include "Package.h"
#include "SimulationModel.h"
#include "Robot.h"

Package::Package(const JsonObject& obj) : IEntity(obj) {}

Vector3 Package::getDestination() const { return destination; }

std::string Package::getStrategyName() const { return strategyName; }

// int Package::getStatus() const { return state; }

Robot* Package::getOwner() const { return owner; }

IEntity* Package::getHolder() const { return holder; }

bool Package::requiresDelivery() const { return requiresDelivery_; }

void Package::setStrategyName(std::string strategyName_) {
  strategyName = strategyName_;
}

void Package::setDestination(Vector3 dest) {
  destination = dest;
}

void Package::update(double dt) {
  if (state == 0) {
    for (auto& t : model->wantedCriminals) {
      if ((t->getPosition()-position).magnitude() < 200) {
        addPackageObserver(t);
        notifyPackageObservers(this);
        removePackageObserver(t);
      }
    }
  } else if (state == 2) {
    for (auto& t : model->popoDrone) {
      if ((t->getPosition()-position).magnitude() < 500) {
        addPackageObserver(t);
        notifyPackageObservers(this);
        removePackageObserver(t);
      }
    }
  }
}

void Package::initDelivery(Robot* owner) {
  this->owner = owner;
  owner->requestedDelivery = false;
  requiresDelivery_ = false;
  addObserver(model);
}

bool Package::pickUp(IEntity* receiver) {
  if (holder) {
    return false;
  } else {
    if ((receiver->getPosition()-position).magnitude() < 40) {
      holder = receiver;
      std::string message = holder->getName() + " picked up: " + getName();
      notifyObservers(message);
      Thief* isThief = dynamic_cast<Thief*>(receiver);
      if (isThief) {
        state = 2;
      } else {
        state = 1;
      }
      return true;
    }
    return false;
  }
}

bool Package::dropOff() {
  if (holder) {
    std::string message = holder->getName() + " dropped off: " + getName();
    notifyObservers(message);
    holder = nullptr;
    state = 0;
    return true;
  } else {
    return false;
  }
}
