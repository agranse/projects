#ifndef PACKAGE_DECORATOR_H_
#define PACKAGE_DECORATOR_H_

#include "IEntityDecorator.h"
#include "Package.h"
#include "Robot.h"
/**
 * @class PackageDecorator
 * @brief Wraps package, inherits from IEntityDecorator<Package>
 */
class PackageDecorator : public IEntityDecorator<Package> {
 public:
   /**
   * @brief Constructor for PackageDecorator
   * @param p of object type Package* to be wrapped
   */
  PackageDecorator(Package* p) : IEntityDecorator(p) {}
  /**
   * @brief gets the destination of the decorated package
   * @return The destination of the decorated package
   */
  virtual Vector3 getDestination() const { return sub->getDestination(); }
  /**
   * @brief gets the strategy name of the decorated package
   * @return The strategy name of the decorated package
   */
  virtual std::string getStrategyName() const { return sub->getStrategyName(); }
  /**
   * @brief gets the owner of the decorated package
   * @return The owner of the decorated package
   */
  virtual Robot* getOwner() const { return sub->getOwner(); }
  /**
   * @brief gets the holder of the decorated package
   * @return The holder of the decorated package
   */
  virtual IEntity* getHolder() const { return sub->getHolder(); }
  /**
   * @brief returns whether or not the wrapped package needs to be delievered
   * @return boolean value of the above statement
   */
  virtual bool requiresDelivery() const { return sub->requiresDelivery(); }
  /**
   * @brief sets the strategy name of the decorated package
   * @param strategyName_ of object type string, contains strategy name
   */
  virtual void setStrategyName(std::string strategyName_) {
    return sub->setStrategyName(strategyName_);
  }
    /**
   * @brief sets the destination of the decorated package
   * @param dest of object type Vector3, contains destination
   */
  virtual void setDestination(Vector3 dest) {return sub->setDestination(dest); }
  /**
   * @brief sets attributes for delivery
   * @param owner of object type Robot*, contains robot for the package to be delivered to 
   */
  virtual void initDelivery(Robot* owner) { return sub->initDelivery(owner); }
  /**
   * @brief The decorated package is picked up by receiver
   * @param receiver of object type IEntity*, contains boolean of whether it's picked up or not
   */
  virtual bool pickUp(IEntity* receiver) { return sub->pickUp(receiver); }
  /**
   * @brief The decorated package is dropped off by entity
   * @returns boolean of whether it's dropped off or not
   */
  virtual bool dropOff() { return sub->dropOff(); }
};

#endif  // PACKAGE_DECORATOR_H_
