# Second-computer import

Reviewed `Archive.zip` against the GitHub main snapshot `59ad65c4a7ee751341e728496abd2c31cc520192` on 2026-11-01. Comparison used exercise structure, function signatures, implementations and supplied datasets; filenames alone were not used to decide whether a project was new.

## Import decisions

The archive contains 14 C source files: eight distinct new exercises, four earlier copies of existing exercises, one repeated student-bonus exercise and one empty file.

Added:

- `class/code/main.c` → `exercises/class/even_numbers.c`: dynamically allocated input array and even-number extraction.
- `eser8apr/task/main.c` → `exercises/eser8apr/spedizioni.c`: shipment progress and unfinished-delivery export.
- `eser27march/task01/task02.c` → `exercises/eser27march/task02.c`: student-average bonus.
- `eser27march/task01/task03.c` → `exercises/eser27march/task03.c`: weather maximum and mean.
- `eser27march/task01/task04.c` → `exercises/eser27march/task04.c`: stable sorting of books by publication year.
- `eser27march/task01/task05.c` → `exercises/eser27march/task05.c`: overdue book-loan export.
- `eser27march/task01/task06.c` → `exercises/eser27march/task06.c`: exam results, course search, attendance statistics and grade updates.
- `esercitazione_01_04/esercitazione5/main.c` → `exercises/esercitazione_01_04/somma_ricorsiva.c`: recursive integer sum.

Kept the existing revised implementations instead of importing earlier/incomplete copies:

- `eser3guigno/agenda/agenda_telefonica.c` → existing `exercises/eser3giugno/agenda_telefonica.c`.
- `eser5guigno/libri/testo.c` → existing `exercises/eser5giugno/testo.c`.
- `eser20magg/untitled1/coda_ordini.c` → existing `exercises/eser20magg/coda_ordini.c`.
- `esercitazione_01_04/file/main.c` → existing `exercises/eser5magg/supermercato.c` (same structs, operations and supermarket menu).

Skipped `esercitazione_01_04/esercitazione2/main.c`, which implements the same student-bonus operation as `task02.c`, and the empty `esercitazione_01_04/esercitazione1/main.c`.

IDE configuration, generated CMake files, executables, macOS metadata and historical output outside the selected reference fixtures were not imported. Original example inputs recovered from build folders are included separately under `examples/recovered/`; the phone-directory dataset was not imported.

## Corrections

- Fixed weather averaging, which previously omitted the first observation.
- Shipment loading now validates all declared records before returning an array and count; partial records, invalid distances, oversized fields and extra records fail without exposing uninitialized elements. Removed the IDE-specific input path.
- Fixed exam results writing into `voto1` rather than `voto_finale`, incorrect string input, uninitialized export counts, missing menu breaks, missing line separators, reload state and unchecked capacity. Repeated calculation preserves the original marks.
- Bounded record input and validated finite numerical values, grades, quantities and attendance. Fixed-size loaders reject excess records rather than silently truncate input. Output routines report detected write and close errors.
- Loan delays are recomputed from scratch, so a former overdue loan can become regular.
- Empty even-number results succeed; malformed console input and incomplete arrays exit cleanly. Array sizes are bounded to 1,000,000 elements. The recursion demo supports 0–1000 to keep stack usage bounded.
- Checking the supermarket duplicate revealed an existing canonical quantity-update bug: a different code could be updated while an exact match was ignored. Corrected matching and added a regression for the first node, later node, missing code and negative quantity. Fixed the insertion-result check and release of repeated menu result allocations.

## Rules and formats

The supplied exam source has no accompanying grading prompt. Its explicit calculation is retained: both marks must be at least 18, their mean must be strictly greater than 18, and the rounded mean plus 2 is capped at 31. Attendance is a fraction from 0 to 1 in the supplied input and is reported separately; it does not change the grade. This documents the recovered behavior, not an independently confirmed university grading policy.

Book years may be negative, as in the supplied `Odissea -800` record. Loan input stores elapsed days before allowed days. Record fields are separated by whitespace; use underscores inside names and titles. Shipment inputs begin with a positive record count and require exactly that many records. Other new file exercises accept empty files as empty datasets.

## Verification

- All 56 exercise targets build with CMake on Linux/GCC.
- All 93 CTest checks pass: 36 functional checks, 56 entrypoint termination checks and one end-to-end suite exercising all eight recovered programs.
- The same 93 checks pass with AddressSanitizer and UndefinedBehaviorSanitizer. Leak detection is disabled in this environment; the sanitizer results do not establish leak freedom.
- Recovered student-bonus, sorted-book, overdue-loan and pending-shipment outputs match the archived reference outputs byte for byte. Weather and exam examples are checked against corrected calculations.
- New regression cases cover malformed/missing files, record limits, invalid distances, empty statistics, stable sorting, grade recalculation and output failures via `/dev/full` on Linux.

These are finite regression checks, not proof that all inputs and all historical programs are correct. Existing exercises retain their earlier coverage and limitations; this import does not reimplement the whole collection. Windows and macOS have not been tested.
