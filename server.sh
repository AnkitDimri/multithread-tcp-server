#!/usr/bin/env bash

echo
echo "Compiling server.cpp..."
g++ server.cpp -o server -lpthread
echo
echo
echo "server.cpp compiled..."
echo
echo "Starting server..."
echo
./server
