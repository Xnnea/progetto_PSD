# PSD Project (Gestatt) - Compilation and Execution Instructions
PSD Project for the first year of Computer Science (2024/2025).


## Prerequisites
- GCC compiler installed on your system
- Make utility available

## Compilation

### Build the main program
To compile the main program, run:
```bash
make
```
or
```bash
make gestatt
```

This command will:
- Create the `bin/` directory if it doesn't exist
- Compile all source files from the `src/` directory
- Generate the executable `gestatt` in the `bin/` directory

### Build and run tests
To compile and execute the test suite, run:
```bash
make test
```

This command will:
- Compile the test version using `test_main.c` instead of `main.c`
- Create the test executable `gestatt_test` in the `tests/` directory
- Automatically run the tests

## Execution

### Run the main program
After compilation, execute the program with:
```bash
cd bin
./gestatt
```

### Run tests only
If you've already compiled the tests and want to run them again:
```bash
cd tests
./gestatt_test
```

## Cleanup
To remove compiled executables, run:
```bash
make clean
```

This will delete:
- `bin/gestatt` (main executable)
- `tests/gestatt_test` (test executable)

## Project Structure
The project follows this directory structure:
```
.
├── src/           # Source code files
├── tests/         # Test directory and test executable
├── bin/           # Main executable directory (created during build)
├── docs/          # Documentation files
└── Makefile       # Build configuration
```

