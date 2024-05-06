#ifndef GREEN_DECORATOR_H_
#define GREEN_DECORATOR_H_

#include "PackageColorDecorator.h"

/**
 * @class GreenDecorator
 * @brief Wraps package in green hue, inherits from PackageColorDecorator
 */
class GreenDecorator : public PackageColorDecorator {
 public:
  /**
   * @brief Constructor for green decorator
   * @param Package* pointer to be wrapped
   */
  GreenDecorator(Package*);
};

#endif  // GREEN_DECORATOR_H_
