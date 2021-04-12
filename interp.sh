#!/usr/bin/env bash

PDM_INPUT_SCRIPT=$1

if test -f "${PDM_INPUT_SCRIPT}"
then

  # see: https://stackoverflow.com/questions/965053/extract-filename-and-extension-in-bash
  PDM_LLVM_IR_FILE="${PDM_INPUT_SCRIPT%.*}.ll"

  echo ${PDM_LLVM_IR_FILE}

  ./build/porch ${PDM_INPUT_SCRIPT} wasi

  if test -f "$PDM_LLVM_IR_FILE"
  then

    cat "${PDM_LLVM_IR_FILE}" > interp.tmp.ll
    echo 'define i32 @"main"() {
      %"return value" = call i32 @"root_$_entry_point_$_main"()
      ret i32 %"return value"
    }' >> interp.tmp.ll

    lli interp.tmp.ll
    RC=$?

    echo "Process exited with return code ${RC}"

    rm interp.tmp.ll
    exit ${RC}

  else

    echo "Compilation failed"
    exit 1

  fi

else

  echo "Input file does not exist"

fi