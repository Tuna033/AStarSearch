# Route Planning Project

This repo contains an implementation of the A* route planner on OpenStreetMap in C++; similiar to 
Google Maps route planner.

The A* algorithm calculates and draws the shortest path from point a to b. The user can specify two coordinate pairs (x, y) fro starting an d end point (between 0 and 100). The map is drawn by the io2d library.

The distance between the two points is returned in meters.

<img src="map.png" width="600" height="450" />

## Cloning

When cloning this project, be sure to use the `--recurse-submodules` flag. Using HTTPS:
```
git clone https://github.com/udacity/CppND-Route-Planning-Project.git --recurse-submodules
```
or with SSH:
```
git clone git@github.com:udacity/CppND-Route-Planning-Project.git --recurse-submodules
```

## Dependencies for Running Locally
* cmake >= 3.11.3
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 7.4.0
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same instructions as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* IO2D
  * Installation instructions for all operating systems can be found [here](https://github.com/cpp-io2d/P0267_RefImpl/blob/master/BUILDING.md)
  * This library must be built in a place where CMake `find_package` will be able to find it

## Compiling and Running

### Compiling
Check out [my detailed setup guide](https://knowledge.udacity.com/questions/42416), which also has a setup for Linux dependencies under the "Test" rubric. 

You need to install io2d and its dependencies first. Under Windows, you can use [vcpkg](https://github.com/microsoft/vcpkg) to do that easily:

```
vcpkg install io2d:x64-windows
```

To compile the project, first, create a `build` directory and change to that directory:

```
mkdir build && cd build
```
From within the `build` directory, then run `cmake` and `make` as follows and change the path to your vcpkg directory:
```
cmake -DCMAKE_TOOLCHAIN_FILE=vcpkg_root/scripts/buildsystems/vcpkg.cmake -DCMAKE_GENERATOR_PLATFORM=x64 ..
make
```
Now the CppND-Route-Planning-Project executable should have been created in the /bin folder.

### Running
The executable will be placed in the `build` directory. From within `build`, you can run the project as follows:
```
./OSM_A_star_search
```
Or to specify a map file:
```
./OSM_A_star_search -f ../<your_osm_file.osm>
```

## Testing

The testing executable is also placed in the `build` directory. From within `build`, you can run the unit tests as follows:
```
./test
```

# AStarSearch
