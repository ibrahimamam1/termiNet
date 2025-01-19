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

        screens/create_community/createcommunity.h
        screens/create_community/createcommunity.cpp
        screens/styles/buttonStyles.h
        screens/create_community/widgets/categorywidget.h screens/create_community/widgets/categorywidget.cpp
        screens/create_community/pages/categoryselectionscreen.h screens/create_community/pages/categoryselectionscreen.cpp
        models/categorymodel.h models/categorymodel.cpp
        db/category_repository.h db/category_repository.cpp
        screens/create_community/pages/comunitydescriptionpage.h screens/create_community/pages/comunitydescriptionpage.cpp
        screens/create_community/pages/communitybannerpage.h screens/create_community/pages/communitybannerpage.cpp

        db/communityrepository.h db/communityrepository.cpp
        screens/community_page/communitypage.h screens/community_page/communitypage.cpp



        sql/storage_buckets.sql
        db/storage/storagerepository.h db/storage/storagerepository.cpp
        utils/helper/apphelper.h utils/helper/apphelper.cpp










        screens/community_page/widgets/communitydescriptionwidget.h screens/community_page/widgets/communitydescriptionwidget.cpp
        models/community/communitymodel.h models/community/communitymodel.cpp

        screens/message/messagepage.h screens/message/messagepage.cpp
        screens/message/widgets/message_list_view/messagelistview.h screens/message/widgets/message_list_view/messagelistview.cpp

        screens/message/widgets/message/messagewidget.h screens/message/widgets/message/messagewidget.cpp
        db/message/messagerepository.h db/message/messagerepository.cpp
        screens/message/widgets/create_message/createmessage.h screens/message/widgets/create_message/createmessage.cpp

        helpers/api_client/apiclient.h helpers/api_client/apiclient.cpp
        helpers/hash_helper/hashhelper.h helpers/hash_helper/hashhelper.cpp
        helpers/message_client/messageclient.h helpers/message_client/messageclient.cpp

        screens/message/widgets/chat_page/singleMessage/singlemessage.h screens/message/widgets/chat_page/singleMessage/singlemessage.cpp
        screens/message/widgets/chat_page/chatpage.h screens/message/widgets/chat_page/chatpage.cpp
        helpers/apphelper.h helpers/apphelper.cpp

        helpers/websocket_client/websocketclient.h helpers/websocket_client/websocketclient.cpp


        src/db/manager/databasemanager.h src/db/manager/databasemanager.cpp

        src/models/message/messagemodel.h src/models/message/messagemodel.cpp
        src/network/user/user_repository.h src/network/user/user_repository.cpp
        src/models/user/usermodel.h src/models/user/usermodel.cpp
        src/models/user/authenticateduser.h src/models/user/authenticateduser.cpp
        screens/profile_view/profileview.h screens/profile_view/profileview.cpp
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
