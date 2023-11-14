from sys import argv
from subprocess import run

if __name__ == "__main__":
    INFILE = argv[1]
    OUTFILE = argv[2]
    SCRIPTFILE = argv[0].rsplit(".py", 1)[0] + ".plt"
    command = f"gnuplot -e \"infile='{INFILE}'; outfile='{OUTFILE}'\" '{SCRIPTFILE}'"
    run(command, shell=True)
