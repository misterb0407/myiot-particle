# myiot
Personal IoT project

TOOLCHAIN

Compiler

Dowload compiler tar from
https://launchpad.net/gcc-arm-embedded/+series

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
