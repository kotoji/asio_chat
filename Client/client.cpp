#include "client.hpp"
#include <boost/bind.hpp>
#include <string>
#include <iostream>

namespace tcp_chat {

void Client::run() {
    start_connect();
}

void Client::start_connect() {
    socket_.async_connect(
        tcp::endpoint(asio::ip::address::from_string(ip_addr), port),
        boost::bind(&Client::on_connect, this, asio::placeholders::error));
}

void Client::on_connect(const boost::system::error_code& error) {
    if (!error) {
        wait_input();
    } else {
        std::cout << "connection failed." << std::endl;
    }
}

void Client::start_write() {
    asio::async_write(socket_, asio::buffer(send_data_),
                      boost::bind(&Client::on_write, this,
                                  asio::placeholders::error));
}

void Client::on_write(const boost::system::error_code& error) {
    if (!error) {
        start_receive();
    } else {
        std::cout << "send failed." << std::endl;
        wait_input();
    }
}

void Client::start_receive() {
    socket_.async_receive(asio::buffer(recv_buf_),
                          boost::bind(&Client::on_receive, this,
                                      asio::placeholders::error,
                                      asio::placeholders::bytes_transferred));
}

void Client::on_receive(const boost::system::error_code& error, size_t recv_size) {
    if (!error) {
        std::string recv_data = std::string(std::begin(recv_buf_), std::begin(recv_buf_) + recv_size);
        std::cout << "res: " << recv_data << std::endl;
        wait_input();
    } else {
        std::cout << "receive failed." << std::endl;
        wait_input();
    }
}

void Client::wait_input() {
    std::cout << "*input send messsage*" << std::endl;
    std::cin >> send_data_;
    std::cout << "sending ..." << std::endl;
    start_write();
}

} // namespace tcp_chat
