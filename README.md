# FEDMIX - Eshmun

![ci](https://github.com/FEDMix/eshmun/actions/workflows/build.yml/badge.svg)

Eshmun is part of the FEDMix project: Fusible evolutionary deep neural network mixture learning. See project's page information: https://www.esciencecenter.nl/projects/fedmix/

![image](https://user-images.githubusercontent.com/4195550/111743278-ba27ce00-8889-11eb-94ec-faa8ddec4b01.png)


'Eshmun' is a standalone, and robust medical image analysis developed with C++, Qt, and VTK that you can use, collaborate with the development and extend.

- [ ] Installable binaries for:
  - [ ] Mac
  - [ ] Windows
  - [ ] Linux
- [ ] Load DICOM images

## TechStack:
- C++ v17
- Qt v5.15
- LLVM v11.1
- clang v11.1 (clang-format - Google style, AStyle)
- VTK v9

# Development
You can clone this repository
```git clone https://github.com/FEDMix/eshmun.git```
and edit the code with your preferent IDE
- [QTCreator](https://www.qt.io/download-thank-you). Used for [Open Source](https://www.qt.io/download-open-source)
- [VSCode](https://code.visualstudio.com/download)

## Installation on MacOS
Install with homebrew:
```
brew install llvm@11 cmake vtk@9 qt@5
```
you may need to install `xcode-select --install` and link qt for cmake:
```shell
brew link --force qt@5
sudo ln -s /usr/local/Cellar/qt@5/5.15.2/mkspecs /usr/local/mkspecs
sudo ln -s /usr/local/Cellar/qt@5/5.15.2/plugins /usr/local/plugins
```

## Installation on Linux
```shell
Linux & WSL2:
wget https://apt.llvm.org/llvm.sh
chmod +x llvm.sh
sudo ./llvm.sh 11

sudo apt-get install clang-format-11
sudo apt-get install clang-tidy-11

curl https://gist.githubusercontent.com/junkdog/70231d6953592cd6f27def59fe19e50d/raw/92f0e73d2558402b7316021c1ab408b30e534de6/update-alternatives-clang.sh > update-alternatives-clang.sh
chmod u+x update-alternatives-clang.sh
sudo ./update-alternatives-clang.sh 11 1
```

## Buid the application
### From the command line
```shell
$ mkdir build #Create build folder if doesn't exist
$ cd build #And follow the sequential steps inside the build folder

# Create the 'make' file inside the build folder for your operative system.
$ cmake .. 
# if you have different version on you computer you can specify the installation path of qt5 with
$ cmake -DCMAKE_PREFIX_PATH="/usr/local/opt/qt5" ..

# Create the binary compiled
$ make

# Run the application
$./src/eshmun  
```

### With QT Creator
Open the txt file `CMakeLists.txt`
and run with 
![image](https://user-images.githubusercontent.com/4195550/111753398-1c3b0000-8897-11eb-9bc7-359fd6a62a14.png)


Configure your project. Be sure that all versions are linked correctly. 
![image](https://user-images.githubusercontent.com/4195550/111751176-725a7400-8894-11eb-8051-f3cc4f86f91b.png)

You have to uncheck the Add build library search path to DYLD_LIBRARY_PATH and DYLD_FRAMEWORK_PATH option from the Run section in the Projects tab:
![image](https://user-images.githubusercontent.com/4195550/111753292-fd3c6e00-8896-11eb-8916-025056b95e84.png)



## Run the tests
If using Qt creator: 

![image](https://user-images.githubusercontent.com/4195550/111753678-7045e480-8897-11eb-8da1-aa24eaca9267.png)

# Contributor Covenant Code of Conduct
https://github.com/FEDMix/eshmun/blob/feature/readme/CODE_OF_CONDUCT.rst

# License
[Apache 2](https://www.apache.org/licenses/LICENSE-2.0)
