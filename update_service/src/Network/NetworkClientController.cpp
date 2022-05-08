//
// Created by nikasilya on 08.05.22.
//

#include "NetworkClientController.h"

#include <iostream>

void NetworkClientController::start() {

}

NetworkClientController::NetworkClientController(std::string_view host, uint16_t port) :
        NetworkController(host, port) {
    std::cout << "NetworkClientController::NetworkClientController" << std::endl;
}
