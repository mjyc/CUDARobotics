#include <Eigen/Eigen>

const int kNumDim{2};
const int kNumLinks{3};
using Matrix23f = Eigen::Matrix<float, kNumDim, kNumLinks>;
using Matrix32f = Eigen::Matrix<float, kNumLinks, kNumDim>;

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

Matrix23f Jacobian(const Eigen::Vector3f& link_lengths,
                         const Eigen::Vector3f& joint_angles)
{
  Matrix23f jacob;
  jacob.setZero();
  for (int i = 0; i < kNumLinks; ++i)
  {
    for (int j = i; j < kNumLinks; ++j)
    {
      float angle_sum = joint_angles.head(j).sum();
      jacob(0, i) -= link_lengths(j) * std::sin(angle_sum);
      jacob(1, i) += link_lengths(j) * std::cos(angle_sum);
    }
  }
  return jacob;
}

std::pair<Eigen::Vector3f, bool> InverseKinematics(
  const Eigen::Vector3f& link_lengths, Eigen::Vector3f joint_angles,
  const Eigen::Vector2f& target, std::vector<Eigen::Vector3f>& debug_path, unsigned short int max_iteration = 100, float tolerance = 0.2)
{
  debug_path.push_back(joint_angles);
  for (int iteration = 0; iteration < max_iteration; ++iteration)
  {
    Eigen::Vector2f current_pos = ForwardKinematics(link_lengths, joint_angles);
    auto errors = target - current_pos;
    auto distance = (errors).norm();

    if (distance < 0.1)
    {
      return {joint_angles, true};
    }

    Matrix32f jacob_inv{
      Jacobian(link_lengths, joint_angles)
        .completeOrthogonalDecomposition().pseudoInverse()};
    joint_angles += jacob_inv * errors * tolerance;
    debug_path.push_back(joint_angles);
  }
  return {joint_angles, false};
}