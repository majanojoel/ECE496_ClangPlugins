add_library(my-recursive-function-plugin MODULE
  RecursiveFunctionsAction.cpp
)
add_library(my-recursive-function STATIC
  RecursiveFunctionsAction.cpp
)

target_include_directories(my-recursive-function
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

install(TARGETS my-recursive-function DESTINATION lib)