#ifndef SECURITY_DRONE_FACTORY_H_
#define SECURITY_DRONE_FACTORY_H_

#include <vector>

#include "SecurityDrone.h"
#include "IEntityFactory.h"

/**
 * @class Security Drone Factory
 * @brief Security Drone Factory to produce SecurityDrones class.
 **/
class SecurityDroneFactory : public IEntityFactory {
 public:
  /**
   * @brief Destructor for SecurityDroneFactory class.
   **/
  virtual ~SecurityDroneFactory() {}

  /**
   * @brief Creates entity using the given JSON object, if possible.
   * @param entity - JsonObject to be used to create the new entity.
   * @return Entity that was created if it was created successfully, or a
   *nullpointer if creation failed.
   **/
  IEntity* createEntity(const JsonObject& entity);
};

#endif  // SECURITY_DRONE_FACTORY_H_
