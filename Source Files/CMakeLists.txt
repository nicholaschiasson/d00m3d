# Specify project files: header files and source files
set(HDR_DIR "${PROJECT_SOURCE_DIR}/Header Files")

set(HDRS
        "${HDR_DIR}/asteroid.h"
        "${HDR_DIR}/black_hole.h"
	"${HDR_DIR}/defines.h"
	"${HDR_DIR}/enemy_spacecraft.h"
	"${HDR_DIR}/entity.h"
	"${HDR_DIR}/mesh_factory.h"
	"${HDR_DIR}/ogre_app_exception.h"
	"${HDR_DIR}/ogre_application.h"
	"${HDR_DIR}/world.h"
	"${HDR_DIR}/camera.h"
	"${HDR_DIR}/input_manager.h"
	"${HDR_DIR}/physics_entity.h"
	"${HDR_DIR}/player_spacecraft.h"
	"${HDR_DIR}/spacecraft.h"
	"${HDR_DIR}/physics_engine.h"
	"${HDR_DIR}/laser.h"
	"${HDR_DIR}/item.h"
)

set(SRCS
    enemy_spacecraft.cpp
        asteroid.cpp
        black_hole.cpp
	asteroid.cpp
	entity.cpp
	main.cpp
        black_hole.material
	asteroid.material
	item.material
	player_spacecraft.material
	red_laser.material
	MaterialFp.glsl
	MaterialFile.material
	MaterialVp.glsl
	mesh_factory.cpp
	ogre_application.cpp
	world.cpp
	camera.cpp
	input_manager.cpp
	physics_entity.cpp
    player_spacecraft.cpp
    spacecraft.cpp
	physics_engine.cpp
	laser.cpp
	item.cpp
)

# The rules here are specific to Windows Systems
if(WIN32)
    # Get Ogre directory from the environment variable
    set(OGRE_HOME $ENV{OGRE_HOME})

    # Set up Ogre include directories
    include_directories(
		"${HDR_DIR}"
        "${OGRE_HOME}/include"
        "${OGRE_HOME}/include/OIS"
        "${OGRE_HOME}/include/OGRE"
        "${OGRE_HOME}/boost"
    )

    # Set up Ogre library directories
    link_directories(
        "${OGRE_HOME}/lib/"
        "${OGRE_HOME}/boost/lib"
    )

    # Applications using Ogre need to be run from inside the Ogre
    # directory. This cmake command needs to come before add_executable
    set(EXECUTABLE_OUTPUT_PATH "${OGRE_HOME}/bin/")

    # Add path name
    configure_file(path_config.h.in path_config.h)

    # Add executable based on the source files
    add_executable(${PROJECT_NAME} ${HDRS} ${SRCS})

    # Set up names of Ogre libraries
    target_link_libraries(${PROJECT_NAME}
        "OgreMain_d.lib"
        "OIS_d.lib"
        "OgreOverlay_d.lib"
    )

    # Avoid ZERO_CHECK target 
    set(CMAKE_SUPPRESS_REGENERATION TRUE)
 
    # This will use the proper libraries in debug mode
    set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX _d)
endif(WIN32)
