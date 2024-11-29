cmake_minimum_required(VERSION 3.16)
project(termiNet VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        login_signup/login.h login_signup/login.cpp
        login_signup/signup.h login_signup/signup.cpp
        db/databasemanager.h db/databasemanager.cpp

)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(termiNet
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        db/user_repository.h db/user_repository.cpp
        screens/home/home.h screens/home/home.cpp screens/home/home.ui
        screens/home/home.h screens/home/home.cpp screens/home/home.ui
        screens/widgets/createpost.h screens/widgets/createpost.cpp
        models/usermodel.h models/usermodel.cpp
        db/thread_repository.h db/thread_repository.cpp
        models/threadmodel.h models/threadmodel.cpp
        screens/widgets/threadwidget.h screens/widgets/threadwidget.cpp
        login_signup/widgets/divider.h login_signup/widgets/divider.cpp
        login_signup/widgets/socials.h login_signup/widgets/socials.cpp
        screens/widgets/clickablelabel.h

        screens/create_community/createcommunity.h
        screens/create_community/createcommunity.cpp






    )
else()
    if(ANDROID)
        add_library(termiNet SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(termiNet
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(termiNet PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql)

if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.termiNet)
endif()

set_target_properties(termiNet PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS termiNet
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(termiNet)
endif()
