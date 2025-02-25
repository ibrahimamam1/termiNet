cmake_minimum_required(VERSION 3.16)
project(termiNet VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql Network WebSockets NetworkAuth)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql Network WebSockets NetworkAuth)

set(PROJECT_SOURCES
        main.cpp







)

set(PROJECT_RESOURCES
    resources.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(termiNet
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES} ${PROJECT_RESOURCES}























        db/message/messagerepository.h db/message/messagerepository.cpp













        src/db/manager/databasemanager.h src/db/manager/databasemanager.cpp

        src/models/message/messagemodel.h src/models/message/messagemodel.cpp
        src/network/user/user_repository.h src/network/user/user_repository.cpp
        src/models/user/usermodel.h src/models/user/usermodel.cpp
        src/models/user/authenticateduser.h src/models/user/authenticateduser.cpp

        src/common/theme/apptheme.h src/common/theme/apptheme.cpp
        src/common/type/types.h
        src/network/login/loginrepository.h src/network/login/loginrepository.cpp
        src/helpers/validators/formvalidator.h src/helpers/validators/formvalidator.cpp
        resources.qrc
        src/common/widgets/clickable_label.h
        src/network/login/.gitignore
        src/screens/signup/signup.h src/screens/signup/signup.cpp
        src/network/signup/signup_repository.h src/network/signup/signup_repository.cpp
        src/common/widgets/divider.h
        src/common/widgets/socials_widget.h
        src/screens/login/login.h src/screens/login/login.cpp
        src/models/thread/threadmodel.h src/models/thread/threadmodel.cpp
        src/network/threads/threadrepository.h src/network/threads/threadrepository.cpp
        src/screens/home/home.h src/screens/home/home.cpp
        src/screens/home/widgets/createPost/createpost.h src/screens/home/widgets/createPost/createpost.cpp
        src/screens/home/widgets/left_navigation/leftnavigation.h src/screens/home/widgets/left_navigation/leftnavigation.cpp
        src/screens/home/widgets/thread_view/threadview.h src/screens/home/widgets/thread_view/threadview.cpp
        src/screens/home/widgets/thread_view/widgets/thread/threadwidget.h src/screens/home/widgets/thread_view/widgets/thread/threadwidget.cpp
        src/screens/home/widgets/thread_view/widgets/replyBox/replybox.h src/screens/home/widgets/thread_view/widgets/replyBox/replybox.cpp
        src/screens/home/widgets/topBar/topbar.h src/screens/home/widgets/topBar/topbar.cpp
        src/screens/create_community/createcommunity.h src/screens/create_community/createcommunity.cpp
        src/screens/create_community/widgets/category_selection/category_selection_widget.h src/screens/create_community/widgets/category_selection/category_selection_widget.cpp
        src/screens/create_community/widgets/community_description/community_description_widget.h src/screens/create_community/widgets/community_description/community_description_widget.cpp
        src/screens/create_community/widgets/banner_selection/banner_selection_widget.h src/screens/create_community/widgets/banner_selection/banner_selection_widget.cpp
        src/screens/create_community/widgets/category/category_widget.h src/screens/create_community/widgets/category/category_widget.cpp
        src/network/category/categoryrepository.h src/network/category/categoryrepository.cpp
        src/models/category/category_model.h src/models/category/category_model.cpp
        src/screens/community/communitypage.h src/screens/community/communitypage.cpp
        src/screens/community/widgets/community_description_widget.h src/screens/community/widgets/community_description_widget.cpp
        src/models/community/communitymodel.h src/models/community/communitymodel.cpp
        src/network/community/communityrepository.h src/network/community/communityrepository.cpp
        src/common/style/styles.h
        src/screens/profile/profileview.h src/screens/profile/profileview.cpp
        src/screens/search/searchview.h src/screens/search/searchview.cpp
        src/network/search/search_repository.h src/network/search/search_repository.cpp
        src/screens/message/messagepage.h src/screens/message/messagepage.cpp
        src/screens/message/widgets/chat_page/single_message/singlemessage.h src/screens/message/widgets/chat_page/single_message/singlemessage.cpp
        src/screens/message/widgets/chat_page/chatpage.h src/screens/message/widgets/chat_page/chatpage.cpp
        src/screens/message/widgets/create_message/createmessage.h src/screens/message/widgets/create_message/createmessage.cpp
        src/screens/message/widgets/message/messagewidget.h src/screens/message/widgets/message/messagewidget.cpp
        src/screens/message/widgets/message_list_view/messagelistview.h src/screens/message/widgets/message_list_view/messagelistview.cpp
        src/network/api/apiclient.h src/network/api/apiclient.cpp
        src/network/websocket/websocketclient.h src/network/websocket/websocketclient.cpp

        src/helpers/apphelper.h src/helpers/apphelper.cpp


















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

target_link_libraries(termiNet PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql Qt${QT_VERSION_MAJOR}::Network Qt${QT_VERSION_MAJOR}::WebSockets Qt${QT_VERSION_MAJOR}::NetworkAuth)

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
