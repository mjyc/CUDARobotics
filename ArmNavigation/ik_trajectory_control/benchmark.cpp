#include <benchmark/benchmark.h>

#include <cmath>

#include "ArmNavigation/ik_trajectory_control/mjyc.h"
#include "ArmNavigation/ik_trajectory_control/utils.h"

static void ikctrl_mjyc(benchmark::State& state)
{
  Eigen::Vector3f link_lengths{3.0, 2.0, 1.0};
  std::size_t num_trajectory_points = 10;

  const double radius = 5.0;
  const double angle_increment = M_PI / 20;
  float angle = 0.0;
  for (auto _ : state)  // NOLINT
  {
    state.PauseTiming();
    angle += static_cast<float>(angle_increment);
    if (angle >= 2 * M_PI) angle -= 2 * M_PI;
    Eigen::Vector2f start{radius * std::cos(angle), radius * std::sin(angle)};
    Eigen::Vector2f goal{radius * std::cos(angle + M_PI),
                         radius * std::sin(angle + M_PI)};  // opposite of start

    auto ik_result =
      InverseKinematics(link_lengths, Eigen::Vector3f{0.1, 0.1, 0.1}, start);
    Eigen::Vector3f init_joint_angles{ik_result.first};
    std::vector<Eigen::Vector2f> trajectory{utils::GetStraightLineTrajectory(
      link_lengths, init_joint_angles, goal, num_trajectory_points)};
    state.ResumeTiming();

    // IK Trajectory Control
    Eigen::Vector3f cur_joint_angles{init_joint_angles};  // x
    for (const Eigen::Vector2f& point : trajectory)
    {
      auto res = InverseKinematics(link_lengths, init_joint_angles, point);
      // u = res.first
      cur_joint_angles = res.first;  // apply control
    }
  }
}
BENCHMARK(ikctrl_mjyc)->Name("ArmNavigation/ik_trajectory_control:mjyc");
