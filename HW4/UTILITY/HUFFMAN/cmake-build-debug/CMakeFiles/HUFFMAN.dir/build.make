# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /snap/clion/73/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/73/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/gaporf/ITMO/C++/2 семестр/HW/HW4/UTILITY/HUFFMAN"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/gaporf/ITMO/C++/2 семестр/HW/HW4/UTILITY/HUFFMAN/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/HUFFMAN.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/HUFFMAN.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/HUFFMAN.dir/flags.make

CMakeFiles/HUFFMAN.dir/coder.cpp.o: CMakeFiles/HUFFMAN.dir/flags.make
CMakeFiles/HUFFMAN.dir/coder.cpp.o: ../coder.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/gaporf/ITMO/C++/2 семестр/HW/HW4/UTILITY/HUFFMAN/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/HUFFMAN.dir/coder.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/HUFFMAN.dir/coder.cpp.o -c "/home/gaporf/ITMO/C++/2 семестр/HW/HW4/UTILITY/HUFFMAN/coder.cpp"

CMakeFiles/HUFFMAN.dir/coder.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HUFFMAN.dir/coder.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/gaporf/ITMO/C++/2 семестр/HW/HW4/UTILITY/HUFFMAN/coder.cpp" > CMakeFiles/HUFFMAN.dir/coder.cpp.i

CMakeFiles/HUFFMAN.dir/coder.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HUFFMAN.dir/coder.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/gaporf/ITMO/C++/2 семестр/HW/HW4/UTILITY/HUFFMAN/coder.cpp" -o CMakeFiles/HUFFMAN.dir/coder.cpp.s

CMakeFiles/HUFFMAN.dir/decoder.cpp.o: CMakeFiles/HUFFMAN.dir/flags.make
CMakeFiles/HUFFMAN.dir/decoder.cpp.o: ../decoder.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/gaporf/ITMO/C++/2 семестр/HW/HW4/UTILITY/HUFFMAN/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/HUFFMAN.dir/decoder.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/HUFFMAN.dir/decoder.cpp.o -c "/home/gaporf/ITMO/C++/2 семестр/HW/HW4/UTILITY/HUFFMAN/decoder.cpp"

CMakeFiles/HUFFMAN.dir/decoder.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HUFFMAN.dir/decoder.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/gaporf/ITMO/C++/2 семестр/HW/HW4/UTILITY/HUFFMAN/decoder.cpp" > CMakeFiles/HUFFMAN.dir/decoder.cpp.i

CMakeFiles/HUFFMAN.dir/decoder.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HUFFMAN.dir/decoder.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/gaporf/ITMO/C++/2 семестр/HW/HW4/UTILITY/HUFFMAN/decoder.cpp" -o CMakeFiles/HUFFMAN.dir/decoder.cpp.s

CMakeFiles/HUFFMAN.dir/tree.cpp.o: CMakeFiles/HUFFMAN.dir/flags.make
CMakeFiles/HUFFMAN.dir/tree.cpp.o: ../tree.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/gaporf/ITMO/C++/2 семестр/HW/HW4/UTILITY/HUFFMAN/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/HUFFMAN.dir/tree.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/HUFFMAN.dir/tree.cpp.o -c "/home/gaporf/ITMO/C++/2 семестр/HW/HW4/UTILITY/HUFFMAN/tree.cpp"

CMakeFiles/HUFFMAN.dir/tree.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HUFFMAN.dir/tree.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/gaporf/ITMO/C++/2 семестр/HW/HW4/UTILITY/HUFFMAN/tree.cpp" > CMakeFiles/HUFFMAN.dir/tree.cpp.i

CMakeFiles/HUFFMAN.dir/tree.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HUFFMAN.dir/tree.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/gaporf/ITMO/C++/2 семестр/HW/HW4/UTILITY/HUFFMAN/tree.cpp" -o CMakeFiles/HUFFMAN.dir/tree.cpp.s

# Object files for target HUFFMAN
HUFFMAN_OBJECTS = \
"CMakeFiles/HUFFMAN.dir/coder.cpp.o" \
"CMakeFiles/HUFFMAN.dir/decoder.cpp.o" \
"CMakeFiles/HUFFMAN.dir/tree.cpp.o"

# External object files for target HUFFMAN
HUFFMAN_EXTERNAL_OBJECTS =

libHUFFMAN.a: CMakeFiles/HUFFMAN.dir/coder.cpp.o
libHUFFMAN.a: CMakeFiles/HUFFMAN.dir/decoder.cpp.o
libHUFFMAN.a: CMakeFiles/HUFFMAN.dir/tree.cpp.o
libHUFFMAN.a: CMakeFiles/HUFFMAN.dir/build.make
libHUFFMAN.a: CMakeFiles/HUFFMAN.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/gaporf/ITMO/C++/2 семестр/HW/HW4/UTILITY/HUFFMAN/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library libHUFFMAN.a"
	$(CMAKE_COMMAND) -P CMakeFiles/HUFFMAN.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/HUFFMAN.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/HUFFMAN.dir/build: libHUFFMAN.a

.PHONY : CMakeFiles/HUFFMAN.dir/build

CMakeFiles/HUFFMAN.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/HUFFMAN.dir/cmake_clean.cmake
.PHONY : CMakeFiles/HUFFMAN.dir/clean

CMakeFiles/HUFFMAN.dir/depend:
	cd "/home/gaporf/ITMO/C++/2 семестр/HW/HW4/UTILITY/HUFFMAN/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/gaporf/ITMO/C++/2 семестр/HW/HW4/UTILITY/HUFFMAN" "/home/gaporf/ITMO/C++/2 семестр/HW/HW4/UTILITY/HUFFMAN" "/home/gaporf/ITMO/C++/2 семестр/HW/HW4/UTILITY/HUFFMAN/cmake-build-debug" "/home/gaporf/ITMO/C++/2 семестр/HW/HW4/UTILITY/HUFFMAN/cmake-build-debug" "/home/gaporf/ITMO/C++/2 семестр/HW/HW4/UTILITY/HUFFMAN/cmake-build-debug/CMakeFiles/HUFFMAN.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/HUFFMAN.dir/depend

