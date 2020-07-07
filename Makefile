CC = g++

CFLAGS = -g

TARGET = muc

all: $(TARGET)
$(TARGET): $(TARGET).cpp
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp
clean:
	$(RM) $(TARGET)