cmake_minimum_required(VERSION 3.5)
project (Box2D)

file(GLOB COLLISION_FILES "${PROJECT_SOURCE_DIR}/Box2D/Collision/*.cpp")
file(GLOB SHAPES_FILES "${PROJECT_SOURCE_DIR}/Box2D/Collision/Shapes/*.cpp")
file(GLOB COMMON_FILES "${PROJECT_SOURCE_DIR}/Box2D/Common/*.cpp")
file(GLOB CONTACT_FILES "${PROJECT_SOURCE_DIR}/Box2D/Dynamics/Contacts/*.cpp")
file(GLOB JOINT_FILES "${PROJECT_SOURCE_DIR}/Box2D/Dynamics/Joints/*.cpp")
file(GLOB DYNAMICS_FILES "${PROJECT_SOURCE_DIR}/Box2D/Dynamics/*.cpp")
file(GLOB ROPE_FILES "${PROJECT_SOURCE_DIR}/Box2D/Rope/b2Rope.cpp")

add_library(Box2D STATIC ${COLLISION_FILES} ${SHAPES_FILES} ${COMMON_FILES} ${CONTACT_FILES} ${JOINT_FILES} ${DYNAMICS_FILES} ${ROPE_FILES})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_11)
