#include "UpdateService.h"
#include <iostream>

UpdateService::~UpdateService() {
    std::cout << "UpdateService::~UpdateService()" << std::endl;
}

UpdateService::UpdateService(std::string_view ip, int port) {

}

bool UpdateService::connect(std::string_view ip, int port) {
    ///use boost for connecting to the server
    boost::asio::io_context io_context;

}

