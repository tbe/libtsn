#ifndef OBJECTS_H
#define OBJECTS_H

#include <stdint.h>
#include <time.h>

#include <string>
#include <vector>
#include <utility>

#ifdef DOXYGEN
#define DOXCOMMENT(a) SLASH(**) @returns a */
#else
#define DOXCOMMENT(a)
#endif

#define SLASH(s) /##s
#define RET_PRIV(t,a) \
  DOXCOMMENT(a) \
  inline t a() { return this-> _##a ; }



namespace tsn {
class objectFactory;

namespace objects {
class Status;


typedef std::pair<int,int> indices_t;



/**
 * @brief user Object
 *
 * currently there are some attributes defined in the API but not supported by this class:
 * - contributors: beta feature
 * - is_translator: no usefull data
 * - lang: not needed
 * - location: must not be parsable or a location, mainly used internal by the services
 * - show_all_inline_media: disused
 * - status: not implentent right now as it is of lesser use
 * - time_zone; no usefull data
 * - withheld_*: we dont expect much usefull data here
 *
 */
class User {
    friend class ::tsn::objectFactory;
    friend class Status;
public:
    RET_PRIV(int64_t,uid)
    RET_PRIV(std::string,screen_name)

    RET_PRIV(std::string,name)
    RET_PRIV(struct tm   ,created_at)

    RET_PRIV(bool,default_profile)
    RET_PRIV(bool,default_profile_image)
    RET_PRIV(std::string,profile_background_color)
    RET_PRIV(std::string,profile_background_image_url)
    RET_PRIV(std::string,profile_background_image_url_https)
    RET_PRIV(bool,profile_background_tile)
    RET_PRIV(std::string,profile_image_url)
    RET_PRIV(std::string,profile_image_url_https)
    RET_PRIV(std::string,profile_link_color)
    RET_PRIV(std::string,profile_sidebar_border_color)
    RET_PRIV(std::string,profile_sidebar_fill_color)
    RET_PRIV(std::string,profile_text_color)
    RET_PRIV(bool,profile_use_background_image)

    RET_PRIV(bool,Protected)
    RET_PRIV(bool,verified)

    RET_PRIV(std::string,description)
    RET_PRIV(std::string,url)


    RET_PRIV(int,statuses_count)
    RET_PRIV(int,favourites_count)
    RET_PRIV(int,followers_count)
    RET_PRIV(int,friends_count)

    RET_PRIV(int,listed_count)

    RET_PRIV(bool,geo_enabled)

    RET_PRIV(bool,follow_request_sent)
    RET_PRIV(bool,following)

private:
    User(int64_t uid = 0, std::string screen_name = "")
        :_uid(uid),_screen_name(screen_name) {
        this->_name = this->_screen_name;
        this->_created_at.tm_sec = 0;
        this->_created_at.tm_min = 0;
        this->_created_at.tm_hour = 0;
        this->_created_at.tm_mday = 1;
        this->_created_at.tm_mon = 0;
        this->_created_at.tm_year = 0;
        mktime(&(this->_created_at));
    }


    int64_t     _uid;
    std::string _screen_name;

    std::string _name;
    struct tm   _created_at;

    bool        _default_profile;
    bool        _default_profile_image;
    std::string _profile_background_color;
    std::string _profile_background_image_url;
    std::string _profile_background_image_url_https;
    bool        _profile_background_tile;
    std::string _profile_image_url;
    std::string _profile_image_url_https;
    std::string _profile_link_color;
    std::string _profile_sidebar_border_color;
    std::string _profile_sidebar_fill_color;
    std::string _profile_text_color;
    bool        _profile_use_background_image;

    bool        _Protected;
    bool        _verified;

    std::string _description;
    std::string _url;

    int         _statuses_count;
    int         _favourites_count;
    int         _followers_count;
    int         _friends_count;

    int         _listed_count;

    bool        _geo_enabled;


    // user-scoped metadata
    bool        _follow_request_sent;
    bool        _following;


};
/**
 * @brief coordinates Object
 */
class Coordinates {
public:
    /**
     * @brief type of the Coordinates object.
     *
     * there are only two types supported
     */
    typedef enum {
        NONE = 0, ///< empty coordinate set
        POINT = 1 ///< point - only supported coordinate type used
    } coordtype_t;
    /**
     * @brief typedef for the Coordinates
     *
     * first value is the longtitude, second the latitude
     */
    typedef std::pair<float,float> coords_t;

    /**
     * constructor
     *
     * @param type Type of the Coordinates, defaults to NONE
     * @param lo   longtitude
     * @param la   lantitude
     */
    Coordinates(coordtype_t type = NONE,float lo = 0, float la = 0)
        :_type(type) {
        this->_coords = std::make_pair(lo,la);
    }

    RET_PRIV(coordtype_t,type)
    RET_PRIV(coords_t,coords)

private:
    coordtype_t _type;
    coords_t _coords;
};

/**
 * @brief media entity
 */
class Media {
    friend class ::tsn::objectFactory;
public:
    typedef enum {
        crop = 0,
        fit = 1
    } resize_t;

    typedef struct {
        int w;
        int h;
        resize_t resize;
    } size_t;

    typedef enum {
        photo
    } type_t;



    RET_PRIV(int64_t,id)
    RET_PRIV(std::string,url)
    RET_PRIV(std::string,display_url)
    RET_PRIV(std::string,expanded_url)

    RET_PRIV(std::string,media_url)
    RET_PRIV(std::string,media_url_https)

    RET_PRIV(std::vector <size_t>,sizes)
    RET_PRIV(type_t,type)

    RET_PRIV(indices_t,indices)

private:
    Media(int64_t id):_id(id) {}

    int64_t     _id;

    std::string _url;
    std::string _display_url;
    std::string _expanded_url;

    std::string _media_url;
    std::string _media_url_https;

    std::vector <size_t> _sizes;
    type_t      _type;

    indices_t   _indices;
};

/**
 * @brief url entity
 */
class Url {
    friend class ::tsn::objectFactory;

public:


    RET_PRIV(std::string,url)
    RET_PRIV(std::string,display_url)
    RET_PRIV(std::string,expanded_url)

    RET_PRIV(indices_t,indices)

private:
    Url() {}

    std::string _url;
    std::string _display_url;
    std::string _expanded_url;


    indices_t   _indices;
};

/**
 * @brief user_mention entity
 */
class User_Mention {
    friend class ::tsn::objectFactory;
public:
    RET_PRIV(User,user)
    RET_PRIV(indices_t,indices)

private:
    User_Mention(User user,indices_t indices):_user(user),_indices(indices) {};

    User _user;
    indices_t _indices;
};

/**
 * @brief hashtag entity
 */
class Hashtag {
    friend class ::tsn::objectFactory;
public:

    RET_PRIV(std::string,text)
    RET_PRIV(indices_t,indices)

private:
    Hashtag(std::string text,indices_t indices):_text(text),_indices(indices) {}

    std::string _text;
    indices_t   _indices;

};





/**
 * @brief a complete status object.
 *
 * currently there are some attributes defined in the API but not supported by this class:
 * - annotations: unused
 * - contributors: beta feature
 * - scopes; only used by twitter promoted products
 * - withheld_*: we dont expect much usefull data here
 */
class Status {
    friend class ::tsn::objectFactory;
public:
    typedef std::vector<Media> media_t;
    typedef std::vector<Url>   urls_t;
    typedef std::vector<User_Mention> user_mentions_t;
    typedef std::vector<Hashtag> hashtags_t;

    RET_PRIV(int64_t,id)
    RET_PRIV(struct tm   ,created_at)
    RET_PRIV(std::string,text)
    RET_PRIV(User,user)

    RET_PRIV(int,retweet_count)
    RET_PRIV(std::string,source)
    RET_PRIV(bool,truncated)
    RET_PRIV(bool,is_reply)
    RET_PRIV(int64_t,in_reply_to_status)
    RET_PRIV(User,in_reply_to_user)

    RET_PRIV(bool,possibly_sensitive)

    RET_PRIV(bool,is_userscope)
    RET_PRIV(bool,retweeted)
    RET_PRIV(int64_t,current_user_retweet)
    RET_PRIV(bool,favorited)

    RET_PRIV(media_t,media)
    RET_PRIV(urls_t,urls)
    RET_PRIV(user_mentions_t,user_mentions)
    RET_PRIV(hashtags_t,hashtags)

    RET_PRIV(Coordinates,coordinates)

private:
    Status(int64_t id,struct tm    created_at,std::string text,User user,
           int retweet_count, std::string source, bool truncated)
        :_id(id),_created_at(created_at),_text(text),_user(user),_retweet_count(retweet_count),
         _source(source),_truncated(truncated),_is_reply(false),_possibly_sensitive(false),
         _is_userscope(false),_retweeted(false),_favorited(false) {
        this->_created_at.tm_sec  = 0;
        this->_created_at.tm_min  = 0;
        this->_created_at.tm_hour = 0;
        this->_created_at.tm_mday = 1;
        this->_created_at.tm_mon  = 0;
        this->_created_at.tm_year = 0;
        mktime(&(this->_created_at));
    }

    inline void set_reply(int64_t to_status, User user) {
        this->_is_reply = true;
        this->_in_reply_to_status = to_status;
        this->_in_reply_to_user   = user;
    }

    inline void set_poissbly_sensitive() {
        this->_possibly_sensitive = true;
    }

    inline void set_current_user_retweet(int64_t status) {
        this->_retweeted = true;
        this->_current_user_retweet = status;
    }

    inline void set_favorited() {
        this->_favorited = true;
    }



    // default tweet data
    int64_t      _id;
    struct tm          _created_at;
    std::string  _text;
    User         _user;


    // tweet meta data
    int          _retweet_count;
    std::string  _source;
    bool         _truncated;

    bool         _is_reply;
    int64_t      _in_reply_to_status;
    User         _in_reply_to_user;

    bool         _possibly_sensitive;


    // user-scoped metadata
    bool         _is_userscope;
    bool         _retweeted;
    int64_t      _current_user_retweet;
    bool         _favorited;



    //TODO places


    //TODO entities
    media_t         _media;
    urls_t          _urls;
    user_mentions_t _user_mentions;
    hashtags_t      _hashtags;


    Coordinates  _coordinates;


};
}
}
#endif//OBJECTS_H
