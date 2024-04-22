#!/bin/bash

gcc music.c \
    lib/utils.c \
    lib/songs.c lib/disks.c lib/items.c lib/data_base.c lib/data_base_io.c lib/dialogs.c \
    -o music.out
