#ifndef SECURITY_DRONE_H_
#define SECURITY_DRONE_H_

#include <vector>

#include "IEntity.h"
#include "Thief.h"
#include "IStrategy.h"
#include "math/vector3.h"
#include "IPackageObserver.h"


class Package;

// Represents a security drone in a physical system.
// Drones move using euler integration based on a specified
// velocity and direction.
/**
 * @class Security Drone
 * @brief Represents a security drone in a physical system. Inherits from IEntity and IThiefObserver
 */
class SecurityDrone : public IEntity, public IPackageObserver {
 public:
  /**
   * @brief Security drones are created with a name
   * @param obj JSON object containing the security drone's information
   */
  SecurityDrone(const JsonObject& obj);

  /**
   * @brief Destructor for SecurityDrone
   */
  ~SecurityDrone();

  /**
   * @brief Updates the security drone's position
   * @param dt Delta time
   */
  void update(double dt);

  /**
   * @brief Notifies SecurityDrone of packages
   * @param thief Type Package*, passes in the package to be notified about
   */
  void notify(Package* package) override;

  /**
   * @brief Removing the copy constructor operator
   * so that security drones cannot be copied.
   */
  SecurityDrone(const SecurityDrone& drone) = delete;

  /**
   * @brief Removing the assignment operator
   * so that security drones cannot be copied.
   */
  SecurityDrone& operator=(const SecurityDrone& drone) = delete;

 private:
  bool available = true;
  bool pickedUp = false;
  Package* package = nullptr;
  IStrategy* toPackage = nullptr;
  IStrategy* toFinalDestination = nullptr;
  IStrategy* movement = nullptr;
  double distanceTraveled = 0;
  Vector3 lastPosition;
};

#endif  // SECURITY_DRONE_H_
