#!/bin/bash


file=$1
echo $1 | grep "verbose" > /dev/null || file+="_verbose"
echo $file | grep ".txt" > /dev/null || file="$file.txt"

input_file="src/test/test_main/input/$file"
expected_output_file="src/test/test_main/expected_output/$file"


valgrind --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all --error-exitcode=1  -q ./main -i -r=$input_file -o=$expected_output_file

# This is needed because the interactive mode does not print the input file name (because there is none)
sed -i '1s,^,Parsing file '"$input_file"' ...\n,' $expected_output_file

echo "Do you wish to keep this test?"
select yn in "Yes" "No"; do
    case $yn in
        Yes ) exit ;;
        No ) rm $expected_output_file; rm $input_file; exit ;;
    esac
done
