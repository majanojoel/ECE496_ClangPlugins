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

### Clone and Compile clang

```
git clone https://github.com/majanojoel/CompiledClang.git
cd CompiledClang
mkdir build
cd build
cmake -DLLVM_ENABLE_PROJECTS="clang;clang-tools-extra" -DLLVM_USE_LINKER=gold -DCMAKE_BUILD_TYPE=Release -G "Unix Makefiles" ../llvm
make
sudo make install
```

## 2. Compiling the plugin

This is an updated version of the plugins example found at https://github.com/nsumner/clang-plugins-demo.

```
mkdir build
cd build
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=True -DCMAKE_CXX_STANDARD=17 -DLLVM_DIR=<path to clang build folder>/lib/cmake/llvm/ ../clang-plugins
make

NOTE: The -DLlVM_DIR lib/cmake/llvm folder is found inside build folder from the CompiledClang step.
```

## 3. Running the plugin

```

<llvm build folder>/bin/clang -fplugin=<path to .so file> -c test.cpp

<llvm build folder>/bin/clang -fplugin=<path to .so file> -fplugin-arg-<plugin name>-<arg name> -c test.cpp

```
