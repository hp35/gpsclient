/*
 * Basic GPS logging client communicating over a serial USB channel.
 *
 * The enclosed client `gpsclient` is a very basic GPS-client intended to
 * read a stream of data from a serial port in Linux (in this case a USB
 * port serving with serial data).
 *
 * The code for the `gpsclient` is written in C99-compliant C-code and can
 * be compiled using GCC and the enclosed Makefile. See the enclosed README
 * and Makefile for instructions on compilation and configuration of the
 * client on any standard Linux system such as Ubuntu, ArchLinux, Debian
 * or Raspbian.
 *
 * The primary source location is https://github.com/hp35/gpsclient
 *
 * Copyright (C) 2024, Fredrik Jonsson, under Gnu General Public License
 * (GPL) v3. See the enclosed LICENSE for details.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include <gps.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <errno.h>

int main() {
struct timeval tv;
struct gps_data_t gps_data;
char tmbuf[64], buf[64];
 
if ((gps_open("localhost", "2947", &gps_data)) == -1) {
    printf("code: %d, reason: %s\n", errno, gps_errstr(errno));
    return EXIT_FAILURE;
}
gps_stream(&gps_data, WATCH_ENABLE | WATCH_JSON, NULL);

while (1) {
    /* wait for 2 seconds to receive data */
    if (gps_waiting (&gps_data, 2000000)) {
        /* read data */
        if ((gps_read(&gps_data,NULL,0)) == -1) {
            printf("error occured reading gps data. code: %d, reason: %s\n", errno, gps_errstr(errno));
        } else {
            /* Display data from the GPS receiver. */
            if ((gps_data.fix.status == STATUS_FIX) && 
                (gps_data.fix.mode == MODE_2D || gps_data.fix.mode == MODE_3D) &&
                !isnan(gps_data.fix.latitude) && 
                !isnan(gps_data.fix.longitude)) {
                    //gettimeofday(&tv, NULL); EDIT: tv.tv_sec isn't actually the timestamp!

 printf("Timestamp: %ld.%09ld ", gps_data.fix.time.tv_sec,
                   gps_data.fix.time.tv_nsec);

 printf("latitude: %f, longitude: %f, speed: %f\n", gps_data.fix.latitude, gps_data.fix.longitude, gps_data.fix.speed); //EDIT: Replaced tv.tv_sec with gps_data.fix.time
            } else {
                printf("no GPS data available\n");
            }
        }
    }

    sleep(3);
}

/* When you are done... */
gps_stream(&gps_data, WATCH_DISABLE, NULL);
gps_close (&gps_data);

return EXIT_SUCCESS;
}

