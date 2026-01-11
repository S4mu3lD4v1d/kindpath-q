# KindPath Q

KindPath Q is a desktop-first standalone + plugin (AU/VST3) music assistant focused on analysis, mix coaching, and teachable “why it feels good” guidance.

## Status
Scaffolding: repo structure + build system baseline.

## Goals
- Standalone app + plugin from the outset (macOS first).
- Mono-safe analysis + club-ready translation focus.
- Teach foundations + psychoacoustic “feel” in plain language.

## Dev
See `docs/DEV_SETUP.md` and `docs/ARCHITECTURE.md`.

## Build (macOS)
```sh
./scripts/bootstrap_macos.sh
./scripts/build_macos.sh
```

## Outputs
- Standalone app: `build/KindPathQStandalone_artefacts/Debug/KindPath Q.app`
- AU: `build/KindPathQ_artefacts/Debug/AU/KindPath Q.component`
- VST3: `build/KindPathQ_artefacts/Debug/VST3/KindPath Q.vst3`
