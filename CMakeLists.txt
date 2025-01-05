cmake_minimum_required(VERSION 3.16)
project(termiNet VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql Network WebSockets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql Network WebSockets)

set(PROJECT_SOURCES
        main.cpp



        login_signup/login.h login_signup/login.cpp
        login_signup/signup.h login_signup/signup.cpp


)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(termiNet
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}

        screens/home/home.h screens/home/home.cpp screens/home/home.ui
        screens/home/home.h screens/home/home.cpp screens/home/home.ui





        login_signup/widgets/divider.h login_signup/widgets/divider.cpp
        login_signup/widgets/socials.h login_signup/widgets/socials.cpp
        screens/widgets/clickablelabel.h

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
        screens/widgets/topbar/customtopbar.h screens/widgets/topbar/customtopbar.cpp
        screens/widgets/leftNavigation/leftnavigationwidget.h screens/widgets/leftNavigation/leftnavigationwidget.cpp

        sql/storage_buckets.sql
        db/storage/storagerepository.h db/storage/storagerepository.cpp
        utils/helper/apphelper.h utils/helper/apphelper.cpp
        screens/widgets/createPost/createpost.cpp
        screens/widgets/createPost/createpost.h
        screens/widgets/thread/threadwidget.h screens/widgets/thread/threadwidget.cpp
        screens/widgets/threadView/threadview.h screens/widgets/threadView/threadview.cpp




        models/thread/threadmodel.h models/thread/threadmodel.cpp
        db/thread/thread_repository.h db/thread/thread_repository.cpp
        screens/community_page/widgets/communitydescriptionwidget.h screens/community_page/widgets/communitydescriptionwidget.cpp
        models/community/communitymodel.h models/community/communitymodel.cpp
        screens/widgets/replyBox/replybox.h screens/widgets/replyBox/replybox.cpp
        screens/message/messagepage.h screens/message/messagepage.cpp
        screens/message/widgets/message_list_view/messagelistview.h screens/message/widgets/message_list_view/messagelistview.cpp

        screens/message/widgets/message/messagewidget.h screens/message/widgets/message/messagewidget.cpp
        db/message/messagerepository.h db/message/messagerepository.cpp
        screens/message/widgets/create_message/createmessage.h screens/message/widgets/create_message/createmessage.cpp

        helpers/api_client/apiclient.h helpers/api_client/apiclient.cpp
        helpers/hash_helper/hashhelper.h helpers/hash_helper/hashhelper.cpp
        helpers/message_client/messageclient.h helpers/message_client/messageclient.cpp
        db/login/loginrepository.h db/login/loginrepository.cpp
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

target_link_libraries(termiNet PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql Qt${QT_VERSION_MAJOR}::Network Qt${QT_VERSION_MAJOR}::WebSockets)

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
