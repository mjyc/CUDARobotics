#pragma once

#include <cmath>
#include <Eigen/Eigen>
#include <models_2d.h>

namespace utils
{
  struct EKFParameters
  {
    float dt = 0.01;

    std::function<Eigen::Vector4f(
        const Eigen::Vector4f &, const Eigen::Vector2f &, float)>
        MotionModel{models_2d::CreateMotionModel()};
    std::function<Eigen::Vector2f(const Eigen::Vector4f &)>
        ObservationModel{models_2d::CreateObservationModel()};

    Eigen::Matrix4f Q{
        {0.1 * 0.1, 0, 0, 0},
        {0, 0.1 * 0.1, 0, 0},
        {0, 0, (1.0 / 180 * M_PI) * (1.0 / 180 * M_PI), 0},
        {0, 0, 0, 0.1 * 0.1}};
    Eigen::Matrix2f R{Eigen::Matrix2f::Identity()};
  };
}