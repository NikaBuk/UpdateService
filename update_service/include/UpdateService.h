#include <iostream>


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
    UpdateService();
    ~UpdateService();

    /**
     * @brief Connect to the server.
     * @return True if the connection was successful, false otherwise.
     */
    bool connec();

private:

};