# CppRobotics: Benchmark

Implements a subset of [CppRobotics](https://github.com/onlytailei/CppRobotics)/[PythonRobotics](https://github.com/AtsushiSakai/PythonRobotics) with:

- [Codespace](https://docs.github.com/en/codespaces) & [Dev Container](https://code.visualstudio.com/docs/devcontainers/containers) support
- Benchmark via [google/benchmark](https://github.com/google/benchmark)
- Data visualization via [matplotlib](https://matplotlib.org/)
- [Bazel](https://bazel.build/) integration with [VS Code](https://code.visualstudio.com/) intelliSense, debugger, and more

For available algorithms, check out folders starting with a capital letter, e.g., `Localization/extended_kalman_filter`.


## Getting started

It's easiest to use Codespace to play with this repo.
To open in Codespace, do

1. Click the **Code** drop-down menu.
1. Click on the **Codespaces tab**.
1. Click **Create codespace on main**.

To open in VS Code Dev Containers, checkout related documentation, e.g., [this](https://github.com/microsoft/vscode-remote-try-cpp/tree/main#vs-code-dev-containers).

To build src code without Dev Container, start with `.devcontainer/Dockerfile`.


## Benchmark

An example run:

```
-----------------------------------------------------------------------------------------------------
Benchmark                                                           Time             CPU   Iterations
-----------------------------------------------------------------------------------------------------
Localization/extended_kalman_filter:mjyc                          615 ns          616 ns      1125872
Localization/extended_kalman_filter:onlytailei                    618 ns          619 ns      1136444
```
Note: this result is from running the command on my local machine, not on a codepsace instance.

To reproduce, do

1. Open `Localization/extended_kalman_filter/benchmark.cpp`
1. Open Command Palette via Ctrl + Shift + P (Linux)
1. Enter "Tasks: Run Task"
1. Enter "bazel: Run Current File Target (opt)"

or run

```
CC=clang bazel run --compilation_mode=opt //Localization/extended_kalman_filter:benchmark
```


## Visualization

To create [PythonRobotics](https://github.com/AtsushiSakai/PythonRobotics)-style plots, do

1. Open `Localization/extended_kalman_filter/plot.png`
1. Open Command Palette via Ctrl + Shift + P (Linux)
1. Enter "Tasks: Run Task"
1. Enter "Bazel: Generate and Open Plot"

or run

```
CC=clang bazel build //Localization/extended_kalman_filter:generate_plot  # generates a plot
code $(bazel info bazel-bin)/Localization/extended_kalman_filter/plot.png  # opens the plot
```
Note: the `plot.png` tab closes itself on regenerating the plot.


## Debugging in VS Code

Try

1. Open a file, e.g., `Localization/extended_kalman_filter/simulate.cpp`
1. Add a breakporint, e.g., by clicking left to a line number
1. Open Command Palette via Ctrl + Shift + P (Linux)
1. Enter "Debug: Start Debugging"


## Profiling with Tracy

1. (on host machine) install `tracy` 0.10 (e.g., using `brew` on mac) or build it from src by following the section '2.3 Building the server' of the user manual available at https://github.com/wolfpld/tracy.
1. (on host machine) Run `tracy`, enter "Client address", click the "Connect" button.
1. (in devcontainer) Run
    ```
    ˙
    ```

## Related projects

- [AtsushiSakai/PythonRobotics](https://github.com/AtsushiSakai/PythonRobotics)
- [onlytailei/CppRobotics](https://github.com/onlytailei/CppRobotics)
- [giacomo-b/CppRobotics](https://github.com/giacomo-b/CppRobotics)
- [TheLartians/ModernCppStarter](https://github.com/TheLartians/ModernCppStarter)
