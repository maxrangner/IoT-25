# AGENTS.md

This file defines local directives for coding agents working in this repository.

## Project Context
- Language: C
- Primary folders: `src/`, `include/`
- Build system: `Makefile` (preferred), `CMakeLists.txt` may exist for compatibility
- Platform target: prototype currently runs on Windows console

## Agent Directives
- Do not make any changes or run modifying commands unless explicitly instructed by the user.
- Keep changes minimal and task-focused.
- Preserve existing code style unless asked to refactor.
- Do not rename files or symbols unless required.
- Avoid adding dependencies unless explicitly requested.
- Prefer fixing root causes over adding workarounds.

## Build And Run
- Default build command: `make`
- Default run command: `./build/main.exe`
- If build setup changes, update this section in the same PR/commit.

## Validation
- After code edits, run build and report success/failure.
- If tests exist, run relevant tests for touched code.
- If validation cannot be run, explain why and what remains unverified.

## Editing Rules
- Use ASCII unless file already uses Unicode and needs it.
- Keep functions cohesive and avoid unnecessary abstraction.
- Add comments only where logic is non-obvious.
- Do not mass-format unrelated files.

## Communication Preferences
- Be concise and concrete.
- Show file paths for modified files.
- Summarize behavior changes and risks.
- Ask before destructive operations.

## Safety
- Never use destructive git commands unless explicitly requested.
- Do not revert unrelated user changes.

## Optional Per-Task Override
For a specific task, follow extra directives from the user even if they conflict with this file.
