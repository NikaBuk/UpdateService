//
// Created by nikasilya on 07.05.22.
//

#include "NetworkController.h"

#include <iostream>

NetworkController::NetworkController(std::string_view host, uint16_t port)
        : port_(port), host_(boost::asio::ip::make_address_v4(host)) {
    std::cout << "NetworkController::NetworkController" << std::endl;
    endpoint.address(host_);
    endpoint.port(port_);
}

std::size_t NetworkController::send(char *data, size_t size) {
    return socket->send(boost::asio::buffer(data, size));
}

std::size_t NetworkController::send(const std::string_view &data) {
    return socket->send(boost::asio::buffer(data.data(), data.size()));
}

std::size_t NetworkController::receive(char *data, size_t size) {
    return socket->receive(boost::asio::buffer(data, size));
}

void NetworkController::async_send(char *data,
                                   size_t size,
                                   const std::function<void(const boost::system::error_code &, size_t)> &callback) {
    if (callback != nullptr) {
        socket->async_send(boost::asio::buffer(data, size), callback);
    } else {
        throw std::runtime_error("Callback is nullptr");
    }
}

void NetworkController::async_receive(char *data,
                                      size_t size,
                                      const std::function<void(const boost::system::error_code &, size_t)> &callback) {
    if (callback != nullptr) {
        socket->async_receive(boost::asio::buffer(data, size), callback);
    } else {
        throw std::runtime_error("Callback is nullptr");
    }
}

bool NetworkController::connect() {
    //use boost::asio for connect to server
    boost::asio::ip::tcp::resolver resolver(io_context);
    boost::asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(endpoint);
    socket.reset(new boost::asio::ip::tcp::socket(io_context));

    for (auto &endpoint: endpoints) {
        try {
            socket->connect(endpoint);
            return true;
        } catch (const boost::system::system_error &e) {
            std::cerr << e.what() << std::endl;
        }
    }
}


NetworkController::~NetworkController() {
    std::cout << "NetworkController::~NetworkController" << std::endl;
}

void NetworkController::disconnect() {
    socket->close();
}

void NetworkController::accept() {
    boost::asio::ip::tcp::acceptor acceptor(io_context, endpoint);
    acceptor.accept(*socket);
}
