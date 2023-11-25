from sys import argv
from json import load

import matplotlib.pyplot as plt

Cell = tuple[int, int]


def save_astar_solution_as_png(
    obstacles: list[Cell],
    start: Cell,
    goal: Cell,
    path: list[Cell],
    visited: list[Cell],
    filename: str = "astar.png",
) -> None:
    """
    Save the A* algorithm solution as a PNG image.

    Args:
        obstacles (list[Cell]): List of obstacle cells.
        start (Cell): Start cell.
        goal (Cell): Goal cell.
        path (list[Cell]): List of cells in the path.
        visited (list[Cell]): List of cells visited during the search.
        filename (str, optional): Name of the output PNG file. Defaults to "astar.png".

    Returns:
        None
    """
    ox, oy = [list(lst) for lst in zip(*obstacles)] if obstacles else [[], []]
    sx, sy = start
    gx, gy = goal
    px, py = [list(lst) for lst in zip(*path)] if path else [[], []]
    vx, vy = [list(lst) for lst in zip(*visited)] if visited else [[], []]
    
    plt.plot(ox, oy, ".k")
    plt.plot(vx, vy, "xc")
    plt.plot(sx, sy, "og")
    plt.plot(gx, gy, "xb")
    plt.plot(px, py, "-r")

    plt.grid(True)
    plt.axis("equal")
    
    plt.savefig(filename)


if __name__ == "__main__":
    if len(argv) < 3:
        raise ValueError("The number of arguments must be gte 2")

    input_filename = argv[1]
    output_filename = argv[2]

    with open(input_filename, "r") as file:
        data = load(file)

        save_astar_solution_as_png(
            obstacles=data["obstacles"],
            start=data["start"],
            goal=data["goal"],
            path=data["path"],
            visited=data["visited"],
            filename=output_filename,
        )
