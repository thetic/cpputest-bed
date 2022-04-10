cmake_minimum_required(VERSION 3.17)

project(cpputest-bed
  LANGUAGES CXX C
)

include(CTest)


# PRODUCTION CODE
# This should build as if CppUTest doesn't exist.
add_library(ApplicationLib
  ApplicationLib/CircularBuffer.cpp
  ApplicationLib/EventDispatcher.cpp
  ApplicationLib/hello.c
  ApplicationLib/Printer.cpp
)

target_include_directories(ApplicationLib
  PUBLIC
    ApplicationLib
)

add_executable(Application
  Application/main.cpp
)

target_link_libraries(Application
  PRIVATE
    ApplicationLib
)


if(BUILD_TESTING)

  # CppUTest should behave consistently, regardless of integration method.
  set(VERBOSE_CONFIG OFF)
  if(INTEGRATION_METHOD STREQUAL "find_package")
    find_package(CppUTest REQUIRED)
  elseif(INTEGRATION_METHOD STREQUAL "add_subdirectory")
    add_subdirectory(cpputest)
  elseif(INTEGRATION_METHOD STREQUAL "FetchContent")
    include(FetchContent)
    FetchContent_Declare(cpputest
      GIT_REPOSITORY https://github.com/cpputest/cpputest.git
      GIT_TAG        latest-passing-build
    )
    FetchContent_MakeAvailable(cpputest)
  else()
    message(FATAL_ERROR "Invalid INTEGRATION_METHOD \"${INTEGRATION_METHOD}\"")
  endif()

  add_executable(Tests
    Tests/AllTests.cpp
    Tests/CircularBufferTest.cpp
    Tests/EventDispatcherTest.cpp
    Tests/FEDemoTest.cpp
    Tests/HelloTest.cpp
    Tests/MockDocumentationTest.cpp
    Tests/PrinterTest.cpp
  )

  target_include_directories(Tests
    PRIVATE
      Tests
    )

  target_link_libraries(Tests
    PRIVATE
      ApplicationLib
      CppUTest::CppUTestExt
  )

  cpputest_buildtime_discover_tests(Tests)
endif()
