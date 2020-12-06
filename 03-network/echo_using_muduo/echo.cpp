#include "muduo/net/TcpServer.h"
#include "muduo/net/EventLoop.h"
#include "muduo/base/Logging.h"
#include <functional>

class echoServer 
{
private:
    void onConnection(const muduo::net::TcpConnectionPtr &conn);
    void onMessage(const muduo::net::TcpConnectionPtr &conn, muduo::net::Buffer* buf, muduo::Timestamp time);
    muduo::net::EventLoop* loop_;
    muduo::net::TcpServer server_;
public:
    echoServer(muduo::net::EventLoop *loop, const muduo::net::InetAddress &listenAddr);
    ~echoServer()=default;
    void start();
};

using namespace std::placeholders;

echoServer::echoServer(muduo::net::EventLoop *loop, const muduo::net::InetAddress &listenAddr)
    : loop_(loop), server_(loop, listenAddr, "EchoServer")
{
    server_.setConnectionCallback(std::bind(&echoServer::onConnection, this, _1));
    server_.setMessageCallback(std::bind(&echoServer::onMessage, this, _1, _2, _3));
}

void echoServer::onConnection(const muduo::net::TcpConnectionPtr &conn)
{
    LOG_INFO << "echoServer - " << conn->peerAddress().toIpPort() << " -> "
             << conn->localAddress().toIpPort() << " is "
             << (conn->connected() ? "UP" : "DOWN");
}


void echoServer::onMessage(const muduo::net::TcpConnectionPtr &conn, muduo::net::Buffer* buf, muduo::Timestamp time)
{
    muduo::string msg(buf->retrieveAllAsString());
    LOG_INFO << conn->name() << " echo " << msg.size() << "bytes, "
             << "data received at " << time.toString();
    conn->send(msg);
}

void echoServer::start()
{
    server_.start();
}

int main()
{
    muduo::net::EventLoop loop;
    muduo::net::InetAddress listenAddr(2007);
    echoServer server(&loop, listenAddr);
    server.start();
    loop.loop();
}


