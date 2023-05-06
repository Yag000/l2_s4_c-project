#!/bin/bash

#TODO: remove output dirs before running tests

has_passed=true
use_valgrind=false
verbose=false
only_main=false
only_unit=false
output_dir="src/test/output"

COLOR_OFF="$(tput sgr0)"
RED="$(tput setaf 1)"
GREEN="$(tput setaf 2)"

TEMP_DIFF_FILE=".diff_tmp"
TEMP_VALGRIND_FILE=".valgrind_tmp"


function clean_before(){
    echo "|-=-=-=-=-=-=-=-=-| Cleaning up before tests |-=-=-=-=-=-=-=-=-|"
    make clean
}

#----------------------------------------------#
#-------------- Helper functions --------------#
#----------------------------------------------#

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

function run_with_valgrind(){
    local executable=$1
    shift
    local input_file=$1
    shift
    local flags=("$@")
    echo "Running valgrind on $executable $input_file ${flags[@]}"
    if ! valgrind --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all --error-exitcode=1 --log-file="$TEMP_VALGRIND_FILE" -q $executable  $input_file "${flags[@]}" ;
    then
        printf "%s%s%s\n" $RED "Valgrind FAIL: $input_file" $COLOR_OFF
        cat $TEMP_VALGRIND_FILE
        echo "----------------------------------------------"
        return 1
    fi
    return 0
}


function clean_temp_files(){
    rm -rf $TEMP_DIFF_FILE
    rm -rf $TEMP_VALGRIND_FILE
}
#----------------------------------------------#
#----------------- Test Main ------------------#
#----------------------------------------------#

function test_main_output_flag(){
    
    echo "-> Testing output flag"
    
    local has_test_output_failed=false
    local expected_output_dir="src/test/test_main/flag_test/output_flag/expected_output"
    local output_dir="src/test/test_main/flag_test/output_flag/output"
    local input_dir="src/test/test_main/flag_test/output_flag/input"
    [ ! -d "$output_dir" ] && mkdir "$output_dir"
    
    local files=$(find $input_dir -type f -name "*.txt" -printf "%f\n")
    
    for file in $files; do
        local output_file="$output_dir/$file"
        local input_file="$input_dir/$file"
        
        local flag="-o=$output_file"
        
        if $use_valgrind; then
            run_with_valgrind "./main" $input_file $flag has_test_output_failed=true
        else
            ./main $input_file $flag || has_test_output_failed=true
        fi
        
        test_one_output $expected_output_dir $output_dir $file || has_test_output_failed=true
    done
    
    clean_temp_files
    $has_test_output_failed && has_passed=false
    ($has_test_output_failed && printf "%s%s%s\n" $RED "There is at least one problem with the output flag" $COLOR_OFF ) || printf '%s%s%s\n' $GREEN "The output flag works" $COLOR_OFF
    
    $has_test_output_failed && return 1
    return 0
}

function test_main_record_flag(){
    
    echo "-> Testing record flag"
    
    local has_test_record_failed=false
    local expected_output_dir="src/test/test_main/flag_test/record_flag/expected_output"
    local output_dir="src/test/test_main/flag_test/record_flag/output"
    local input_dir="src/test/test_main/flag_test/record_flag/input"
    [ ! -d "$output_dir" ] && mkdir "$output_dir"
    
    local files=$(find $input_dir -type f -name "*.txt" -printf "%f\n")
    
    for file in $files; do
        local output_file="$output_dir/$file"
        local input_file="$input_dir/$file"
        
        local flag="-r=$output_file -o=/dev/null"
        
        if $use_valgrind; then
            run_with_valgrind "./main" $input_file $flag ||  has_test_record_failed=true
        else
            ./main $input_file $flag || has_test_record_failed=true
        fi
        
        test_one_output $expected_output_dir $output_dir $file || has_test_record_failed=true
    done
    
    clean_temp_files
    $has_test_record_failed && has_passed=false
    ($has_test_record_failed && printf "%s%s%s\n" $RED "There is at least one problem with the output flag" $COLOR_OFF ) || printf '%s%s%s\n' $GREEN "The output flag works" $COLOR_OFF
    
    $has_test_record_failed && return 1
    return 0
}

function test_flags(){
    local has_test_flags_failed=0
    test_main_output_flag || has_test_flags_failed=1
    test_main_record_flag || has_test_flags_failed=1

    return has_test_flags_failed
}

