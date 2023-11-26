#pragma once

#include <Eigen/Dense>

#include <vector>

namespace utils
{

inline const int kNumDim{2};
inline const int kNumLinks{3};

/**
 * Calculates the forward kinematics of a robotic arm.
 *
 * @param link_lengths The lengths of the arm links.
 * @param joint_angles The angles of the arm joints.
 * @return The end effector position in 2D space.
 */
Eigen::Vector2f ForwardKinematics(const Eigen::Vector3f& link_lengths,
                                  const Eigen::Vector3f& joint_angles)
{
  float x = 0, y = 0;
  for (int i = 1; i < kNumLinks + 1; i++)
  {
    x += link_lengths[i - 1] * std::cos(joint_angles.head(i).sum());
    y += link_lengths[i - 1] * std::sin(joint_angles.head(i).sum());
  }
  return Eigen::Vector2f{x, y};
}

/**
 * Performs linear interpolation between two 2D vectors.
 * 
 * @param start The starting vector.
 * @param goal The goal vector.
 * @param num_points The number of points to interpolate between start and goal.
 * @return A vector of interpolated points between start and goal.
 */
std::vector<Eigen::Vector2f> LinearInterpolation(const Eigen::Vector2f& start,
                                                 const Eigen::Vector2f& goal,
                                                 std::size_t num_points)
{
  std::vector<Eigen::Vector2f> trajectory;
  trajectory.reserve(num_points);

  for (std::size_t i = 0; i < num_points; ++i)
  {
    float t = static_cast<float>(i) /
              (num_points - 1);  // Normalized interpolation parameter
    Eigen::Vector2f point = start + t * (goal - start);
    trajectory.push_back(point);
  }

  return trajectory;
}

/**
 * @brief Generates a straight line trajectory in 2D space.
 * 
 * @param link_lengths The lengths of the robot arm links.
 * @param init_joint_angles The initial joint angles of the robot arm.
 * @param target The target position in 2D space.
 * @param num_points The number of points to generate along the trajectory.
 * @return A vector of 2D points representing the straight line trajectory.
 */
std::vector<Eigen::Vector2f> GetStraightLineTrajectory(
  const Eigen::Vector3f& link_lengths, const Eigen::Vector3f& init_joint_angles,
  const Eigen::Vector2f& target, std::size_t num_points)
{
  Eigen::Vector2f start_xy{ForwardKinematics(link_lengths, init_joint_angles)};
  std::vector<Eigen::Vector2f> trajectory{
    LinearInterpolation(std::move(start_xy), target, num_points)};
  return trajectory;
}

}  // namespace utils