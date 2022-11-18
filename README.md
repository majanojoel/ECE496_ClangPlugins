# ECE496_ClangPlugins

## 1. Compiling Clang 

### Clone and compile CMAKE release branch

```
git clone https://gitlab.kitware.com/cmake/cmake.git
cd cmake
git checkout release
./bootstrap
make
sudo make install
```

## Clone and Compile clang

```
git clone --depth=1 https://github.com/llvm/llvm-project.git
cd llvm-project
mkdir build
cd build
cmake -DLLVM_ENABLE_PROJECTS="clang;clang-tools-extra" -DLLVM_USE_LINKER=gold -DCMAKE_BUILD_TYPE=Release -G "Unix Makefiles" ../llvm
make

```

## 2. Compiling the plugin

```
cd clang-plugins
//The rest of the instructions are TBD.
```
