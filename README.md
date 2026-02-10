# mDash

## Building
Install build tools
``` sh
sudo apt update && sudo apt install git cmake clang ninja-build pkg-config libssl-dev uuid-dev zlib1g-dev libjsoncpp-dev -y
```
Clone the project 
``` sh
git clone --recursive https://github.com/ForgeAndFury/mDash.git
cd mDash
```
### Build Debug
``` sh
cmake --preset debug
cmake --build --preset=debug -j$(nproc)
```
### Build Release
``` sh
cmake --preset release
cmake --build --preset=release -j$(nproc)
```
