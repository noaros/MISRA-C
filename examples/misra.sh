#!/bin/sh
# Run the cppcheck MISRA C:2012 addon on one or more C files.
#
#   ./misra.sh r10/good.c r10/bad.c
#
# cppcheck writes a .dump file per source; the addon script reads it.
# MISRA_ADDON can point at misra.py if it is not in a standard location.
set -u

addon="${MISRA_ADDON:-}"
if [ -z "$addon" ]; then
    for candidate in \
        /usr/lib/x86_64-linux-gnu/cppcheck/addons/misra.py \
        /usr/lib/cppcheck/addons/misra.py \
        /usr/share/cppcheck/addons/misra.py \
        /usr/local/share/Cppcheck/addons/misra.py \
        /opt/homebrew/share/cppcheck/addons/misra.py; do
        if [ -f "$candidate" ]; then
            addon="$candidate"
            break
        fi
    done
fi
if [ -z "$addon" ]; then
    echo "misra.py not found: install cppcheck or set MISRA_ADDON" >&2
    exit 2
fi

status=0
for src in "$@"; do
    dir=$(dirname "$src")
    cppcheck --quiet --dump --std=c99 -Iinclude -I"$dir" "$src" || status=1
    python3 "$addon" --cli "$src.dump" 2>/dev/null \
        | grep -o '"file": "[^"]*", "linenr": [0-9]*\|"errorId": "[^"]*"' \
        | paste - - \
        | sed -E 's/"file": "([^"]*)", "linenr": ([0-9]*)\t"errorId": "c2012-([0-9.]*)"/\1:\2: Rule \3/' \
        | sort -t: -k2,2n
    rm -f "$src.dump" "$src.ctu-info"
done
exit $status
