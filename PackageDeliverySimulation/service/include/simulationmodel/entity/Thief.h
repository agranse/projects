#ifndef THIEF_H_
#define THIEF_H_

#include "IEntity.h"
#include "IStrategy.h"
#include "IPackageObserver.h"
#include "Package.h"

/**
 * @class Thief
 * @brief Represents a thief in a physical system. Inherits from PackageObserver
 */
class Thief : public IEntity, public IPackageObserver {
 public:
  /**
   * @brief Thieves are created with a name
   * @param obj JSON object containing the thief's information
   */
  Thief(const JsonObject& obj);
  /**
   * @brief Deconstructor for Thief
   */
  ~Thief();

  /**
   * @brief Determines whether the package was removed or not
   * @param package type Package* contains package
   * @return a bool
   */
  bool removePackage(Package* package);

  /**
   * @brief Notifies thief of package
   * @param package type Package* contains package
   */
  void notify(Package* package) override;
  /**
   * @brief Updates the thief's position
   * @param dt Delta time
   */
  void update(double dt);

 private:
  IStrategy* movement = nullptr;
  Package* targetPackage = nullptr;
  std::vector<Package*> stolenPackages;
};

#endif  // THIEF_H_
