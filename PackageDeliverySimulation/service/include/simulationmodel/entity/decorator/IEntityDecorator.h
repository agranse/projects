#ifndef ENTITY_DECORATOR_H_
#define ENTITY_DECORATOR_H_

#include <concepts>

#include "IEntity.h"

template <std::derived_from<IEntity> T = IEntity>
/**
 * @class IEntityDecorator
 * @brief Wraps IEntity, inherits from T
 */
class IEntityDecorator : public T {
 public:
   /**
   * @brief Constructor for IEntityDecorator
   * @param e of object type T* to be wrapped
   */
  IEntityDecorator(T* e) : T(e->getDetails()), sub(e) {}
  virtual ~IEntityDecorator() {
    if (sub) delete sub;
  }
  /**
   * @brief links this decorated entity to a simulation model
   * @param model of object type SimulationModel* contains model to link
   */
  virtual void linkModel(SimulationModel* model) {
    return sub->linkModel(model);
  }
  /**
   * @brief gets the ID of the decorated entity
   * @return The ID of the decorated entity
   */
  virtual int getId() const { return sub->getId(); }
  /**
   * @brief gets the position of the decorated entity
   * @return The position of the decorated entity
   */
  virtual Vector3 getPosition() const { return sub->getPosition(); }
  /**
   * @brief gets the direction of the decorated entity
   * @return The direction of the decorated entity
   */
  virtual Vector3 getDirection() const { return sub->getDirection(); }
  /**
   * @brief gets the details of the decorated entity
   * @return The details of the decorated entity
   */
  virtual const JsonObject& getDetails() const { return sub->getDetails(); }
  /**
   * @brief gets the color of the decorated entity
   * @return The color of the decorated entity
   */
  virtual std::string getColor() const { return sub->getColor(); }
  /**
   * @brief gets the name of the decorated entity
   * @return The name of the decorated entity
   */
  virtual std::string getName() const { return sub->getName(); }
  /**
   * @brief gets the speed of the decorated entity
   * @return The speed of the decorated entity
   */
  virtual double getSpeed() const { return sub->getSpeed(); }
  /**
   * @brief sets the position of the decorated entity
   * @param pos_ of object type Vector3 that contains the desired position of the decorated entity
   */
  virtual void setPosition(Vector3 pos_) { return sub->setPosition(pos_); }
  /**
   * @brief sets the direction of the decorated entity
   * @param dir_ of object type Vector3 that contains the desired direction of the decorated entity
   */
  virtual void setDirection(Vector3 dir_) { return sub->setDirection(dir_); }
  /**
   * @brief sets the color of the decorated entity
   * @param col_ of object type string that contains the desired color of the decorated entity
   */
  virtual void setColor(std::string col_) { return sub->setColor(col_); }
  /**
   * @brief rotate the decorated entity around y axis
   * @param angle of object type double of the angle to rotate the decorated entity by
   */
  virtual void rotate(double angle) { return sub->rotate(angle); }
  /**
   * @brief Updates the decorated entity's position in the physical system.
   * @param dt of object type double of the time step of the update.
   */
  virtual void update(double dt) { return sub->update(dt); }

 protected:
  T* sub = nullptr;
};

#endif  // ENTITY_DECORATOR_H_
