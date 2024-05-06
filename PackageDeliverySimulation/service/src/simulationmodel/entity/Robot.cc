#include "Robot.h"
#include "AstarStrategy.h"
#include "SimulationModel.h"

Robot::Robot(const JsonObject& obj) : IEntity(obj) {}

Robot::~Robot() {
  if (movement) delete movement;
}


void Robot::notify(Package* package) {
  if (!movement) {
    Vector3 dest = package->getDestination();
    dest[1] = 254.665;
    if (model) movement = new AstarStrategy(position, dest, model->getGraph());
    this->package = package;
  }
}

void Robot::update(double dt) {
  if (movement && !movement->isCompleted()) {
    movement->move(this, dt);
  } else {
    if (movement) delete movement;
    movement = nullptr;
  }
  if (package) {
    package->pickUp(this);
  }
}
