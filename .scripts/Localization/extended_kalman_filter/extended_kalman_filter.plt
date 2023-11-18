set terminal png
set output outfile
set datafile separator ","
plot infile using 2:3 title "Ground truth" with lines linecolor "blue", \
    infile using 6:7 title "Observation" with points pointtype 7 linecolor "dark-spring-green", \
    infile using 8:9 title "EKF" with lines linecolor "red", \
    infile using 12:13 title "Dead reckoning" with lines linecolor "black"