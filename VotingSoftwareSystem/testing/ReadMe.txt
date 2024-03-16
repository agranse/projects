GoogleTests was set up using the "Quickstart: CMake" tutorial from
GoolgleTest github repo. You can find the tutorial at 
https://google.github.io/googletest/quickstart-cmake.html

The framework was set up to test anything included into the test.cc file
that is located in the testing directory. To test, include the file you want 
to test within the test.cc file. You also need to add the .cc and .h file
to the CMakeLists.txt, under the 'add executables' section. To run the 
test, run make in the terminal while in the repo-Team5/Project2/testing directory. 

If you are having trouble with cmake, delete repo-Team5/Project2/testing/build directory 
and run make again. The makefile creates a build directory that is specific to each machine.
If you are ever having any issues, delete this build directoru and rebuild by running make.  

Make sure you are in the testing folder before you run make. 