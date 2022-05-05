//
// Created by nikasilya on 03.05.22.
//

#include "UpdateService.h"

int main(){
    UpdateService updateService("127.0.0.1", 8080);
    updateService.start();
    return 0;
}