#define _USE_MATH_DEFINES
#include "Drone.h"

#include <cmath>
#include <limits>

#include "AstarStrategy.h"
#include "BeelineStrategy.h"
#include "BfsStrategy.h"
#include "DfsStrategy.h"
#include "DijkstraStrategy.h"
#include "JumpDecorator.h"
#include "Package.h"
#include "SimulationModel.h"
#include "SpinDecorator.h"

#include "Singleton.h"

Drone::Drone(const JsonObject& obj) : IEntity(obj) {
  available = true;
  this->lastPosition = this->position;
  }

Drone::~Drone() {
  if (toPackage) delete toPackage;
  if (toFinalDestination) delete toFinalDestination;
}

void Drone::getNextDelivery() {
  if (model && model->scheduledDeliveries.size() > 0) {
    package = model->scheduledDeliveries.front();
    model->scheduledDeliveries.pop_front();

    if (package) {
      std::string message = getName() + " heading to: " + package->getName();
      notifyObservers(message);
      available = false;
      pickedUp = false;

      Vector3 packagePosition = package->getPosition();
      Vector3 finalDestination = package->getDestination();

      toPackage = new BeelineStrategy(position, packagePosition);

      std::string strat = package->getStrategyName();
      if (strat == "astar") {
        toFinalDestination = new JumpDecorator(new AstarStrategy(
            packagePosition, finalDestination, model->getGraph()));
      } else if (strat == "dfs") {
        toFinalDestination =
            new SpinDecorator(new JumpDecorator(new DfsStrategy(
                packagePosition, finalDestination, model->getGraph())));
      } else if (strat == "bfs") {
        toFinalDestination =
            new SpinDecorator(new SpinDecorator(new BfsStrategy(
                packagePosition, finalDestination, model->getGraph())));
      } else if (strat == "dijkstra") {
        toFinalDestination =
            new JumpDecorator(new SpinDecorator(new DijkstraStrategy(
                packagePosition, finalDestination, model->getGraph())));
      } else {
        toFinalDestination =
            new BeelineStrategy(packagePosition, finalDestination);
      }
    }
  }
}

void Drone::update(double dt) {
  Singleton* s = Singleton::getInstance();  // beginning of data collection

  if (available) getNextDelivery();
  if (toPackage) {
    s->increaseNumPackages();
    toPackage->move(this, dt);
    double diff = this->lastPosition.dist(this->position);
    this->lastPosition = this->position;
    this->distanceTraveled += diff;

    if (toPackage->isCompleted()) {
      if (package->pickUp(this)) {
        pickedUp = true;
      } else {
        delete toFinalDestination;
        toFinalDestination = nullptr;
        package = nullptr;
        available = true;
        pickedUp = false;
      }

      s->increaseNumDeliveries();
      double miles = distanceTraveled / 1625.0;
      std::string message = getName() + "," +
      std::to_string(miles) + ",N/A,beeline,N/A";
      //  message for distance traveled between packages
      s->pushNumPackageMiles(message);
      notifyObservers(message);  //  testing
      distanceTraveled = 0;  //  reset distanceTraveled for next movement
      message = getName() + " picked up: " + package->getName();
      notifyObservers(message);

      delete toPackage;
      toPackage = nullptr;
    }
  } else if (toFinalDestination) {
    toFinalDestination->move(this, dt);
    double diff = this->lastPosition.dist(this->position);
    this->lastPosition = this->position;
    this->distanceTraveled += diff;

    if (package && pickedUp) {
      package->setPosition(position);
      package->setDirection(direction);
    }

    if (toFinalDestination->isCompleted()) {
      package->dropOff();
      package->addPackageObserver(package->getOwner());
      package->notifyPackageObservers(package);
      package->removePackageObserver(package->getOwner());
      delete toFinalDestination;
      double miles = distanceTraveled / 1625.0;
      std::string message = getName() + "," +
      std::to_string(miles) + "," + package->getName() +
      "," + package->getStrategyName() +
      ",Delivered";  //  message for distance traveled on a delivery in miles
      s->pushNumPackageMiles(message);
      distanceTraveled = 0;  //  reset distanceTraveled for next movement
      notifyObservers(message);  //  testing
      toFinalDestination = nullptr;
      package = nullptr;
      available = true;
      pickedUp = false;
    }
  }
}
