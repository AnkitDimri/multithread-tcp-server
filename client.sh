#!/usr/bin/env bash

# Compile client code and run
echo
echo "Compiling client.cpp..."
# compiling
g++ client.cpp -o client
echo
echo
echo "client.cpp compiled..."
echo
echo "Starting client..."
echo
#run the object file
./client
