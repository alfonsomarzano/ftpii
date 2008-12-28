/*

ftpii -- an FTP server for the Wii

Copyright (C) 2008 Joseph Jordan <joe.ftpii@psychlaw.com.au>

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from
the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1.The origin of this software must not be misrepresented; you must not
claim that you wrote the original software. If you use this software in a
product, an acknowledgment in the product documentation would be
appreciated but is not required.

2.Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.

3.This notice may not be removed or altered from any source distribution.

*/
#include <gccore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/dir.h>

#include "dol.h"
#include "loader.h"

static bool read_from_file(u8 *buf, FILE *f) {
    while (1) {
        s32 bytes_read = fread(buf, 1, 0x8000, f);
        if (bytes_read > 0) buf += bytes_read;
        if (bytes_read < 0x8000) return feof(f);
    }
}

void load_from_file(FILE *f) {
    struct stat st;
    int fd = fileno(f);
    if (fstat(fd, &st)) return;
    u8 *buf = malloc(st.st_size);
    if (!buf) return;
    if (!read_from_file(buf, f)) return;
    run_dol(buf);
    free(buf);
}