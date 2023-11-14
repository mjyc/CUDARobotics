#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using Cell = std::pair<int, int>;

std::vector<Cell> CreateObstacles()
{
    std::vector<Cell> obstacles;
    for (int i = -10; i < 60; ++i)
    {
        obstacles.emplace_back(i, -10);
        obstacles.emplace_back(60, i);
    }
    for (int i = -10; i <= 60; ++i)
    {
        obstacles.emplace_back(i, 60);
        obstacles.emplace_back(-10, i);
    }
    for (int i = -10; i < 40; ++i)
    {
        obstacles.emplace_back(20, i);
    }
    for (int i = 0; i < 40; ++i)
    {
        obstacles.emplace_back(40, 60 - i);
    }
    return obstacles;
}

json ToJSON(
    const std::vector<Cell>& obstacles,
    const Cell& start,
    const Cell& goal
) {
    json j;
    j["obstacles"] = json::array();
    for (const auto& obstacle : obstacles) {
        j["obstacles"].push_back({obstacle.first, obstacle.second});
    }
    j["start"] = {start.first, start.second};
    j["goal"] = {goal.first, goal.second};
    return j;
}

int main()
{
    std::vector<Cell> obstacles{CreateObstacles()};
    Cell start{10, 10};
    Cell goal{50, 50};
    std::cout << ToJSON(obstacles, start, goal).dump() << std::endl;
    return 0;
}