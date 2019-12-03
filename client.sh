#!/usr/bin/env bash

# @author: Ankit Dimri
# Shell script to run the client which connects to server MISTCP

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

count=0
ps_running=$(pidof client)
for pids in $ps_running
do
  count=`expr $count + 1`
done

count=`expr $count + 1`

echo "Starting client $count ..."

#run the object file
./client
