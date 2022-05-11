//
// Created by nikasilya on 07.05.22.
//

#include "NetworkClientController.h"

#include <iostream>

NetworkClientController::NetworkClientController(std::string_view host, uint16_t port) {
    std::cout << "NetworkClientController::NetworkClientController" << std::endl;
    endpoint.address(boost::asio::ip::address::from_string(host.data()));
    endpoint.port(port);
}

std::size_t NetworkClientController::send(char *data, size_t size) {
    return socket->send(boost::asio::buffer(data, size));
}

std::size_t NetworkClientController::send(const std::string_view &data) {
    return socket->send(boost::asio::buffer(data.data(), data.size()));
}

std::size_t NetworkClientController::receive(char *data, size_t size) {
    return socket->receive(boost::asio::buffer(data, size));
}

void NetworkClientController::async_send(char *data,
                                         size_t size,
                                         const std::function<
                                                 void(const boost::system::error_code &, size_t)
                                         > &callback) {
    if (callback != nullptr) {
        socket->async_send(boost::asio::buffer(data, size), callback);
    } else {
        throw std::runtime_error("Callback is nullptr");
    }
}

void NetworkClientController::async_receive(char *data,
                                            size_t size,
                                            const std::function<void(const boost::system::error_code &,
                                                                     size_t)> &callback) {
    if (callback != nullptr) {
        socket->async_receive(boost::asio::buffer(data, size), callback);
    } else {
        throw std::runtime_error("Callback is nullptr");
    }
}

bool NetworkClientController::connect() {
//    namespace ssl = boost::asio::ssl;
//    using boost::asio::ip::tcp;
////    //use boost::asio for connect to server
////    boost::asio::ip::tcp::resolver resolver(io_context);
////    boost::asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(endpoint);
////    socket.reset(new boost::asio::ip::tcp::socket(io_context));
////
////    for (auto &item: endpoints) {
////        try {
////            socket->connect(item);
////            return true;
////        } catch (const boost::system::system_error &e) {
////            std::cerr << e.what() << std::endl;
////        }
////    }
//
//    //here we connect with SSL
//    ssl::context ctx(ssl::context::sslv3_client);
////    ctx.set_default_verify_paths();
//    ctx.add_verify_path("/etc/ssl/certs");
//
//    // Get a list of endpoints corresponding to the server name.
//    tcp::resolver resolver(io_context);
//    tcp::resolver::query query("127.0.0.1", "https");
//    tcp::resolver::iterator endpoint_iterator = resolver.resolve(endpoint);
//    ssl_socket ssl_socket_inst(io_context, ctx);
//    boost::asio::connect(ssl_socket_inst.lowest_layer(), endpoint_iterator);
//    ssl_socket_inst.lowest_layer().set_option(tcp::no_delay(true));
//
//    // Perform SSL handshake and verify the remote host's
//    // certificate.
//    ssl_socket_inst.set_verify_mode(ssl::verify_none);
//    ssl_socket_inst.set_verify_callback(ssl::rfc2818_verification("127.0.0.1"));
//    ssl_socket_inst.handshake(ssl_socket::client);
    boost::system::error_code ec;
    using namespace boost::asio;

    // what we need
    io_service svc;
    ssl::context ctx(ssl::context::method::sslv23_client);
    ssl::stream <ip::tcp::socket> ssock(svc, ctx);
    ip::tcp::resolver resolver(svc);
    auto it = resolver.resolve({"127.0.0.1", "8087"}); // http://localhost:8087 for test
    boost::asio::connect(ssock.lowest_layer(), it);
    ssock.handshake(ssl::stream_base::handshake_type::client);

    // send request
    std::string request("GET helloPage HTTP/1.1\r\n\r\n");
    boost::asio::write(ssock, buffer(request));

    // read response
    std::string response;

    do {
        char buf[1024];
        size_t bytes_transferred = ssock.read_some(buffer(buf), ec);
        if (!ec) response.append(buf, buf + bytes_transferred);
    } while (!ec);

    // print and exit
    std::cout << "Response received: '" << response << "'\n";
}


NetworkClientController::~NetworkClientController() {
    std::cout << "NetworkClientController::~NetworkClientController" << std::endl;
}

void NetworkClientController::disconnect() {
    socket->close();
}
