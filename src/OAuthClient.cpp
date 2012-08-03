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


#include "OAuthClient.h"

#include <string.h>
#include <sstream>

using namespace std;

OAuthClient::OAuthClient(string ckey, string csec, string tkey, string tsec, OAuthMethod method)
    :ckey(ckey),csec(csec),tkey(tkey),tsec(tsec),method(method)
{

}

OAuthClient::~OAuthClient()
{

}

string OAuthClient::signGET(string url)
{
  string sURL;
  
  char * signedUrl = oauth_sign_url2(url.c_str(),NULL,this->method,"GET",this->ckey.c_str(),this->csec.c_str(),this->tkey.c_str(),this->tsec.c_str());
  
  sURL.assign(signedUrl);
  free(signedUrl);
  
  return sURL;
}

OAuthClient::signed_POST_t OAuthClient::signPOST(string url, OAuthClient::postargs_t postargs)
{
  OAuthClient::signed_POST_t sPOST;
  
  stringstream buf;
  
  OAuthClient::postargs_t::iterator it;
  for(it = postargs.begin(); it != postargs.end(); ++it) // iterate over all postarguments 
    buf << it->first << "=" << it->second << "&";        // append the current argument to the buffer

  string postcont = buf.str();                          // copy the content of the buffer to a new string
  postcont.resize(postcont.size()-1);                   // remove the last "&"

  char * postchr = strdup(postcont.c_str());            // copy the c_str to a char*
  
  char * signedUrl = oauth_sign_url2(string(url + string("&") + postcont).c_str(), // create the full url to sign
                                    &postchr,this->method,"POST",this->ckey.c_str(),this->csec.c_str(),this->tkey.c_str(),this->tsec.c_str());

  // Fill the return struct
  sPOST.url.assign(signedUrl);
  sPOST.postdata.assign(postchr);

  // cleanup
  free(signedUrl);
  free(postchr);
  
  return sPOST;
}


