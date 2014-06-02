#include "server.hpp"
#include <boost/bind.hpp>

namespace tcp_chat {

Server::Server(asio::io_service& io_service, int port)
    : acceptor_(io_service, tcp::endpoint(tcp::v4(), port)) {
    start_accept();
}

void Server::start_accept() {
    std::shared_ptr<Connection> connection = Connection::create(acceptor_.get_io_service());
    acceptor_.async_accept(connection->socket(),
                           boost::bind(&Server::on_accept, this, connection, asio::placeholders::error));
}

void Server::on_accept(std::shared_ptr<Connection> connection,
                       const boost::system::error_code& error) {
    if (!error) {
        connection->run();
    }
    start_accept();
}

} // namespace tcp_chat
