SRC_FILES := $(wildcard *.cpp)
OBJ_FILES := $(patsubst %.cpp,%.o,$(SRC_FILES))
HEADER_FILES := $(wildcard *.h)
LDFLAGS := -g -ggdb -static-libstdc++
CPPFLAGS := -g -ggdb -static-libstdc++
main.exe: $(OBJ_FILES)
   g++ $(LDFLAGS) -o $@ $^
%.o: %.cpp $(HEADER_FILES)
   g++ $(CPPFLAGS) -c -o $@ $<

