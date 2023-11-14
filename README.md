# CppRobotics: Benchmark

[CppRobotics](https://github.com/onlytailei/CppRobotics) with benchmark.

## Features

- Benchmark via [google/benchmark](https://github.com/google/benchmark)
- Codespace & Dev Container support
- Bazel with intelliSense and debugger support
- [PythonRobotics](https://github.com/AtsushiSakai/PythonRobotics)-style visualization 

### Available Algorithms

- Localizatoin
    - Extended Kalman Filter

## Getting started

It's easiest to use Codespace to play with this repo.
To open in Codespace, do

1. Click the **Code** drop-down menu.
1. Click on the **Codespaces tab**.
1. Click **Create codespace on main**.

To open in VS Code Dev Containers, checkout related documentation, e.g., [this](https://github.com/microsoft/vscode-remote-try-cpp/tree/main#vs-code-dev-containers).

## Benchmark

An example run:

```
-----------------------------------------------------------------------------------------------------
Benchmark                                                           Time             CPU   Iterations
-----------------------------------------------------------------------------------------------------
Localization/extended_kalman_filter:extended_kalman_filter        615 ns          616 ns      1125872
Localization/extended_kalman_filter:onlytailei                    618 ns          619 ns      1136444
```
Note: this result is from running the command on my local machine, not on a codepsace instance.

To reproduce, do

1. Open `Localization/extended_kalman_filter/benchmark.cpp`
1. Open Command Palette via Ctrl + Shift + P (Linux)
1. Enter "Tasks: Run Task"
1. Enter "Bazel: Run (opt)"

or run

```
CC=clang bazel run --compilation_mode=opt //Localization/extended_kalman_filter:benchmark
```

## Visualization

To create [PythonRobotics](https://github.com/AtsushiSakai/PythonRobotics)-style animations, run

```
.scripts/create_animations.sh  # creates gif files in .scripts/
```

and open the freshly created `gif` file (e.g., `.script/Localization/extended_kalman_filter/extended_kalman_filter.gif`) you'd like to see, e.g., in VS Code.

## Debugging in VS Code

Try

1. Open a file, e.g., `Localization/extended_kalman_filter/simulate.cpp`
1. Add a breakporint, e.g., by clicking left to a line number
1. Open Command Palette via Ctrl + Shift + P (Linux)
1. Enter "Debug: Start Debugging"
