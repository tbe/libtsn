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


#ifndef OAUTHCLIENT_H
#define OAUTHCLIENT_H

#include <stdlib.h>

extern "C" {
#include <oauth.h>
}

#include <string>
#include <map>

class OAuthClient
{

public:
    /**
     * OAuth Signed Post request
     */
    typedef struct {
        std::string url;
        std::string postdata;
    } signed_POST_t;
    
    /**
     * POST Argument list
     */
    typedef std::map<std::string,std::string> postargs_t;

    /**
     * OAuthClient constructor
     *
     * @param ckey Consumer Key
     * @param csec Consumer Secret
     * @param tkey Token Key
     * @param tsec Token Secret
     * @param method OAuthMethod for all generated signatures
     */
    OAuthClient(std::string ckey, std::string csec, std::string tkey, std::string tsec,OAuthMethod method = OA_HMAC);
    virtual ~OAuthClient();

    /**
     * sign a GET request
     *
     * @param url Full URL with all GET arguments
     * @return the signed URL
     */
    std::string   signGET (std::string url);

    /**
     * sign a POST request
     *
     * @param url Full URL for the POST request
     * @param postargs List of all POST arguments
     * @return the signed POST request
     */
    signed_POST_t signPOST(std::string url,postargs_t postargs);

private:
    std::string ckey;
    std::string csec;
    std::string tkey;
    std::string tsec;
    OAuthMethod method;
};

#endif // OAUTHCLIENT_H
