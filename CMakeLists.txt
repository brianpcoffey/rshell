CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

ADD_SUBDIRECTORY(googletest)

SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG")

FIND_PACKAGE(Boost COMPONENTS filesystem REQUIRED)
INCLUDE_DIRECTORIES(${BOOST_INCLUDE_DIRS})

ADD_EXECUTABLE(rshell
        src/command.cpp
        src/and.cpp
        src/or.cpp
        src/semi.cpp
        src/append.cpp
        src/out.cpp
        src/redirect.cpp
        src/pipe.cpp
        src/user_input
        src/test.cpp
        src/main.cpp
)

ADD_EXECUTABLE(test
        src/command.cpp
        src/semi.cpp
        src/and.cpp
        src/or.cpp
        src/append.cpp
        src/out.cpp
        src/redirect.cpp
        src/pipe.cpp
        src/user_input
        src/test.cpp
        unit_tests/unit_test.cpp
)

TARGET_LINK_LIBRARIES(test ${Boost_LIBRARIES} )
TARGET_LINK_LIBRARIES(rshell ${Boost_LIBRARIES} )
TARGET_LINK_LIBRARIES(rshell ${Boost_TOKENIZER_LIBRARY})
TARGET_LINK_LIBRARIES(test gtest)
TARGET_LINK_LIBRARIES(test ${Boost_TOKENIZER_LIBRARY})
TARGET_COMPILE_DEFINITIONS(test PRIVATE gtest_disable_pthreads=ON)
