#include "SecurityDroneFactory.h"

IEntity* SecurityDroneFactory::createEntity(const JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("security_drone") == 0) {
    std::cout << "Security Drone Created" << std::endl;
    return new SecurityDrone(entity);
  }
  return nullptr;
}
