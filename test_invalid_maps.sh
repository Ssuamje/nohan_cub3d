#!/bin/bash

# Directory containing map files
map_directory="./maps"

# Find all files in the map directory that start with "invalid_"
map_files=("$map_directory"/invalid_*)

# Check if there are any matching files
if [ ${#map_files[@]} -eq 0 ]; then
  echo "No map files starting with 'invalid_' found in $map_directory"
  exit 1
fi

# Loop through the matching files and execute ./cub3D with them
for map_file in "${map_files[@]}"; do
  echo "Running ./cub3D with file: $map_file"
  ./cub3D "$map_file"
done
