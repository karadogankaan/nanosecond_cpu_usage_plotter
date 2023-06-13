set terminal svg enhanced background rgb 'white' size 1920, 1080
set output "$svg_filename"
set datafile separator ','
set xdata time
set timefmt '%Y-%m-%d %H:%M:%S'
set format x '%H:%M:%S'
set xlabel 'Time'
set ylabel 'Value'
set style line 1 linewidth 2
set boxwidth 2
plot "$csv_filename" using 0.0000000001:2 with lines title 'User Time', '' using 0.0000000001:3 with lines title 'System Time'
