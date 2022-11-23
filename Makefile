CXX=g++
CXXFLAGS=-Wall -Wextra -Werror -O2
CPPFLAGS=-I"C:/Program Files/Mono/include/mono-2.0"
LDFLAGS=-L"C:/Program Files/Mono/lib"
LDLIBS=-l"mono-2.0-sgen"

all: managed.exe mono-test.exe

managed.exe: Test.cs
	mcs Test.cs -out:managed.exe

mono-test.exe: main.cpp
	$(CXX) main.cpp $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS) -o mono-test.exe
