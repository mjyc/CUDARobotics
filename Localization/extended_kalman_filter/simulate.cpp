#include <Eigen/Eigen>
#include <tracy/Tracy.hpp>

#include <fstream>
#include <iostream>

#include "Localization/extended_kalman_filter/mjyc.h"
#include "Localization/models_2d.h"

const float kInitTime{0.0};
const float kDeltaTime{0.1};
const Eigen::Vector4f kInitState{0.0, 0.0, 0.0, 0.0};  // [x y yaw v]'
const float kMaxTime{50.0};

int main(int argc, char* argv[])
{
  // EKF parameters
  utils::EKFParameters params{
    .dt = kDeltaTime,
    .MotionModel = models_2d::CreateMotionModel(),
    .ObservationModel = models_2d::CreateObservationModel(),
    .Q = Eigen::Matrix4f{{0.1 * 0.1, 0, 0, 0},
                         {0, 0.1 * 0.1, 0, 0},
                         {0, 0, (1.0 / 180 * M_PI) * (1.0 / 180 * M_PI), 0},
                         {0, 0, 0, 0.1 * 0.1}},
    .R = Eigen::Matrix2f::Identity()};

  // Estimated state
  Eigen::Vector4f xEst{kInitState};
  // Estimated covariance
  Eigen::Matrix4f PEst{Eigen::Matrix4f::Identity()};
  // Dead reckoned state
  Eigen::Vector4f xDR{kInitState};
  // Fixed control input
  Eigen::Vector2f u{1.0, 0.1};  // [v yawrate]'

  // Robot model
  models_2d::DifferentialDriveRobot sim{kInitTime, kDeltaTime, kInitState};
  // Motion model for dead reckoning
  std::function<Eigen::Vector4f(const Eigen::Vector4f&, const Eigen::Vector2f&,
                                float)>
    MotionModel = models_2d::CreateMotionModel();

  // Create ostream
  std::ofstream file;
  std::ostream* out = &std::cout;
  if (argc > 1)
  {
    std::string filename{argv[1]};  // NOLINT
    file.open(filename);
    if (!file)
    {
      std::cerr << "Error opening file: " << filename << std::endl;
      return 1;
    }
    out = &file;
  }

  while (true)
  {
    // Simulate new state and observation
    sim.Step(u);
    float sim_time = sim.GetTime();
    Eigen::Vector4f x{sim.GetState()};
    Eigen::Vector2f z{sim.Observe()};

    // Estimate with EKF
    mjyc::EKFEstimation(xEst, PEst, z, u, params);

    // Estimate with Dead Reckoning
    xDR = MotionModel(xDR, u, kDeltaTime);

    // Print or save
    *out << sim.GetTime() << "," << models_2d::to_string(x) << ","
         << models_2d::to_string(z) << "," << models_2d::to_string(xEst) << ","
         << models_2d::to_string(xDR) << std::endl;

    if (sim_time > kMaxTime) break;

    FrameMark;  // tracy
  }
}