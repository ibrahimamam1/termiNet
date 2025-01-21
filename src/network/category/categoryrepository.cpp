#include "categoryrepository.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QEventLoop>
#include "../../models/category/category_model.h"
#include "../../../helpers/api_client/apiclient.h"

CategoryRepository::CategoryRepository() {}

QList<CategoryModel> CategoryRepository::getCategories(const QString& filter, const QString& value){
    QList<CategoryModel> result;

    ApiClient& client = ApiClient::getInstance();
    QString url = client.getCategoriesUrl() + filter + "/" + value;

    QEventLoop loop;
    QNetworkReply *reply = client.makeGetRequest(url);
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);

    loop.exec();
    if(reply->error() == QNetworkReply::NoError){
        QByteArray data = reply->readAll();
        QJsonDocument jsonData = QJsonDocument::fromJson(data);

        if (jsonData.isArray()) {
            QJsonArray jsonArray = jsonData.array();

            for (const QJsonValue& jsonValue : jsonArray) {
                if (jsonValue.isObject()) {
                    QJsonObject jsonObject = jsonValue.toObject();

                    // Extract values from the JSON object
                    QString name = jsonObject["category_name"].toString();
                    size_t id = static_cast<size_t>(jsonObject["category_id"].toInt());
                    qDebug() << "Found Category in Json: " << id << " -> " << name;

                    CategoryModel cat(id, name);
                    result.append(cat);
                }
            }
        } else {
            qDebug() << "JSON data is not an array.";
        }
    }else {
        qDebug() << "Network Error";
    }
    return result;
}

QList<CategoryModel> CategoryRepository::getAllCategories(){
    return getCategories("none", "0");
}
QList<CategoryModel> CategoryRepository::getCategoriesForCommunity(size_t community_id){

    return getCategories("community_id", QString::number(community_id));
}
