#pragma once

#include <Eigen/Eigen>

#include "ArmNavigation/ik_trajectory_control/utils.h"

using Matrix23f = Eigen::Matrix<float, utils::kNumDim, utils::kNumLinks>;
using Matrix32f = Eigen::Matrix<float, utils::kNumLinks, utils::kNumDim>;

/**
 * Calculates the Jacobian matrix for a robotic arm.
 *
 * @param link_lengths The lengths of the arm links.
 * @param joint_angles The angles of the arm joints.
 * @return The Jacobian matrix.
 */
Matrix23f Jacobian(const Eigen::Vector3f& link_lengths,
                   const Eigen::Vector3f& joint_angles)
{
  Matrix23f jacob;
  jacob.setZero();
  int num_links = jacob.cols();
  for (int i = 0; i < num_links; ++i)
  {
    for (int j = i; j < num_links; ++j)
    {
      float angle_sum = joint_angles.head(j).sum();
      jacob(0, i) -= link_lengths(j) * std::sin(angle_sum);
      jacob(1, i) += link_lengths(j) * std::cos(angle_sum);
    }
  }
  return jacob;
}

/**
 * Calculates the inverse kinematics for a robotic arm.
 * 
 * @param link_lengths The lengths of the arm links.
 * @param joint_angles The current joint angles of the arm.
 * @param target The target position for the end effector.
 * @param max_iteration The maximum number of iterations for the inverse kinematics solver (default: 100).
 * @param tolerance The tolerance for convergence of the inverse kinematics solver (default: 0.01).
 * @param damping The damping factor for the inverse kinematics solver (default: 0.1).
 * @return A pair containing the calculated joint angles and a boolean indicating if the solver converged.
 */
std::pair<Eigen::Vector3f, bool> InverseKinematics(
  const Eigen::Vector3f& link_lengths, const Eigen::Vector3f& joint_angles,
  const Eigen::Vector2f& target, unsigned short int max_iteration = 100,
  float tolerance = 0.01, float damping = 0.1)
{
  Eigen::Vector3f cur_joint_ang{joint_angles};
  for (int iteration = 0; iteration < max_iteration; ++iteration)
  {
    Eigen::Vector2f current_pos =
      utils::ForwardKinematics(link_lengths, cur_joint_ang);
    auto errors = target - current_pos;
    auto distance = (errors).norm();

    if (distance < tolerance)
    {
      return {cur_joint_ang, true};
    }

    Matrix32f jacob_inv{Jacobian(link_lengths, cur_joint_ang)
                          .completeOrthogonalDecomposition()
                          .pseudoInverse()};
    cur_joint_ang += jacob_inv * errors * damping;
  }
  return {cur_joint_ang, false};
}
