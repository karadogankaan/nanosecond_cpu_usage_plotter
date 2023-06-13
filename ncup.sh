#!/bin/bash

csv_filename="cpu_usage.csv"  #Specifies the save name of the CSV file.
svg_filename="cpu_usage_$(date +%s).svg" #Specifies the name to save the SVG file.
duration=10 #Specifies how many seconds the program will run.

pid=$$ #It is used to get the PID (Process ID) value.

create_csv_file() {
    local filename=$1 #The name of the CSV file to be created.
    local duration=$2 #Time value to save.
    local pid=$3 #PID of the corresponding process

    echo "Timestamp,User Time (%),System Time (%)" > "$filename"
    #creates a CSV file with the specified filename and writes a header line in it. The header row contains the columns 'Timestamp', 'User Time' and 'System Time'.
    start_time=$(date +%s) #Returns the current time in seconds.
    end_time=$((start_time + duration)) 
    #represents the end time, in seconds, of the current period from the start time.
    current_time=$start_time #monitor the progress of time in the loop or perform time-based operations.

    while [ $current_time -lt $end_time ]; do #it continues the loop to check the status of the process for a certain time.
        stat_filename="/proc/$pid/stat" #Specifies the name of the /proc/$pid/stat file.
        if [ ! -f "$stat_filename" ]; then #Checks if the file defined as $stat_filename exists.
            echo "Hata: $stat_filename dosyası bulunamadı."  #Error when the file cannot be created.
            return
        fi

        stat_data=$(cat "$stat_filename") #reads the contents of the specified file with the cat command and assigns it to a variable named stat_data.
        IFS=' ' read -ra stat_array <<< "$stat_data" #It parses the value of the stat_data variable according to the space character and assigns it to an array called stat_array.

        utime=${stat_array[13]} #Assigns the 13th element of the array to a variable named utime. This stores the value of the user time in the process in the utime variable.
        stime=${stat_array[14]} #Assigns the 14th element of the array to a variable named stime. This stores the value of the system time in the process in the stime variable.

        if [ $utime -eq 0 ] && [ $stime -eq 0 ]; then
            user_percent=0
            system_percent=0
            #Checks whether the utime and stime variables are both equal to 0. If both are 0, there are no time values ​​associated with the processing time and there is no need to do percentage calculations. In this case, it sets the user_percent and system_percent values ​​to 0.
        else #If the 'if' condition is not met, i.e. time values ​​are available, it enters this block to perform calculations.
            total_time=$((utime + stime)) #represents the total processing time.
            user_percent=$(bc <<< "scale=2; ($utime / $total_time) * 100") #Calculates the user time percentage and assigns it to the user_percent variable.
            system_percent=$(bc <<< "scale=2; ($stime / $total_time) * 100") #Calculates the percentage of system time and assigns it to the system_percent variable.
        fi

        echo "$(date +%s),$user_percent,$system_percent" >> "$filename"
        #adds a row with calculated percentages of time and current time.

        sleep 0.001 #We control how many seconds the program will measure.
        current_time=$(date +%s) #Exports time information from SVG and CSV file.
    done
}

create_svg_graph() {
    local csv_filename=$1 #It takes the PID value and creates the CSV file.
    local svg_filename=$2 #It takes the PID value and creates the SVG file.
	#first creates a CSV file and then creates a line chart using that CSV file and saves it to a file in SVG format. This is used to graph the trading time.
    gnuplot <<EOF
set terminal svg enhanced background rgb 'white' size 1920, 1080
set output "$svg_filename"
set datafile separator ","
set xrange [0:]
plot "$csv_filename" using 0.0000000001:2 with lines title 'User Time', '' using 0.0000000001:3 with lines title 'System Time'
EOF
#Eof = End Of File
}

create_csv_file "$csv_filename" "$duration" "$pid"
create_svg_graph "$csv_filename" "$svg_filename"

echo "CSV dosyası '$csv_filename' olarak oluşturuldu."
echo "SVG dosyası '$svg_filename' olarak oluşturuldu."
