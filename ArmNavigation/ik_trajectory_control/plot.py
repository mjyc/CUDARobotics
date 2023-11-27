#!/usr/bin/env python3

from json import load
from math import cos, sin
from sys import argv

import matplotlib.pyplot as plt


def save_ik_path_as_png(
    joint_angles: list[float],
    link_lengths: list[float],
    target: list[float],
    path: list[list[float]],
    output_filename: str,
) -> None:
    """
    Save the inverse kinematics path as a PNG image.

    Args:
        joint_angles (list[float]): List of joint angles.
        link_lengths (list[float]): List of link lengths.
        target (list[float]): Target position.
        path (list[list[float]]): List of path points.
        output_filename (str): Output filename for the PNG image.

    Returns:
        None
    """
    nlink = len(joint_angles)
    for i, joint_angles in enumerate(path):
        alpha = (i + 1) / (len(path))
        pts = [[0, 0] for _ in range(nlink + 1)]
        for i in range(1, nlink + 1):
            pts[i][0] = pts[i - 1][0] + link_lengths[i - 1] * cos(sum(joint_angles[:i]))
            pts[i][1] = pts[i - 1][1] + link_lengths[i - 1] * sin(sum(joint_angles[:i]))
        for i in range(nlink + 1):
            if i != nlink:
                plt.plot(
                    [pts[i][0], pts[i + 1][0]],
                    [pts[i][1], pts[i + 1][1]],
                    "r-",
                    alpha=alpha,
                )
            plt.plot(pts[i][0], pts[i][1], "ko", alpha=alpha)

    plt.plot(target[0], target[1], "go")

    plt.xlim([-10, 10])
    plt.ylim([-10, 10])
    plt.grid(True)

    plt.savefig(output_filename)


if __name__ == "__main__":
    if len(argv) < 3:
        raise ValueError("The number of arguments must be gte 2")

    input_filename = argv[1]
    output_filename = argv[2]
    with open(input_filename, "r") as file:
        data = load(file)
        joint_angles: list[float] = data["joint_angles"]
        link_lengths: list[float] = data["link_lengths"]
        target: list[float] = data["target"]
        path: list[list[float]] = data["path"]
        save_ik_path_as_png(joint_angles, link_lengths, target, path, output_filename)
