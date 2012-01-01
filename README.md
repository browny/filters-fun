Installation Guide
--

Prepare your OpenCV environment 
---
   [Installing Opencv2.2 in Ubuntu 11.04](http://www.samontab.com/web/2011/06/installing-opencv-2-2-in-ubuntu-11-04/)

Prepare the CMake build environment
---
	$ sudo apt-get install cmake

Clone the project to local
---
	$ git clone git@github.com:browny/filtersFun.git
	$ cd filterFun

Take out-of-source CMake build
---
	$ mkdir release
	$ cd release
	$ cmake ..
	$ make

Enjoy
---
	$ cd bin
	$ ./main test.jpg

Exit
---
	Press 'Esc' to close window and quit
