#!/bin/bash

verbose=false
has_failed=false

function testOuput(){
    expected_output_dir="src/test/expected_output"
    output_dir="src/test/output"
    
    # Get a list of input file names (excluding directories)
    input_files=$(find $expected_output_dir -type f -name "expected_output*" -printf "%f\n")
    
    # Loop through the input files
    for file in $input_files; do
        # Construct the corresponding output file name
        output_file="$output_dir/${file/expected_output/output}"
        
        # Compare the input and output files using diff
        if ! diff "$expected_output_dir/$file" "$output_file" >/dev/null;
        then
            echo "FAIL: $file"
            has_failed=true
        fi
    done
}

#Add a flag for a verbose oftion
[ "$1" == "-v" ] && verbose=true

# Compile and run the tests
make test

# Run the tests
$verbose && ./test -v
! $verbose && ./test

# Test the output
testOuput

# Exit with a non-zero status if any of the tests failed
$has_failed && exit 1

# Exit with a zero status if all the tests passed
exit 0