function test_main(){
    echo
    echo "|-=-=-=-=-=-=-=-=-| Testing compiling main |-=-=-=-=-=-=-=-=-|"
    make all
    
    echo
    echo "|-=-=-=-=-=-=-=-=-| Testing main function |-=-=-=-=-=-=-=-=-|"
    
    echo "-> Testing main function"
    local has_main_test_failed=false
    local expected_output_dir="src/test/test_main/expected_output"
    local output_dir="src/test/test_main/output"
    local input_dir="src/test/test_main/input"
    [ ! -d "$output_dir" ] && mkdir "$output_dir"
    
    # Get a list of output file names (excluding directories)
    local expected_output_files=$(find $expected_output_dir -type f -name "*.txt" -printf "%f\n")
    # Loop through the input files
    for file in $expected_output_files; do
        # Create the corresponding output file name
        local output_file="$output_dir/$file"
        local input_file="$input_dir/$file"
        local flags=()
        
        flags+=("-o=$output_file")
        echo $file | grep "verbose" > /dev/null && flags+=("-v")
        
        if $use_valgrind; then
            run_with_valgrind "./main" $input_file  "${flags[@]}" || has_main_test_failed=true
        else
            ./main $input_file "${flags[@]}" || has_main_test_failed=true
        fi
        
        # if the test fails then set has_test_output_failed to true
        test_one_output $expected_output_dir $output_dir $file || has_main_test_failed=true
    done
    
    clean_temp_files
    test_main_output_flag || has_main_test_failed=true
    $has_main_test_failed && has_passed=false
    
    echo
    ($has_main_test_failed && printf "%s%s%s\n" $RED "There is at least one problem with the main function" $COLOR_OFF ) || printf '%s%s%s\n' $GREEN "The main function works" $COLOR_OFF
    
}

#----------------------------------------------#
#----------------- Unit Tests -----------------#
#----------------------------------------------#

function compile_test(){
    echo
    echo "|-=-=-=-=-=-=-=-=-| Compiling tests |-=-=-=-=-=-=-=-=|"
    make test
}

function run_tests(){
    echo
    
    local flag=""
    $verbose && flag="-v"
    
    if $use_valgrind ; then
        echo "|-=-=-=-=-=-=-=-=-| Running tests with valgrind |-=-=-=-=-=-=-=-=-|"
        run_with_valgrind   "./test" "" $flag || has_passed=false
    else
        echo "|-=-=-=-=-=-=-=-=-| Running tests |-=-=-=-=-=-=-=-=-|"
        ./test $flag || has_passed=false
    fi
    
    $use_valgrind && rm $TEMP_VALGRIND_FILE
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
    
    clean_temp_files
    $has_test_output_failed && has_passed=false
    ($has_test_output_failed && printf "%s%s%s\n" $RED "There is at least one difference from the expected output" $COLOR_OFF ) || printf '%s%s%s\n' $GREEN "The output is correct" $COLOR_OFF
}


function unit_tests(){
    # Compile and run the tests
    compile_test
    
    # Run tests
    run_tests
    
    # Test the output
    test_ouput
}

#----------------------------------------------#
#----------------- Main -----------------------#
#----------------------------------------------#

function help(){
    echo "Usage: $0 [options]"
    echo "Options:"
    echo "  -v: verbose mode"
    echo "  --valgrind: run tests with valgrind"
    echo "  --only-main: only test the main function"
    echo "  --only-unit: only test the unit tests"
    echo "  -h|--help: display this help message"
}

[ ! -d "$output_dir" ] && mkdir "$output_dir"

while [[ $# -gt 0 ]]; do
    case $1 in
        -v)
            verbose=true
        ;;
        --valgrind)
            use_valgrind=true
        ;;
        --only-main)
            only_main=true
        ;;
        --only-unit)
            only_unit=true
        ;;
        -h|--help)
            help
            exit 0
        ;;
        *)
            echo "Invalid option: $1"
            exit 1
        ;;
    esac
    shift
done




# Clean up before running the tests
clean_before

# Test the main function
$only_unit || test_main

# Run the unit run_test
$only_main || unit_tests

echo
echo "|-=-=-=-=-=-=-=-=-| Results |-=-=-=-=-=-=-=-=-|"
($has_passed && printf '%s%s%s\n' $GREEN "All tests passed" $COLOR_OFF) || printf '%s%s%s\n' $RED "Some tests failed" $COLOR_OFF

# Exit with a non-zero status if any of the tests failed
$has_passed && exit 0

# Exit with a zero status if all the tests passed
exit 1
