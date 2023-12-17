
#!/bin/bash
set -e
XEPHYR=$(whereis -b Xephyr | cut -f2 -d' ')
echo $XEPHYR
xinit ./xinitrc -- \
    "$XEPHYR" \
        :100 \
        -ac \
        -screen 1366x768 \
        -host-cursor

