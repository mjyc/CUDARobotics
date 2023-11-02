#include <cmath>
#include <Eigen/Eigen>
#include <models_2d.h>

namespace ekf
{

  Eigen::Matrix4f JacobF(const Eigen::Vector4f &x, const Eigen::Vector2f &u, float dt)
  {
    Eigen::Matrix4f JF{Eigen::Matrix4f::Identity()};
    float yaw = x(2);
    float v = u(0);
    JF(0, 2) = -dt * v * std::sin(yaw);
    JF(0, 3) = dt * std::cos(yaw);
    JF(1, 2) = dt * v * std::cos(yaw);
    JF(1, 3) = dt * std::sin(yaw);
    return JF;
  }

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

  void EKFEstimation(Eigen::Vector4f &xEst, Eigen::Matrix4f &PEst,
                     const Eigen::Vector2f &z, const Eigen::Vector2f &u,
                     const EKFParameters &params)
  {
    Eigen::Vector4f xPred{params.MotionModel(xEst, u, params.dt)};
    Eigen::Matrix4f JF{JacobF(xPred, u, params.dt)};
    Eigen::Matrix4f PPred{JF * PEst * JF.transpose() + params.Q};

    Matrix24f JH{
        {1.0, 0.0, 0.0, 0.0},
        {0.0, 1.0, 0.0, 0.0}};
    Eigen::Vector2f zPred{params.ObservationModel(xPred)};
    Eigen::Vector2f y{z - zPred};
    Eigen::Matrix2f S{JH * PPred * JH.transpose() + params.R};
    Matrix42f K{PPred * JH.transpose() * S.inverse()};

    xEst = xPred + K * y;
    PEst = (Eigen::Matrix4f::Identity() - K * JH) * PPred;
  }

}