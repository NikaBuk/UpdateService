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

    void start();

private:


    /**
     * @brief This function is used to receive the list of files to be changed
     */
    virtual void receiveFileList();

    /**
     * @brief This function is used to connect to the server
     * @param ip - address of the server
     * @param port - port of the server
     * @return true if the connection was successful, false otherwise
     */
    bool connect(std::string_view ip, int port);


    void update();
    int get_needed_update_flag();
};