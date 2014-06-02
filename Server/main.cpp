#include "server.hpp"
#include <boost/asio.hpp>
#include <memory>

using namespace tcp_chat;

int main(int argc, char* argv[]) {
    asio::io_service io_service;
    std::shared_ptr<Server> server = std::make_shared<Server>(io_service, 11451);
    io_service.run();
}
