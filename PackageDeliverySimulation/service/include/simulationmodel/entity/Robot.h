#ifndef ROBOT_H
#define ROBOT_H

#include <vector>

#include "IEntity.h"
#include "math/vector3.h"
#include "util/json.h"
#include "IPackageObserver.h"
#include "IStrategy.h"

class Package;

/**
 * @class Robot
 * @brief Represents a robot in a physical system
 *
 * Robots move using euler integration based on a specified
 * velocity and direction.
 */
class Robot : public IEntity, public IPackageObserver {
 public:
  /**
   * @brief Constructor
   * @param obj JSON object containing the robot's information
   */
  Robot(const JsonObject& obj);

  ~Robot();

  /**
   * @brief Sends notification regarding package
   *
   * @param package associated with Robot
   */
  void notify(Package* package);

  /**
   * @brief Updates the Robot
   *
   * @param dt difference in time since last update
   */
  void update(double dt);

  bool requestedDelivery = true;

 protected:
  Package* package = nullptr;;
  IStrategy* movement = nullptr;
};

#endif  // ROBOT_H
