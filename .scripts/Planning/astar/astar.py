from sys import argv
from json import load

import matplotlib.pyplot as plt

Cell = tuple[int, int]


def save_astar_solution_as_png(
    obstacles: list[Cell],
    start: Cell,
    goal: Cell,
    # path: list[Cell],
    # visited: None | list[Cell] = None,
    filename: str = "astar.png",
) -> None:
    # if visited is None:
    #     visited = []
    ox, oy = [list(lst) for lst in zip(*obstacles)]
    sx, sy = start
    gx, gy = goal
    # px, py = [list(lst) for lst in zip(*path)]
    # vx, vy = [list(lst) for lst in zip(*visited)]
    plt.plot(ox, oy, ".k")
    # plt.plot(vx, vy, "xc")
    plt.plot(sx, sy, "og")
    plt.plot(gx, gy, "xb")
    # plt.plot(px, py, "-r")
    plt.grid(True)
    plt.axis("equal")
    plt.savefig(filename)
    plt.close()


if __name__ == "__main__":
    with open(argv[1], "r") as file:
        data = load(file)

        obstacles = data["obstacles"]
        start = data["start"]
        goal = data["goal"]
        save_astar_solution_as_png(obstacles, start, goal, argv[2])
