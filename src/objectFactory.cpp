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

#define _XOPEN_SOURCE
#include "objectFactory.h"
#include <stdexcept>
using namespace std;

const char* TIME_FORMAT = "%a %b %d %T %z %Y";

namespace tsn {

#define SET(v,type) \
if (VSOURCE.isMember(#v) && VSOURCE[#v].is##type() ) VTARGET._##v = VSOURCE[#v].as##type ();

objectFactory::objectFactory()
{

}

objectFactory::~objectFactory()
{

}

inline struct tm objectFactory::api2tm(string time)
{
  struct tm date;
  strptime(time.c_str(),TIME_FORMAT,&date);
  return date;
}


User objectFactory::createUser(Json::Value root)
{
    // check for needed values to construct an object
    if (!root.isMember("id") || !root.isMember("screen_name"))
        throw(runtime_error("incomplete dataset")); //TODO create own exception classes

    User user(root["id"].asLargestInt(),root["screen_name"].asString());
    // check for the values availible and set them within the object
#define VSOURCE root
#define VTARGET user

    SET(name,String)
    SET(profile_background_color,String)
    SET(profile_background_image_url,String)
    SET(profile_background_image_url_https,String)
    SET(profile_image_url,String)
    SET(profile_image_url_https,String)
    SET(profile_link_color,String)
    SET(profile_sidebar_border_color,String)
    SET(profile_sidebar_fill_color,String)
    SET(profile_text_color,String)
    SET(description,String)
    SET(url,String)

    SET(default_profile,Bool)
    SET(default_profile_image,Bool)
    SET(profile_background_tile,Bool)


    SET(profile_use_background_image,Bool)

    //SET(protected,Bool)
    if (VSOURCE.isMember("protected") && VSOURCE["protected"].isBool() )
      VTARGET._Protected = VSOURCE["protected"].asBool();
    SET(verified,Bool)

    SET(geo_enabled,Bool)

    SET(follow_request_sent,Bool)
    SET(following,Bool)

    SET(statuses_count,Int)
    SET(favourites_count,Int)
    SET(followers_count,Int)
    SET(friends_count,Int)

    SET(listed_count,Int)

    if (VSOURCE.isMember("created_at") && VSOURCE["created_at"].isString() )
      VTARGET._created_at = this->api2tm(VSOURCE["created_at"].asString() );
#undef VSOURCE
#undef VTARGET

    return user;

}


}



