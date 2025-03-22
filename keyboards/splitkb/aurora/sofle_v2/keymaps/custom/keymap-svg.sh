#!/usr/bin/env bash
set -euo pipefail

cd /Users/tuopppi/Projects/Personal/keymap-drawer
source .venv/bin/activate

img=$(mktemp).svg
qmk c2json -kb splitkb/aurora/sofle_v2 -km custom --no-cpp | keymap parse -c 10 -q - | keymap draw - > "$img"
open -n -a "Google Chrome" "$img"
