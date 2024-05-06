#define _USE_MATH_DEFINES
#include "Thief.h"

#include <cmath>
#include <limits>

#include "AstarStrategy.h"
#include "SimulationModel.h"

#include "Singleton.h"

Thief::Thief(const JsonObject& obj) : IEntity(obj) {}

Thief::~Thief() {
  if (movement) delete movement;
}

bool Thief::removePackage(Package* package) {
  int packageId = package->getId();
  for (int i = 0; i < stolenPackages.size(); i++) {
    if (stolenPackages[i]->getId() == packageId) {
      stolenPackages.erase(stolenPackages.begin() + i);
      return true;
    }
  }
  return false;
}


void Thief::notify(Package* package) {
  if (!targetPackage) {
    if (movement) delete movement;
    Vector3 dest = package->getPosition();
    if (model) movement = new AstarStrategy(position, dest, model->getGraph());
    targetPackage = package;
  }
}

void Thief::update(double dt) {
  Singleton* s = Singleton::getInstance();  //  beginning of data collection
  for (auto& p : stolenPackages) {
    p->setPosition(position);
    p->setDirection(direction);
  }

  if (movement && !movement->isCompleted()) {
    movement->move(this, dt);
  } else {
    if (movement) delete movement;
    if (targetPackage) {
      if (targetPackage->pickUp(this)) {
        stolenPackages.push_back(targetPackage);
        std::string message = "N/A, N/A," + targetPackage->getName() +
        ",N/A,Stolen";  //  message for stolen packages
        s->pushNumPackageMiles(message);
      }
      targetPackage = nullptr;
    }
    Vector3 dest;
    dest.x = ((static_cast<double>(rand())) / RAND_MAX) * (2900) - 1400;
    dest.y = position.y;
    dest.z = ((static_cast<double>(rand())) / RAND_MAX) * (1600) - 800;
    if (model) movement = new AstarStrategy(position, dest, model->getGraph());
  }
}
