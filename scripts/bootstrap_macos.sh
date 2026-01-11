#!/usr/bin/env bash
set -euo pipefail

printf "KindPath Q bootstrap (macOS)\n"

if command -v brew >/dev/null 2>&1; then
  printf "Homebrew detected. Installing dependencies...\n"
  brew install cmake ninja git || true
else
  printf "Homebrew not found.\n"
  printf "Install manually:\n"
  printf "- CMake: https://cmake.org/download/\n"
  printf "- Ninja: https://ninja-build.org/\n"
  printf "- Git: https://git-scm.com/download/mac\n"
fi

if [ ! -d "external/JUCE" ]; then
  printf "\nJUCE not found at external/JUCE.\n"
  printf "Clone it with:\n"
  printf "  git clone https://github.com/juce-framework/JUCE.git external/JUCE\n"
fi
