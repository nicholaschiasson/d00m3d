# d00m3d
COMP3501 Term Group Project

### Requirements
- Visual C++ 2012 compiler
- CMake
- Ogre 1.9 SDK for Visual C++ 2012 (32-bit)

### Setup
1. Follow installation instructions for Ogre from the [Ogre Wiki](http://www.ogre3d.org/tikiwiki/tiki-index.php?page=Installing+the+Ogre+SDK)
  - The 'OGRE_HOME' environment variable is necessary for the project to compile successfully
2. Using CMake, generate a Visual Studio 11 2012 project with native compilers using the project root as the source directory, and a binaries directory of your choosing
3. Open the generated solution (.sln) file in Visual Studio 11 and set **this** project as the startup project
  - By default the startup project is the ALL_BUILD project - this is not what we want
4. Confirm that the project is configured properly by following the instructions [here](http://www.ogre3d.org/tikiwiki/Setting+Up+An+Application+-+Visual+Studio#Project_Configuration)
5. At this point, the project should be ready to be modified, built, and run

### Game Controls
- W            - Forward thrusters
- A            - Left thrusters
- S            - Backward thrusters
- D            - Right thrusters
- Q            - Upward thrusters
- C            - Downward thrusters
- UP           - Pitch up (also mouse up)
- LEFT         - Yaw left (also mouse left)
- DOWN         - Pitch down (also mouse down)
- RIGHT        - Yaw right (also mouse right)
- V            - Roll counter clockwise
- B            - Roll clockwise
- Scroll Wheel - Change camera perspective (scroll in toward first person perspective; scroll out toward third person perspective)
- SPACE        - Fire weapon
- 1            - Switch to laser cannon
- 2            - Switch to plasma cannon
- 3            - Switch to black hole cannon
- Esc          - Exit game
