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

## Wiki (because I'm too lazy to make an actual one)
#### Input Manager
###### Description
Wraps functionality of Ogre's own input manager. Allows a user to register many callbacks to a specific key or mouse event.

###### How To Use
For now, this class only uses a prebuilt Ogre::Mouse and Ogre::Keyboard, thus, the initialization of the Ogre::InputManager, Ogre::Mouse, and Ogre::Keyboard must be done before hand.

Instantiate this class by passing an Ogre::Keyboard and an Ogre::Mouse to the constructor. After that is done, callbacks may be registered (or unregistered).

The RegisterCallback and UnregisterCallback functions have the same parameters. They are used to register a specific callback under a specify context to be called on a specific mouse of keyboard event. The callback being registered must take parameters for a context and an Ogre::FrameEvent, since these will be passed to it when its event is triggered. Should there be no intended context for a callback (intended to be a static function), then 0 may be passed in place of the context.

After callbacks have been registered with the input manager, be sure to call its Update method in an appropriate place. The Update method takes an Ogre::FrameEvent as a parameter so the input manager may pass the elapsed time since the last update to its callback functions.

#### Game Controls
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
