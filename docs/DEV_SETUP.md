# KindPath Q Dev Setup (macOS Monterey 12.7.x Intel)

## Requirements
- Xcode Command Line Tools
- CMake
- Ninja
- Git
- JUCE source checkout (in `external/JUCE`)

## Setup
```sh
xcode-select --install
```

If you use Homebrew:
```sh
brew install cmake ninja git
```

Clone JUCE into the repo:
```sh
git clone https://github.com/juce-framework/JUCE.git external/JUCE
```

## Build
```sh
./scripts/build_macos.sh
```

## Run Standalone (Debug)
```sh
open build/KindPathQStandalone_artefacts/Debug/KindPath\ Q.app
```

## Plugin Outputs
- AU: `build/KindPathQ_artefacts/Debug/AU/KindPath Q.component`
- VST3: `build/KindPathQ_artefacts/Debug/VST3/KindPath Q.vst3`

## Notes
- The cards JSON is loaded from `core/education/cards.json` during development.
- Use the MONO toggle to collapse monitoring while keeping analysis active.
