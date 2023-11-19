#!/usr/bin/env python3

from sys import argv
from json import load

import matplotlib.pyplot as plt

from math import cos, sin

NUM_LINK = 3


def save_ik_path_as_png(
    joint_angles: list[float, float, float],
    link_lengths: list[float, float, float],
    target: list[float, float],
    path: list[list[float, float, float]],
) -> None:
    for i, j_angles in enumerate([joint_angles] + path):
        pts = [[0, 0] for _ in range(NUM_LINK + 1)]
        for i in range(1, NUM_LINK + 1):
            pts[i][0] = pts[i - 1][0] + link_lengths[i - 1] * cos(sum(j_angles[:i]))
            pts[i][1] = pts[i - 1][1] + link_lengths[i - 1] * sin(sum(j_angles[:i]))
        for i in range(NUM_LINK + 1):
            if i != NUM_LINK:
                plt.plot(
                    [pts[i][0], pts[i + 1][0]],
                    [pts[i][1], pts[i + 1][1]],
                    "r-",
                )
            plt.plot(pts[i][0], pts[i][1], "ko")

    plt.plot(target[0], target[1], "go")
    plt.grid(True)
    plt.xlim([-10, 10])
    plt.ylim([-10, 10])
    plt.savefig(argv[2])
    plt.close()


if __name__ == "__main__":
    if len(argv) < 3:
        raise ValueError("The number of arguments must be gte 2")

    with open(argv[1], "r") as file:
        data = load(file)
        joint_angles: list[float, float, float] = data["joint_angles"]
        link_lengths: list[float, float, float] = data["link_lengths"]
        target: list[float, float] = data["target"]
        path: list[list[float, float, float]] = data["path"]
        save_ik_path_as_png(joint_angles, link_lengths, target, path)
