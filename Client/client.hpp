#ifndef INCLUDED_TCP_CHAT_CLIENT
#define INCLUDED_TCP_CHAT_CLIENT

#include <boost/asio.hpp>
#include <array>

namespace tcp_chat {

namespace asio = boost::asio;
using asio::ip::tcp;

constexpr size_t buf_size = 4096;
constexpr const char* ip_addr = "192.168.11.2";
constexpr int port = 11451;

class Client {
    tcp::socket socket_;
    std::array<char, buf_size> recv_buf_;
    std::string send_data_;

public:
    Client(asio::io_service& io_service) : socket_(io_service) {};
    Client(const Client&) = default;
    Client(Client&&) = default;
    Client& operator=(const Client&) = default;
    Client& operator=(Client&&) = default;
    virtual ~Client() = default;

    void run();

protected:
    void start_connect();
    void start_write();
    void start_receive();
    virtual void on_connect(const boost::system::error_code& error);
    virtual void on_write(const boost::system::error_code& error);
    virtual void on_receive(const boost::system::error_code& error, size_t recv_size);
    virtual void wait_input();
};

} // namespace tcp_chat

#endif
