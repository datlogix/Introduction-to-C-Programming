# Module 0 — Setup: Tools, Git & GitHub Classroom

## Hook: your first build, before you understand a single line

Before anything else, let's prove the machinery works. Create a file
called `hook.c` anywhere on your computer and paste this in exactly:

```c
#include <stdio.h>

int main(void) {
    int year = 2026;
    printf("If you started today, by %d you could have written your\n", year);
    printf("own game, your own tool, or your own excuse for why the\n");
    printf("bug definitely isn't your fault. Let's find out.\n");
    return 0;
}
```

Once your compiler is installed below, run:

```bash
gcc hook.c -o hook
./hook
```

You just turned text into a running program on your own machine. You
don't understand `#include`, `printf`, or `return` yet — that's fine,
that's the entire rest of this course. Keep that feeling of "it worked
and I don't fully know why" in mind; every module from here replaces one
piece of "I don't know why" with "I know exactly why."

## 1. Install a C compiler

C needs to be **compiled** — translated into machine code before it runs
(more on this in Module 1). You need a compiler on your machine.

**macOS**

```bash
xcode-select --install
```

This installs Apple's Command Line Tools, which includes `clang` (a C
compiler). This course uses `gcc` as the command name throughout — on
macOS, `gcc` is typically aliased to `clang` already. Check with:

```bash
gcc --version
```

**Windows**

Install [WSL (Windows Subsystem for Linux)](https://learn.microsoft.com/windows/wsl/install)
— open PowerShell as Administrator and run `wsl --install`, then restart.
Inside the Ubuntu terminal that opens, run:

```bash
sudo apt update && sudo apt install build-essential -y
```

This gives you `gcc`, `make`, and a real Linux terminal — the same
environment your instructor and classmates are using, which avoids
"works on my machine" problems.

**Linux**

```bash
sudo apt install build-essential -y      # Debian/Ubuntu
sudo dnf groupinstall "Development Tools" # Fedora
```

Verify on any platform:

```bash
gcc --version
```

You should see a version number, not "command not found."

## 2. Install VS Code

Download from [code.visualstudio.com](https://code.visualstudio.com). Then
install two extensions from the Extensions panel (`Cmd/Ctrl+Shift+X`):

- **C/C++** (by Microsoft) — syntax highlighting and IntelliSense.
- **Code Runner** (by Jun Han) — lets you run a `.c` file with one click.

## 3. Install and configure Git

Git is almost certainly already installed (`git --version` to check). If
not, install it from [git-scm.com](https://git-scm.com). Then tell Git who
you are — this name and email get attached to every commit you make:

```bash
git config --global user.name "Your Full Name"
git config --global user.email "the-email-you-use-for-github@example.com"
```

## 4. Create a GitHub account

If you don't already have one, sign up at [github.com](https://github.com).
Use a professional-looking username — this account will hold your work
long after this course ends, and employers do look.

## 5. Accept your first GitHub Classroom assignment

This course does **not** collect work by email or file upload — everything
goes through **GitHub Classroom**.

1. Your instructor shares an **assignment invite link** for Module 0
   (in a codespace, LMS post, or class chat).
2. Open the link and sign in with your GitHub account.
3. Click **Accept this assignment**. GitHub Classroom creates a private
   repository just for you (something like
   `module-0-setup-yourusername`), copied from a starter template.
4. Wait a few seconds for "Your assignment repository has been created"
   and click through to it.

## 6. Clone your repository and make your first commit

On your computer, in a terminal, navigate to where you keep your code and
clone the repo GitHub Classroom just created for you:

```bash
git clone https://github.com/YOUR-CLASSROOM-ORG/module-0-setup-yourusername.git
cd module-0-setup-yourusername
```

Open the folder in VS Code (`code .` from that terminal, or File → Open
Folder). Add a `hook.c` file with the hook program from the top of this
page (personalize the message if you like), then:

```bash
git add hook.c
git commit -m "Complete Module 0 setup"
git push
```

Refresh the repository page on GitHub — you should see your file and your
commit. **This is your workflow for every module from now on**: edit code
locally, `git add` the files you changed, `git commit` with a short
description, `git push` to send it to your GitHub Classroom repo. Nothing
is submitted until it's pushed.

## Common setup problems

- `gcc: command not found` — the compiler isn't installed, or your
  terminal was opened before installation finished. Close and reopen the
  terminal.
- `git push` asks for a password and rejects it — GitHub no longer accepts
  account passwords for this. Use a
  [personal access token](https://github.com/settings/tokens) as the
  password, or set up SSH keys (ask your instructor which your class
  uses).
- Nothing shows up on GitHub after `git push` — check `git status` first;
  if it says "nothing to commit," you likely forgot `git add` before
  `git commit`.

## Try it yourself

1. Confirm `gcc --version` and `git --version` both work.
2. Accept the Module 0 GitHub Classroom assignment.
3. Clone it, add your `hook.c`, commit, and push.
4. Confirm your commit appears on GitHub.

Next: **[Module 1 — Basics of Programming](../01-basics-of-programming/README.md)**.
