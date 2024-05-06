#ifndef SINGLETON_H
#define SINGLETON_H

#include <iostream>
#include <fstream>
#include <vector>

#include "Drone.h"
#include "Package.h"
#include "util/json.h"

/**
 * @class Singleton
 * @brief Singleton pattern used to collect, process,
 * and output data on simulation.
 */
class Singleton {
 public:
  /**
   * @brief Gets the instance of the Singleton class itself.
   * @return A Singleton pointer that points to the current instance.
   */
  static Singleton* getInstance();

  /**
   * @brief Send data to csv file for later analysis
   */
  void outputData();

  /**
   * @brief Increments number of packages in system by 1.
   */
  void increaseNumPackages();

  /**
   * @brief Increments number of deliveries in system by 1.
   */
  void increaseNumDeliveries();

  /**
   * @brief Pushes new miles drone traveled onto droneMiles vector.
   * @param line std::string containing entity name, distance
                traveled, strategy used (if it's a drone or security),
                the package name and status (if there is a package)
  */
  void pushNumPackageMiles(std::string line);

 private:
  /**
   * @brief Constructor for the Singleton Class.
   */
  Singleton();

  /**
  * @brief Destructor for the Singleton Class.
  */
  ~Singleton();

  static Singleton* instance;
  int numPackages = 0;
  std::vector<std::string> packageMiles;
  int numDeliveries = 0;
};

#endif  // SINGLETON_H
