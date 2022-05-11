#include "UpdateService.h"
#include "JSON/JSONController.h"

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <iostream>


UpdateService::~UpdateService() {
    std::cout << "UpdateService::~UpdateService()" << std::endl;
}

UpdateService::UpdateService(std::string_view ip, int port) {
    std::cout << "UpdateService::UpdateService()" << std::endl;
    auto file_future = std::async(std::launch::async, []() -> std::string {
        auto config_file_path = boost::filesystem::path("config.json");

        boost::filesystem::fstream file(config_file_path, std::ios::in);
        if (!file.is_open()) {
            std::cout << "Could not open config.xml" << std::endl;
        }


        std::stringstream file_data;
        file_data << file.rdbuf();

        //here we did it for check json format in file
        return JSONController::check_convertable(file_data.str()) ? file_data.str() : "";
    });

    network_client_controller.reset(new NetworkClientController(ip, port));


    file_future.wait();
    auto json_dump_string = file_future.get();
    if (json_dump_string.empty()) {
        std::cout << "Could not parse config.json" << std::endl;
    }
    network_client_controller->connect();
//    network_client_controller->send(json_dump_string);
}


void UpdateService::start() {
    std::cout << "UpdateService::start()" << std::endl;
}
