#include <Eigen/Eigen>

class ThreeLinkArm
{
public:
  explicit ThreeLinkArm(
    const Eigen::Vector2f& base = Eigen::Vector2f::Zero(),
    const Eigen::Vector3f& joint_angles = Eigen::Vector3f::Zero(),
    const Eigen::Vector3f& link_lengths = Eigen::Vector3f::Zero(),
    const Eigen::Vector2f& target = Eigen::Vector2f::Zero())
      : base_(base)
      , joint_angles_(joint_angles)
      , link_lengths_(link_lengths)
      , target_(target)
  {
  }

  Eigen::Vector3f const& joint_angles() const
  {
    return joint_angles_;
  };

  void joint_angles(const Eigen::Vector3f& joint_angles)
  {
    joint_angles_ = joint_angles;
  }

private:
  Eigen::Vector2f base_;
  Eigen::Vector3f joint_angles_;
  Eigen::Vector3f link_lengths_;
  Eigen::Vector2f target_;
};