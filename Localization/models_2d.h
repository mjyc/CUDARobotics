#pragma once

#include <Eigen/Eigen>

#include <functional>
#include <random>

using Vector9f = Eigen::Vector<float, 9>;
using Matrix42f = Eigen::Matrix<float, 4, 2>;
using Matrix24f = Eigen::Matrix<float, 2, 4>;
using Matrix49f = Eigen::Matrix<float, 4, 9>;
using Matrix29f = Eigen::Matrix<float, 2, 9>;

namespace models_2d
{

template <int Size>
std::string to_string(const Eigen::Vector<float, Size>& v)
{
  std::ostringstream oss;
  for (int i = 0; i < v.size(); ++i)
    oss << v[i] << (i < v.size() - 1 ? "," : "");
  return oss.str();
}

/**
 * @brief Creates a motion model with an optional transformation matrix.
 *
 * The motion model represents the transformation applied to a robot's pose
 * during motion. It takes an optional transformation matrix `F` which defaults
 * to an almost identity matrix; there are only three `1.0`s.
 *
 * @param F The transformation matrix representing the motion model. Defaults to
 * an identity matrix.
 */
std::function<Eigen::Vector4f(const Eigen::Vector4f&, const Eigen::Vector2f&,
                              float)>
CreateMotionModel(const Eigen::Matrix4f& F = Eigen::Matrix4f{
                    {1.0, 0.0, 0.0, 0.0},
                    {0.0, 1.0, 0.0, 0.0},
                    {0.0, 0.0, 1.0, 0.0},
                    {0.0, 0.0, 0.0, 0.0}})
{
  return [F](const Eigen::Vector4f& x, const Eigen::Vector2f& u,
             float dt) -> Eigen::Vector4f
  {
    Matrix42f B{{dt * std::cos(x(2)), 0.0},
                {dt * std::sin(x(2)), 0.0},
                {0.0, dt},
                {1.0, 0.0}};
    return F * x + B * u;
  };
}

/**
 * @brief Creates an observation model with the given transformation matrix.
 *
 * This function creates an observation model using the provided transformation
 * matrix. The transformation matrix is a 2x4 matrix that represents the
 * observation model. The default transformation matrix is set to {{1.0, 0.0,
 * 0.0, 0.0}, {0.0, 1.0, 0.0, 0.0}}.
 *
 * @param H The transformation matrix for the observation model.
 * @return The created observation model.
 */
std::function<Eigen::Vector2f(const Eigen::Vector4f&)> CreateObservationModel(
  const Matrix24f& H = Matrix24f{{1.0, 0.0, 0.0, 0.0}, {0.0, 1.0, 0.0, 0.0}})
{
  return [H](const Eigen::Vector4f& x) -> Eigen::Vector2f
  {
    return H * x;
  };
}

/**
 * @brief Class representing a GPS sensor for localization.
 */
class GPSSensor
{
public:
  /**
   * @brief Default constructor for GPSSensor.
   */
  explicit GPSSensor()
      : gen_{std::random_device{}()}
      , gaussian_{0, 1}
      , Rsim_{{0.5 * 0.5, 0.0}, {0.0, 0.5 * 0.5}}
  {
  }

  /**
   * @brief Measures the position using the GPS sensor.
   * @param x The current state of the robot.
   * @return The measured position.
   */
  Eigen::Vector2f Measure(const Eigen::Vector4f& x) const
  {
    return Eigen::Vector2f{x(0) + gaussian_(gen_) * Rsim_(0, 0),
                           x(1) + gaussian_(gen_) * Rsim_(1, 1)};
  }

private:
  mutable std::mt19937 gen_;  // Random number generator.
  mutable std::normal_distribution<float>
    gaussian_;            // Gaussian distribution for measurement noise.
  Eigen::Matrix2f Rsim_;  // Observation model simulation error.
};

// Function object representing the GPS sensor model.
std::function<Eigen::Vector2f(const Eigen::Vector4f&)> const GPSSensorModel =
  [instance = GPSSensor()](const Eigen::Vector4f& x) mutable -> Eigen::Vector2f
{
  return instance.Measure(x);
};

/**
 * @brief Class representing a differential drive robot.
 *
 * The DifferentialDriveRobot class models a differential drive robot in a 2D
 * environment. It provides methods to control the robot's motion, retrieve its
 * state, and observe its surroundings.
 */
class DifferentialDriveRobot
{
public:
  /**
   * @brief Constructor for DifferentialDriveRobot.
   *
   * @param init_time The initial time of the robot. Default is 0.0.
   * @param delta_time The time step for each motion update. Default is 0.1.
   * @param init_state The initial state of the robot. Default is [0, 0, 0, 0].
   */
  explicit DifferentialDriveRobot(float init_time = 0.0, float delta_time = 0.1,
                                  Eigen::Vector4f init_state = {0, 0, 0, 0})
      : time_{init_time}
      , dt_{delta_time}
      , x_{std::move(init_state)}
      , motion_model_{CreateMotionModel()}
      , sensor_model_{GPSSensorModel}
      , gen_{std::random_device{}()}
      , gaussian_{0, 1}
      , Qsim_{{1.0, 0.0}, {0.0, (30.0 / 180.0 * M_PI) * (30.0 / 180.0 * M_PI)}}
  {
  }

  /**
   * @brief Performs a motion update for the robot.
   *
   * @param u The control input for the robot's motion.
   * @return The updated time of the robot.
   */
  float Step(const Eigen::Vector2f& u)
  {
    time_ += dt_;
    Eigen::Vector2f ud{u(0) + gaussian_(gen_) * Qsim_(0, 0),
                       u(1) + gaussian_(gen_) * Qsim_(1, 1)};
    x_ = motion_model_(x_, ud, dt_);
    return time_;
  }

  /**
   * @brief Retrieves the current time of the robot.
   *
   * @return The current time of the robot.
   */
  float GetTime() const noexcept
  {
    return time_;
  }

  /**
   * @brief Retrieves the current state of the robot.
   *
   * @return The current state of the robot.
   */
  Eigen::Vector4f GetState() const noexcept
  {
    return x_;
  }

  /**
   * @brief Observes the surroundings and returns the sensor reading.
   *
   * @return The sensor reading of the robot's surroundings.
   */
  Eigen::Vector2f Observe() const
  {
    return sensor_model_(x_);
  }

private:
  float time_;  // The current time of the robot.
  float dt_;    // The time step for each motion update.

  // State vector: [x y yaw v]'
  Eigen::Vector4f x_;  // The current state of the robot.

  std::function<Eigen::Vector4f(const Eigen::Vector4f&, const Eigen::Vector2f&,
                                float dt)>
    motion_model_;  // The motion model for the robot.
  std::function<Eigen::Vector2f(const Eigen::Vector4f&)>
    sensor_model_;  // The sensor model for the robot.

  // Motion model noise parameters
  std::mt19937 gen_;  // The random number generator.
  std::normal_distribution<float>
    gaussian_;            // The Gaussian distribution for noise.
  Eigen::Matrix2f Qsim_;  // The covariance matrix for motion model noise.
};

}  // namespace models_2d