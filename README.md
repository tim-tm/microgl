# microgl

Microgl is an embedded graphics library for the Raspberry PI Pico.
It aims to provide access to different displays, such as for example sh1106 based displays.

## Support

Supported displays:

-   sh1106

In progress:

-   none

## Getting started

Building:

```sh
cmake -B build
```

```sh
cmake --build build
```

The static library will be located at build/libmicrogl.a

## License

In order to match the license of the [pico-sdk](https://github.com/raspberrypi/pico-sdk), microgl is licensed under the BSD-3-Clause.
