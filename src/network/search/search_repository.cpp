#include "search_repository.h"
#include "../../../helpers/api_client/apiclient.h"
#include "../../network/user/user_repository.h"
#include <QEventLoop>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

SearchRepository::SearchRepository() {

}
int SearchRepository::searchFor(const QString& target, QList<ThreadModel>& threads, QList<CommunityModel>& comms, QList<UserModel>& users){
    ApiClient& client = ApiClient::getInstance();
    QString url = client.getSearchUrl() + target;
    QEventLoop loop;
    QNetworkReply *reply = client.makeGetRequest(url);
    qDebug() << "Search Repo made request";
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);

    loop.exec();

    if (reply->error() == QNetworkReply::NoError) {
        qDebug() << "Search Repo received reply with no error";
        QByteArray data = reply->readAll();
        QJsonObject jsonData = QJsonDocument::fromJson(data).object();

        // Parse threads
        if (jsonData.contains("Threads") && jsonData["Threads"].isArray()) {
            QJsonArray threadArray = jsonData["Threads"].toArray();
            for (const QJsonValue& threadValue : threadArray) {
                QJsonObject threadObj = threadValue.toObject();
                QString title = threadObj["thread_title"].toString();
                QString content = threadObj["thread_content"].toString();
                UserModel author = UserRepository::getUserFromId(threadObj["author_id"].toString());
                QString created_at = threadObj["created_at"].toString();
                size_t c_id = static_cast<size_t>(threadObj["community_id"].toInt());
                size_t p_id = static_cast<size_t>(threadObj["parent_thread_id"].toInt());
                size_t t_id = static_cast<size_t>(threadObj["thread_id"].toInt());
                size_t c_count = static_cast<size_t>(threadObj["comment_count"].toInt());
                ThreadModel thread(
                    title, content, author, c_id, p_id, t_id, created_at, c_count
                    );
                threads.append(thread);
            }
        }

        // Parse communities
        if (jsonData.contains("Communities") && jsonData["Communities"].isArray()) {
            QJsonArray communityArray = jsonData["Communities"].toArray();
            for (const QJsonValue& communityValue : communityArray) {
                QJsonObject communityObj = communityValue.toObject();
                QImage communityIcon = QImage::fromData(QByteArray::fromBase64(communityObj["community_icon"].toString().toLatin1()));
                QImage communityBanner = QImage::fromData(QByteArray::fromBase64(communityObj["community_banner"].toString().toLatin1()));
                CommunityModel community(
                    communityObj["community_name"].toString(),
                    communityObj["community_description"].toString(),
                    communityIcon,
                    communityBanner,
                    communityObj["community_id"].toInt(),
                    communityObj["created_at"].toString(),
                    communityObj["member_count"].toInt()
                    );
                comms.append(community);
            }
        }

        // Parse users
        if (jsonData.contains("Users") && jsonData["Users"].isArray()) {
            QJsonArray userArray = jsonData["Users"].toArray();
            for (const QJsonValue& userValue : userArray) {
                QJsonObject userObj = userValue.toObject();
                QString name = userObj["user_name"].toString();
                QString email = userObj["user_email"].toString();
                QString user_id =  userObj["user_id"].toString();
                QDate dob = QDate::fromString(userObj["user_dob"].toString());
                QString bio =  userObj["user_bio"].toString();
                QString created_at = userObj["created_at"].toString();
                QIcon profileImage;
                QString base64Data = userObj["profile_image"].toString();
                QByteArray imageData = QByteArray::fromBase64(base64Data.toUtf8());
                QPixmap pixmap;
                if (pixmap.loadFromData(imageData)) {
                        profileImage = QIcon(pixmap);
                }

                UserModel user(
                    user_id, name, email, dob, bio, created_at, profileImage
                    );
                users.append(user);
            }
        }

        reply->deleteLater();
        return 0; // No error
    } else {
        reply->deleteLater();
        return 1; // Error occurred
    }
}
