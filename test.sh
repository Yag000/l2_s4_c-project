#!/bin/bash

has_passed=true
use_valgrind=false
verbose=false
only_main=false
only_unit=false

COLOR_OFF="$(tput sgr0)"
RED="$(tput setaf 1)"
GREEN="$(tput setaf 2)"

TEMP_DIFF_FILE=".diff_tmp"
TEMP_VALGRIND_FILE=".valgrind_tmp"

CURRENT_TESTING_DIR=""
CURRENT_TESTING_FILE=""
CURRENT_FLAGS=()


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
    local should_fail=$1
    shift
    if ! valgrind --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all --error-exitcode=1 --log-file="$TEMP_VALGRIND_FILE" -q $executable  $CURRENT_TESTING_FILE ${CURRENT_FLAGS[@]} ;
    then
        [ -z $(cat $TEMP_VALGRIND_FILE) ] && $should_fail  && return 0
        printf "%s%s%s\n" $RED "The program failed unexpectedly while testing $CURRENT_TESTING_FILE" $COLOR_OFF
        cat $TEMP_VALGRIND_FILE
        echo "----------------------------------------------"
        return 1
    fi
    return 0
}

function run_program(){

    local exec=$1
    local should_fail=$(echo $CURRENT_TESTING_FILE | grep "fail" > /dev/null && echo true || echo false)
    shift 1

    $verbose && echo "Running $exec $CURRENT_TESTING_FILE ${CURRENT_FLAGS[@]}, should fail : $should_fail"

    if $use_valgrind; then
        run_with_valgrind $exec $should_fail ||  return 1
    else
        $exec $CURRENT_TESTING_FILE ${CURRENT_FLAGS[@]} || ( $should_fail && return 0 ) || ( printf "%s%s%s\n" $RED "The program failed unexpectedly while testing $CURRENT_TESTING_FILE" $COLOR_OFF
        return 1)
    fi
}

function clean_temp_files(){
    rm -f $TEMP_DIFF_FILE
    rm -f $TEMP_VALGRIND_FILE
}

function clean_output_dir(){
    output_dir=$1
    [  -d "$output_dir" ] && rm -rf "$output_dir"
    mkdir "$output_dir"
}
#----------------------------------------------#
#----------------- Test Main ------------------#
#----------------------------------------------#

function test_invalid_flag(){
    local output_dir=$1
    local expected_output_dir=$2

    local has_test_invalid_flag_failed=false
    local test_name="invalid_output_fail"
    $verbose && test_name+="_verbose"
    test_name+=".txt"

    $verbose && echo "Running ./main $CURRENT_TESTING_FILE ${CURRENT_FLAGS[@]}, should fail : true"
    run_program "./main" > "$output_dir/$test_name" && has_test_invalid_flag_failed=true
    test_one_output $expected_output_dir $output_dir $test_name || has_test_invalid_flag_failed=true

    $has_test_output_failed && return 1
    return 0
}

function test_main_output_flag(){

    echo "-> Testing output flag"

    local has_test_output_failed=false
    CURRENT_TESTING_DIR="src/test/test_main/flag_test/output_flag"
    local expected_output_dir="$CURRENT_TESTING_DIR/expected_output"
    local output_dir="$CURRENT_TESTING_DIR/output"
    local input_dir="$CURRENT_TESTING_DIR/input"

    clean_output_dir "$output_dir"

    local files=$(find $input_dir -type f -name "*.txt" -printf "%f\n")

    for file in $files; do
        local output_file="$output_dir/$file"
        CURRENT_TESTING_FILE="$input_dir/$file"
        CURRENT_FLAGS=("-o=$output_file")

        run_program "./main" || has_test_output_failed=true

        test_one_output $expected_output_dir $output_dir $file || has_test_output_failed=true
    done

    # Testing invalid output file
    CURRENT_TESTING_FILE="$input_dir/invalid_output_fail.txt"
    CURRENT_FLAGS=("-o=")
    test_invalid_flag $output_dir $expected_output_dir || has_test_output_failed=true

    clean_temp_files
    $has_test_output_failed && has_passed=false
    ($has_test_output_failed && printf "%s%s%s\n" $RED "There is at least one problem with the output flag" $COLOR_OFF ) || printf '%s%s%s\n' $GREEN "The output flag works" $COLOR_OFF

    $has_test_output_failed && return 1
    return 0
}

