#include <vector>

/**
 * @brief Creates obstacles for the simulation.
 *
 * @return std::vector<Cell> - A vector of cells representing the obstacles.
 */
std::vector<Cell> CreateObstacles()
{
  std::vector<Cell> obstacles;
  for (short int i = -10; i < 60; ++i)
  {
    obstacles.emplace_back(i, -10);
    obstacles.emplace_back(60, i);
  }
  for (short int i = -10; i <= 60; ++i)
  {
    obstacles.emplace_back(i, 60);
    obstacles.emplace_back(-10, i);
  }
  for (short int i = -10; i < 40; ++i)
  {
    obstacles.emplace_back(20, i);
  }
  for (short int i = 0; i < 40; ++i)
  {
    obstacles.emplace_back(40, 60 - i);
  }
  return obstacles;
}
