# See the build system documentation in IDF programming guide
# for more information about component CMakeLists.txt files.

idf_component_register(
    SRCS main.c st7789.c # list the source files of this component
    INCLUDE_DIRS lvgl   # optional, add here public include directories
    PRIV_INCLUDE_DIRS   # optional, add here private include directories
    REQUIRES            # optional, list the public requirements (component names)
    PRIV_REQUIRES       # optional, list the private requirements
)


target_include_directories(${COMPONENT_LIB} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/path/to/lvgl)
#include_directories(${CMAKE_CURRENT_LIST_DIR}/path/to/lvgl)
#target_link_libraries(${COMPONENT_LIB} PRIVATE lvgl)

#target_include_directories(${COMPONENT_LIB} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/lvgl)
#include_directories(${CMAKE_CURRENT_LIST_DIR}/lvgl)
#target_link_libraries(${COMPONENT_LIB} PRIVATE lvgl)