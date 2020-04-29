# myiot
Personal IoT project

# TOOLCHAINS

## Particle Workbench

Consult https://docs.particle.io/tutorials/developer-tools/cli/ for development
setup.

install CLI
$ bash <( curl -sL https://particle.io/install-cli )

update
$ particle update-cli

setup credential
$ particle setup

create project
$ particle project create

compile in cloud, anything in 'src' will be sent and compiled
$ particle compile argon

search available library (e.g. any library name containing 'internet'
$ particle library search internet

to add found library (e.g. found InternetButton), verify this is accounte in
project.properties
$ particle library add InternetButton

to download library into project folder (consume space in project space)
$ particle library copy InternetButton

to download source of new added library in properties (but not added physically
to project space, it will be linked during 'cloud-compile'
$ particle library view InternetButton

## Others
Compiler

Dowload compiler tar from
https://launchpad.net/gcc-arm-embedded/+series

newer release from
https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads

$ tar xjf <.bz2>
Then add the bin path to path

$ export PATH=compiler_bin_path:$PATH

Compatibility issue

Since many iot project using 32bit based CPU ARM, it needs additional setting
to make it work on Ubuntu 64 machine.

Ref:
https://askubuntu.com/questions/133389/no-such-file-or-directory-but-the-file-exists

sudo dpkg --add-architecture i386
sudo apt-get update
sudo apt-get install libc6:i386 libncurses5:i386 libstdc++6:i386

To make it work on WSL, need to install qemu
ref https://github.com/microsoft/wsl/issues/2468#issuecomment-374904520

sudo apt update
sudo apt install qemu-user-static

sudo update-binfmts --install i386 /usr/bin/qemu-i386-static --magic '\x7fELF\x01\x01\x01\x03\x00\x00\x00\x00\x00\x00\x00\x00\x03\x00\x03\x00\x01\x00\x00\x00' --mask '\xff\xff\xff\xff\xff\xff\xff\xfc\xff\xff\xff\xff\xff\xff\xff\xff\xf8\xff\xff\xff\xff\xff\xff\xff'

You will need to reactivate this every time you restart WSL and want i386
support:
sudo service binfmt-support start

Enable i386 architecture and packages
sudo dpkg --add-architecture i386
sudo apt update
sudo apt install gcc:i386

# Misc Note

# README from project created by Particle Workbench CLI

## Welcome to your project!

Every new Particle project is composed of 3 important elements that you'll see have been created in your project directory for first-app.

#### ```/src``` folder:
This is the source folder that contains the firmware files for your project. It should *not* be renamed.
Anything that is in this folder when you compile your project will be sent to our compile service and compiled into a firmware binary for the Particle device that you have targeted.

If your application contains multiple files, they should all be included in the `src` folder. If your firmware depends on Particle libraries, those dependencies are specified in the `project.properties` file referenced below.

#### ```.ino``` file:
This file is the firmware that will run as the primary application on your Particle device. It contains a `setup()` and `loop()` function, and can be written in Wiring or C/C++. For more information about using the Particle firmware API to create firmware for your Particle device, refer to the [Firmware Reference](https://docs.particle.io/reference/firmware/) section of the Particle documentation.

#### ```project.properties``` file:
This is the file that specifies the name and version number of the libraries that your project depends on. Dependencies are added automatically to your `project.properties` file when you add a library to a project using the `particle library add` command in the CLI or add a library in the Desktop IDE.

## Adding additional files to your project

#### Projects with multiple sources
If you would like add additional files to your application, they should be added to the `/src` folder. All files in the `/src` folder will be sent to the Particle Cloud to produce a compiled binary.

#### Projects with external libraries
If your project includes a library that has not been registered in the Particle libraries system, you should create a new folder named `/lib/<libraryname>/src` under `/<project dir>` and add the `.h`, `.cpp` & `library.properties` files for your library there. Read the [Firmware Libraries guide](https://docs.particle.io/guide/tools-and-features/libraries/) for more details on how to develop libraries. Note that all contents of the `/lib` folder and subfolders will also be sent to the Cloud for compilation.

## Compiling your project

When you're ready to compile your project, make sure you have the correct Particle device target selected and run `particle compile <platform>` in the CLI or click the Compile button in the Desktop IDE. The following files in your project folder will be sent to the compile service:

- Everything in the `/src` folder, including your `.ino` application file
- The `project.properties` file for your project
- Any libraries stored under `lib/<libraryname>/src`
