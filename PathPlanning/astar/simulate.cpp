#include <nlohmann/json.hpp>

#include <fstream>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

#include "PathPlanning/astar/mjyc.h"
#include "PathPlanning/astar/utils.h"

using json = nlohmann::json;
using Cell = std::pair<short int, short int>;  // x, y

/**
 * @brief Converts the given data into a JSON object.
 *
 * @param obstacles A vector of cells representing obstacles.
 * @param start The starting cell.
 * @param goal The goal cell.
 * @param path A vector of cells representing the path.
 * @param visited A vector of cells representing the visited cells.
 * @return A JSON object containing the converted data.
 */
json ToJSON(const std::vector<Cell>& obstacles, const Cell& start,
            const Cell& goal, const std::vector<Cell>& path,
            const std::shared_ptr<std::vector<Cell>>& visited)
{
  json j;
  j["obstacles"] = json::array();
  for (const auto& cell : obstacles)
  {
    j["obstacles"].push_back({cell.first, cell.second});
  }
  j["start"] = {start.first, start.second};
  j["goal"] = {goal.first, goal.second};
  j["path"] = json::array();
  for (const auto& cell : path) j["path"].push_back(cell);
  j["visited"] = json::array();
  for (const auto& cell : *visited) j["visited"].push_back(cell);
  return j;
}

int main(int argc, char* argv[])
{
  // A* parameters
  const std::vector<Cell> obstacles{CreateObstacles()};
  const Cell start{10, 10};
  const Cell goal{50, 50};
  const std::function<float(const Cell&, const Cell&)> h_fnc =
    [](const Cell& c1, const Cell& c2)
  {
    return CalcDist(c1, c2);
  };
  std::shared_ptr<std::vector<Cell>> visited =
    std::make_shared<std::vector<Cell>>();

  // Plan with A*
  const std::vector<Cell> path = AStar(obstacles, start, goal, h_fnc,
                                       AStarOptions{.debug_visited = visited});

  // Print or save everything
  std::ofstream file;
  std::ostream* out = &std::cout;
  if (argc > 1)
  {
    std::string filename = argv[1];  // NOLINT
    file.open(filename);
    if (!file)
    {
      std::cerr << "Error opening file: " << filename << std::endl;
      return 1;
    }
    out = &file;
  }
  *out << ToJSON(obstacles, start, goal, path, visited).dump() << std::endl;

  return 0;
}