function test_main_record_flag(){

    echo "-> Testing record flag"

    local has_test_record_failed=false
    CURRENT_TESTING_DIR="src/test/test_main/flag_test/record_flag"
    local expected_output_dir="$CURRENT_TESTING_DIR/expected_output"
    local output_dir="$CURRENT_TESTING_DIR/output"
    local input_dir="$CURRENT_TESTING_DIR/input"

    clean_output_dir "$output_dir"

    local files=$(find $input_dir -type f -name "*.txt" -printf "%f\n")

    for file in $files; do
        local output_file="$output_dir/$file"
        CURRENT_TESTING_FILE="$input_dir/$file"
        CURRENT_FLAGS=("-r=$output_file -o=/dev/null")

        run_program "./main" || has_test_record_failed=true

        test_one_output $expected_output_dir $output_dir $file || has_test_record_failed=true
    done

    # Testing invalid output file
    CURRENT_TESTING_FILE="$input_dir/invalid_output_fail.txt"
    CURRENT_FLAGS=("-r=")
    test_invalid_flag $output_dir $expected_output_dir || has_test_output_failed=true

    clean_temp_files
    $has_test_record_failed && has_passed=false
    ($has_test_record_failed && printf "%s%s%s\n" $RED "There is at least one problem with the record flag" $COLOR_OFF ) || printf '%s%s%s\n' $GREEN "The record flag works" $COLOR_OFF

    $has_test_record_failed && return 1
    return 0
}

function test_flags(){
    local has_test_flags_failed=0
    test_main_output_flag || has_test_flags_failed=1
    test_main_record_flag || has_test_flags_failed=1

    return $has_test_flags_failed
}

function test_main(){
    echo
    echo "|-=-=-=-=-=-=-=-=-| Compiling main |-=-=-=-=-=-=-=-=-|"
    make all

    echo
    echo "|-=-=-=-=-=-=-=-=-| Testing main function |-=-=-=-=-=-=-=-=-|"

    echo "-> Testing main function"
    local has_main_test_failed=false
    CURRENT_TESTING_DIR="src/test/test_main"
    local expected_output_dir="$CURRENT_TESTING_DIR/expected_output"
    local output_dir="$CURRENT_TESTING_DIR/output"
    local input_dir="$CURRENT_TESTING_DIR/input"

    clean_output_dir "$output_dir"

    # Get a list of output file names (excluding directories)
    # we use the output instead of the input because we want to alse tests 
    # invalid input files.
    local expected_output_files=$(find $expected_output_dir -type f -name "*.txt" -printf "%f\n")
    # Loop through the input files
    for file in $expected_output_files; do
        # Create the corresponding output file name
        local output_file="$output_dir/$file"
        CURRENT_TESTING_FILE="$input_dir/$file"

        CURRENT_FLAGS=("-o=$output_file")
        echo $file | grep "verbose" > /dev/null && CURRENT_FLAGS+=("-v")

        run_program "./main" || has_main_test_failed=true

        # if the test fails then set has_test_output_failed to true
        test_one_output $expected_output_dir $output_dir $file || has_main_test_failed=true
    done

    # Testing invalid input file

    CURRENT_TESTING_FILE="$input_dir/invalid_input_fail.txt"
    CURRENT_FLAGS=("-o=$output_dir/invalid_input_fail.txt")
    run_program "./main" || has_main_test_failed=true
    test_one_output $expected_output_dir $output_dir "invalid_input_fail.txt" || has_main_test_failed=true

    clean_temp_files
    test_flags || has_main_test_failed=true
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

    CURRENT_TESTING_DIR="src/test"
    local output_dir="$CURRENT_TESTING_DIR/output"
    clean_output_dir "$output_dir"
}

function run_tests(){
    echo

    local flag=""
    $verbose && flag="-v"

    if $use_valgrind ; then
        echo "|-=-=-=-=-=-=-=-=-| Running tests with valgrind |-=-=-=-=-=-=-=-=-|"
        run_with_valgrind   "./test" "" false $flag || has_passed=false
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
