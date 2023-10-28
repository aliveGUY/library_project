# Library MNTU Project

This is uni group project. It uses cross-platform tools and libraries. 

**To install and set the project run these commands:**

`
git clone https://github.com/aliveGUY/library_project.git
`

 `
 cd library_project
 `

`
git submodule add -f https://github.com/chriskohlhoff/asio external/asio
`

`
 git submodule add -f https://github.com/wxWidgets/wxWidgets external/wxWidgets
`

`
git submodule update --init --recursive
`

**To build and run the project run these commands:**

`
cmake -Bbuild . -G "MinGW Makefiles"
`

`
cmake --build build
`

If you using Windows you should update your PATH environment variable to include the gcc_x64_dll folder at <u>path\to\project\build\external\wxWidgets\lib\gcc_x64_dll</u>
