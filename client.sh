#!/usr/bin/env bash

echo
echo "Compiling client.cpp..."
g++ client.cpp -o client
echo
echo
echo "client.cpp compiled..."
echo
echo "Starting client..."
echo
./client
