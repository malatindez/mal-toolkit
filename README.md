[![Stand With Ukraine](https://raw.githubusercontent.com/vshymanskyy/StandWithUkraine/main/banner-direct-single.svg)](https://stand-with-ukraine.pp.ua)

# mal-toolkit C++ Library

mal-toolkit is a C++20 utility library that provides a collection of helpful tools and functionalities commonly used across my projects. It is built using CMake and relies on the excellent [spdlog](https://github.com/gabime/spdlog) library for logging. The library is structured for easy integration into various projects and includes a range of modules for tasks like logging, debugging, file manipulation, string handling, and more.

## Table of Contents

- [Features](#features)
- [Dependencies](#dependencies)
- [Usage](#usage)
- [Documentation](#documentation)
- [License](#license)

## Features

- Logging utilities powered by [spdlog](https://github.com/gabime/spdlog).
- Common data structures and helper functions in `common-structures.hpp`.
- Callback system implementation in `callback-system.hpp`.
- Conversion functions and utilities in `converter.hpp`.
- Debugging tools and macros in `debug.hpp`.
- File watcher for monitoring file changes in `file-watcher.hpp`.
- Precompiled header support in `library-pch.hpp`.
- Useful macros in `macro.hpp`.
- Performance measuring tools in `measurer.hpp`.
- Various utility functions for STL containers in `stl-helpers.hpp`.
- String manipulation functions in `string.hpp`.
- Template utility functions in `template.hpp`.
- Timing functionality in `timer.hpp`.
- UUID generation and handling in `uuid.hpp`.
- Additional details and configuration files in the `detail` and `include` directories.

## Dependencies

- [spdlog](https://github.com/gabime/spdlog): Fast C++ logging library.

## Usage

To use mal-toolkit in your C++ project, follow these steps:

1. Clone or download the mal-toolkit repository.

2. Integrate the library into your CMake project:

   ```cmake
   add_subdirectory(path/to/mal-toolkit)
   target_link_libraries(your_project PUBLIC mal-toolkit)
   target_include_directories(your_project PUBLIC MAL_TOOLKIT_INCLUDE)
   ```

3. Include the desired headers in your source files:

   ```cpp
   #include <mal_toolkit/mal_toolkit.hpp>
   #include <mal_toolkit/debug.hpp>
   // ... other headers ...
   ```

4. Make use of the utility functions and modules in your project code.

## Documentation

The library is documented using Doxygen. To generate the documentation, navigate to the root of the mal-toolkit directory and run:

```sh
doxygen Doxyfile
```

This will generate HTML documentation in the `docs` directory.

Or you can open documentation [here](https://malatindez.github.io/mal-toolkit/)

## License

mal-toolkit is released under the [MIT License](LICENSE). Feel free to use, modify, and distribute the library as needed.
