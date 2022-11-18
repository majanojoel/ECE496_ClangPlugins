add_library(my-library-catch-plugin MODULE
  LibraryCatchAction.cpp
)
add_library(my-library-catch STATIC
  LibraryCatchAction.cpp
)

target_include_directories(my-library-catch
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

install(TARGETS my-library-catch DESTINATION lib)