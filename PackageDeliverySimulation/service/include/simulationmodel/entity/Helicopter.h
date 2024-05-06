#ifndef HELICOPTER_H_
#define HELICOPTER_H_

#include "IEntity.h"
#include "IStrategy.h"

class Helicopter : public IEntity {
 public:
  /**
   * @brief Helicopter are created with a name
   * @param obj JSON object containing the helicopter's information
   */
  Helicopter(const JsonObject& obj);

  /**
   * @brief Destructor for helicopter
   */
  ~Helicopter();

  /**
   * @brief Updates the helicopter's position
   * @param dt Delta time
   */
  void update(double dt);

 private:
  IStrategy* movement = nullptr;
  double distanceTraveled = 0;
  unsigned int mileCounter = 0;
  Vector3 lastPosition;
};

#endif  // HELICOPTER_H_
