# FileGuard

FileGuard is a C++ command-line tool that checks whether a file has changed by comparing its SHA-256 hash with a previously saved hash.

This is my first public C++ project. I'm building it to practice file handling, input validation, and hashing, and will improve it as I learn.

## Features

- Save multiple file paths and their SHA-256 hashes.
- Select a saved file to check for changes.
- Report whether the file matches its saved hash.
- Report when a file cannot be opened.

## Usage

1. Start FileGuard.
2. Enter the path of a file to save its initial hash.
3. Add more files if needed, then enter `n` to continue.
4. Select a file using its number.
5. FileGuard calculates its current hash and compares it with the saved value.

Paths and hashes are stored in `meta.txt` in the working directory. Keep this file between runs to compare against the original hashes.

## Building

The project is developed with Visual Studio and C++.

1. Clone or download the repository.
2. Open the solution in Visual Studio with the C++ desktop development workload installed.
3. Build and run the project.

The SHA-256 implementation used by `sha256.h` must be included in the build.

## Limitations

FileGuard checks files only when you run a scan. It does not monitor them in the background or prevent modifications.

The saved hashes in `meta.txt` are not protected against changes. This project is intended for learning and basic file comparison.

## Planned improvements

- Improve input validation and error handling.
- Validate saved metadata more thoroughly.
- Allow saved entries to be removed or updated.
- Add a graphical interface.
