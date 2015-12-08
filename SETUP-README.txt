Game setup instructions

Follow installation instructions for Ogre from the Ogre Wiki : http://www.ogre3d.org/tikiwiki/tiki-index.php?page=Installing+the+Ogre+SDK
The 'OGRE_HOME' environment variable is necessary for the project to compile successfully

Using CMake, generate a Visual Studio 11 2012 project with native compilers using the project root as the source directory (.../D00M3D).

Create a folder named 'bin' in the root directory and use this as the binaries folder in cmake (.../D00M3D/bin).

Open project file and set D00M3D as startup project

Build/run the project.