//
// Created by nikasilya on 07.05.22.
//

#ifndef UPDATESERVICE_NetworkClientController_H
#define UPDATESERVICE_NetworkClientController_H


#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/memory_order.hpp>

#include <string_view>

/**
 * @brief The NetworkClientController class use Boost asio
 * library to manage network connections
 */
class NetworkClientController {
public:

    /**
     * @brief Construct a new NetworkClientController object
     * @param host The address to connect to
     * @param port The port to connect to
    */
    NetworkClientController(std::string_view host, uint16_t port);

    /**
     * @brief Destroy the NetworkClientController object
    */
    ~NetworkClientController();

    /**
     * @brief Connect to the server
     * @return connected state
    */
    bool connect();

    /**
     * @brief Disconnect from the server
    */
    void disconnect();

    /**
     * @brief Function that just send data synchronously
     * @param data The data to send
     * @return The number of bytes sent
     */
    std::size_t send(char *data, size_t size);

    std::size_t send(const std::string_view &data);

    /**
     * @brief Function that just receive data synchronously
     * @param data The buffer to store data
     * @param size The size of the buffer
    */
    std::size_t receive(char *data, size_t size);

    /**
     * @brief Function that just send data asynchronously
     * @param data The data to send
     * @param size The size of the data
     * @param callback The callback to call when data is sent
     */
    void async_send(char *data,
                    size_t size,
                    const std::function<void(const boost::system::error_code &, size_t)> &callback);

    /**
     * @brief Function that just receive data asynchronously
     * @param data The buffer to store data
     * @param size The size of the buffer
     * @param callback The callback to call when data is received
     */
    void async_receive(char *data,
                       size_t size,
                       const std::function<void(const boost::system::error_code &, size_t)> &callback);

private:
    boost::asio::io_context io_context;
    boost::asio::detail::scoped_ptr<boost::asio::ip::tcp::socket> socket;

    typedef boost::asio::ssl::stream<boost::asio::ip::tcp::socket> ssl_socket;

    boost::asio::ip::tcp::endpoint endpoint;
};


#endif //UPDATESERVICE_NetworkClientController_H
