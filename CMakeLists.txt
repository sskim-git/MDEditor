cmake_minimum_required(VERSION 3.16)

project(MDEditor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_add_executable(MDEditor
    main.cpp
    MainWindow.h MainWindow.cpp
    MDEditor.h MDEditor.cpp
    MDParser.h MDParser.cpp
    MDPreviewer.h MDPreviewer.cpp
    IMarkdownRule.h
    HeaderRule.h HeaderRule.cpp
    BoldRule.h BoldRule.cpp
    ItalicRule.h ItalicRule.cpp
    ListRule.h ListRule.cpp
    CodeBlockRule.h CodeBlockRule.cpp
)

set_target_properties(MDEditor PROPERTIES
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(MDEditor
    PRIVATE Qt6::Widgets
)

install(TARGETS MDEditor
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
