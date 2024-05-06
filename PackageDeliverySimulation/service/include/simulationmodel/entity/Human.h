#ifndef HUMAN_H_
#define HUMAN_H_

#include "IEntity.h"
#include "IStrategy.h"

class Human : public IEntity {
 public:
  /**
   * @brief Humans are created with a name
   * @param obj JSON object containing the human's information
   */
  Human(const JsonObject& obj);

  /**
   * @brief Destructor for Human
   */
  ~Human();

  /**
   * @brief Updates the human's position
   * @param dt Delta time
   */
  void update(double dt);

 private:
  static Vector3 kellerPosition;
  IStrategy* movement = nullptr;
  bool atKeller = false;
};

#endif  // HUMAN_H_
