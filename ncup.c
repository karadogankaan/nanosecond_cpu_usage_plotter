#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> // System specific libraries(pid_t)
#include <unistd.h> // Operating system services (sleep)
#include <time.h> 


void create_csv_file(const char* filename, int duration, pid_t pid){ 
    FILE* csv_file = fopen(filename, "w"); // It creates the file with the fopen function.
    if (csv_file == NULL) { // If the file cannot be created;
        printf("Dosya oluşturma hatası: %s\n", filename); // Error unable to create file
        return;
    }

    fprintf(csv_file, "Timestamp,User Time (%%),System Time (%%)\n"); // Writing the starting columns in the CSV file in order.

    // Defines the variables for time operations, gives an initial value.
    time_t start_time = time(NULL); // Sets the start time of the program (takes the current time)
    time_t end_time = start_time + duration; // It determines the running time of the program by adding duration to the start time.
    time_t current_time = start_time; // Assigns the current time to the start time during the program duration.

    // It uses the file /proc/[pid]/stat to read statistics about the process.
    while (current_time < end_time) {  // Time values  used to control the loop.
        char stat_filename[50]; //It keeps the path to the /proc/[pid]/stat file created using (pid).
        sprintf(stat_filename, "/proc/%d/stat", pid); // The format specifier %d and the variable 'pid' are placed in this array.
        //The sprintf function creates the path to /proc/[pid]/stat.

        FILE* stat_file = fopen(stat_filename, "r"); // With fopen, it opens the file in the 'stat_file' path in read mode and assigns it to the 'stat_file' variable.
        if (stat_file == NULL) {  // Considering that the file cannot be opened properly;
            printf("Hata: %s dosyası açılamadı.\n", stat_filename); // The error message to be given.
            return; // The loop terminates.
        }

        unsigned long long utime = 0; //  Calculates 'utime' (user time) using statistics information from /proc/[pid]/stat.
        unsigned long long stime = 0; //  Calculates 'stime' (system time) using statistics information from the /proc/[pid]/stat file.

        // The utime and stime variables are used to hold user and system times and are 64-bit integer variables.

        char stat_data[4096]; // The stat_data array is the memory where the data read from the file '/proc/[pid]/stat' is stored. It is '4096' bytes in size.

        fgets(stat_data, sizeof(stat_data), stat_file);  // stat_file means it will read data from file pointer to stat_data string 'sizeof(stat_data)'.
        //  Reads the first line in /proc/[pid]/stat.
        fclose(stat_file);  //finishes the file reading process.

        char* token = strtok(stat_data, " "); // Separates the stat_data string with separators. It uses the strtok function for statistical information.
        // (count) converts the value of the separator (token) to the corresponding variables utime and stime .
        int count = 1;
        while (token != NULL) {  // It continues as long as the token has value.
        // At each step of the loop the 'count' value is checked and the specific (token) value is converted to the appropriate utime and stime.
            if (count == 14) // The variable 'utime' is updated with the value of 'token' converted to 10 with the 'strtoull' function.
                utime = strtoull(token, NULL, 10);
            else if (count == 15)  // The variable 'stime' is updated with the value of 'token' converted to 10 with the 'strtoull' function.
                stime = strtoull(token, NULL, 10);

            token = strtok(NULL, " ");  // The 'strtok' function is called again with the 'NULL' parameter to move to the next space.
            count++; // The count variable is incremented.
            // Loop ends when 'token' value is 'NULL' and gets statistics values.
            //  It performs the process of splitting the data read from the /proc/[pid]/stat file and assigning it to the utime and stime variables using the values of the token in a certain order.
        }

        clock_t total_time = utime + stime; // Total processing time of user and system time.

        double user_percent = (double)utime / total_time * 100; // It expresses the ratio of utime values to the total time as a percentage.
        double system_percent = (double)stime / total_time * 100; // Expresses the ratio of stime values to total time as a percentage.

        fprintf(csv_file, "%ld,%.2lf,%.2lf\n", time(NULL), user_percent, system_percent); // Prints data in the specified format to a CSV file. time(NULL) -&gt; current time information
        // 'user_percent' -&gt; user time percentage, 'system_percent' -&gt; system time percentage.
        usleep(1);  // 1 microsecond wait (delay).
        current_time = time(NULL); // It is updated with the time(NULL) function to get the current time information.
    }

    fclose(csv_file); //The CSV file is closed.
}

// Creates an SVG file using data from the CSV file:
void create_svg_graph(const char* csv_filename, const char* svg_filename) { // The 'crate_svg_graph' function takes as parameters the name of a csv file called 'csv_filename' and the name of the SVG file to be created.
    char command[200]; // The command string contains the command to use to run gnuplot .
    sprintf(command, "gnuplot -e \"set terminal svg; set output '%s'; set datafile separator ','; plot '%s' using 1:2 with lines title 'User Time', '' using 1:3 with lines title 'System Time'\"", svg_filename, csv_filename);
    // The sprintf function creates the command formatted into the 'command' array.
    // With the %s token, the values 'svg_filename' and 'csv_filename' are put into the array.
    system(command); // The system function runs the generated command command by the operating system.
    //Allows the gnuplot program to run.
    // Based on the data in the CSV file. The SVG graphic file is created. Values are indicated by lines.}
}

int main() {
    const char* csv_filename = "cpu_usage.csv";  // The name of the csv file to be created.
    char svg_filename[200]; // Specifies the size of the array.
    time_t current_time = time(NULL); // The variable 'current_time' is defined with the time(NULL) function for current time information.
    sprintf(svg_filename, "Firefox_NCUP_%ld.svg", current_time); // The 'sprintf' function generates the name of the SVG file. The current_time value is placed in its place in the SVG file.
    int duration = 10;  // It will continue for 10 seconds.

    pid_t pid = getpid(); // Gets the PID of the current process.

    create_csv_file(csv_filename, duration, pid); // It saves CPU usage data to csv file.
    create_svg_graph(csv_filename, svg_filename); // Creates an SVG file.

    printf("CSV dosyası '%s' olarak oluşturuldu.\n", csv_filename);
    printf("SVG dosyası '%s' olarak oluşturuldu.\n", svg_filename);
    // The names of the created files are printed on the screen.

    return 0;
}
