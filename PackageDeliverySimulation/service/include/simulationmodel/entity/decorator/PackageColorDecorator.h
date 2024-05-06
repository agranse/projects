#ifndef PACKAGE_COLOR_DECORATOR_H_
#define PACKAGE_COLOR_DECORATOR_H_

#include "PackageDecorator.h"

/**
 * @class PackageColorDecorator
 * @brief Wraps package in hues, inherits from PackageDecorator
 */
class PackageColorDecorator : public PackageDecorator {
 private:
  double hue = 0;
  double saturation = 0;
  double light = 0;

 public:
 /**
   * @brief Constructor for package color decorator
   * @param Package* pointer to be wrapped
   * @param double = hue
   * @param double = saturation
   * @param double = light
   */
  PackageColorDecorator(Package*, double = 0, double = 0, double = 0);

  /**
   * @brief Get the current color of the package
   * @return std::string of package color
   */
  std::string getColor() const;
};

#endif  // PACKAGE_COLOR_DECORATOR_H_
