file(WRITE "${SCRIPT_PATH}" "${SCRIPT}")
execute_process(
  COMMAND "${RUNNER}" "${SCRIPT_PATH}"
  TIMEOUT 10
  RESULT_VARIABLE result
  ERROR_VARIABLE error
)
file(REMOVE "${SCRIPT_PATH}")
if(NOT result STREQUAL "1" OR NOT error MATCHES "${EXPECTED_ERROR}")
  message(FATAL_ERROR "Expected exit 1 with '${EXPECTED_ERROR}', got '${result}': ${error}")
endif()
