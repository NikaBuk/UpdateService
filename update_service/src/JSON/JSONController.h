//
// Created by nikasilya on 07.05.22.
//

#include "../../third-party/json/json.hpp"

#ifndef UPDATESERVICE_JSONCONTROLLER_H
#define UPDATESERVICE_JSONCONTROLLER_H

#include <string_view>

class JSONController {
public:
    /**
     * @brief Parse JSON string to JSON object
     * @param data JSON string
     * @return JSON object
     */
    static nlohmann::json parse_string(const std::string_view &data);

    /**
     * @brief Parse JSON object to JSON string
     * @param data JSON object
     * @return JSON string
    */
    static std::string parse_object(const nlohmann::json &data);

    /**
     * @brief Check what string is in JSON format
     * @param data JSON string
     * @return true if string is in JSON format
     */
    static bool check_convertable(const std::string_view &data);
};


#endif //UPDATESERVICE_JSONCONTROLLER_H
