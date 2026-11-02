# C Programming Lab

**56 C programs exploring data structures, algorithms and file-based simulations.**

By [Nikita Kozchenko](https://github.com/Nk0shey) · Computer Engineering, University of Catania

C11 · CMake · CTest · Regression checks · Sanitizer support

[Build](#build-and-run) · [Examples](#examples) · [Tests](#tests) · [Review](docs/REVIEW.md)

University practice with arrays, linked lists, stacks, queues, binary trees and combinations of those structures. The collection includes simulations of delivery services, libraries, help desks, taxi fleets, warehouses and irrigation systems. Original Italian identifiers and dated folders preserve the course context.

## Build and run

Requires a C11 compiler (`cc`, GCC or Clang) and CMake 3.16+. Python is not required for the primary workflow.

```sh
cmake -S . -B build
cmake --build build --parallel 2
```

Build and run a single exercise:

```sh
cmake --build build --target alberi_ricercaAlbero
./build/alberi_ricercaAlbero
```

```text
Elemento trovato: 57
Altezza albero: 3
```

The standalone example can also be compiled directly:

```sh
cc -std=c11 exercises/alberi/ricercaAlbero.c -o ricercaAlbero
./ricercaAlbero
```

Exercises with separate implementation files need those files linked too; the CMake targets handle this. On Windows with a multi-configuration generator, add `--config Debug`, use `build/Debug/<target>.exe`, and test with `ctest --test-dir build -C Debug`. Windows/macOS have not been verified during this review.

## Where to start

- `exercises/eser6magg/`, `exercises/eser8magg/`: stack and queue representations.
- `exercises/alberi/`: tree construction, traversal and search.
- `exercises/eser3giugno/`: tree-indexed telephone directory.
- `exercises/es1/`, `exercises/eser9giugno/`: delivery simulations.
- `exercises/es2/`, `exercises/eser5giugno/`: book loans and indexing.
- `exercises/es3/`: ticket filtering with an array of queues.
- `exercises/chat1/`, `exercises/sim24aug/`: nested structures and mixed simulations.
- `exercises/class/`, `exercises/eser8apr/`, `exercises/eser27march/`, `exercises/esercitazione_01_04/`: recovered array, file-processing and recursion exercises.
- `tests/`: small regression harnesses with isolated working directories.

## Examples

[The irrigation demo](examples/irrigation/README.md) provides complete input files and menu instructions. It explains a discrepancy between the assignment's written formula and its historical sample.

[Recovered examples](examples/recovered/README.md) cover shipments, student bonuses, weather, book sorting, loan delays and exam results. The [import report](docs/SECOND_COMPUTER_IMPORT.md) records duplicate decisions and the grading rule preserved from the source.

Many exercises read files relative to the current working directory and write output files there. Run them with the appropriate example data in a disposable working directory. Input formats are documented in the source or example instructions.

## Tests

```sh
ctest --test-dir build --output-on-failure
```

The suite has **93 checks**: 36 functional checks, 56 entrypoint-termination checks and one end-to-end suite for the recovered programs. Tests cover FIFO/LIFO ordering, cleanup, filtering, sorting ties, file errors, statistics and exact expected outputs. Assertions stay enabled in Release builds.

Optional GCC/Clang sanitizers:

```sh
cmake -S . -B build-sanitize -DENABLE_SANITIZERS=ON
cmake --build build-sanitize --parallel 2
ctest --test-dir build-sanitize --output-on-failure
```

Where LeakSanitizer process inspection is unavailable, use `ASAN_OPTIONS=detect_leaks=0` before the CTest command. This keeps address/undefined-behavior checks but does not check leak freedom. The optional `python3 tests/run.py` runs the 36 functional checks; Python is required only for that alternative. Use `-DBUILD_TESTING=OFF` to build just the exercises.

## Verification and scope

The latest repository-wide review rebuilt all 56 programs and reran all 93 checks on Linux/GCC. The earlier correction/import pass also passed the sanitizer configuration. The empty historical `hw1/task5.c` is not a runnable target. Passing tests does not establish correctness of every historical exercise or every menu path.

Small console exercises stop on malformed/incomplete input through `common/console.h`; they do not all recover an interactive session. The irrigation menu validates full lines and retries. Entry-point checks verify termination, while business-rule coverage varies by exercise.

See [current review](docs/REVIEW.md), [historical audit](docs/AUDIT.md) and [changes](docs/CHANGES.md) for the exact scope. Original prompts and teaching scaffolds may have separate authorship; no blanket license has been assigned.
