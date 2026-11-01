# C Programming Lab

University practice in C by [Nikita Kozchenko](https://github.com/Nk0shey), a Computer Engineering student at the University of Catania.

48 standalone programs exploring arrays, linked lists, stacks, queues, binary trees and file-based simulations. This repository documents academic practice and subsequent improvements. It is a learning collection, with varying test coverage across exercises.

## Highlights

- Static, dynamic and linked stacks; sequential and linked queues.
- Lists of queues, queues of stacks, stacks of lists and stacks of queues.
- Simulations of delivery services, libraries, help desks, taxi fleets and warehouses.
- Binary-search-tree construction, traversal, search and cleanup.
- File input, filtering and dynamic statistics, including device energy-consumption periods.
- Automated regression checks for the completed functions and corrected defects.

Italian identifiers and original folder names are retained so the work remains traceable to its course context. Documentation is in English.

## Build and run

Requires a C11 compiler (`cc`, `gcc` or `clang`) and CMake 3.16 or later. Python is not required to build or run the C programs.

Build all exercises:

```sh
cmake -S . -B build
cmake --build build --parallel 2
```

Build and run one exercise:

```sh
cmake --build build --target alberi_ricercaAlbero
./build/alberi_ricercaAlbero
```

Expected output:

```text
Elemento trovato: 57
Altezza albero: 3
```

You can also compile this standalone example directly without CMake:

```sh
cc -std=c11 exercises/alberi/ricercaAlbero.c -o ricercaAlbero
./ricercaAlbero
```

Exercises using separate implementation files must compile and link those files too; the CMake targets handle this automatically.

All 48 programs were compiled individually on Linux. CMake configuration and the full build have been verified on Linux with GCC 13.3.0.

## Tests

The primary test workflow uses CMake and CTest, with no Python dependency:

```sh
cmake -S . -B build
cmake --build build --parallel 2
ctest --test-dir build --output-on-failure
```

29 functional checks cover data-structure operations, cleanup, FIFO/LIFO ordering, filtering, sorting ties, invalid file input, closed-ticket statistics and exact matrix output. Another 48 entrypoint checks exercise empty, incomplete and malformed console input. Each regression test has an isolated working directory and keeps assertions enabled in Release builds.

Optional memory and undefined-behaviour checks with GCC or Clang:

```sh
cmake -S . -B build-sanitize -DENABLE_SANITIZERS=ON
cmake --build build-sanitize --parallel 2
ctest --test-dir build-sanitize --output-on-failure
```

Where LeakSanitizer cannot inspect processes (as in the preparation environment), use `ASAN_OPTIONS=detect_leaks=0` before the CTest command. Address and undefined-behaviour checks remain enabled; this does not verify leak freedom.

The optional `python3 tests/run.py` runner runs the 29 functional checks (the 48 entrypoint checks are registered with CTest). Python is needed only for that alternative runner. Use `-DBUILD_TESTING=OFF` to build exercises without the regression executables.

## Navigate

- `exercises/hw1/`: array operations and search.
- `exercises/eser17apr/`: linked lists and library records.
- `exercises/eser6magg/`, `exercises/eser8magg/`: stack and queue representations.
- `exercises/alberi/`: binary-tree practice.
- `exercises/eser3giugno/`: telephone directory grouped in a search tree.
- `exercises/es1/`, `exercises/eser9giugno/`: delivery simulations.
- `exercises/es2/`, `exercises/eser5giugno/`: book loans and indexing.
- `exercises/es3/`: ticket filtering with an array of queues.
- `exercises/chat1/`: mixed ADT, parcel-centre, postal, scooter and device-log exercises.
- `exercises/sim24aug/`: nested ADT variants and drone-base simulation.
- Other dated and simulation folders: additional academic practice.
- `tests/`: regression harnesses.
- `docs/`: compilation audit, changes and verification limits.

## Input files and scope

Many programs expect text input files in their current working directory. Original datasets were not included outside IDE-generated build folders. Source comments describe the exercise-specific formats; regression tests create synthetic data for their own checks. Run file-based programs in a temporary directory because some write output files.

All 48 programs compile and link on the verified Linux toolchain. Passing compilation and 29 functional checks and 48 entrypoint checks does not establish correctness of every exercise or interactive path. See the [repository audit](docs/AUDIT.md), [review notes](docs/REVIEW_NOTES.md) and the [build audit](docs/BUILD_AUDIT.md).

## Provenance

The original archive included exercise prompts, starter code and student implementations. Individual authorship of supplied teaching scaffolds has not been established. The correction pass completed identified empty function stubs, repaired identified defects, added regression tests and prepared build/documentation files. See [changes](docs/CHANGES.md). The original upload remains separate; this repository contains the revised working versions.

No blanket open-source license has been assigned to teaching material whose ownership has not been confirmed.

On Windows with a multi-configuration generator, build with `--config Debug`, test with `ctest --test-dir build -C Debug`, and use `build/Debug/<target>.exe`. Windows and macOS have not been verified in this review.

## Irrigation demo

A complete example with input files and menu instructions is provided in [examples/irrigation](examples/irrigation/README.md). The implementation follows the written exercise formula; the discrepancy with the historical sample is explained there.

## Console input

Small console exercises use `common/console.h` to stop with a diagnostic and exit status 1 on an incomplete or malformed scan, rather than continue with uninitialized values. String scans have finite widths and line draining handles EOF. This fail-fast path exits the process; it does not recover the interactive session. The irrigation menu instead validates full lines and prompts again.

The entrypoint tests check termination, not each application's business rules. File parsers and application-specific valid-input scenarios have separate, varying test coverage.
