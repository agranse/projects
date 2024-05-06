#ifndef BLUE_DECORATOR_H_
#define BLUE_DECORATOR_H_

#include "PackageColorDecorator.h"

/**
 * @class BlueDecorator
 * @brief Wraps package in blue hue, inherits from PackageColorDecorator
 */
class BlueDecorator : public PackageColorDecorator {
 public:
  /**
   * @brief Constructor for blue decorator
   * @param Package* pointer to be wrapped
   */
  BlueDecorator(Package*);
};

#endif  // BLUE_DECORATOR_H_
