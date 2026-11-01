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

Requires Python 3 and a C11 compiler (`cc`, `gcc` or `clang`).

```sh
python3 build.py
python3 build.py --list
python3 build.py alberi_ricercaAlbero
./build/alberi_ricercaAlbero
```

Expected output for that demonstration:

```text
Elemento trovato: 57
Altezza albero: 3
```

Each exercise builds separately. Alternative CMake configuration is included, requiring CMake 3.16 or later:

```sh
cmake -S . -B build-cmake
cmake --build build-cmake --parallel 2
```

The Python build has been verified on Linux. CMake was unavailable in the preparation environment, so that configuration has not been exercised.

## Tests

```sh
python3 tests/run.py
python3 tests/run.py --sanitize
python3 tests/run.py --sanitize --address
```

The regression runner compiles isolated harnesses and executes them in a temporary directory. Tests cover empty structures, FIFO/LIFO order, transfer and deletion, filtering, statistics, file loading and the corrected matrix result. `--sanitize` enables UndefinedBehaviorSanitizer; `--address` adds AddressSanitizer. These options require a supporting GCC/Clang toolchain.

The preparation environment does not support LeakSanitizer's process inspection; the address-sanitizer run used:

```sh
ASAN_OPTIONS=detect_leaks=0 python3 tests/run.py --sanitize --address
```

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

All 48 programs compile and link after this correction pass. See [review notes](docs/REVIEW_NOTES.md) and the [build audit](docs/BUILD_AUDIT.md).

## Provenance

The original archive included exercise prompts, starter code and student implementations. Individual authorship of supplied teaching scaffolds has not been established. The correction pass completed identified empty function stubs, repaired identified defects, added regression tests and prepared build/documentation files. See [changes](docs/CHANGES.md). The original upload remains separate; this repository contains the revised working versions.

No blanket open-source license has been assigned to teaching material whose ownership has not been confirmed.
