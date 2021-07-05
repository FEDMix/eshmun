## Continuous Integration

Continuous integration (CI) is a software practice that ensures frequent testing on multiple platforms, to make sure that errors are caught quickly. Every time code is pushed to the repository, the software is built and tests are being run for all intended platforms. Reports on these runs are being generated in the 'Actions' tab in Github, here https://github.com/FEDMix/eshmun/actions

The CI iss set up to use 3 main configurations, as detailed in the section 'matrix'.
For each configuration, the following steps follow rougly the same pattern.

- Checkout the repository
- Set any environment variables needed
- Install dependencies
- Install LLVM and Clang
- Check the compiler and cmake versions
- Download and install ccache for speeding up the compilation of VTK
- Download, compile and install VTK
- Set any additional environment variables
- Configure, make and install the Eshmun code
- Test
- Upload artifacts

# Continuous deployment

After building and testing, the CI also creates 'artifacts' which are fully built and runnable versions of the software. Please keep in mind that due to licencing restrictions, we cannot package these with the dynamically linked libraries necessary to run them on your system, so you will still need manually installed versions of the dependencies on your machine. 

Installable binaries for:
- [x] MacOS
- [x] Windows
- [x] Linux

# Github Actions

We have used 'Github Actions' to create the steps necessary to build and test. Full documentation on this platform can be found here https://docs.github.com/en/actions

## TechStack:
 
# Windows:
Ninja as a build system
Ccache 4.2.0
- C++ from https://github.com/ilammy/msvc-dev-cmd
- Qt from https://github.com/jurplel/install-qt-action
- LLVM from https://github.com/KyleMayes/install-llvm-action
- clang from https://github.com/KyleMayes/install-llvm-action
- VTK compiled
 
# MacOS:
- C++ as dependency of 'brew install vtk'
- Qt as dependency of 'brew install vtk'
- LLVM as dependency of 'brew install vtk'
- clang as dependency of 'brew install vtk'
- VTK by 'brew install vtk'
 
# Linux:
Ccache 4.2.0
- C++ from apt repositories
- Qt v5.15 from apt repositories
- LLVM v11 from https://apt.llvm.org/llvm.sh
- clang v11.1 from apt repositories
- VTK v9 compiled
