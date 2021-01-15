#!/bin/bash

#rozszerz
#liczba dni
#nazwa archiwum


find . -name *.$1 -mtime -$2 -exec tar -rvf $3.tar {} +
