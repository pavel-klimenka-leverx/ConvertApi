cmake_minimum_required(VERSION 3.22)
project(ConvertApi VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

### Put the names of your source files here ###
set(SRC_FILES 
    main.cpp
    file_format.hpp file_format.cpp
    libreoffice_service.hpp libreoffice_service.cpp
    logger.hpp
    cors_middleware.hpp cors_middleware.cpp
)

list(TRANSFORM SRC_FILES PREPEND "src/")

add_executable(${PROJECT_NAME} ${SRC_FILES})

set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX -d)

### Add link directories here ###
if (WIN32)
    target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/external/lib/windows)
else()
    target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/external/lib/linux)
endif()

### Add include directories here ###
target_include_directories(${PROJECT_NAME} PRIVATE external external/crow)

### Uncomment this line if you want the standard libraries to be linked statically ###
# target_link_options(${PROJECT_NAME} PRIVATE -static-libgcc -static-libstdc++)

### Use this line to link external libraries
set(CROSSGUID_LIB debug crossguid-dgb optimized crossguid)
set(FMT_LIB debug fmtd optimized fmt)
target_link_libraries(${PROJECT_NAME} ${CROSSGUID_LIB} ${FMT_LIB})

if (UNIX)
    target_link_libraries(${PROJECT_NAME} uuid)
endif()