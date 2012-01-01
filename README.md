##Installation Guide##

###0. Prepare your OpenCV environment### 
	Ref:http://www.samontab.com/web/2011/06/installing-opencv-2-2-in-ubuntu-11-04/)

###1. Prepare the CMake build environment### 
	$ sudo apt-get install cmake

###2. Clone the project to local###
	$ git clone git@github.com:browny/filtersFun.git
	$ cd filterFun

###3. Take out-of-source CMake build###
	$ mkdir release
	$ cd release
	$ cmake ..
	$ make

###4. Enjoy###
	$ cd bin
	$ ./main test.jpg

###5. Exit###
	Press 'Esc' to close window and quit
