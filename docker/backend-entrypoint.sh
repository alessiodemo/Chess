#!/bin/sh
set -e

WATCH_DIRS="/app/Scacchiera /app/Giocatori /app/Partite /app/server /app/CMakeLists.txt"
MARKER=/tmp/.last_build

cmake -S /app -B /app/build -DCMAKE_BUILD_TYPE=Release

run_server() {
  cmake --build /app/build --target server -j"$(nproc)"
  /app/build/server &
  SERVER_PID=$!
}

run_server
touch "$MARKER"

# I bind mount di Docker Desktop su Windows non propagano eventi inotify reali,
# quindi si controllano i timestamp dei sorgenti a intervalli invece di usare inotifywait.
while true; do
  sleep 2
  changed=$(find $WATCH_DIRS -type f \( -name '*.cpp' -o -name '*.h' -o -name 'CMakeLists.txt' \) -newer "$MARKER" 2>/dev/null)
  if [ -n "$changed" ]; then
    echo "[backend] modifica rilevata, ricompilo..."
    touch "$MARKER"
    kill "$SERVER_PID" 2>/dev/null || true
    wait "$SERVER_PID" 2>/dev/null || true
    run_server
  fi
done
