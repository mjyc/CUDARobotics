#include <nlohmann/json.hpp>

#include <iostream>
#include <mjyc.h>

using json = nlohmann::json;

json ToJSON(const Eigen::Vector2f base, const Eigen::Vector3f joint_angles,
            const Eigen::Vector3f link_lengths, const Eigen::Vector2f target)
{
  json j;
  j["base"] = base;
  j["joint_angles"] = joint_angles;
  j["link_lengths"] = link_lengths;
  j["target"] = target;
  return j;
}

int main()
{
  std::cout << "Hello, World!" << std::endl;

  Eigen::Vector2f base{1.0, 2.0};
  Eigen::Vector3f joint_angles{0.0, 0.0, 0.0};
  Eigen::Vector3f links{0.0, 0.0, 0.0};
  Eigen::Vector2f target{0.0, 0.0};

  std::cout << ToJSON(base, joint_angles, links, target).dump() << std::endl;
  // ThreeLinkArm robot{Eigen::Vector2f{1.0, 2.0}};

  // std::cout << robot.JointAngles().transpose() << std::endl;
  // std::cout << robot.JointAngles().transpose() << std::endl;

  return 0;
}