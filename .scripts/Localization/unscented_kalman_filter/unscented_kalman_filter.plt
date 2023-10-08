set terminal gif animate
set output outfile
set datafile separator ","
do for [i=1:500] {
    plot infile every ::1::i using 2:3 title "Ground truth" with lines linecolor "blue", \
    infile every ::1::i using 6:7 title "Observation" with points pointtype 7 linecolor "green", \
    infile every ::1::i using 8:9 title "EKF" with lines linecolor "red", \
    infile every ::1::i using 12:13 title "Dead reckoning" with lines linecolor "black"
}