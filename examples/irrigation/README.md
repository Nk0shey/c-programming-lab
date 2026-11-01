# Irrigation example

From the repository root:

```sh
cmake -S . -B build
cmake --build build --target compiti_anni_precedenti_compito_5_testo
./build/compiti_anni_precedenti_compito_5_testo examples/irrigation/aree.txt examples/irrigation/zone.txt
```

Enter `1` to load, `2` to list active zones, `4` to build the index and `5` followed by `Z1` to look up its time (30 seconds). `Z2` is suppressed by rain probability and `Z3` is off.

Option `3` accepts a zone code, state (0/1) and correction factor. A negative factor preserves the old factor. For example, `Z3 1 0.5` activates Z3 with a 45-second time. Rebuild the index with option `4` after an update. Option `1` can reload data safely; a failed reload preserves the old plant.

The formula follows the written exercise specification: `(100 - humidity) * correction_factor`, truncated to whole seconds. The historical example in the uploaded source multiplied by flow as well, contradicting the written specification. Flow is retained as zone metadata and is not used in this calculation.

Input files reject duplicates, missing areas, extra fields, invalid states, out-of-range percentages/factors and non-finite floats. On malformed console lines the menu prompts again; EOF exits and frees the plant and index.
