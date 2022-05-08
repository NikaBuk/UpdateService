//
// Created by nikasilya on 08.05.22.
//

#ifndef UPDATESERVICE_NETWORKCLIENTCONTROLLER_H
#define UPDATESERVICE_NETWORKCLIENTCONTROLLER_H

#include "Base/NetworkController.h"

class NetworkClientController : public NetworkController {
public:
    NetworkClientController(std::string_view host, uint16_t port);

private:

};


#endif //UPDATESERVICE_NETWORKCLIENTCONTROLLER_H
