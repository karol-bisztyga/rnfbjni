#!/bin/bash

set -e

echo "setting up libsodium..."

find Pods/libsodium -name "*.h" -o -name "*.c" | xargs sed -i '' 's/#include "utils.h"/#include <utils.h>/g'

sed -i '' 's/#include "sodium\/version.h"//g' Pods/libsodium/src/libsodium/include/sodium.h
sed -i '' 's/include "sodium\//include "/g' Pods/libsodium/src/libsodium/include/sodium.h

echo "
#ifndef sodium_version_H
#define sodium_version_H

#include \"export.h\"

#define SODIUM_VERSION_STRING \"1.0.18\"

#define SODIUM_LIBRARY_VERSION_MAJOR 11
#define SODIUM_LIBRARY_VERSION_MINOR 0

#ifdef __cplusplus
extern \"C\" {
#endif

SODIUM_EXPORT
const char *sodium_version_string(void);

SODIUM_EXPORT
int         sodium_library_version_major(void);

SODIUM_EXPORT
int         sodium_library_version_minor(void);

SODIUM_EXPORT
int         sodium_library_minimal(void);

#ifdef __cplusplus
}
#endif

#endif
" > Pods/libsodium/src/libsodium/include/sodium/version.h

echo "libsodium set up"
