# Repository audit

Reviewed the GitHub main snapshot `b0a192324249554f030de0e6ac0a1fbe498a4517` and applied the corrections below. Local file comparisons accounted for GitHub text newline normalization.

## Verified

- 48 exercise programs configured and built through CMake on Linux, GCC 13.3.0.
- 27 CTest checks passed in the standard build and with AddressSanitizer/UndefinedBehaviorSanitizer enabled. Leak detection was disabled because process inspection is unavailable in this environment.
- The optional Python test runner was checked separately without sanitizer flags.
- All exercise translation units were compiled with warning flags and GCC's static analyzer. Static-analysis output is a diagnostic aid, not proof of a defect or its absence.

## Changes

- Made CMake/CTest the complete primary build-and-test workflow. Removed the redundant root `build.py` and updated stale documentation.
- Isolated CTest working directories; assertions remain enabled in Release builds. Added an opt-in sanitizer configuration.
- Fixed the optional test runner's unconditional matrix sanitizer flags and limited its Linux-specific link flag to Linux.
- Fixed null dereference during linked-list cleanup and allocation checks in shipment enqueueing.
- Reused tested cleanup, loan, loader and filtering operations in the equivalent library variant.
- Initialized the delivery variant's customer tree and aggregated by customer code rather than rider code.
- Reworked laboratory loading to clean partially built queues, reject unknown laboratories and close the input file exactly once.
- Counted only matched open/closed ticket periods, preventing uninitialized trailing statistics.
- Corrected sorting tie-breaks and guarded sorters against missing arrays; reset dimensions after failed allocations.
- Added regression coverage for the newly identified defects.

## Remaining work

This remains an academic collection, not 48 finished applications. In particular:

- The irrigation exercise (`compiti anni precedenti/compito 5/testo.c`) still has unwired menu branches for loading/modifying data and lacks complete main-level cleanup. It should not be promoted as a finished application.
- Many legacy interactive inputs use unchecked `scanf` results or unbounded string formats. Malformed input and end-of-file behaviour need a separate systematic pass before calling the applications robust.
- Some original exercise comments still say TODO even where an implementation follows. These are not a reliable completion checklist.
- Original runtime datasets are absent; synthetic regression fixtures cover selected paths only.
- Some compiler warnings and analyzer reports remain in untested legacy paths. No blanket claim of memory safety, allocation-failure correctness or full specification compliance is made.
- Windows/macOS and all compiler families have not been tested.

Further changes should focus on completing and testing one portfolio application end to end, then improving the remaining archive incrementally. Automatically rewriting every exercise would obscure the educational history and exceed what the current tests can validate.
