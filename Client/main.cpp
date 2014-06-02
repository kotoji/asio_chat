#include "client.hpp"
#include <boost/asio.hpp>
#include <memory>

using namespace tcp_chat;

int main(int argc, char* argv[]) {
    asio::io_service io_service;
    std::shared_ptr<Client> client = std::make_shared<Client>(io_service);
    client->run();
    io_service.run();
}
