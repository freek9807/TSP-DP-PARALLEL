cmake_minimum_required(VERSION 3.1)

project(TSP CXX)

execute_process (
    COMMAND bash -c "sh install.sh"
    OUTPUT_VARIABLE outVar
)

find_package(OpenMP)
set(JSON_BuildTests OFF CACHE INTERNAL "")
set(CURL_LIBRARY "-lcurl") 
set(CMAKE_CXX_FLAGS "-Wall -Wextra -O2")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
find_package(X11 REQUIRED)
link_libraries(${X11_LIBRARIES})
include_directories(${X11_INCLUDE_DIR})
find_package(CURL REQUIRED)
add_subdirectory(${nlohmann_json_source}
   ${CMAKE_CURRENT_BINARY_DIR}/external/json)
add_subdirectory(external/robin-map)
add_executable(TSP main.cpp src/TSP/TSP.cpp src/Location/Location.cpp src/Utils/Utils.cpp src/Proj/Proj.cpp)
include_directories(${CURL_INCLUDE_DIR})
target_link_libraries(TSP nlohmann_json::nlohmann_json)
target_link_libraries(TSP tsl::robin_map)
target_link_libraries(TSP ${CURL_LIBRARIES})
if(OpenMP_CXX_FOUND)
    target_link_libraries(TSP OpenMP::OpenMP_CXX)
endif()
