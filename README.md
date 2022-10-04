# triangles - a program that lists triangles that intersect with other triangles at least once

### Installing and running

Prerequisites:
1) gtest should be installed on your system
2) cmake should be installed on your system

1. Create an empty folder where you want to build your project (f.e. it is called build)
2. `cd build`
3. run `cmake . `
4. run `make` or `cmake --build`

After following this simple set of instructions all apps are now in `build/apps` in each separate directory. All unit tests are in `build/tests`. Test generation lies in another folder
called `gen-test`

### Generating tests

1. Run `./gen-gen/generator` in build directory
2. Input three numbers: amount of triangles that you want in your test and two bounds for their coordinates.

After that a test file called test.dat is generated directly in build directory. You can run any of the apps using it.

