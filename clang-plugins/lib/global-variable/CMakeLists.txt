add_library(my-global-variable-plugin MODULE
  GlobalVariableAction.cpp
)
add_library(my-global-variable STATIC
  GlobalVariableAction.cpp
)

target_include_directories(my-global-variable
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

install(TARGETS my-global-variable DESTINATION lib)