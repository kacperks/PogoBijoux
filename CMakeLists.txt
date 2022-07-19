cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(PB)

add_executable(PB "src/main.cpp" "src/Sound.c")

if(UNIX AND NOT APPLE) # linux
target_link_libraries(PB -lopenal)
target_link_libraries(PB -lsndfile)
target_link_libraries(PB -lIrrlicht -lGL -lGLU -lXxf86vm -lXext -lX11)
endif()

if (WIN32) # windows
target_link_libraries(${PROJECT_NAME} -lopenal-soft)
target_link_libraries(${PROJECT_NAME} -lsndfile)
target_link_libraries(${PROJECT_NAME} -lirrlicht)
endif(WIN32)