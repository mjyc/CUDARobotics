#include <Eigen/Eigen>
#include <tracy/Tracy.hpp>

#include <cmath>

#include "Localization/extended_kalman_filter/utils.h"
#include "Localization/models_2d.h"

namespace mjyc
{

/**
 * Calculates the Jacobian matrix of the state transition function F.
 *
 * @param x The state vector.
 * @param u The control input vector.
 * @param dt The time step.
 * @return The Jacobian matrix of F.
 */
Eigen::Matrix4f JacobF(const Eigen::Vector4f& x, const Eigen::Vector2f& u,
                       float dt)
{
  Eigen::Matrix4f JF{Eigen::Matrix4f::Identity()};
  float yaw = x(2);
  float v = u(0);
  float dt_v = dt * v;
  JF(0, 2) = -dt_v * std::sin(yaw);
  JF(0, 3) = dt * std::cos(yaw);
  JF(1, 2) = dt_v * std::cos(yaw);
  JF(1, 3) = dt * std::sin(yaw);
  return JF;
}

/**
 * Performs Extended Kalman Filter estimation.
 *
 * @param xEst The estimated state vector.
 * @param PEst The estimated state covariance matrix.
 * @param z The measurement vector.
 * @param u The control input vector.
 * @param params The EKF parameters.
 */
void EKFEstimation(Eigen::Vector4f& xEst, Eigen::Matrix4f& PEst,
                   const Eigen::Vector2f& z, const Eigen::Vector2f& u,
                   const utils::EKFParameters& params)
{
  ZoneScoped;  // tracy

  Eigen::Vector4f xPred{params.MotionModel(xEst, u, params.dt)};
  Eigen::Matrix4f JF{JacobF(xPred, u, params.dt)};
  Eigen::Matrix4f PPred{JF * PEst * JF.transpose() + params.Q};

  static const Matrix24f JH{{1.0, 0.0, 0.0, 0.0}, {0.0, 1.0, 0.0, 0.0}};
  Eigen::Vector2f zPred{params.ObservationModel(xPred)};
  Eigen::Vector2f y{z - zPred};
  Eigen::Matrix2f S{JH * PPred * JH.transpose() + params.R};
  Matrix42f K{PPred * JH.transpose() * S.inverse()};

  xEst.noalias() = xPred + K * y;
  PEst.noalias() = (Eigen::Matrix4f::Identity() - K * JH) * PPred;
}

}  // namespace mjyc