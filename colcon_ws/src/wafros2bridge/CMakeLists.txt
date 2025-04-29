cmake_minimum_required(VERSION 3.8)
project(wafros2bridge)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

# Add your shared library
add_library(${PROJECT_NAME} SHARED
    src/bridge_publisher_string.cpp
    src/bridge_node.cpp
)

ament_target_dependencies(${PROJECT_NAME}
  rclcpp
  std_msgs
)

# Include additional directories
target_include_directories(${PROJECT_NAME}
  PUBLIC
    # Add the path to the include directories (example)
    ${CMAKE_SOURCE_DIR}/include
)

# Link any additional libraries
target_link_libraries(${PROJECT_NAME})

# Install the library
install(TARGETS ${PROJECT_NAME}
  DESTINATION lib
)

ament_package()
