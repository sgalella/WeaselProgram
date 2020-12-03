set terminal pngcairo size 600,400
set output "results/fitness.png"
set title "Weasel Program" font ",20"
set xlabel "Iterations" font ",15"
set ylabel "Fitness" font ",15"
set yrange [0:1.1]
set grid
set datafile separator whitespace
set key inside bottom right
plot "results/fitness.txt" using 1:2 with lines linecolor "blue" title "Best fitness", \
     "" using 1:3 with lines linecolor "orange" title "Mean fitness"