# 53E Over Under

This is 53E's codebase for the 2023, 2024 Over Under Season.


## Style Guide

This project follows [Google's](https://google.github.io/styleguide/cppguide.html) style guide, with a few exceptions.

### Pragma Once

Use of pragma once is permitted in the place of normal header guards. We only ever need to compile for one architecture, so using non-standard features is not an issue for us.


### File names

Use .cpp for C++ body files, and .hpp for C++ header files.