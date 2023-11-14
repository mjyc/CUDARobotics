#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using Cell = std::pair<int, int>;

std::vector<Cell> CreateObstacles()
{
    std::vector<Cell> obstacles;
    for (unsigned short int i = -10; i < 60; ++i)
    {
        obstacles.emplace_back(i, -10);
        obstacles.emplace_back(60, i);
    }
    for (unsigned short int i = -10; i <= 60; ++i)
    {
        obstacles.emplace_back(i, 60);
        obstacles.emplace_back(-10, i);
    }
    for (unsigned short int i = -10; i < 40; ++i)
    {
        obstacles.emplace_back(20, i);
    }
    for (unsigned short int i = 0; i < 40; ++i)
    {
        obstacles.emplace_back(40, 60 - i);
    }
    return obstacles;
}

int main()
{
    std::vector<Cell> obstacles{CreateObstacles()};
    Cell start{10, 10};
    Cell goal{50, 50};

    json j;
    j["obstacles"] = json::array();
    for (const auto& pos : obstacles) {
        j["obstacles"].push_back({pos.first, pos.second});
    }

    std::ofstream file("obstacles.json");
    if (file.is_open()) {
        file << j.dump();
        file.close();
        std::cout << "JSON data written to obstacles.json" << std::endl;
    } else {
        std::cerr << "Unable to open file for writing." << std::endl;
    }

    return 0;
}