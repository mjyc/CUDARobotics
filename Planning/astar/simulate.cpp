#include <nlohmann/json.hpp>

#include <fstream>
#include <iostream>
#include <utility>
#include <vector>

#include "Planning/astar/mjyc.h"

using json = nlohmann::json;
using Cell = std::pair<short int, short int>;  // x, y

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

json ToJSON(const std::vector<Cell>& obstacles, const Cell& start,
            const Cell& goal, const std::vector<Cell>& path,
            const std::vector<Cell>& visited)
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
  for (const auto& cell : path)
  {
    j["path"].push_back(cell);
  }
  j["visited"] = json::array();
  for (const auto& cell : visited)
  {
    j["visited"].push_back(cell);
  }
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
  std::vector<Cell> visited;

  // Plan with A*
  const std::vector<Cell> path = AStar(obstacles, start, goal, h_fnc, visited);

  // Print
  if (argc <= 1)
  {
    std::cout << ToJSON(obstacles, start, goal, path, visited).dump()
              << std::endl;
    return 0;
  }

  // Save
  std::string filename = argv[1];  // NOLINT
  std::ofstream file(filename);
  if (!file)
  {
    std::cerr << "Error opening file: " << filename << std::endl;
    return 1;
  }
  file << ToJSON(obstacles, start, goal, path, visited).dump() << std::endl;

  return 0;
}