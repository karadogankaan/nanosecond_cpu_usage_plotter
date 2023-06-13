CC = gcc
CFLAGS = -Wall -Wextra

TARGET = ncup
CSV_FILENAME = cpu_usage.csv

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

all: $(TARGET).c
    

clean:
	rm -f $(TARGET) $(CSV_FILENAME)

install: $(TARGET)
	cp $(TARGET) /usr/local/bin
.PHONY: install
