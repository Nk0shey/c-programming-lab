# Repository audit

Current extension: the [second-computer import](SECOND_COMPUTER_IMPORT.md) brings the collection to 56 programs and 93 passing CTest checks. The sections below record earlier review stages and their historical counts.

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

- Resolved in the completion pass: the irrigation exercise now implements loading, updating, listing, indexing, lookup, reload and cleanup, with synthetic fixtures and a full menu regression test. The written formula is used; the contradictory historical sample is explained in examples/irrigation/README.md.
- Resolved for console scanning in the completion pass: scans fail fast on missing/malformed input, string conversions have finite widths, and line draining stops at EOF. This is process termination rather than interactive recovery; malformed numeric extremes and file parsing still need application-specific validation.
- Some original exercise comments still say TODO even where an implementation follows. These are not a reliable completion checklist.
- Original runtime datasets are absent; synthetic regression fixtures cover selected paths only.
- Some compiler warnings and analyzer reports remain in untested legacy paths. No blanket claim of memory safety, allocation-failure correctness or full specification compliance is made.
- Windows/macOS and all compiler families have not been tested.

Further changes should focus on completing and testing one portfolio application end to end, then improving the remaining archive incrementally. Automatically rewriting every exercise would obscure the educational history and exceed what the current tests can validate.

## Completion pass

- Added the irrigation implementation, strict record validation, memory cleanup and a documented example dataset.
- Added 48 isolated entrypoint checks (empty/zero/malformed input) alongside 29 functional checks.
- Fixed patient admission input, circular probing for 17 rooms (the supplied hash's range), repeated tree rebuilding and normal-exit cleanup.
- Fixed the queue-interleaving exercise to populate its second queue correctly.
- All 48 exercises build; 77 CTest checks pass in the normal and sanitizer builds. Leak detection remains disabled for the environment limitation above.

These results establish the scenarios asserted by the tests. They do not recover the exact text of earlier unsaved versions or prove that every original file parser and allocation-failure path is correct.
