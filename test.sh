#!/bin/bash

has_passed=true
output_dir="src/test/output"

COLOR_OFF="$(tput sgr0)"
RED="$(tput setaf 1)"
GREEN="$(tput setaf 2)"

TEMP_DIFF_FILE=".diff_tmp"

function testOuput(){
    has_test_output_failed=false
    expected_output_dir="src/test/expected_output"
    
    # Get a list of input file names (excluding directories)
    input_files=$(find $expected_output_dir -type f -name "*.txt" -printf "%f\n")
    
    # Loop through the input files
    for file in $input_files; do
        # Construct the corresponding output file name
        output_file="$output_dir/$file"
        
        # Compare the input and output files using diff
        if  ! diff -y  "$expected_output_dir/$file" "$output_file" > $TEMP_DIFF_FILE;
        then
            printf "%s%s%s\n" $RED "FAIL: $file" $COLOR_OFF
            cat $TEMP_DIFF_FILE
            echo "----------------------------------------------"
            has_passed=false
            has_test_output_failed=true
        fi
    done
    rm $TEMP_DIFF_FILE
    ($has_test_output_failed && printf "%s%s%s\n" $RED "There is at least one difference from the expected output" $COLOR_OFF ) || printf '%s%s%s\n' $GREEN "The output is correct" $COLOR_OFF
}

[ ! -d "${output_dir}" ] && mkdir "${output_dir}"


# Compile and run the tests
echo "|-=-=-=-=-=-=-=-=-| Compiling tests |-=-=-=-=-=-=-=-=|"
make test
echo
echo "|-=-=-=-=-=-=-=-=-| Running tests |-=-=-=-=-=-=-=-=-|"

if ./test $1; then
    has_passed=true
else
    has_passed=false
fi

echo
echo "|-=-=-=-=-=-=-=-=-| Testing output |-=-=-=-=-=-=-=-=-|"

# Test the output
testOuput

echo
echo "|-=-=-=-=-=-=-=-=-| Results |-=-=-=-=-=-=-=-=-|"
($has_passed && printf '%s%s%s\n' $GREEN "All tests passed" $COLOR_OFF) || printf '%s%s%s\n' $RED "Some tests failed" $COLOR_OFF

# Exit with a non-zero status if any of the tests failed
$has_passed && exit 0

# Exit with a zero status if all the tests passed
exit 1