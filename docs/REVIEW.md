# Repository review — 2026-11-02

Rebuilt the current GitHub source snapshot with CMake/GCC and reran CTest on Linux. All 56 exercise targets compile and all 93 checks pass: 36 functional checks, 56 termination checks and one recovered-program end-to-end suite.

Reorganized the root README around quick start, selected exercises, examples, verification and limits. The earlier sanitizer results are retained as historical verification; this repository-wide pass reran the standard configuration. No new C algorithm changes were needed for the repeated build/test checks.

Coverage differs across exercises. Termination checks are not full acceptance tests, invalid console input is often fail-fast, and very large/unspecified inputs have not been exhaustively checked. The empty historical hw1/task5.c remains excluded from CMake. See AUDIT.md and SECOND_COMPUTER_IMPORT.md for earlier corrections and assumptions.
