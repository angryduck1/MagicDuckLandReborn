cmake_minimum_required(VERSION 3.16)
cmake_policy(SET CMP0167 NEW)

project(MagicDuckLandReborn LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost 1.73 REQUIRED COMPONENTS system thread)

add_executable(MagicDuckLandReborn main.cpp
    Titan/RC4/Rc4.h
    Server/Connection.h
    Server/Messaging.h
    Server/Header.h
    Logic/LogicMagicMessageFactory.h
    Titan/PiranhaMessage.h
    Logic/Login/LoginMessage.h
    Titan/ByteStream.h
    Titan/LogicLong.h
    Titan/ChecksumEncoder.h
    Titan/LogicLong.cpp
    Server/MessageManager.h
    Titan/PiranhaMessage.cpp
    Logic/Login/LoginOkMessage.h
    Logic/Home/OwnHomeDataMessage.h
    Logic/Home/LogicClientHome.h
    Logic/Home/LogicClientAvatar.h
    Logic/LogicBase.h
    Logic/Commands/EndClientTurnMessage.h
    Logic/Commands/LogicCommandManager.h
    Logic/Commands/LogicCommand.h
    Logic/Commands/LogicBuyBuildingCommand.h
    Logic/Name/ChangeAvatarNameMessage.h)

target_include_directories(MagicDuckLandReborn PRIVATE
    ${Boost_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/Titan
    ${CMAKE_SOURCE_DIR}/Server
    ${CMAKE_SOURCE_DIR}/Logic
    ${CMAKE_SOURCE_DIR}/Titan/RC4
    ${CMAKE_SOURCE_DIR}/Logic/Home
    ${CMAKE_SOURCE_DIR}/Logic/Login
    ${CMAKE_SOURCE_DIR}/Logic/Commands
    ${CMAKE_SOURCE_DIR}/Logic/Name
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
