#!/bin/bash
file1=$1
file2=$2
echo "start"
chmod 600 id_rsa
scp $file1 $file2 ws@192.168.3.159:/usr/local/bin
echo "success"









