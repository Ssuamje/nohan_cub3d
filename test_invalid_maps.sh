#!/bin/bash

map_directory="./maps"
map_files=("$map_directory"/invalid_*)

if [ ${#map_files[@]} -eq 0 ]; then
  echo "No map files starting with 'invalid_' found in $map_directory"
  exit 1
fi

for map_file in "${map_files[@]}"; do
  echo "./cub3D $map_file"
  ./cub3D "$map_file"
  echo ""
done
