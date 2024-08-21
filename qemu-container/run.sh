#!/bin/bash

if [ ! -d "$1" ] ; then
  mount_path="$(realpath ..)"
else
  mount_path="$(realpath $1)"
fi

docker run -it --rm -v "$mount_path":"$mount_path" \
                    -p 1234:1234 \
                    -p 5900:5900 \
                    --hostname alpine-qemu \
                    alpine-qemu
