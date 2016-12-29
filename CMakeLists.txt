cmake_minimum_required(VERSION 2.6)
project(test_openalpr)

set(OPENALPR_INCLUDE /usr/include)
set(OPENALPR_LIB_DIR /usr/lib)
set(OPENALPR_LIB_FILES openalpr)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

link_directories(${OPENALPR_LIB_DIR})

add_executable(test_openalpr main.cpp)
target_link_libraries(test_openalpr ${OpenCV_LIBS} ${OPENALPR_LIB_FILES})
# install(TARGETS test_openalpr RUNTIME DESTINATION bin)
