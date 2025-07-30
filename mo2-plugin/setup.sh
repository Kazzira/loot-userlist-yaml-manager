#!/bin/sh

PROJECT_DIR=$(dirname "$(realpath "$0")")

echo "Setting up virtual environment in $PROJECT_DIR/.venv"
python3 -m venv "$PROJECT_DIR/.venv" >/dev/null 2>/dev/null

if [ -f "$PROJECT_DIR/.venv/bin/activate" ]; then
    chmod +x "$PROJECT_DIR/.venv/bin/activate"
    . "$PROJECT_DIR/.venv/bin/activate" >/dev/null 2>/dev/null

    if [ $? -ne 0 ]; then
        echo "Failed to activate virtual environment."
        exit 1
    fi
else
    echo "Virtual environment activation script not found."
    exit 1
fi

echo "Installing required packages in the virtual environment..."
"$PROJECT_DIR/.venv/bin/python" -m pip install pytest pytest-cov >/dev/null 2>/dev/null

if [ $? -ne 0 ]; then
    echo "Failed to install pytest and pytest-cov."
    exit 1
fi

echo "Virtual environment setup complete."
