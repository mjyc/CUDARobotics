#include <nlohmann/json.hpp>

#include <fstream>
#include <iostream>
#include <vector>

#include "ArmNavigation/ik_trajectory_control/mjyc.h"
#include "ArmNavigation/ik_trajectory_control/utils.h"

using json = nlohmann::json;

/**
 * @brief Converts the given joint angles, link lengths, target position, and path to a JSON object.
 * 
 * @param joint_angles The joint angles of the arm.
 * @param link_lengths The lengths of the arm links.
 * @param target The target position.
 * @param path The path followed by the arm.
 * @return json The JSON object representing the input data.
 */
json ToJSON(const Eigen::Vector3f& joint_angles,
            const Eigen::Vector3f& link_lengths, const Eigen::Vector2f& target,
            const std::vector<Eigen::Vector3f>& path)
{
  json j;
  j["joint_angles"] = joint_angles;
  j["link_lengths"] = link_lengths;
  j["target"] = target;
  j["path"] = json::array();
  for (const Eigen::Vector3f& joint_angles : path)
    j["path"].push_back(joint_angles);
  return j;
}

int main(int argc, char* argv[])
{
  Eigen::Vector3f link_lengths{3.0, 2.0, 1.0};
  Eigen::Vector3f init_joint_angles{1.5, 1.0, 0.5};
  Eigen::Vector2f target{2.0, 2.0};

  // Generate a straight line trajectory
  std::size_t num_trajectory_points = 10;
  std::vector<Eigen::Vector2f> trajectory{utils::GetStraightLineTrajectory(
    link_lengths, init_joint_angles, target, num_trajectory_points)};

  // ~IK Trajectory Control
  std::vector<Eigen::Vector3f> path;
  Eigen::Vector3f cur_joint_angles{init_joint_angles};  // x
  for (const Eigen::Vector2f& point : trajectory)
  {
    auto ik_result = InverseKinematics(link_lengths, init_joint_angles, point);
    // u = ik_result.first
    cur_joint_angles = ik_result.first;  // apply control
    path.push_back(cur_joint_angles);    // record result
  }

  // Print or save everything
  std::ofstream file;
  std::ostream* out = &std::cout;
  if (argc > 1)
  {
    std::string filename = argv[1];  // NOLINT
    file.open(filename);
    if (!file)
    {
      std::cerr << "Error opening file: " << filename << std::endl;
      return 1;
    }
    out = &file;
  }
  *out << ToJSON(init_joint_angles, link_lengths, target, path).dump()
       << std::endl;

  return 0;
}