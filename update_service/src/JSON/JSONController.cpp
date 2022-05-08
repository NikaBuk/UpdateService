//
// Created by nikasilya on 07.05.22.
//

#include "JSONController.h"

#include <iostream>

nlohmann::json JSONController::parse_string(const std::string_view &data) {
    nlohmann::json json;

    try {
        json = nlohmann::json::parse(data);
    } catch (nlohmann::json::parse_error &e) {
        std::cerr << "JSON parse error: " << e.what() << std::endl;
    }

    return json;
}

std::string JSONController::parse_object(const nlohmann::json &data) {
    std::string string_json;

    try {
        string_json = data.dump();
    } catch (nlohmann::json::parse_error &e) {
        std::cerr << "JSON parse error: " << e.what() << std::endl;
    }

    return string_json;
}

bool JSONController::check_convertable(const std::string_view &data) {
    if (!nlohmann::json::accept(data)) {
        std::cerr << "Data is not convertable to JSON!" << std::endl;
        return false;
    }
    return true;
}
