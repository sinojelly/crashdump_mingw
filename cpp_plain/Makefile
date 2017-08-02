CXXFLAGS += -I../common
CXXFLAGS += -g

.PHONY: clean all

all: crasher.exe dumper.exe

crasher.exe: main_crasher.o crash_handler_register.o
	$(CXX) $(CXXFLAGS) -o $@ $^

dumper.exe: main_dumper.o crash_handler_dump.o
	$(CXX) $(CXXFLAGS) -o $@ $^ -lDbgHelp

main_%.o: main_%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

crash_handler_%.o: ../common/crash_handler_%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.s *.o *.exe
