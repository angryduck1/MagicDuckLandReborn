cmake_minimum_required(VERSION 3.16)
cmake_policy(SET CMP0167 NEW)

project(MagicDuckLandReborn LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost 1.73 REQUIRED COMPONENTS system thread)

add_executable(MagicDuckLandReborn main.cpp
    Rc4.h
    Connection.h
    Messaging.h
    Header.h
    LogicMagicMessageFactory.h
    PiranhaMessage.h
    LoginMessage.h
    ByteStream.h
    LogicLong.h
    ChecksumEncoder.h
    LogicLong.cpp
    MessageManager.h
    PiranhaMessage.cpp
    LoginOkMessage.h
    OwnHomeDataMessage.h
    LogicClientHome.h
    LogicClientAvatar.h
    LogicBase.h)

target_include_directories(MagicDuckLandReborn PRIVATE
    ${Boost_INCLUDE_DIRS}
)

target_link_libraries(MagicDuckLandReborn PRIVATE
    ${Boost_LIBRARIES}
    pthread
)

include(GNUInstallDirs)
install(TARGETS MagicDuckLandReborn
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
