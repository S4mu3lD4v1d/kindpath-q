# KindPath Q — Project Brief (v0.1)

## Mission
KindPath Q is a desktop-first standalone + plugin audio tool that helps producers analyze and rebuild music with pro-grade guidance:
- spectral/tempo/key/transient + mix translation checks
- mono-safe club-ready decision support
- psychoacoustic / psychosomatic education ("why this feels good")
- contextual music-history micro-lessons (“Did you know…?”)

## Product Pillars
1) **Analyzer Mode**: import audio, analyze, and explain.
2) **Coach Mode**: actionable mix guidance, A/B referencing, translation checks.
3) **Blueprint Mode**: recreate structure + sound design recipes (without cloning).
4) **Teach Mode**: psychoacoustics, rhythm-body mapping, history snippets, further reading.

## Platform
- macOS first (Monterey compatible; Intel 2015 MBP)
- standalone app + plugin from the outset
- cloud support optional (not required for core function)

## Hard Constraints
- Must work well in MONO (clubs).
- Must run on macOS 12.7.x Intel.
- Avoid heavy/fragile dependencies early.

## Non-goals (for v0.1)
- Full AI cloud pipeline
- Stem-separation at release quality (ok for demo/education)
- Mobile-first (later)

## Deliverables (Phase 1)
- Repo scaffolding + buildable hello-world standalone
- Audio file import
- Basic analysis: loudness (RMS/LUFS approx), spectrum snapshot, mono correlation, peak detection
- UI shell: tabs for Analyzer / Coach / Teach

