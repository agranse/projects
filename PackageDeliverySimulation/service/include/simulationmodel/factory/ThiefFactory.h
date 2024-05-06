#ifndef THIEF_FACTORY_H_
#define THIEF_FACTORY_H_

#include <vector>

#include "Thief.h"
#include "IEntityFactory.h"

/** 
 * @class Thief Factory
 * @brief Thief Factory to produce Thief class.
 **/
class ThiefFactory : public IEntityFactory {
 public:
  /**
   * @brief Destructor for ThiefFactory class.
   **/
  virtual ~ThiefFactory() {}

  /**
   * @brief Creates entity using the given JSON object, if possible.
   * @param entity - JsonObject to be used to create the new entity.
   * @return Entity that was created if it was created successfully, or a
   *nullpointer if creation failed.
   **/
  IEntity* createEntity(const JsonObject& entity);
};

#endif  // THIEF_FACTORY_H_

