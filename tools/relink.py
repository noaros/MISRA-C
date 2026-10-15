#!/usr/bin/env python3
"""Keep the Markdown links into examples/ pointing at the right lines.

Every example block in examples/<chapter>/{bad,good}.c starts with a
marker comment such as  /* === Rule 10.3 === */  or  /* === Dir 4.10 === */.
This script finds those blocks and rewrites each link like

    [Bad example](../examples/r10/bad.c#L40-L52)

so its #L anchor covers the block for the rule the link belongs to. The
rule is taken from the first cell of a table row, or else from the most
recent Markdown heading that names a rule ("### Rule 10.3 ..."). Links
that belong to no rule are left pointing at the whole file.

    python3 tools/relink.py           rewrite links in place
    python3 tools/relink.py --check   exit 1 if any link is stale
"""
import pathlib
import re
import sys

ROOT = pathlib.Path(__file__).resolve().parent.parent
EXAMPLES = ROOT / "examples"
DOCS = sorted((ROOT / "presentation").glob("*.md")) + [ROOT / "CHEATSHEET.md", ROOT / "README.md"]

MARKER = re.compile(r"^/\* === (Rule|Dir) (\d+\.\d+) === \*/$")
ENTRY = re.compile(r"^void \w+_(good|bad)\(void\)$")
LINK = re.compile(r"\(((?:\.\./)?examples/(\w+)/(bad|good)\.c)(?:#L\d+(?:-L\d+)?)?\)")
HEADING = re.compile(r"^#+ .*?\b(Rule|Dir) (\d+\.\d+)\b")
ROW_ID = re.compile(r"^\|\s*(?:\*\*)?(?:(Rule|Dir) )?(\d+\.\d+)")


def blocks(path):
    """Map rule id -> (first line, last line) for one example file."""
    lines = path.read_text().splitlines()
    starts = []
    for i, line in enumerate(lines, 1):
        m = MARKER.match(line)
        if m:
            starts.append((i, m.group(2)))
    result = {}
    group = []
    for idx, (line_no, rule) in enumerate(starts):
        group.append(rule)
        next_start = starts[idx + 1][0] if idx + 1 < len(starts) else None
        if next_start == line_no + 1:
            continue  # consecutive markers share the block that follows
        end = (next_start - 1) if next_start else len(lines)
        for j in range(line_no, end + 1):
            if ENTRY.match(lines[j - 1]):
                end = j - 1
                break
        while end > line_no and lines[end - 1].strip() == "":
            end -= 1
        first = line_no - (len(group) - 1)
        for r in group:
            result[r] = (first, end)
        group = []
    return result


def load_index():
    index = {}
    for src in EXAMPLES.glob("*/*.c"):
        if src.name in ("bad.c", "good.c"):
            index[(src.parent.name, src.stem)] = blocks(src)
    return index


def relink(doc, index):
    text = doc.read_text()
    out = []
    current = None
    errors = []
    for n, line in enumerate(text.splitlines(keepends=True), 1):
        if line.startswith("#"):
            h = HEADING.match(line)
            current = h.group(2) if h else None
        row = ROW_ID.match(line)
        rule = row.group(2) if row else current

        def fix(m):
            target, chapter, kind = m.group(1), m.group(2), m.group(3)
            if rule is None:
                return f"({target})"  # not under a rule: link the whole file
            spans = index.get((chapter, kind), {})
            if rule not in spans:
                errors.append(f"{doc.name}:{n}: no block for {rule} in {chapter}/{kind}.c")
                return m.group(0)
            first, last = spans[rule]
            return f"({target}#L{first}-L{last})"

        out.append(LINK.sub(fix, line))
    return "".join(out), errors


def main():
    check = "--check" in sys.argv
    index = load_index()
    stale = []
    all_errors = []
    for doc in DOCS:
        if not doc.exists():
            continue
        new, errors = relink(doc, index)
        all_errors += errors
        if new != doc.read_text():
            stale.append(doc)
            if not check:
                doc.write_text(new)
    for e in all_errors:
        print(e, file=sys.stderr)
    if check and stale:
        for doc in stale:
            print(f"stale links: {doc.relative_to(ROOT)}", file=sys.stderr)
    if all_errors or (check and stale):
        sys.exit(1)
    if not check:
        print(f"updated {len(stale)} file(s)")


if __name__ == "__main__":
    main()
