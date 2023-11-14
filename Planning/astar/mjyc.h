#include <utility>

using Cell = std::pair<short int, short int>;

float Dist(const Cell &a, const Cell &b)
{
    auto dx = static_cast<float>(a.first - b.first);
    auto dy = static_cast<float>(a.second - b.second);
    return std::sqrt(dx * dx + dy * dy);
}

std::vector<Cell> AStar(
    const std::vector<Cell> &obstacles,
    const Cell &start,
    const Cell &goal,
    const std::function<float(const Cell &, const Cell &)> &h_fnc)
{
    std::vector<Cell> path;
    return path;
}