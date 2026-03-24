# CMakeList.txt : CMake project for game for studying practise, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (CMakeTarget "main.cpp" 
"main.h" 
"Rect.h" 
"Rect.cpp" 
"Vector2.h" 
"RigidBody.h" 
"Stats.h"
"IController.h"
"Entity.h"

 "Weapon.h" "Weapon.cpp" "IEntityPresenter.h" "Entity.cpp" "Floor.h" "PhysicsEngine.h" "PhysicsEngine.cpp" "Floor.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMakeTarget PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if neede
target_link_libraries(CMakeTarget PRIVATE SDL3::SDL3 SDL3_image::SDL3_image)