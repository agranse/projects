#ifndef RED_DECORATOR_H_
#define RED_DECORATOR_H_

#include "PackageColorDecorator.h"

/**
 * @class RedDecorator
 * @brief Wraps package in red hue, inherits from PackageColorDecorator
 */
class RedDecorator : public PackageColorDecorator {
 public:
  /**
   * @brief Constructor for red decorator
   * @param Package* pointer to be wrapped
   */
  RedDecorator(Package*);
};

#endif  // RED_DECORATOR_H_
