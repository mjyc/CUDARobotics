#include <benchmark/benchmark.h>

#include "Localization/extended_kalman_filter/mjyc.h"
#include "Localization/extended_kalman_filter/onlytailei.h"
#include "Localization/extended_kalman_filter/utils.h"
#include "Localization/models_2d.h"

const float kInitTime = 0.0;
const float kDeltaTime = 0.1;
const Eigen::Vector4f kInitState{0.0, 0.0, 0.0, 0.0};  // [x y yaw v]'

static void extended_kalman_filter(benchmark::State& state)
{
  utils::EKFParameters params{};

  Eigen::Vector4f x{kInitState};
  Eigen::Matrix4f P{Eigen::Matrix4f::Identity()};
  Eigen::Vector2f u{1.0, 0.1};  // [v yawrate]'

  models_2d::DifferentialDriveRobot sim{kInitTime, kDeltaTime, kInitState};
  for (auto _ : state)  // NOLINT
  {
    state.PauseTiming();
    sim.Step(u);
    Eigen::Vector2f z{sim.Observe()};
    state.ResumeTiming();

    mjyc::EKFEstimation(x, P, z, u, params);
  }
}
BENCHMARK(extended_kalman_filter)
  ->Name("Localization/extended_kalman_filter:extended_kalman_filter");

static void ekf_onlytailei(benchmark::State& state)
{
  utils::EKFParameters params{};

  Eigen::Vector4f x{kInitState};
  Eigen::Matrix4f P{Eigen::Matrix4f::Identity()};
  Eigen::Vector2f u{1.0, 0.1};  // [v yawrate]'

  models_2d::DifferentialDriveRobot sim{kInitTime, kDeltaTime, kInitState};
  for (auto _ : state)  // NOLINT
  {
    state.PauseTiming();
    sim.Step(u);
    Eigen::Vector2f z{sim.Observe()};
    state.ResumeTiming();

    onlytailei::ekf_estimation(x, P, z, u, params.Q, params.R);
  }
}
BENCHMARK(ekf_onlytailei)
  ->Name("Localization/extended_kalman_filter:onlytailei");