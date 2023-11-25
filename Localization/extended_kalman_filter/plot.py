from sys import argv

import matplotlib.pyplot as plt
import numpy as np


def plot(
    ground_truth_x: np.ndarray,
    ground_truth_y: np.ndarray,
    observation_x: np.ndarray,
    observation_y: np.ndarray,
    ekf_x: np.ndarray,
    ekf_y: np.ndarray,
    dead_reckoning_x: np.ndarray,
    dead_reckoning_y: np.ndarray,
    output_filename: str,
):
    """
    Plots the ground truth, observation, EKF, and dead reckoning data on a graph.

    Args:
        ground_truth_x (np.ndarray): Array of x-coordinates for ground truth data.
        ground_truth_y (np.ndarray): Array of y-coordinates for ground truth data.
        observation_x (np.ndarray): Array of x-coordinates for observation data.
        observation_y (np.ndarray): Array of y-coordinates for observation data.
        ekf_x (np.ndarray): Array of x-coordinates for EKF data.
        ekf_y (np.ndarray): Array of y-coordinates for EKF data.
        dead_reckoning_x (np.ndarray): Array of x-coordinates for dead reckoning data.
        dead_reckoning_y (np.ndarray): Array of y-coordinates for dead reckoning data.
        output_filename (str): Filename to save the plot.

    Returns:
        None
    """
    ground_truth_x = data[:, 1]
    ground_truth_y = data[:, 2]
    observation_x = data[:, 5]
    observation_y = data[:, 6]
    ekf_x = data[:, 7]
    ekf_y = data[:, 8]
    dead_reckoning_x = data[:, 11]
    dead_reckoning_y = data[:, 12]

    plt.plot(
        ground_truth_x,
        ground_truth_y,
        label="Ground truth",
        color="blue",
        linestyle="-",
    )
    plt.scatter(
        observation_x, observation_y, label="Observation", color="green", marker="o"
    )
    plt.plot(ekf_x, ekf_y, label="EKF", color="red", linestyle="-")
    plt.plot(
        dead_reckoning_x,
        dead_reckoning_y,
        label="Dead reckoning",
        color="black",
        linestyle="-",
    )
    plt.legend()

    plt.title("Extended Kalman Filter")
    plt.xlabel("x")
    plt.ylabel("y")

    plt.savefig(output_filename)


if __name__ == "__main__":
    if len(argv) < 3:
        raise ValueError("The number of arguments must be gte 2")

    input_filename = argv[1]
    output_filename = argv[2]
    with open(input_filename, "r") as file:
        data = np.loadtxt(argv[1], delimiter=",")
        plot(
            ground_truth_x=data[:, 1],
            ground_truth_y=data[:, 2],
            observation_x=data[:, 5],
            observation_y=data[:, 6],
            ekf_x=data[:, 7],
            ekf_y=data[:, 8],
            dead_reckoning_x=data[:, 11],
            dead_reckoning_y=data[:, 12],
            output_filename=argv[2],
        )
