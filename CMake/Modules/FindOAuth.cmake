# - Try to find OAuth  library
# Once done, this will define
#
#  OAUTH_FOUND - system has OAuth library
#  OAUTH_INCLUDE_DIRS - the OAuth include directories
#  OAUTH_LIBRARIES - link these to use the OAuth

include(LibFindMacros)
# Include dir
find_path(OAUTH_INCLUDE_DIR
  NAMES oauth.h
  PATHS ${OAUTH_PKGCONF_INCLUDE_DIRS}
)

# Finally the library itself
find_library(OAUTH_LIBRARY
  NAMES oauth
  PATHS ${OAUTH_PKGCONF_LIBRARY_DIRS}
)

# Set the include dir variables and the libraries and let libfind_process do the rest.
# NOTE: Singular variables for this library, plural for libraries this this lib depends on.
set(OAUTH_PROCESS_INCLUDES OAUTH_INCLUDE_DIR OAUTH_INCLUDE_DIRS)
set(OAUTH_PROCESS_LIBS OAUTH_LIBRARY OAUTH_LIBRARIES)

libfind_process(OAUTH)
