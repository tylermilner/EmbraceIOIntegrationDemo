#!/bin/bash
DIR=$(cd "$(dirname "$0")" && pwd -P)

if [ -z "$EMBRACE_ID" ]
then
  echo "Missing EMBRACE_ID environment variable"
  exit 1
fi

if [ -z "$EMBRACE_TOKEN" ]
then
  echo "Missing EMBRACE_TOKEN environment variable"
  exit 1
fi

if [ -z "$BUILD_ROOT" ]
then
  echo "Missing BUILD_ROOT environment variable. Are you running this from a build step in XCode?"
  exit 1
fi

shopt -s nullglob
icon=$(echo "$PWD"/*/*.xcassets/AppIcon.appiconset/Icon-60@2x.png | head -n 1)
if [ -n "$icon" ] ; then
  icon_arg="-icon $icon"
else
  icon_arg=""
fi

cd "$BUILD_ROOT"
"$DIR"/upload -app $EMBRACE_ID -token $EMBRACE_TOKEN $icon_arg */*dSYM/*/Resources/*/* >> "$DIR"/log 2>&1 &
