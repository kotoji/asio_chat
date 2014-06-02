#ifndef INCLUDED_TCP_CHAT_CONNECTION
#define INCLUDED_TCP_CHAT_CONNECTION

#include <boost/asio.hpp>
#include <array>
#include <memory>

namespace tcp_chat {

namespace asio = boost::asio;
using asio::ip::tcp;

constexpr size_t recv_buf_size = 4096;

class Connection : public std::enable_shared_from_this<Connection> {
    tcp::socket socket_;
    std::array<char, recv_buf_size> recv_buf_;
   
public: // it should be private 
    Connection(asio::io_service& io_service) : socket_(io_service) {}
    Connection(const Connection&) = delete;
    Connection(Connection&&) = delete;
    Connection& operator=(const Connection&) = delete;
    Connection& operator=(Connection&&) = delete;
    ~Connection() = default;

public:
    static std::shared_ptr<Connection> create(asio::io_service& io_service) {
        return std::make_shared<Connection>(io_service);
    }
    
    void run();
    void start_receive();
    void start_write();
    void on_receive(const boost::system::error_code& error, size_t recv_size);
    void on_write(const boost::system::error_code& error);
    
    tcp::socket& socket() { return socket_; }
};

} // namespace tcp_chat

#endif
