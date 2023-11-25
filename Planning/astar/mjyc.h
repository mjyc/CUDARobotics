#include <algorithm>
#include <deque>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <utility>

using Cell = std::pair<short int, short int>;

template <>
struct std::hash<Cell>
{
  std::size_t operator()(const Cell& cell) const
  {
    std::size_t h1 = std::hash<short int>{}(cell.first);
    std::size_t h2 = std::hash<short int>{}(cell.second);
    return h1 ^ (h2 << 1);
  }
};

/**
 * Calculates the distance between two cells.
 *
 * @param a The first cell.
 * @param b The second cell.
 * @return The distance between the two cells.
 */
float CalcDist(const Cell& a, const Cell& b)
{
  auto dx = static_cast<float>(a.first - b.first);
  auto dy = static_cast<float>(a.second - b.second);
  return std::sqrt(dx * dx + dy * dy);
}

/**
 * A* algorithm for path planning.
 *
 * @param obstacles A vector of cells representing the obstacles to avoid.
 * @param start The starting cell.
 * @param goal The goal cell.
 * @param h_fnc The heuristic function to estimate the cost of reaching the goal.
 * @param debug_visited (optional) A shared pointer to a vector of cells to store
 *                      the visited cells for debugging purposes.
 * @return A vector of cells representing the shortest path from start to goal.
 */
std::vector<Cell> AStar(
  const std::vector<Cell>& obstacles, const Cell& start, const Cell& goal,
  const std::function<float(const Cell&, const Cell&)>& h_fnc,
  std::shared_ptr<std::vector<Cell>> debug_visited = nullptr)
{
  using QueueElement = std::pair<float, Cell>;  // f_score, position

  std::unordered_set<Cell> obstacle_set{obstacles.begin(), obstacles.end()};
  std::unordered_set<Cell> open_set;
  std::unordered_set<Cell> closed_set;
  std::unordered_map<Cell, float> f_scores;
  std::unordered_map<Cell, float> g_scores;
  std::unordered_map<Cell, Cell> prevs;  // for reconstructing the path
  std::deque<QueueElement> queue;        // for selecting the next cell to visit

  open_set.insert(start);
  g_scores[start] = CalcDist(start, goal);
  f_scores[start] = g_scores[start];  // h_score is 0
  queue.push_back({f_scores[start], start});

  while (!open_set.empty())
  {
    // Pop the cell with the lowest f_score from the priority queue
    auto& [unused, current] = queue.front();
    queue.pop_front();

    if (current == goal) break;

    open_set.erase(current);
    closed_set.insert(current);
    for (short int x_diff = -1; x_diff <= 1; ++x_diff)
    {
      for (short int y_diff = -1; y_diff <= 1; ++y_diff)
      {
        if (x_diff == 0 && y_diff == 0) continue;

        Cell neighbor{current.first + x_diff, current.second + y_diff};
        if (obstacle_set.find(neighbor) != obstacle_set.end() ||
            closed_set.find(neighbor) != closed_set.end())
          continue;

        float neighbor_g_score =
          g_scores[current] + CalcDist(current, neighbor);
        float neighbor_h_score = h_fnc(neighbor, goal);
        if (open_set.find(neighbor) != open_set.end())
        {
          // Update scores and path if a better path is found
          if (neighbor_g_score < g_scores[neighbor])
          {
            g_scores[neighbor] = neighbor_g_score;
            f_scores[neighbor] = g_scores[neighbor] + neighbor_h_score;
            prevs[neighbor] = current;
          }
        }
        else
        {
          // Add the new neighbor to open set and priority queue
          open_set.insert(neighbor);
          g_scores[neighbor] = neighbor_g_score;
          f_scores[neighbor] = g_scores[neighbor] + neighbor_h_score;
          prevs[neighbor] = current;
          queue.push_back({f_scores[neighbor], neighbor});
          std::push_heap(queue.begin(), queue.end(),
                         [](const QueueElement& a, const QueueElement& b)
                         {
                           return a.first > b.first;
                         });
          if (debug_visited)
            debug_visited->push_back({neighbor.first, neighbor.second});
        }
      }
    }
  }

  // Reconstruct the path from goal to start
  std::vector<Cell> path;
  Cell cell_in_path{goal};
  while (prevs.find(cell_in_path) != prevs.end())
  {
    path.push_back(cell_in_path);
    cell_in_path = prevs[cell_in_path];
  }
  std::reverse(path.begin(), path.end());
  return path;
}