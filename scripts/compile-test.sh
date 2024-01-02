#!/usr/bin/env bash

DIR=${1:-.}
SCRIPT_DIR=$DIR/scripts

tests="$(find $DIR/content -name '*.hpp')"

declare -i pass=0
declare -i fail=0
failTests=""

for test in $tests; do
  echo "$(basename $test): "
  $SCRIPT_DIR/compile.sh $test
  res=$?
  if (($res != 0)); then
    echo "Failed with $res"
    fail+=1
    failTests="$failTests$(basename $test)\n"
  else
    pass+=1
  fi
  rm -f a.out
  echo
done

echo "$pass/$(($pass+$fail)) tests passed"
if (($fail==0)); then
    echo "No tests failed"
    exit 0
else
    echo -e "These tests failed: \n $failTests"
    exit 1
fi
