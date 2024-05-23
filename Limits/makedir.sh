#!/bin/bash

# Start mass value
start=80
# End mass value
end=160
# Special case
special=155
# Increment
increment=10

for (( mass=$start; mass<=$end; mass+=$increment ))
do
  dir_name="mass$mass"
  echo "Creating directory: $dir_name"
  mkdir -p "$dir_name"
done

# Handle special case
echo "Creating directory: mass$special"
mkdir -p "mass$special"

echo "All directories created."
