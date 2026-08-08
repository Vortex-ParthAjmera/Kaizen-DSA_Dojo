#!/usr/bin/env python3
"""Regenerate the automated stats and solution index in README.md."""

from __future__ import annotations

import re
from collections import Counter
from dataclasses import dataclass
from pathlib import Path
from urllib.parse import quote


ROOT = Path(__file__).resolve().parents[2]
README = ROOT / "README.md"

SOLUTION_EXTENSIONS = {
    ".c": "C",
    ".cc": "C++",
    ".cpp": "C++",
    ".cs": "C#",
    ".dart": "Dart",
    ".go": "Go",
    ".java": "Java",
    ".js": "JavaScript",
    ".kt": "Kotlin",
    ".kts": "Kotlin",
    ".php": "PHP",
    ".py": "Python",
    ".rb": "Ruby",
    ".rs": "Rust",
    ".scala": "Scala",
    ".swift": "Swift",
    ".ts": "TypeScript",
}

IGNORED_PARTS = {".git", ".github", "node_modules", "venv", ".venv"}
NUMBERED_NAME = re.compile(r"^(?P<number>\d+)[-_. ]+(?P<title>.+)$")


@dataclass(frozen=True)
class Problem:
    number: int | None
    title: str
    difficulty: str
    directory: Path
    solutions: tuple[Path, ...]


def humanize(value: str) -> str:
    value = re.sub(r"[-_]+", " ", value).strip()
    return " ".join(word.upper() if word.lower() in {"ii", "iii", "iv"} else word.capitalize() for word in value.split())


def identity(path: Path) -> tuple[int | None, str, Path]:
    """Derive a problem identity from a LeetSync directory or filename."""
    candidates = [path.parent.name, path.stem]
    for candidate in candidates:
        match = NUMBERED_NAME.match(candidate)
        if match:
            return int(match.group("number")), humanize(match.group("title")), path.parent
    # For non-numbered layouts, all solution files in a named folder are one problem.
    name = path.parent.name if path.parent != ROOT else path.stem
    return None, humanize(name), path.parent


def difficulty_for(directory: Path) -> str:
    for name in ("README.md", "readme.md", "README.MD"):
        metadata = directory / name
        if not metadata.is_file():
            continue
        text = metadata.read_text(encoding="utf-8", errors="ignore")[:12000]
        match = re.search(r"\b(Easy|Medium|Hard)\b", text, re.IGNORECASE)
        if match:
            return match.group(1).title()
    return "Unknown"


def discover() -> list[Problem]:
    grouped: dict[tuple[int | None, str, Path], list[Path]] = {}
    for path in ROOT.rglob("*"):
        if not path.is_file() or path.suffix.lower() not in SOLUTION_EXTENSIONS:
            continue
        relative = path.relative_to(ROOT)
        if any(part in IGNORED_PARTS or part.startswith(".") for part in relative.parts):
            continue
        key = identity(path)
        grouped.setdefault(key, []).append(relative)

    problems = [
        Problem(number, title, difficulty_for(directory), directory.relative_to(ROOT), tuple(sorted(files)))
        for (number, title, directory), files in grouped.items()
    ]
    return sorted(problems, key=lambda p: (p.number is None, p.number or 0, p.title.lower()))


def repo_link(path: Path) -> str:
    return "/".join(quote(part) for part in path.as_posix().split("/"))


def render_stats(problems: list[Problem]) -> str:
    difficulties = Counter(problem.difficulty for problem in problems)
    languages = sorted({SOLUTION_EXTENSIONS[file.suffix.lower()] for problem in problems for file in problem.solutions})
    language_text = ", ".join(languages) if languages else "—"
    return (
        "| Problems solved | Easy | Medium | Hard | Languages |\n"
        "|:---:|:---:|:---:|:---:|:---:|\n"
        f"| **{len(problems)}** | 🟢 {difficulties['Easy']} | 🟡 {difficulties['Medium']} "
        f"| 🔴 {difficulties['Hard']} | {language_text} |"
    )


def render_solutions(problems: list[Problem]) -> str:
    if not problems:
        return "_The mats are ready. The first synced solution will appear here automatically._"

    icons = {"Easy": "🟢 Easy", "Medium": "🟡 Medium", "Hard": "🔴 Hard", "Unknown": "⚪ —"}
    rows = ["| # | Problem | Difficulty | Solution |", "|---:|:---|:---:|:---|"]
    for problem in problems:
        number = str(problem.number) if problem.number is not None else "—"
        folder_target = problem.directory if problem.directory != Path(".") else problem.solutions[0]
        title = f"[{problem.title}]({repo_link(folder_target)})"
        links = []
        for solution in problem.solutions:
            language = SOLUTION_EXTENSIONS[solution.suffix.lower()]
            links.append(f"[{language}]({repo_link(solution)})")
        rows.append(f"| {number} | {title} | {icons[problem.difficulty]} | {' · '.join(links)} |")
    return "\n".join(rows)


def replace_section(text: str, name: str, content: str) -> str:
    start = f"<!-- LEETSYNC:{name}:START -->"
    end = f"<!-- LEETSYNC:{name}:END -->"
    pattern = re.compile(re.escape(start) + r".*?" + re.escape(end), re.DOTALL)
    if not pattern.search(text):
        raise RuntimeError(f"README is missing automation markers for {name}")
    return pattern.sub(f"{start}\n{content}\n{end}", text, count=1)


def main() -> None:
    text = README.read_text(encoding="utf-8")
    problems = discover()
    updated = replace_section(text, "STATS", render_stats(problems))
    updated = replace_section(updated, "SOLUTIONS", render_solutions(problems))
    if updated != text:
        README.write_text(updated, encoding="utf-8")
        print(f"README updated: indexed {len(problems)} problem(s).")
    else:
        print(f"README already current: {len(problems)} problem(s).")


if __name__ == "__main__":
    main()

