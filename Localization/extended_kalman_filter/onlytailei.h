// from https://github.com/onlytailei/CppRobotics/blob/master/src/extended_kalman_filter.cpp

#include <Eigen/Eigen>

#define SIM_TIME 50.0
#define DT 0.1
#define PI 3.141592653

namespace onlytailei
{

  // x_{t+1} = F@x_{t}+B@u_t
  Eigen::Vector4f motion_model(Eigen::Vector4f x, Eigen::Vector2f u)
  {
    Eigen::Matrix4f F_;
    F_ << 1.0, 0, 0, 0,
        0, 1.0, 0, 0,
        0, 0, 1.0, 0,
        0, 0, 0, 1.0;

    Eigen::Matrix<float, 4, 2> B_;
    B_ << DT * std::cos(x(2, 0)), 0,
        DT * std::sin(x(2, 0)), 0,
        0.0, DT,
        1.0, 0.0;

    return F_ * x + B_ * u;
  };

  Eigen::Matrix4f jacobF(Eigen::Vector4f x, Eigen::Vector2f u)
  {
    Eigen::Matrix4f jF_ = Eigen::Matrix4f::Identity();
    float yaw = x(2);
    float v = u(0);
    jF_(0, 2) = -DT * v * std::sin(yaw);
    jF_(0, 3) = DT * std::cos(yaw);
    jF_(1, 2) = DT * v * std::cos(yaw);
    jF_(1, 3) = DT * std::sin(yaw);
    return jF_;
  };

  // observation mode H
  Eigen::Vector2f observation_model(Eigen::Vector4f x)
  {
    Eigen::Matrix<float, 2, 4> H_;
    H_ << 1, 0, 0, 0,
        0, 1, 0, 0;
    return H_ * x;
  };

  Eigen::Matrix<float, 2, 4> jacobH()
  {
    Eigen::Matrix<float, 2, 4> jH_;
    jH_ << 1, 0, 0, 0,
        0, 1, 0, 0;
    return jH_;
  };

  void ekf_estimation(Eigen::Vector4f &xEst, Eigen::Matrix4f &PEst,
                      Eigen::Vector2f z, Eigen::Vector2f u,
                      Eigen::Matrix4f Q, Eigen::Matrix2f R)
  {
    Eigen::Vector4f xPred = motion_model(xEst, u);
    Eigen::Matrix4f jF = jacobF(xPred, u);
    Eigen::Matrix4f PPred = jF * PEst * jF.transpose() + Q;

    Eigen::Matrix<float, 2, 4> jH = jacobH();
    Eigen::Vector2f zPred = observation_model(xPred);
    Eigen::Vector2f y = z - zPred;
    Eigen::Matrix2f S = jH * PPred * jH.transpose() + R;
    Eigen::Matrix<float, 4, 2> K = PPred * jH.transpose() * S.inverse();
    xEst = xPred + K * y;
    PEst = (Eigen::Matrix4f::Identity() - K * jH) * PPred;
  };
}