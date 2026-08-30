*This project has been created as part of the 42 curriculum by anogueir and abouchat.*

# minishell

A small Unix shell written in C. It reads a line, parses it, and runs commands the way bash does for the subset defined in the 42 subject: executables, builtins, quotes, `$VAR` / `$?`, redirections, pipes, and signals.

Intra: Common Core, ~210h, **pass with bonus** (September 2025).

## Description

**Goal.** Recreate enough of a real shell to understand process control, file descriptors, and how a command line becomes running programs. The reference behaviour is bash: when the subject is silent, bash wins.

**Overview.** The program shows an interactive prompt (GNU Readline + history), tokenizes the line, expands the environment, builds a pipeline, then `fork` / `execve` / `dup2` each stage. Builtins that change the shell itself (`cd`, `export`, `unset`, `exit`) run in the parent when they are a single command; in a pipeline they run in the child so they do not leak state into a process that is about to die.

What it implements (mandatory part of the subject):

- Prompt, history, and launch of binaries from `PATH` or an absolute/relative path
- Quotes: `'` (no expansion) and `"` (expansion of `$` only)
- Environment expansion (`$NAME`) and `$?` (last exit status)
- Pipes: `cmd1 | cmd2 | …` — one process per stage
- Redirections: `<`, `>`, `>>`, and heredoc `<<`
- Signals in interactive mode: `Ctrl-C` reprints the prompt, `Ctrl-D` exits, `Ctrl-\` does nothing
- Builtins: `echo` (`-n`), `cd` (relative or absolute path), `pwd`, `export`, `unset`, `env`, `exit`

Allowed API is the subject’s list only (Readline, a short set of libc/POSIX calls). Libft is allowed. The Norm applies. Readline’s own leaks are ignored; the rest of the heap must not leak.

## Instructions

### Requirements

- A Unix-like system (Linux or macOS)
- `cc` (or `gcc`/`clang`) and GNU Make
- GNU Readline development files

Debian / Ubuntu:

```bash
sudo apt update
sudo apt install build-essential libreadline-dev
```

macOS (Homebrew):

```bash
brew install readline
```

On macOS you may need extra include/lib flags if Readline is not in the default path (the Makefile should already pass `-lreadline`; adjust `-I` / `-L` to the brew prefix if the linker fails).

### Compilation

From the repository root:

```bash
make
```

Standard 42 rules:

| Target    | Effect                                      |
|-----------|---------------------------------------------|
| `make` / `make all` | Build `./minishell` (`-Wall -Wextra -Werror`) |
| `make clean`        | Remove object files                     |
| `make fclean`       | `clean` + remove the binary             |
| `make re`           | `fclean` then `all`                     |

The Makefile must not relink when nothing changed.

### Execution

```bash
./minishell
```

Type commands as in bash. Leave with `exit` or `Ctrl-D`.

### Usage examples

```bash
echo $USER
echo -n "hello" | cat -e
cd /tmp
pwd
export FOO=bar
echo "$FOO" | tr a-z A-Z
cat < Makefile | grep NAME > /tmp/out
cat << EOF
hello
EOF
```

Exit codes follow bash conventions where the subject requires it (for example `127` when the command is not found).

## Features

- Parser separated from execution: a syntax error never leaves a half-built pipeline or a zombie
- One `pipe()` per junction; unused ends closed in every process to avoid deadlock
- Environment copied and mutated only through `export` / `unset` (not `putenv` on the process `environ` unless that is how this tree is written)
- Interactive signals vs child signals: the child must see default `SIGINT` / `SIGQUIT` so `Ctrl-C` kills `sleep`, not the shell

## Resources

### Documentation and references

- [GNU Bash manual — Bourne Shell Builtins](https://www.gnu.org/software/bash/manual/html_node/Bourne-Shell-Builtins.html)
- [GNU Readline](https://tiswww.case.edu/php/chet/readline/rltop.html)
- [pipe(2)](https://man7.org/linux/man-pages/man2/pipe.2.html), [fork(2)](https://man7.org/linux/man-pages/man2/fork.2.html), [execve(2)](https://man7.org/linux/man-pages/man2/execve.2.html), [dup2(2)](https://man7.org/linux/man-pages/man2/dup2.2.html), [waitpid(2)](https://man7.org/linux/man-pages/man2/waitpid.2.html)
- [signal(7)](https://man7.org/linux/man-pages/man7/signal.7.html)
- 42 subject *minishell* (intra PDF — not committed here)

### How AI was used

No LLM generated the C sources of this shell (parser, execution, builtins, signals). Those were written and evaluated as part of the 42 Common Core.

An AI coding assistant was used **only to draft and format this README**: required first line, Description / Instructions / Resources layout, and wording for peers and recruiters. The author reviewed the text against the subject and the delivered binary. AI was **not** used to invent Makefile targets, bonus flags, or behaviour that is not in the subject or in the program as submitted.
