#pragma once

#include <random>
#include <functional>
#include <Eigen/Eigen>

using Vector9f = Eigen::Vector<float, 9>;
using Matrix42f = Eigen::Matrix<float, 4, 2>;
using Matrix24f = Eigen::Matrix<float, 2, 4>;
using Matrix49f = Eigen::Matrix<float, 4, 9>;
using Matrix29f = Eigen::Matrix<float, 2, 9>;

namespace models_2d
{

  template <int Size>
  std::string to_string(const Eigen::Vector<float, Size> &v)
  {
    std::ostringstream oss;
    std::string s{};
    for (int i = 0; i < v.size(); ++i)
      oss << v[i] << (i < v.size() - 1 ? "," : "");
    return oss.str();
  }

  Eigen::Vector4f MotionModel(
      const Eigen::Vector4f &x, const Eigen::Vector2f &u, float dt)
  {
    Eigen::Matrix4f F{{1.0, 0.0, 0.0, 0.0},
                      {0.0, 1.0, 0.0, 0.0},
                      {0.0, 0.0, 1.0, 0.0},
                      {0.0, 0.0, 0.0, 0.0}};

    Matrix42f B{
        {dt * std::cos(x(2)), 0.0},
        {dt * std::sin(x(2)), 0.0},
        {0.0, dt},
        {1.0, 0.0}};

    return F * x + B * u;
  };

  Eigen::Vector2f ObservationModel(const Eigen::Vector4f &x)
  {
    Matrix24f H{{1.0, 0.0, 0.0, 0.0},
                {0.0, 1.0, 0.0, 0.0}};

    return H * x;
  }

  class GPSSensor
  {
  public:
    explicit GPSSensor()
        : gen_{std::random_device{}()},
          gaussian_{0, 1},
          Rsim_{{0.5 * 0.5, 0.0},
                {0.0, 0.5 * 0.5}}
    {
    }

    Eigen::Vector2f Measure(const Eigen::Vector4f &x) const
    {
      return Eigen::Vector2f{
          x(0) + gaussian_(gen_) * Rsim_(0, 0),
          x(1) + gaussian_(gen_) * Rsim_(1, 1)};
    }

  private:
    mutable std::mt19937 gen_;
    mutable std::normal_distribution<float> gaussian_;
    // Observation model simulation error
    Eigen::Matrix2f Rsim_;
  };

  std::function<Eigen::Vector4f(const Eigen::Vector4f &, const Eigen::Vector2f &)>
  CreateMotionModel(float dt)
  {
    return [dt](const Eigen::Vector4f &x, const Eigen::Vector2f &u)
               -> Eigen::Vector4f
    {
      return MotionModel(x, u, dt);
    };
  }

  std::function<Eigen::Vector2f(const Eigen::Vector4f &)> const GPSSensorModel = [instance = GPSSensor()](
                                                                                     const Eigen::Vector4f &x) mutable -> Eigen::Vector2f
  { return instance.Measure(x); };

  class DifferentialDriveRobot
  {
  public:
    explicit DifferentialDriveRobot(
        float init_time = 0.0,
        float delta_time = 0.1,
        Eigen::Vector4f init_state = {0, 0, 0, 0})
        : time_{init_time},
          dt_{delta_time},
          x_{std::move(init_state)},
          motion_model_{CreateMotionModel(delta_time)},
          observation_model_{GPSSensorModel},
          gen_{std::random_device{}()},
          gaussian_{0, 1},
          Qsim_{{1.0, 0.0},
                {0.0, (30.0 / 180.0 * M_PI) * (30.0 / 180.0 * M_PI)}}
    {
    }

    float Step(const Eigen::Vector2f &u)
    {
      time_ += dt_;
      Eigen::Vector2f ud{u(0) + gaussian_(gen_) * Qsim_(0, 0),
                         u(1) + gaussian_(gen_) * Qsim_(1, 1)};
      x_ = motion_model_(x_, ud);
      return time_;
    }

    float GetTime() const noexcept { return time_; }
    Eigen::Vector4f GetState() const noexcept { return x_; }
    Eigen::Vector2f Observe() const { return observation_model_(x_); }

  private:
    float time_;
    float dt_;

    // State vector: [x y yaw v]'
    Eigen::Vector4f x_;

    std::function<Eigen::Vector4f(
        const Eigen::Vector4f &, const Eigen::Vector2f &)>
        motion_model_;
    std::function<Eigen::Vector2f(const Eigen::Vector4f &)> observation_model_;

    // Motion model noise parameters
    std::mt19937 gen_;
    std::normal_distribution<float> gaussian_;
    Eigen::Matrix2f Qsim_;
  };

}