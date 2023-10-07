#include <iostream>
#include <Eigen/Eigen>
#include <models_2d.h>
#include "unscented_kalman_filter.h"

const float kInitTime{0.0};
const float kDeltaTime{0.1};
const Eigen::Vector4f kInitState{0.0, 0.0, 0.0, 0.0}; // [x y yaw v]'
const float kMaxTime{50.0};

int main()
{
  // UKF parameters
  ukf::UKFParameters params{
      .dt = kDeltaTime,
      .MotionModel = models_2d::MotionModel,
      .ObservationModel = models_2d::ObservationModel,
      .Q = Eigen::Matrix4f{
          {0.1 * 0.1, 0, 0, 0},
          {0, 0.1 * 0.1, 0, 0},
          {0, 0, (1.0 / 180 * M_PI) * (1.0 / 180 * M_PI), 0},
          {0, 0, 0, 0.1 * 0.1}},
      .R = Eigen::Matrix2f::Identity(),
      .alpha = 0.001,
      .beta = 2,
      .kappa = 0};

  // Estimated state
  Eigen::Vector4f xEst{kInitState};
  // Estimated covariance
  Eigen::Matrix4f PEst{Eigen::Matrix4f::Identity()};
  // Dead reckoned state
  Eigen::Vector4f xDR{kInitState};
  // Fixed control input
  Eigen::Vector2f u{1.0, 0.1}; // [v yawrate]'

  models_2d::DifferentialDriveRobot sim{kInitTime, kDeltaTime, kInitState};
  while (true)
  {
    // Simulate new state and observation
    sim.Step(u);
    float sim_time = sim.GetTime();
    Eigen::Vector4f x{sim.GetState()};
    Eigen::Vector2f z{sim.Observe()};

    // Estimate with EKF
    ukf::UKFEstimation(xEst, PEst, z, u, params);

    // Estimate with DeadReckoning
    xDR = models_2d::MotionModel(xDR, u, kDeltaTime);

    // Print
    std::cout << sim.GetTime() << ","
              << models_2d::to_string(x) << ","
              << models_2d::to_string(z) << ","
              << models_2d::to_string(xEst) << ","
              << models_2d::to_string(xDR) << std::endl;

    if (sim_time > kMaxTime)
      break;
  }
}