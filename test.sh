#!/bin/bash

has_passed=true
output_dir="src/test/output"

function testOuput(){
    expected_output_dir="src/test/expected_output"
    
    # Get a list of input file names (excluding directories)
    input_files=$(find $expected_output_dir -type f -name "*.txt" -printf "%f\n")
    
    # Loop through the input files
    for file in $input_files; do
        # Construct the corresponding output file name
        output_file="$output_dir/$file"
        
        # Compare the input and output files using diff
        if ! diff "$expected_output_dir/$file" "$output_file" ;
        then
            echo ""
            echo "FAIL: $file"
            has_passed=false
        fi
    done
    
    # rm -rf src/test/output/*
}

[ ! -d "${output_dir}" ] && mkdir "${output_dir}"


# Compile and run the tests
echo "Compiling..."
make test
echo
echo
echo "----------------Running tests----------------"

if ./test $1; then
    has_passed=true
else
    has_passed=false
fi

echo
echo "----------------Testing output----------------"

# Test the output
testOuput

# Exit with a non-zero status if any of the tests failed
$has_passed && exit 0

# Exit with a zero status if all the tests passed
exit 1