#!/bin/bash

has_passed=true
output_dir="src/test/output"

COLOR_OFF="$(tput sgr0)"
RED="$(tput setaf 1)"
GREEN="$(tput setaf 2)"

TEMP_DIFF_FILE=".diff_tmp"


function clean(){
    echo "|-=-=-=-=-=-=-=-=-| Cleaning up before tests |-=-=-=-=-=-=-=-=-|"
    make clean
}

function test_one_output(){
    # Construct the corresponding output file name
    local expected_output_dir=$1
    local output_dir=$2
    local file=$3
    local output_file="$output_dir/$file"
    
    if  ! diff -y  "$expected_output_dir/$file" "$output_file" > $TEMP_DIFF_FILE;
    then
        printf "%s%s%s\n" $RED "FAIL: $file" $COLOR_OFF
        cat $TEMP_DIFF_FILE
        echo "----------------------------------------------"
        return 1
    fi
    return 0
}

function test_main(){
    echo
    echo "|-=-=-=-=-=-=-=-=-| Testing compiling main |-=-=-=-=-=-=-=-=-|"
    make all
    
    echo
    echo "|-=-=-=-=-=-=-=-=-| Testing main function |-=-=-=-=-=-=-=-=-|"
    
    local has_main_test_failed=false
    local expected_output_dir="src/test/test_main/expected_output"
    local output_dir="src/test/test_main/output"
    local input_dir="src/test/test_main/input"
    
    # Get a list of output file names (excluding directories)
    local expected_output_files=$(find $expected_output_dir -type f -name "*.txt" -printf "%f\n")
    # Loop through the input files
    for file in $expected_output_files; do
        # Create the corresponding output file name
        local output_file="$output_dir/$file"
        local input_file="$input_dir/$file"
        local flags=""
        
        echo $file | grep "verbose.txt$" > /dev/null && flags="-v"
        ./main  "$input_file"  $flags > "$output_dir/$file"
        
        # if the test fails then set has_test_output_failed to true
        test_one_output $expected_output_dir $output_dir $file || has_main_test_failed=true
    done
    
    rm $TEMP_DIFF_FILE
    $has_main_test_failed && has_passed=false
    ($has_main_test_failed && printf "%s%s%s\n" $RED "There is at least one problem with the main function" $COLOR_OFF ) || printf '%s%s%s\n' $GREEN "The main function works" $COLOR_OFF
    
}

function compile_test(){
    echo
    echo "|-=-=-=-=-=-=-=-=-| Compiling tests |-=-=-=-=-=-=-=-=|"
    make test
}

function run_tests(){
    echo
    echo "|-=-=-=-=-=-=-=-=-| Running tests |-=-=-=-=-=-=-=-=-|"
    
    if ./test $1; then
        has_passed=true
    else
        has_passed=false
    fi
}

function test_ouput(){
    echo
    echo "|-=-=-=-=-=-=-=-=-| Testing output |-=-=-=-=-=-=-=-=-|"
    
    local has_test_output_failed=false
    local expected_output_dir="src/test/expected_output"
    local output_dir="src/test/output"
    
    # Get a list of input file names (excluding directories)
    local expected_output_files=$(find $expected_output_dir -type f -name "*.txt" -printf "%f\n")
    
    # Loop through the input files
    for file in $expected_output_files; do
        # if the test fails then set has_test_output_failed to true
        test_one_output $expected_output_dir $output_dir $file || has_test_output_failed=true
    done
    
    rm $TEMP_DIFF_FILE
    $has_test_output_failed && has_passed=false
    ($has_test_output_failed && printf "%s%s%s\n" $RED "There is at least one difference from the expected output" $COLOR_OFF ) || printf '%s%s%s\n' $GREEN "The output is correct" $COLOR_OFF
}



[ ! -d "${output_dir}" ] && mkdir "${output_dir}"

# Clean up before running the tests
clean

# Test the main function
test_main

# Compile and run the tests
compile_test

run_tests $1

# Test the output
test_ouput

echo
echo "|-=-=-=-=-=-=-=-=-| Results |-=-=-=-=-=-=-=-=-|"
($has_passed && printf '%s%s%s\n' $GREEN "All tests passed" $COLOR_OFF) || printf '%s%s%s\n' $RED "Some tests failed" $COLOR_OFF

# Exit with a non-zero status if any of the tests failed
$has_passed && exit 0

# Exit with a zero status if all the tests passed
exit 1
