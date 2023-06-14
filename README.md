# nanosecond_cpu_usage_plotter
Nanosecond cpu usage plotter for linux


# Purpose 
The purpose of this program is to measure the utime (user time) and stime (system time) values of the desired application every 1 microsecond, in line with the specified time (often 10 seconds). It keeps these values ​​in a CSV file and outputs an SVG file (graphic) after the specified time.

# Build
Steps to build this program:
First of all, if there is no Git: we install it by typing sudo apt-get install git. Then we can clone our project and run it with the make command.
- You can clone it with git clone &lt;repository_url&gt;. You must know the url of the file to be cloned.
- Go to the directory of the makefile and the file where the program is created.
- Terminale : You can build this program by typing `make -f Makefile.mak` .

# Installation
To install the program on the system:
We go to the file path where our file is with the `cd` command.
Then we install our program on the system by typing `sudo make -f Makefile.mak install` in the terminal.

# Run  
To run our program, you need to do:
`./ncup.sh process_name duration`
from the terminal.
You need to type the full name of the application you want to measure in place of process_name.(eg firefox)
In the Duration part, you need to specify how many seconds you want to measure the program. (For example 10)
If you call our program with `--help` , you will get the usage instructions for the script as output.
Another way to run the program after installing it:
`gcc -o ncup ncup.c`
`./ncup Firefox`

# Contrib  
Contributions are welcome.

# Discussion 
My program is open for improvements. My program, which I run with Stat, is in a state of closing and opening every time it is read.
The interval between each opening and closing is not 1 microsecond, it times out and makes delays.
I preferred to write a wrapper with bash script for my program where I call the gnuplot command with the `system() call` .
This is because my program is under development.

# Screenshots
Below are graphs showing the measured CPU values of some popular applications:
- ![firefox_ncup](https://github.com/karadogankaan/nanosecond_cpu_usage_plotter/assets/134071144/727cf3cf-d07b-4ad0-849e-08be37596120)

- ![systemd_ncup](https://github.com/karadogankaan/nanosecond_cpu_usage_plotter/assets/134071144/86eb235d-8201-41ce-b510-bfeb7ba994ae)



