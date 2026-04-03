CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g -O2
LDFLAGS = 

TARGET = ultrasonic_with_buzzer
SOURCES = main.cpp GPIO.cpp Ultrasonic.cpp PWM.cpp Buzzer.cpp
OBJECTS = $(SOURCES:.cpp=.o)
HEADERS = GPIO.h Ultrasonic.h PWM.h Buzzer.h

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS) $(LDFLAGS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

run: $(TARGET)
	sudo ./$(TARGET)

rebuild: clean all

.PHONY: all clean run rebuild
