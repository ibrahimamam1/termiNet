#include "websocketclient.h"

std::unique_ptr<WebSocketClient> WebSocketClient::instance = nullptr;

WebSocketClient::WebSocketClient(QObject *parent)
    :m_isConnected(false), QObject{parent}
{
    // Connect WebSocket signals to our slots
    connect(&webSocket, &QWebSocket::connected, this, &WebSocketClient::onConnected);
    //connect(&webSocket, &QWebSocket::disconnected, this, &WebSocketClient::onDisconnected);
    connect(&webSocket, &QWebSocket::errorOccurred,
            this, &WebSocketClient::onError);
    //connect(&webSocket, &QWebSocket::textMessageReceived,
           // this, &WebSocketClient::onTextMessageReceived);
}

WebSocketClient& WebSocketClient::getInstance() {
    if(instance == nullptr)
        instance = std::make_unique<WebSocketClient>();
    return *instance;
}

void WebSocketClient::connectToServer()
{
    qDebug() << "Connecting to:" << url;
    webSocket.open(QUrl(url));
}

bool WebSocketClient::isConnected() const{ return m_isConnected;}


//private slots
void WebSocketClient::onConnected(){
    qDebug() << "Yaaaay we connected to out web socket";
    m_isConnected = true;
    emit connected();
}
void WebSocketClient::onError(QAbstractSocket::SocketError error)
{
    QString errorString = webSocket.errorString();
    qDebug() << "WebSocket error:" << errorString;
    emit errorOccurred(errorString);
}

void WebSocketClient::sendMessage(const QString& message){
    if (m_isConnected) {
        webSocket.sendTextMessage(message);
        qDebug() << "Sent Message";
    } else {
        emit errorOccurred("Not connected to server");
    }
}
