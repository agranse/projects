#ifndef BEELINE_H_
#define BEELINE_H_

#include "PathStrategy.h"

/**
 * @class BeelineStrategy
 * @brief this class inherits from the PathStrategy class and is responsible for
 * generating the beeline that the entity will take.
 */
class BeelineStrategy : public PathStrategy {
 public:
  /**
   * @brief Construct a new Beeline Strategy object
   *
   * @param pos Starting position
   * @param des End destination
   */
  BeelineStrategy(Vector3 pos, Vector3 des);
};

#endif  // BEELINE_H_
