#ifndef INCLUDED_TCP_CHAT_SERVER
#define INCLUDED_TCP_CHAT_SERVER

#include <boost/asio.hpp>
#include <memory>
#include "connection.hpp"

namespace tcp_chat {

namespace asio = boost::asio;
using asio::ip::tcp;

class Server {
    tcp::acceptor acceptor_;
    
    void start_accept();
    void on_accept(std::shared_ptr<Connection> connection,
                   const boost::system::error_code& error);

public:
    Server(asio::io_service& io_service, int port);
    Server(const Server&) = default;
    Server(Server&&) = default;
    Server& operator=(const Server&) = default;
    Server& operator=(Server&&) = default;
    ~Server() = default;
};

} // namespace tcp_chat

#endif
