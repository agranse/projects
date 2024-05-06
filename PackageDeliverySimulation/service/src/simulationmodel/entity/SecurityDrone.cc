#define _USE_MATH_DEFINES
#include "SecurityDrone.h"

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

SecurityDrone::SecurityDrone(const JsonObject& obj) : IEntity(obj) {
available = true; }

SecurityDrone::~SecurityDrone() {
  if (toPackage) delete toPackage;
  if (toFinalDestination) delete toFinalDestination;
  if (movement) delete movement;
}

void SecurityDrone::update(double dt) {
  Singleton* s = Singleton::getInstance();  // beginning of data collection

  double miles;
  double diff;
  if (available) {
    if (movement && !movement->isCompleted()) {
      movement->move(this, dt);
    } else {
      if (movement) delete movement;
      Vector3 dest;
      dest.x = ((static_cast<double>(rand())) / RAND_MAX) * (2900) - 1400;
      dest.y = position.y;
      dest.z = ((static_cast<double>(rand())) / RAND_MAX) * (1600) - 800;
      if (model) movement =
      new AstarStrategy(position, dest, model->getGraph());
    }
  }

  if (toPackage) {
    toPackage->move(this, dt);
    diff = this->lastPosition.dist(this->position);  //  calculate movement
    this->lastPosition = this->position;  //  Update the position for next time
    this->distanceTraveled += diff;  //  Update distance traveled

    if (toPackage->isCompleted()) {
      delete toPackage;
      toPackage = nullptr;
      if ((package->getPosition()-position).magnitude() < 30) {
        Thief* thief = dynamic_cast<Thief*>(package->getHolder());
        if (thief && thief->removePackage(package)) {
          package->dropOff();
          if (package->pickUp(this)) {
            pickedUp = true;
          }
        } else {
          delete toFinalDestination;
          toFinalDestination = nullptr;
          package = nullptr;
          available = true;
          pickedUp = false;
        }
      } else {
        toPackage = new BeelineStrategy(position, package->getPosition());
      }
    }
  } else if (toFinalDestination) {
    toFinalDestination->move(this, dt);
    diff = this->lastPosition.dist(this->position);  //  calculate movement
    this->lastPosition = this->position;  // Update the position for next time
    this->distanceTraveled += diff;  //  Update distance traveled

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
      miles = distanceTraveled / 1625.0;
      std::string message = getName() + "," + std::to_string(miles)
      + "," + package->getName() + "," + package->getStrategyName()
      + ",Retrieved";  //  message for distance traveled on a delivery in miles
      s->pushNumPackageMiles(message);
      distanceTraveled = 0;  //  reset distanceTraveled for next movement
      toFinalDestination = nullptr;
      package = nullptr;
      available = true;
      pickedUp = false;
    }
  }
}

void SecurityDrone::notify(Package* package) {
  if (!(this->package)) {
    this->package = package;

    std::string message = getName() + " heading to: " +
    this->package->getName();
    notifyObservers(message);
    available = false;
    pickedUp = false;

    Vector3 packagePosition = this->package->getPosition();
    Vector3 finalDestination = this->package->getDestination();

    toPackage = new BeelineStrategy(position, packagePosition);

    std::string strat = this->package->getStrategyName();
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
