# Mini Grep C++

## Overview

Mini Grep is a command-line tool written in C++ that allows you to search for specific text patterns within files. It is designed to provide basic text searching functionality similar to the Unix `grep` command.

## Features

- Search for text patterns within files.
- Display matching lines.
- Perform case-sensitive or case-insensitive searches.
- Search for patterns using regular expressions (regex).
- Output results to the console or a file.

## Usage

To use Mini Grep, follow these basic usage instructions:

1. Compile the program: You can compile the source code using a C++ compiler like g++ or cmake.
   
   ```bash
   mkdir build && cd build
   ```
   ```bash
   cmake ..
   ```
   ```bash
   make
   ```


2. Run the program with the desired options:

   ```bash
   ./minigrep [options] pattern file
   ```

   - `[options]`:
     - `-i`: Perform a case-insensitive search.
     - `-r`: Use regular expressions for pattern matching.
     - `-o <output_file>`: Specify an output file for results.
   
   - `pattern`: The text pattern you want to search for.
   - `file`: The name of the file or files you want to search within.

## Examples

- Search for the word "bog" in a file:
   
   ```bash
   ./mini_grep bog ../poem.txt
   ```

- Perform a case-insensitive search for "pattern" in multiple files:

   ```bash
   ./mini_grep -i pattern file1.txt file2.txt
   ```

- Use regular expressions to search for email addresses and save the results to a file:

   ```bash
   ./mini_grep -r -o results.txt "^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,4}$" emails.txt
   ```

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE.md) file for details.

## Contributing

Feel free to contribute to the project by submitting pull requests or opening issues on the [GitHub repository](https://github.com/xyzeebit/minigrep-cpp).

## Disclaimer

This is a basic implementation of a grep-like tool in C++. It may not have all the features or performance of the standard Unix `grep` command.
