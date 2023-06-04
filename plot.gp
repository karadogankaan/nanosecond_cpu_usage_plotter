set terminal svg
set output 'output.svg'
set datafile separator ','
set xdata time
set timefmt '%Y-%m-%d %H:%M:%S'
set format x '%H:%M:%S'
set xlabel 'Time'
set ylabel 'Value'
plot 'output.csv' using 1:2 with lines title 'Data'
