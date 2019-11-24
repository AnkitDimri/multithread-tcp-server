#!/usr/bin/env bash

# Compile server code and run
echo
echo "Compiling server.cpp..."
# Compiling
# lpthread flag to support multithreading
g++ server.cpp -o server -lpthread
echo
echo
echo "server.cpp compiled..."
echo
echo "Starting server..."
echo
# start the server
./server
