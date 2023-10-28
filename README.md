# Library MNTU Project

This is uni group project. It uses crossplatform tools and libraries. 

**To install and setup the project run these commands:**

`
git clone https://github.com/aliveGUY/library_project.git
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
