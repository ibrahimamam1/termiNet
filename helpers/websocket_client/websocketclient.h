#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H

#include <QObject>
#include <QWebSocket>
#include "../api_client/apiclient.h"

class WebSocketClient : public QObject
{
    Q_OBJECT
    QWebSocket webSocket;
    bool m_isConnected;
    const QString url = ApiClient::getInstance()->getWebSocketUrl();
    static std::unique_ptr<WebSocketClient> instance;

public:
    explicit WebSocketClient(QObject *parent = nullptr);
    static WebSocketClient& getInstance();
    void connectToServer();
    //void sendMessage(const QString& message);
    bool isConnected() const;
    //void disconnect();

signals:
    void connected();
    //void disconnected();
    //void messageReceived(const QString& message);
    void errorOccurred(const QString& error);

private slots:
    void onConnected();
    //void onDisconnected();
    void onError(QAbstractSocket::SocketError error);
    //void onTextMessageReceived(const QString& message);
};

#endif // WEBSOCKETCLIENT_H
