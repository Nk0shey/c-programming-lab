# Review and verification limits

## Completed correction pass

The original five compilation failures were resolved. All 48 standalone programs compile and link using C11 on Linux. Empty function stubs identified during inspection were completed, including nested ADT operations, tree operations, filtered extraction, device statistics, postal queues and scooter rental. Several menu branches were also wired to their implemented functions.

Tests run against the revised implementations, not the original archive. A passing test covers its asserted cases, not all paths of the surrounding exercise.

## Regression coverage

The automated runner covers linked ADT transfers and duplicate insertion, nested stacks/queues, circular-queue wraparound, delivery-client aggregation, book filtering/indexing/deletion, hospital-room collisions, phone-tree lookup/cleanup, weather-tree cleanup, lab request processing, postal FIFO operations, scooter transfers, taxi transitions/statistics, parcel-centre loading, ticket filtering, warehouse extraction, device periods across midnight and exact matrix output.

## Environment and remaining limits

- GCC 13.3.0 on Linux; the Python build was verified for all 48 programs.
- CMake configuration supplied but not executed because CMake was unavailable.
- Regression harnesses passed with UndefinedBehaviorSanitizer and AddressSanitizer. Leak detection was disabled because LeakSanitizer cannot inspect processes in this environment. Do not interpret this as a full leak audit.
- Compiler warnings remaining in legacy exercises are recorded in BUILD_AUDIT.md.
- Not every original loader, menu, malformed-input path, allocation failure or exercise specification has been functionally verified. Original training comments and alternative solutions are retained in places.
- The parcel-centre template had no file-format specification; its implemented loader uses one centre code per record, then `centre_code parcel_id destination weight priority` records. The regression test demonstrates this convention.
- Sources containing teaching prompts and starter code should be reviewed for ownership before public licensing.

This repository is suitable for continued academic development. A finished portfolio application should be selected and tested against its complete requirements separately.
