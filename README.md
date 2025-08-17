# C Programs Collection

A curated set of C programs organized by topic. This repository is
intended for **learning, practice, and quick reference**. Each program
is self-contained unless otherwise noted, and most can be compiled with
a single `gcc` command.

## Project Structure

    C-Programs-main/
      Digital Logic/
        Makefile
        truthtable.c
      Matrix Operations/
        Makefile
        estimate.c

## Contents

### Digital Logic --- `truthtable.c`

-   Implements an **enumeration of logic gate types** (AND, OR, NOT,
    etc.).
-   Builds and prints a **truth table** for selected gates.
-   Demonstrates use of enums, conditionals, and formatted I/O in C.
-   **Entry point:** `main()` in `truthtable.c`.

### Matrix Operations --- `estimate.c`

-   Implements **basic matrix operations**.
-   Contains a function to **multiply two matrices** entered by the
    user.
-   Uses standard input/output for matrix dimension and element
    handling.
-   **Entry point:** `main()` in `estimate.c`.

## Build and Run

### Option 1: Using Makefile

If a Makefile is present in a folder, you can build targets directly:

``` bash
cd C-Programs-main/Digital Logic
make            # build default target
make clean      # remove build artifacts (if supported)
```

### Option 2: Using gcc directly

For a single-file program:

``` bash
cd C-Programs-main/Digital Logic
gcc -Wall -Wextra -O2 truthtable.c -o truthtable
./truthtable
```

For matrix operations:

``` bash
cd C-Programs-main/Matrix Operations
gcc -Wall -Wextra -O2 estimate.c -o estimate
./estimate
```

## Notes

-   Each program is standalone and illustrates **core C concepts** (I/O,
    arrays, control flow).
-   Check the **source comments** for usage details or input format
    expectations.
-   If extending these programs, consider refactoring repetitive I/O
    into utility functions for cleaner design.
