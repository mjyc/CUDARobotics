#include <benchmark/benchmark.h>

#include "PathPlanning/astar/types.h"
#include "PathPlanning/astar/mjyc.h"
#include "PathPlanning/astar/utils.h"

static void astar_mjyc(benchmark::State& state)
{
  // A* parameters
  const std::vector<Cell> obstacles{CreateObstacles()};
  const std::function<float(const Cell&, const Cell&)> h_fnc =
    [](const Cell& c1, const Cell& c2)
  {
    return CalcDist(c1, c2);
  };

  const std::size_t num_shortest_path_nodes = 50;
  const int y_coord_range = 41;  // from 10 to 50 inclusive, 41 values
  for (auto _ : state)  // NOLINT
  {
    state.PauseTiming();
    int iter = static_cast<int>(state.iterations());
    int start_y = 10 + (iter / y_coord_range) % y_coord_range;
    int goal_y = 10 + iter % y_coord_range;
    Cell start{10, start_y};
    Cell goal{50, goal_y};
    state.ResumeTiming();

    const std::vector<Cell> path =
      AStar(obstacles, start, goal, h_fnc,
            AStarOptions{.max_nodes_to_explore = num_shortest_path_nodes});
    benchmark::DoNotOptimize(path);
  }
}
BENCHMARK(astar_mjyc)->Name("Localization/astar:mjyc");
