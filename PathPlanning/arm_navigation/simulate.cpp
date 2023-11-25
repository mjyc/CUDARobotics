#include <nlohmann/json.hpp>

#include <fstream>
#include <iostream>
#include <vector>

#include "Planning/arm_navigation/mjyc.h"

using json = nlohmann::json;

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
  Eigen::Vector3f joint_angles{1.57, 0.0, 0.0};
  Eigen::Vector3f link_lengths{3.0, 2.0, 1.0};
  Eigen::Vector2f target{2.0, 2.0};

  // Run IK
  std::vector<Eigen::Vector3f> path;
  InverseKinematics(link_lengths, joint_angles, target, path);

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
  *out << ToJSON(joint_angles, link_lengths, target, path).dump() << std::endl;

  return 0;
}