
#include "Network/NetworkClientController.h"

#include <iostream>
#include <string_view>

#include <boost/asio.hpp>

/**
 * @brief This class is the main one. 
 * It allows you to connect to some server (remote, local) and receive 
 * from it a list of files to be changed (deleted, added, replaced) 
 * and then receive the files themselves.
 */
class UpdateService
{
public:
    /**
     * @brief Constructor
     * @param hostname The hostname of the server to connect to
     * @param port The port of the server to connect to
     */
    UpdateService(std::string_view ip, int port);

    ~UpdateService();

    /**
     * @brief Main function of the program
     *        It connects to the server, receives the list of files to be changed,
     *        and then receives the files themselves.
     *        It then updates the files and then exits.
     *        If something goes wrong, it prints an error message and exits.
     *
     */
    void start();

private:
    boost::asio::detail::scoped_ptr<NetworkClientController> network_client_controller;
};