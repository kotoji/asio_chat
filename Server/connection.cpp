#include "connection.hpp"
#include <boost/bind.hpp>
#include <string>

namespace tcp_chat {

void Connection::run() {
    // start Connection
    start_receive();
}

void Connection::start_receive() {
    socket_.async_receive(asio::buffer(recv_buf_),
                          boost::bind(&Connection::on_receive, shared_from_this(),
                                      asio::placeholders::error,
                                      asio::placeholders::bytes_transferred));
}

void Connection::on_receive(const boost::system::error_code& error, size_t recv_size) {
    if (!error) {
        { // test
            std::string message(recv_buf_.data(), recv_size);
            std::cout << message << std::endl;
        }
        // responce to client
        start_write();
    }
    // continue connection
    start_receive();
}

void Connection::start_write() {
    std::shared_ptr<std::string> send_buf = std::make_shared<std::string>("hoge."); // test
    asio::async_write(socket_, asio::buffer(*send_buf),
                     boost::bind(&Connection::on_write, shared_from_this(),
                                 asio::placeholders::error));
}

void Connection::on_write(const boost::system::error_code& error) {
    // 
}

} // namespace tcp_chat
