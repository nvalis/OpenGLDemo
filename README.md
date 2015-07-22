# OpenGLDemo
A demo.

## Compiling

### Linux

Get needed packages:

	sudo apt-get install build-essential cmake

Assuming you are in the repos root directory:

	mkdir build
	cd build
	cmake .. # cmake with OpenGLDemo directory as root using the provided CMakeLists.txt
	cd ..
	make
	./Demo

### Windows

Get [CMake](http://www.cmake.org/download/ "Download CMake") for Windows.

Run CMake GUI and navigate to source directory and provide a build directory.
Configure and generate the choosen profile (Subl, Code::Blocks, Eclipse, ...).
Open the generated project file in your IDE and try to compile and run.

