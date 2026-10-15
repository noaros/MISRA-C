# MISRA C
(created by Claude)

A hands-on course on **MISRA C:2012** (with Amendments 1 and 2), the coding guidelines used for safety- and security-critical C in the automotive, aerospace, medical, rail and industrial industries.

| | |
|---|---|
| 🎓 **[Presentation](presentation/README.md)** | 14 parts: the big picture, then every one of the 17 directives and 158 rules, each with the *why* |
| 💻 **[Examples](examples/)** | A `bad.c` and a `good.c` for every chapter, one marked block per rule, linked line-by-line from the slides |
| 📋 **[Cheatsheet](CHEATSHEET.md)** | Every guideline on one page, plus the habits, shapes and banned-library list worth memorising |

## Repository layout

```
presentation/      the slides (Markdown, one page per part)
examples/
  dir/             directives:  bad.c, good.c (+ bad.h, good.h)
  r01/ ... r22/    rule chapters: bad.c, good.c
  include/         shared header with each chapter's entry point
  main.c           runs every good example
  Makefile         build, run and check
  misra.sh         runs the cppcheck MISRA addon on given files
tools/relink.py    keeps the slides' line links pointing at the right code
CHEATSHEET.md      the one-page reference
```

## Build and run the examples

```sh
cd examples
make            # good files: strict C99, warnings are errors; bad files: warnings expected
make run        # run every good example
make misra      # cppcheck MISRA addon on all files (needs cppcheck 2.x)
```

- Every `good.c` compiles cleanly with `-std=c99 -pedantic-errors -Wall -Wextra -Werror`.
- Every `bad.c` compiles too (with warnings), except for a few blocks no modern compiler accepts. Those are guarded by `SHOW_COMPILE_ERRORS`; try `make bad BAD_CFLAGS+=-DSHOW_COMPILE_ERRORS` to see the errors.
- The bad files are compiled but **never run**: several contain undefined behaviour on purpose.

## Editing

Each example block starts with a marker like `/* === Rule 10.3 === */`. After you change any example, run

```sh
python3 tools/relink.py          # update the #Lnn-Lmm anchors in the docs
python3 tools/relink.py --check  # verify they are current (e.g. in CI)
```

## A note on the rule text

The guideline summaries here are **plain-English paraphrases**, not MISRA's official wording, which is copyrighted. For real projects get the guidelines from [misra.org.uk](https://misra.org.uk/). They're inexpensive and include detailed amplification, exceptions and examples.
