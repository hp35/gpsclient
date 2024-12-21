# Basic GPS logging client communicating over a serial USB channel

The enclosed client `gpsclient` is a very basic GPS-client intended to read a
stream of data from a serial port in Linux (in this case a USB port serving
with serial data). The code for the `gpsclient` is written in C99-compliant
C-code and can be compiled using GCC and the enclosed Makefile.

## Compiling and running the code

The below compilation and setup examples are assuming that you are running
any standard Linux system such as Ubuntu, ArchLinux, Debian or Raspbian.
Compilation of the client `gpsclient.c` requires `gps.h` and `libgps`.
These come with `libgps`, so install these by running

    ```bash
    $ sudo apt-get install libgps-dev
    ```

Copile the enclosed code by simply running `make`.

    ```bash
    $ make
    ```

## Setup of the environment for serial communication with the GPS

Raw setup of the "GPS-puck" from terminal:

    ```bash
    $ stty -F /dev/ttyUSB0 9600
    $ cat /dev/ttyUSB0
    ```

Install and start the gpsd daemon (see, for example, https://kickstartembedded.com/2022/07/23/a-beginners-guide-to-using-gpsd-in-linux/#:~:text=gpsd%20is%20a%20service%20daemon,of%20platforms%20based%20on%20linux):

    ```bash
    $ sudo apt update; sudo apt install gpsd gpsd-clients libgps-dev
    $ gpsd /dev/ttyUSB0 --port 2947 --speed 4800
    ```

Check that the gpsd daemon is up and running:

    ```bash
    $ service --status-all|grep gpsd
    ```

(or simply check by running `ps -aux|grep gpsd`)

## Running the GPS client

Once the gpsd daemon is up and running, start the cgps test client in a
terminal to verify that everything is okay:

    ```bash
    $ cgps -s
    ```

## Copyright
Copyright (C) 2024, Fredrik Jonsson, under GPL 3.0. See enclosed LICENSE.

## Location of master source code
The source and documentation can be found at https://github.com/hp35/gpsclient
