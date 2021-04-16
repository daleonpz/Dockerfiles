# pfeiffer-vaccum-poc

## Zum Kompilieren

```sh
$ rake
```

## Zum Aufräumen 

```sh
$ rake clean
```

## Zum Programieren

```sh
$ mspdebug tilib "prog build/app.out"
```

## Zum Debuggen mit Printf

```sh
$ sudo screen /dev/ttyUSB0 9600
```

## Zum Debuggen mit GDB
Terminal 1:

```sh
mspdebug tilib gdb
```

Terminal 2:

```sh
/home/me/ti/ccs1000/ccs/tools/compiler/msp430-gcc-8.3.1.25_linux64/bin/msp430-elf-gdb build/app.elf
```

Wenn gdb läuft:
```sh
target remote localhost:2000
monitor reset halt
load
```

## NOTES
PUB data to the cloud takes at least 2.5s 

