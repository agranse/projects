#ifndef PACKAGE_H
#define PACKAGE_H

#include <vector>

#include "IEntity.h"
#include "IPackagePublisher.h"
#include "math/vector3.h"
#include "util/json.h"

class Robot;

class Package : public IEntity, public IPackagePublisher {
 public:
  /**
   * @brief Constructor
   * @param obj JSON object containing the package's information
   */
  Package(const JsonObject& obj);

  /**
   * @brief Gets the Package's destination
   * @return The Package's destination
   */
  virtual Vector3 getDestination() const;

  /**
   * @brief Returns the name of the strategy for this package
   *
   * @returns String name of strategy
   */
  virtual std::string getStrategyName() const;

  /**
   * @brief Returns the owner of the package
   *
   * @return pointer to Robot owning the package
   */
  virtual Robot* getOwner() const;

  /**
   * @brief Returns the holder of the package
   *
   * @return pointer to IEntity holding the package
   */
  virtual IEntity* getHolder() const;

  /**
   * @brief Returns whether or not the package needs to be delivered
   *
   * @return boolean value of the above statement
   */
  virtual bool requiresDelivery() const;

  /**
   * @brief Set the Strategy Name
   *
   * @param strategyName_ Strategy name
   */
  virtual void setStrategyName(std::string strategyName_);

  /**
   * @brief Sets the Package's destination
   *
   * @param dest destination
   */
  virtual void setDestination(Vector3 dest);

  /**
   * @brief Updates the Package
   *
   * @param dt difference in time since last update
   */
  virtual void update(double dt);

  /**
   * @brief Sets the attributes for delivery
   *
   * @param owner Robot for the package to be delivered to
   */
  virtual void initDelivery(Robot* owner);

  /**
   * @brief The robot/owner/thief picks up the package
   * @param receiver type IEntity* containing whoever is receiving the package
   * @returns boolean of whether it's picked up or not
   */
  virtual bool pickUp(IEntity* receiver);
  /**
   * @brief The robot/owner/thief drops off the package
   * @returns boolean of whether it's dropped off or not
   */
  virtual bool dropOff();


 protected:
  bool requiresDelivery_ = true;
  Vector3 destination;
  std::string strategyName;
  IEntity* holder = nullptr;
  Robot* owner = nullptr;

 private:
  int state = 1;
};

#endif  // PACKAGE_H
