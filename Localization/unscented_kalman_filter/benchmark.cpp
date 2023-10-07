#include <benchmark/benchmark.h>
#include <models_2d.h>
#include "unscented_kalman_filter.h"

const float kInitTime = 0.0;
const float kDeltaTime = 0.1;
const Eigen::Vector4f kInitState{0.0, 0.0, 0.0, 0.0}; // [x y yaw v]'

static void UKF(benchmark::State &state)
{
  ukf::UKFParameters params{};

  Eigen::Vector4f x{kInitState};
  Eigen::Matrix4f P{Eigen::Matrix4f::Identity()};
  Eigen::Vector2f u{1.0, 0.1}; // [v yawrate]'

  models_2d::DifferentialDriveRobot sim{kInitTime, kDeltaTime, kInitState};
  for (auto _ : state) // NOLINT
  {
    state.PauseTiming();
    sim.Step(u);
    Eigen::Vector2f z{sim.Observe()};
    state.ResumeTiming();

    ukf::UKFEstimation(x, P, z, u, params);
  }
}
BENCHMARK(UKF);

BENCHMARK_MAIN();