# Recovered exercise examples

Build from the repository root:

```sh
cmake -S . -B build
cmake --build build --parallel 2
```

The file-based exercises use filenames relative to the current working directory. Copy their example directory to a scratch directory before running because the programs write outputs there.

For example, from the repository root, copy `examples/recovered/shipments/Spedizioni.txt` into a temporary directory, change into that directory, and run `/absolute/path/to/c-programming-lab/build/eser8apr_spedizioni`. At the prompt enter `pending.txt`. The result matches `expected_pending.txt` (13 unfinished deliveries).

The `eser27march` directory provides inputs for these CMake targets:

- `eser27march_task02`: `es_2_studenti.txt` → `es_2_studenti_bonus.txt`; compare with `expected_bonus.txt`.
- `eser27march_task03`: `es_3_meteo.txt` → maximum 21.30 and mean 12.19 on standard output.
- `eser27march_task04`: `es_4_libri.txt` → `libri_ordinati.txt`; compare with `expected_books.txt`. Negative publication years are supported.
- `eser27march_task05`: `es_5_prestiti_libri.txt` → `es_5_ritardi_prestiti.txt`; compare with `expected_loans.txt`. Each input record ends with elapsed days, then allowed days.
- `eser27march_task06`: `es_6_esito_esami.txt`; select 1 to load, 2 to list, 3 to export failures, 4 to find a course maximum, 5 for attendance, 6 to export IDs above a mean threshold, 7 to update marks, 0 to quit. Attendance uses fractions 0–1. The supplied 15 records yield average attendance 0.84 among passing students. See the [import report](../../docs/SECOND_COMPUTER_IMPORT.md) for the recovered grading rule.

The original datasets were recovered from the uploaded archive. CTest uses temporary copies and verifies the reference outputs without modifying these examples.

The two console-only targets need no files:

```sh
printf '5\n1 2 -4 5 6\n' | ./build/class_even_numbers
# Vettore pari: 2 -4 6
printf '10\n' | ./build/apr01_somma_ricorsiva
# The somma number is: 55
```

The recursion demonstration supports 0–1000. Windows users can type the input interactively and use `build/Debug/<target>.exe` with multi-configuration generators.
