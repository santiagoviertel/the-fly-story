# specify the cmake minimum version required
cmake_minimum_required(VERSION 3.3.0)

# specify which version and components you need
find_package(OGRE 1.11 REQUIRED COMPONENTS Bites Terrain RTShaderSystem)

# copy plugins.cfg and resources.cfg next to our binaries where OGRE looks for it
file(COPY ${OGRE_CONFIG_DIR}/plugins.cfg DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${OGRE_CONFIG_DIR}/resources.cfg DESTINATION ${CMAKE_BINARY_DIR})

# open other libraries
set(ZZLIB "/home/santiago/OGRE/build/Dependencies/lib/libzzip.so")

# add the header files path
include_directories(include)

# add the source files as usual
add_executable(main src/main.cpp src/TerrainsManager.cpp)

# this also sets the includes and pulls third party dependencies
target_link_libraries(main ${ZZLIB} OgreBites OgreTerrain OgreRTShaderSystem)