#include "user_repository.h"

UserRepository::UserRepository() {}
bool UserRepository::addUserToDb(std::string name, std::string email, std::string sex, char* dob, std::string passwd, char* created_at){
    QSqlQuery q;
    int id; //generate a unique id using a stored sequence in database
    if (q.exec("SELECT NEXTVAL('IDSEQ');")) {
        if (q.next()) {
            id = q.value(0).toInt();
        } else {
            qDebug() << "Failed to retrieve the next sequence value.";
            return false;
        }
    } else {
        qDebug() << "Failed to execute the sequence query:" << q.lastError().text();
        return false;
    }

    q.prepare(
        "INSERT into users(user_id, user_name, user_email, user_sex, user_dob, user_bio, passwd, created_at)"
        "values(:user_id, :user_name, :user_email, :user_sex, :user_dob, :user_bio, :passwd, :created_at)"
        );

    q.bindValue(":user_id", id);
    q.bindValue(":user_name",  QString::fromStdString(name));
    q.bindValue(":user_email", QString::fromStdString(email));
    q.bindValue(":user_sex",   QString::fromStdString(sex));
    q.bindValue(":user_dob",   QString::fromStdString(dob));
    q.bindValue(":user_bio",   QString::fromStdString(" "));
    q.bindValue(":passwd",   QString::fromStdString(passwd));
    q.bindValue(":created_at", QString::fromStdString(created_at));

    if (!q.exec()) {
        qDebug() << "Insert failed:" << q.lastError().text();
        return false;
    }
    qDebug() << "Insert successful";
    return true;


}

void UserRepository::readUserFromDb(){
    QSqlQuery query;

    // Execute the SELECT query
    if (query.exec("SELECT user_id, user_name, user_email, user_sex, user_dob, created_at FROM users")) {
        // Iterate over each row in the result set
        while (query.next()) {
            int userId = query.value("user_id").toInt();
            QString userName = query.value("user_name").toString();
            QString userEmail = query.value("user_email").toString();
            QString userSex = query.value("user_sex").toString();
            QString userDob = query.value("user_dob").toString();
            QString createdAt = query.value("created_at").toString();

            // Print the user details
            qDebug() << "User ID:" << userId
                     << "Name:" << userName
                     << "Email:" << userEmail
                     << "Sex:" << userSex
                     << "DOB:" << userDob
                     << "Created At:" << createdAt;
        }
    } else {
        // Print error if the query execution fails
        qDebug() << "Failed to execute query:" << query.lastError().text();
    }
}
