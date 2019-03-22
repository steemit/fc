#!/bin/sh

if [ "$#" != 1 ]; then
    echo "Usage: $0 <boost-unit-test-executable>" 1>&2
    exit 1
fi

CACHE="$( find . -name CMakeCache.txt )"
if [ "$CACHE" != "" ]; then
    BOOST_INC="$( grep Boost_INCLUDE_DIR:PATH "$CACHE" | cut -d= -f 2 )"
    if [ "$BOOST_INC" != "" ]; then
	BOOST_VERSION="$( grep '^#define *BOOST_VERSION ' "$BOOST_INC/boost/version.hpp" | sed 's=^.* ==' )"
    fi
fi

if [ "$BOOST_VERSION" = "" -o "$BOOST_VERSION" -lt 105900 ]; then
    echo "Boost version '$BOOST_VERSION' - executing tests serially"
    "$1"
else
  "$1" --list_content 2>&1 \
    | grep '\*$' \
    | sed 's=\*$==;s=^    =/=' \
    | while read t; do
	case "$t" in
	/*) echo "$pre$t"; ;;
	*) pre="$t"; ;;
	esac
      done \
    | parallel echo Running {}\; "$1" -t {}
fi
