set terminal gif animate
set output outfile
set datafile separator ","
do for [i=1:500] {
    plot infile every ::1::i using 2:3 notitle with lines linecolor "blue", \
    infile every ::1::i using 6:7 notitle with points pointtype 7 linecolor "dark-spring-green", \
    infile every ::1::i using 8:9 notitle with lines linecolor "red", \
    infile every ::1::i using 12:13 notitle with lines linecolor "black"
}