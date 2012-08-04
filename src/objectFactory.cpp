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
if (root.isMember(#v) && root[#v].is##type() ) VTARGET._##v = root[#v].as##type ();

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
    if (root.isMember("protected") && root["protected"].isBool() )
        VTARGET._Protected = root["protected"].asBool();
    SET(verified,Bool)

    SET(geo_enabled,Bool)

    SET(follow_request_sent,Bool)
    SET(following,Bool)

    SET(statuses_count,Int)
    SET(favourites_count,Int)
    SET(followers_count,Int)
    SET(friends_count,Int)

    SET(listed_count,Int)

    if (root.isMember("created_at") && root["created_at"].isString() )
        VTARGET._created_at = this->api2tm(root["created_at"].asString() );
#undef VTARGET

    return user;

}

Media objectFactory::createMedia(Json::Value root)
{
    // check that we have at least an id
    if (!root.isMember("id"))
        throw(runtime_error("incomplete dataset")); //TODO create own exception classes

    Media media(root["id"].asLargestInt());
#define VTARGET media
    SET(url,String)
    SET(display_url,String)
    SET(expanded_url,String)

    SET(media_url,String)
    SET(media_url_https,String)


    Json::Value::Members members = root["sizes"].getMemberNames();
    Json::Value::Members::iterator it;
    for(it = members.begin(); it != members.end(); ++it) {
        Media::size_t size;
        size.h = root["sizes"][*it]["h"].asInt();
        size.w = root["sizes"][*it]["w"].asInt();
        string resize = root["sizes"][*it]["resize"].asString();
        if ( resize == "crop" )
            size.resize = Media::crop;
        else if ( resize == "fit" )
            size.resize = Media::fit;

        VTARGET._sizes[*it] = size;
    }
    if ( root.isMember("type") ) {
        string type = root["type"].asString();
        if (type == "photo") {
            VTARGET._type = Media::photo;
        }
    }
    if ( root.isMember("indices") )
        VTARGET._indices = make_pair(root["indices"][0].asInt(),root["indices"][1].asInt());

#undef VTARGET

    return media;
}


Url objectFactory::createUrl(Json::Value root)
{
    // check for the minimum paramter set to checkt that we got realy the data for an url entity
    if (!root.isMember("url") || !root.isMember("expanded_url"))
        throw(runtime_error("incomplete dataset")); //TODO create own exception classes

    Url url(root["url"].asString(),root["expanded_url"].asString());

#define VTARGET url

    SET(display_url,String)

    if ( root.isMember("indices") )
        VTARGET._indices = make_pair(root["indices"][0].asInt(),root["indices"][1].asInt());

#undef VTARGET
    return url;
}
}



}



