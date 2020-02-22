#!/bin/bash
cd $(dirname "$0")

source scripts/flags.sh
scripts/build_impl.sh
