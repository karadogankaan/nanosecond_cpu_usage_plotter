set terminal svg enhanced background rgb 'white' size 1920, 1080
set title 'Nanosecond CPU Usage Plotter'
set xlabel "Time [miliseconds]"
set ylabel "%CPU USAGE"
set tics out
set autoscale y
set tics font ", 10"
set output "$svg_filename"
set datafile separator ","
set yrange [0:100]
set xrange [0:1200]
set xtics ("500 ms" 50, "1000 ms" 100, "1500 ms" 150, "2000 ms" 200, "2500 ms" 250, "3000 ms" 300, "3500 ms" 350, "4000 ms" 400, "4500 ms" 450, "5000 ms" 500, "5500 ms" 550, "6000 ms" 600, "6500 ms" 650, "7000 ms" 700, "7500 ms" 750, "8000 ms" 800, "8500 ms" 850, "9000 ms" 900, "9500 ms" 950, "10000 ms" 1000, "10500 ms" 1050, "11000 ms" 1100, "11500 ms" 1150, "12000 ms" 1200)
plot "$csv_filename" using 0.000001:2 with lines title 'User Time', '' using 0.000001:3 with lines title 'System Time'
