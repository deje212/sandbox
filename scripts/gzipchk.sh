#!/bin/bash

# Dica de nixCraft.

gzipchk() { 
  curl -sILH 'Accept-Encoding: gzip,deflate' "$@" | grep --color 'Content-Encoding:'; 
}

gzipchk "$1"
