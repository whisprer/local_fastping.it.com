#!/bin/bash

# === CONFIGURATION ===
PORT=3456
DEST_DIR="$HOME/received_files"

# === PREP ===
mkdir -p "$DEST_DIR"
echo "[INFO] Listening on port $PORT..."
echo "[INFO] Files will be saved in: $DEST_DIR"
echo "[INFO] Waiting for senders. Ctrl+C to stop."

# === LISTEN LOOP ===
while true; do
    TIMESTAMP=$(date +"%Y%m%d_%H%M%S")
    FILENAME="$DEST_DIR/recv_$TIMESTAMP.bin"
    
    echo -e "\n[WAITING] Ready to receive next file..."
    nc -lvnp "$PORT" > "$FILENAME"

    FILESIZE=$(du -h "$FILENAME" | cut -f1)
    echo "[RECEIVED] Saved: $FILENAME ($FILESIZE)"
done
