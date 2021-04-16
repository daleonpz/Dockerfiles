# Template Project

Before you compile any project you must follow a structure similar to this:

```sh
project_template/
├── CompileProject.sh
├── include/
├── src/ 
├── rakefile.rb
└── README.md
```

Open `CompileProject.sh` and add your device and toolchain. For example: 

```sh
DEVICE_NAME="msp430fr2433"
IMAGE_NAME="git.infra.cospace.de:4567/daniel.paredes/toolchain-msp430"
```

To compile you must run `CompileProject.sh`

```sh
$ ./CompileProject.sh
```


