# CppRobotics

[CppRobotics](https://github.com/onlytailei/CppRobotics) with benchmark.

## Table of Contents

* [Features](#features)
* [Getting started](#getting-started)
* [Benchmark](#localization)
    * [Extended Kalman Filter](#extended-kalman-filter)

## Features

- Benchmark via [google/benchmark](https://github.com/google/benchmark)
- Bazel with intelliSense and debugger support
- Codespace & Dev Container support
- Independent data generation & visualization 

## Getting started

It's easiest to use Codespace to play with this repo.
To open in Codespace, do

1. Click the **Code** drop-down menu.
1. Click on the **Codespaces tab**.
1. Click **Create codespace on main**.

### Debugging in VS Code

To try Do

1. Open a file, e.g., `Benchmark/benchmark.cpp`
1. Add a breakporint, e.g., by clicking left to a line number
1. Open Command Palette via Ctrl + Shift + P (Linux)
1. Enter "Debug: Start Debugging"

## Benchmark

```
------------------------------------------------------------------------------
Benchmark                                    Time             CPU   Iterations
------------------------------------------------------------------------------
Localization/extended_kalman_filter        637 ns          636 ns      1099803
```

To reproduce, run

```
bazel run --compilation_mode=opt //benchmark
```

or do

1. Open `Benchmark/benchmark.cpp`
1. Open Command Palette via Ctrl + Shift + P (Linux)
1. Enter "Tasks: Run Task"
1. Enter "Bazel: Run (opt)"

## Visualizations

Run
```
.scripts/create_animations.sh  # overwrites existing gif files in .scripts/
```

and open a `gif` file (e.g., `.script/path/to/{algorithm}.gif`) you like to see, e.g., in VS Code.