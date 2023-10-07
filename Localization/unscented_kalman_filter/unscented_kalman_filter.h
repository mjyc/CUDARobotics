#include <cmath>
#include <Eigen/Eigen>
#include <models_2d.h>

namespace ukf
{

  // State vector dimension
  const int kStateDim = 4;
  // Observation vector dimension
  const int kObsDim = 2;

  Matrix49f GenerateSigmaPoints(
      const Eigen::Vector4f &xEst, const Eigen::Matrix4f &PEst, float gamma)
  {
    // Square root of PEst using Cholesky decomposition
    Eigen::Matrix4f Psqrt = PEst.llt().matrixL();

    Matrix49f sigma{};
    sigma.col(0) = xEst;

    // Positive direction
    int n = xEst.size();
    for (int i = 0; i < n; ++i)
    {
      sigma.col(i + 1) = xEst + gamma * Psqrt.col(i);
    }

    // Negative direction
    for (int i = 0; i < n; ++i)
      sigma.col(i + 1 + n) = xEst - gamma * Psqrt.col(i);

    return sigma;
  }

  Matrix49f PredictSigmaMotion(
      const Matrix49f &sigma, const Eigen::Vector2f &u, float dt,
      std::function<Eigen::Vector4f(
          const Eigen::Vector4f &, const Eigen::Vector2f &, float)>
          MotionModel)
  {
    Matrix49f result{};

    for (int i = 0; i < sigma.cols(); ++i)
      result.col(i) = MotionModel(sigma.col(i), u, dt);

    return result;
  }

  Matrix29f PredictSigmaObservation(
      const Matrix49f &sigma,
      std::function<Eigen::Vector2f(const Eigen::Vector4f &)>
          ObservationModel)
  {
    Matrix29f result{};

    for (int i = 0; i < sigma.cols(); ++i)
      result.col(i) = ObservationModel(sigma.col(i));

    return result;
  }

  Eigen::Matrix4f CalcSigmaCovariance(
      const Eigen::Vector4f &x,
      const Matrix49f &sigma,
      const Vector9f &wc,
      const Eigen::Matrix4f &Pi)
  {
    Matrix49f d{sigma - x.replicate(1, sigma.cols())};
    Eigen::Matrix4f P{Pi};

    for (int i = 0; i < sigma.cols(); ++i)
      P += wc(i) * d.col(i) * d.col(i).transpose();

    return P;
  }

  Eigen::Matrix2f CalcSigmaCovariance(
      const Eigen::Vector2f &x,
      const Matrix29f &sigma,
      const Vector9f &wc,
      const Eigen::Matrix2f &Pi)
  {
    Matrix29f d{sigma - x.replicate(1, sigma.cols())};
    Eigen::Matrix2f P{Pi};

    for (int i = 0; i < sigma.cols(); ++i)
      P += wc(i) * d.col(i) * d.col(i).transpose();

    return P;
  }

  Matrix42f CalcPxz(
      const Matrix49f &sigma,
      const Eigen::Vector4f &x,
      const Matrix29f &z_sigma,
      const Eigen::Vector2f &zb,
      const Vector9f &wc)
  {
    Matrix49f dx{sigma - x.replicate(1, sigma.cols())};
    Matrix29f dz{z_sigma - zb.replicate(1, z_sigma.cols())};
    Matrix42f P{Matrix42f::Zero(dx.rows(), dz.rows())};

    for (int i = 0; i < sigma.cols(); ++i)
      P += wc(i) * dx.col(i) * dz.col(i).transpose();

    return P;
  }

  struct UKFParameters
  {
    float dt = 0.01;

    std::function<Eigen::Vector4f(
        const Eigen::Vector4f &, const Eigen::Vector2f &, float)>
        MotionModel{models_2d::MotionModel};
    std::function<Eigen::Vector2f(const Eigen::Vector4f &)>
        ObservationModel{models_2d::ObservationModel};

    Eigen::Matrix4f Q{
        {0.1 * 0.1, 0, 0, 0},
        {0, 0.1 * 0.1, 0, 0},
        {0, 0, (1.0 / 180 * M_PI) * (1.0 / 180 * M_PI), 0},
        {0, 0, 0, 0.1 * 0.1}};
    Eigen::Matrix2f R{Eigen::Matrix2f::Identity()};

    float alpha = 0.001;
    float beta = 2;
    float kappa = 0;
  };

  void UKFEstimation(
      Eigen::Vector4f &xEst,
      Eigen::Matrix4f &PEst,
      const Eigen::Vector2f &z,
      const Eigen::Vector2f &u,
      const UKFParameters &params)
  {
    // Compute weights
    float lamb =
        std::pow(params.alpha, 2) * (kStateDim + params.kappa) - kStateDim;
    Vector9f wm{}, wc{};
    wm(0) = lamb / (lamb + kStateDim);
    wc(0) =
        lamb / (lamb + kStateDim) + (1 - std::pow(params.alpha, 2) + params.beta);
    for (int i = 1; i < 2 * kStateDim + 1; ++i)
    {
      wm(i) = 1.0 / (2 * (kStateDim + lamb));
      wc(i) = 1.0 / (2 * (kStateDim + lamb));
    }
    float gamma = std::sqrt(kStateDim + lamb);

    // Predict
    Matrix49f sigma_points{GenerateSigmaPoints(xEst, PEst, gamma)};
    Matrix49f sigma{
        PredictSigmaMotion(sigma_points, u, params.dt, params.MotionModel)};
    Eigen::Vector4f xPred = sigma * wm;
    Eigen::Matrix4f PPred = CalcSigmaCovariance(xPred, sigma, wc, params.Q);

    // Update
    Eigen::Vector2f zPred = models_2d::ObservationModel(xPred);
    Eigen::Vector2f y = z - zPred;
    Matrix49f z_sigma_points{GenerateSigmaPoints(xPred, PPred, gamma)};
    Eigen::Vector4f zb4f = z_sigma_points * wm;
    Eigen::Vector2f zb = {zb4f(0), zb4f(1)};
    Matrix29f z_sigma =
        PredictSigmaObservation(z_sigma_points, params.ObservationModel);
    Eigen::Matrix2f st = CalcSigmaCovariance(zb, z_sigma, wc, params.R);
    Matrix42f Pxz = CalcPxz(z_sigma_points, xPred, z_sigma, zb, wc);
    Matrix42f K = Pxz * st.inverse();
    Eigen::Vector4f xEstNew = xPred + K * y;
    Eigen::Matrix4f PEstNew = PPred - K * st * K.transpose();
    xEst = xEstNew;
    PEst = PEstNew;
  }

}