#ifndef DIJKSTRA_STRATEGY_H_
#define DIJKSTRA_STRATEGY_H_

#include "PathStrategy.h"
#include "Graph.h"

/**
 * @class DijkstraStrategy
 * @brief this class inherits from the PathStrategy class and is responsible for
 * generating the dijkstra path that the entity will take.
 */
class DijkstraStrategy : public PathStrategy {
 public:
  /**
   * @brief Construct a new Dijkstra Strategy object
   *
   * @param position Current position
   * @param destination End destination
   * @param graph Graph/Nodes of the map
   */
  DijkstraStrategy(Vector3 position, Vector3 destination,
                   const routing::Graph* graph);
};
#endif  // DIJKSTRA_STRATEGY_H_
