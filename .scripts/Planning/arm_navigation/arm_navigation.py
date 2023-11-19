#!/usr/bin/env python3

from sys import argv
from json import load

import matplotlib.pyplot as plt

# def save_astar_solution_as_png(
#     obstacles: list[Cell],
#     start: Cell,
#     goal: Cell,
#     path: list[Cell],
#     visited: list[Cell],
#     filename: str = "astar.png",
# ) -> None:
#     ox, oy = [list(lst) for lst in zip(*obstacles)] if obstacles else [[], []]
#     sx, sy = start
#     gx, gy = goal
#     px, py = [list(lst) for lst in zip(*path)] if path else [[], []]
#     vx, vy = [list(lst) for lst in zip(*visited)] if visited else [[], []]
#     plt.plot(ox, oy, ".k")
#     plt.plot(vx, vy, "xc")
#     plt.plot(sx, sy, "og")
#     plt.plot(gx, gy, "xb")
#     plt.plot(px, py, "-r")
#     plt.grid(True)
#     plt.axis("equal")
#     plt.savefig(filename)
#     plt.close()


if __name__ == "__main__":
    if len(argv) < 3:
        raise ValueError("The number of arguments must be gte 2")

    with open(argv[1], "r") as file:
        data = load(file)
        # obstacles: list[Cell] = data["obstacles"]
        # start: Cell = data["start"]
        # goal: Cell = data["goal"]
        # path: list[Cell] = data["path"]
        # visited: list[Cell] = data["visited"]
        # save_astar_solution_as_png(obstacles, start, goal, path, visited, argv[2])
