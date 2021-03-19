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
You can edit the code with your preferent IDE: 
- [QTCreator](https://www.notion.so/Developer-documentation-fe20b6a0c58c4e0cb518fc26d23d71f9#669ac289d7fd4e2fae37d0abaffdcf6b) Open Source edition
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
$ mkdir build #Create build folder if (add it to git if possible)
$ cd build #And follow the sequential steps inside the build folder

# Create the 'make' file inside the build folder for your operative system.
$ cmake .. 
# if you have different version on you computer you can specify the installation path of qt5 with
$ cmake -DCMAKE_PREFIX_PATH="/usr/local/opt/qt5" ..`

# Create the binary compiled
$ make

# Run the application
$./src/eshmun  
```

### With QT Creator
Documentation in progress


## Run the tests
Documentation in progress


# License
[Apache 2](https://www.apache.org/licenses/LICENSE-2.0)
