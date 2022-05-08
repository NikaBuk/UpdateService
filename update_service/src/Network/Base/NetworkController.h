//
// Created by nikasilya on 07.05.22.
//

#ifndef UPDATESERVICE_NETWORKCONTROLLER_H
#define UPDATESERVICE_NETWORKCONTROLLER_H


#include <boost/asio.hpp>
#include <boost/memory_order.hpp>

#include <string_view>

/**
 * @brief The NetworkController class use Boost asio
 * library to manage network connections
 */
class NetworkController {
public:

    /**
     * @brief Construct a new NetworkController object
     * @param host The address to connect to
     * @param port The port to connect to
    */
    NetworkController(std::string_view host, uint16_t port);

    /**
     * @brief Destroy the NetworkController object
    */
    ~NetworkController();

    /**
     * @brief Start controller
     */
    virtual void start() = 0;

    /**
     * @brief Connect to the server
     * @return connected state
    */
    virtual bool connect();

    /**
     * @brief Disconnect from the server
    */
    virtual void disconnect();

    /**
     * @brief Accept a new connection
     */
    virtual void accept();


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
    boost::asio::ip::tcp::endpoint endpoint;
    uint16_t port_;
    boost::asio::ip::address host_;
};


#endif //UPDATESERVICE_NETWORKCONTROLLER_H
