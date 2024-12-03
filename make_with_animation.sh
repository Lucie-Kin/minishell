#!/bin/bash

# Animation
spinner() {
    local pid=$1
    local delay=0.1
    local spinstr='|/-\'
    echo -n "Building... "
    while kill -0 $pid 2>/dev/null; do
        local temp=${spinstr#?}
        printf " [%c]  " "$spinstr"
        local spinstr=$temp${spinstr%"$temp"}
        sleep $delay
        printf "\b\b\b\b\b\b"
    done
    echo "Done!"
}

# Run make in the background
make "$@" &
pid=$!
spinner $pid
wait $pid
