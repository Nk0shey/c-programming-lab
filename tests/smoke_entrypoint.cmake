# These are termination checks, not full application acceptance tests.
file(MAKE_DIRECTORY "${WORK}")
foreach(mode empty zero malformed)
  set(input "")
  if(mode STREQUAL "zero")
    set(input "0\n")
  elseif(mode STREQUAL "malformed")
    set(input "invalid\n")
  endif()
  file(WRITE "${WORK}/${mode}.txt" "${input}")
  execute_process(COMMAND "${PROGRAM}" WORKING_DIRECTORY "${WORK}"
    INPUT_FILE "${WORK}/${mode}.txt" OUTPUT_QUIET ERROR_VARIABLE diagnostic
    RESULT_VARIABLE result TIMEOUT 3)
  if(NOT result MATCHES "^[01]$")
    message(FATAL_ERROR "${PROGRAM}: ${mode} input returned ${result}: ${diagnostic}")
  endif()
endforeach()
