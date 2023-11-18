#!/usr/bin/env python3

from sys import argv
from subprocess import run

if __name__ == "__main__":
    if len(argv) < 3:
        raise ValueError("The number of arguments must be gte 2")
    
    script_filename = argv[0].rsplit(".py", 1)[0] + ".plt"
    command = f"gnuplot -e \"infile='{argv[1]}'; outfile='{argv[2]}'\" '{script_filename}'"
    run(command, shell=True)
