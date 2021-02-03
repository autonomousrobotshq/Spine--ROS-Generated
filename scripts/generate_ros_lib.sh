#!/bin/zsh
#
# Spine - Spine - MCU code for robotics.
# Copyright (C) 2019-2021 Codam Robotics
#
# This file is part of Spine.
#
# Spine is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Spine is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with Spine.  If not, see <http://www.gnu.org/licenses/>.
#

BASEDIR=$(realpath $(dirname "$0"))

ROSLIB_DST_DIR=$BASEDIR/../src
LIB_PROPERTIES=$BASEDIR/../library.properties
GIT_REPO="git@github.com:autonomousrobotshq/Spine--ROS-Messages"
GIT_REPO_NAME="ros_packages"

which catkin_make || { echo "Don't forget to source setup.zsh or setup.bash first!"; exit 1; }
which cmake || exit 1
which git || exit 1
which mktemp || exit 1

TMP_DIR=`mktemp -d`
cd $TMP_DIR && echo "Temporary folder @ $(pwd)" || exit 1

# clone ROS packages
git clone $GIT_REPO $GIT_REPO_NAME || exit 1
pushd . && cd $GIT_REPO_NAME && git submodule update --init --recursive && popd || exit 1

# initialize workspace
pushd . && mkdir src && cd src && catkin_init_workspace && cd .. || exit 1
mv $GIT_REPO_NAME ./src && popd || exit 1

# build and generate ROS headers
catkin_make && source ./devel/setup.zsh && rosrun rosserial_arduino make_libraries.py .  || exit 1

# setup src directory
rm -rf $ROSLIB_DST_DIR && mkdir $ROSLIB_DST_DIR || exit 1
mv ./ros_lib/* $ROSLIB_DST_DIR && rm -rf $TMP_DIR || exit 1

# shuffle around examples folder in generated folder
rm -rf $ROSLIB_DST_DIR/../examples && mv $ROSLIB_DST_DIR/examples $ROSLIB_DST_DIR/.. \
&& mv $ROSLIB_DST_DIR/tests/* $ROSLIB_DST_DIR/../examples && rmdir $ROSLIB_DST_DIR/tests

# patches
find $ROSLIB_DST_DIR \( -type d -name .git -prune \) -o -type f -print0 | xargs -0 sed -i 's/cstring/string\.h/g' || exit 1
find $ROSLIB_DST_DIR \( -type d -name .git -prune \) -o -type f -print0 | xargs -0 sed -i 's/std::memcpy/memcpy/g' || exit 1
find $ROSLIB_DST_DIR/../examples/ -name "*.pde" -exec sh -c 'mv "$1" "${1%.pde}.ino"' _ {} \; &>/dev/null # rename .pde -> .ino

# OSx expects String.h instead of string.h ...........
tmp_f=`mktemp`
cat>$tmp_f<<EOF
#ifdef __MACH__
	#include "String.h"
#else
	#include "string.h"
#endif
EOF
find $ROSLIB_DST_DIR -exec sed -i -e "/#include <string\.h>/{r$tmp_f" -e "d}" {} \;
rm $tmp_f

# remove bad examples (they cannot be compiled with just ROSSerial or are outdated)
cd $ROSLIB_DST_DIR/../examples || exit 1
BADEXAMPLES=(
				"TimeTF/TimeTF.ino" \
				"ServiceClient/ServiceClient.ino" \
				"Odom/Odom.ino" \
				"Esp8266HelloWorld/Esp8266HelloWorld.ino" \
			)
for ino in "${BADEXAMPLES[@]}"; do rm $ino; done

# add includes to library.properties
sed -i '/includes=/d' $LIB_PROPERTIES
tmp_f=`mktemp`
find $ROSLIB_DST_DIR -name "*.h" -exec basename {} >> $tmp_f \;
echo -n "includes=" >> $LIB_PROPERTIES
cat $tmp_f | while read lib; do echo -n "$lib, " >> $LIB_PROPERTIES; done
rm $tmp_f

echo "Succesfully regenerated ROS libraries for Arduino."
