#include "ThiefFactory.h"

IEntity* ThiefFactory::createEntity(const JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("thief") == 0) {
    std::cout << "Thief Created" << std::endl;
    return new Thief(entity);
  }
  return nullptr;
}
