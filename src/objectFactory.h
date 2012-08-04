/*
    libtsn
    Copyright (C) 2012  Thomas Berger <loki@lokis-chaos.de>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include <json/json.h>

#include "objects.h"

namespace tsn {
  
using namespace objects;


class objectFactory
{

public:
    objectFactory();
    virtual ~objectFactory();

    struct tm api2tm(std::string time);

protected:
    // User Manipulation functions
    /** create User from json values */
    User createUser(Json::Value root);
    /** create "small" User with minimal parameters */
    User createUser(uint64_t id, std::string screen_name) {
      return User(id,screen_name);
    };

    // Entites
    // media manipulation functions
    /** crate Media from json values */
    Media createMedia(Json::Value root);

    /** create Url from json values */
    Url createUrl(Json::Value root);
    
    
};
}

#endif // OBJECTFACTORY_H
