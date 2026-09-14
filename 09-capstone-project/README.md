# Module 9 — Capstone Project

This is where every module comes together: variables, control structures,
arrays, strings, functions, pointers, structs, and file I/O, combined into
one real program you'll be proud to link from your GitHub profile.

## 1. How teams are formed

Your instructor announces the class size before this module starts, which
sets your group size:

| Class size | Group size | Ratio |
|---|---|---|
| Up to 20 students | Pairs | **2:1** |
| More than 20 students | Groups of 4 | **4:1** |
| Approved solo ("daring") students, any class size | Individual | **1:1** |

**Going solo ("daring" track):** any student may request to build the
capstone alone instead of in a group. This isn't a smaller workload —
it's the same core requirements (§3) **plus every stretch goal** listed
for your chosen project (§4), since you don't have teammates splitting
the work. Request this from your instructor *before* Sprint 0 (§5) so
GitHub Classroom can set up your repo correctly. Going solo is a good fit
if you're already comfortable with everything through Module 8 and want
the extra stretch — it is not a reward for wanting to avoid teammates.

## 2. Forming your team in GitHub Classroom

1. Your instructor posts **one Group Assignment invite link** for the
   capstone.
2. Open it, sign in with GitHub, and either **create a new team** (name it
   after your project idea, e.g. `library-system-team1`) or **join an
   existing team** a teammate already created. Team size is enforced by
   the size from the table above — Classroom won't let you overfill it.
3. Solo/"daring" students accept the same link but create a team of one.
4. GitHub Classroom provisions **one shared repository** for your team,
   copied from the capstone starter template. Every teammate clones the
   *same* repo:

   ```bash
   git clone https://github.com/YOUR-CLASSROOM-ORG/capstone-yourteamname.git
   cd capstone-yourteamname
   ```

5. Everyone commits under their **own** Git identity (`git config
   user.name` / `user.email` from Module 0) — this is how your instructor
   sees who contributed what. A repo with every commit from one teammate
   and none from the other is a problem worth fixing early, not at the
   deadline.

## 3. Requirements for every project (any topic, any team size)

Regardless of which idea you pick from §4, your submission must include:

- **At least one `struct` type**, used in an array or similar collection
  (Module 8) — this is your program's core data.
- **File I/O** (Module 8): your program's data must survive being closed
  and reopened. If you quit and relaunch, your data should still be
  there.
- **At least 4 functions you wrote yourself** (Module 6), each doing one
  clear job — not one giant `main`.
- **Pointers used with intention** (Module 7) somewhere real — e.g.
  passing a struct by pointer to modify it, not just because it's
  required. Be ready to explain why you used a pointer where you did.
- **Arrays and/or strings** (Module 5) for any collection of data or text
  processing.
- **Control structures and a menu-driven loop** (Module 4) — the program
  should run continuously, present options, and only exit when the user
  chooses to.
- **A project `README.md`** in your team's repo explaining: what the
  program does, how to compile and run it, and a one-paragraph
  description of who worked on what.
- **No compiler warnings** with `gcc -Wall yourfile.c -o yourprogram`.
  Warnings are gcc telling you about likely bugs — clear them all.

## 4. Choose a project

Pick one. All of them are scoped to fit the requirements above with room
for your own ideas on top.

1. **Student Grading & Report Card System** — store students (struct:
   name, ID, array of scores), compute averages/grades, save/load the
   class roster to a file. *Stretch:* rank students, export a
   formatted report per student.
2. **Library / Inventory Management System** — track items (struct:
   title, ID, quantity, checked-out status), check items in/out, persist
   the catalog to a file. *Stretch:* search by keyword, track due dates.
3. **Contact Book / Phone Directory** — add, search, edit, and delete
   contacts (struct: name, phone, email), saved to a file. *Stretch:*
   sort alphabetically, group by category.
4. **Quiz Game Engine** — load a question bank from a file, ask
   questions, score the player, save high scores. *Stretch:* multiple
   difficulty levels, a timer.
5. **Simple Bank Account Simulator** — deposit, withdraw, check balance,
   with a persisted transaction log (struct per transaction). *Stretch:*
   multiple accounts, interest calculation, transaction history search.
6. **Text-Based Adventure Game** — rooms and choices driving the player
   through a small story, with save/load progress. *Stretch:* an
   inventory system using structs, multiple endings.
7. **Personal Expense Tracker** — log expenses (struct: category, amount,
   date) to a file, show totals and simple statistics. *Stretch:*
   monthly summaries, a simple budget-vs-actual comparison.

Have your own idea? Propose it to your instructor — as long as it can
satisfy every requirement in §3, it's fair game.

## 5. Suggested timeline

| Sprint | Focus | Git evidence expected |
|---|---|---|
| Sprint 0 | Team formed, project chosen, `struct`s designed on paper first | An initial commit with your struct definitions and a plan in the README |
| Sprint 1 | Core data operations working (add/search/edit) in memory, no file I/O yet | Several small commits, each compiling cleanly |
| Sprint 2 | File I/O: save and load your data correctly | A commit where you can close and reopen the program without losing data |
| Sprint 3 | Menu loop, polish, edge cases (empty list, bad input) | Commits addressing specific bugs/edge cases you found |
| Final | Clean `-Wall` build, finished README, last push before deadline | Your final commit *is* your submission |

Commit at the end of every session you work, even if it's not finished —
a commit history of one giant commit the night before the deadline is a
red flag, not a shortcut.

## 6. How this gets assessed

- **Correctness** — does it do what it claims, including edge cases
  (empty input, invalid menu choice, saving/loading correctly)?
- **Use of the module concepts** — structs, pointers, functions, arrays,
  and file I/O used appropriately, not bolted on to satisfy a checklist.
- **Code organization** — logically split into functions, consistent
  style, comments where the *why* isn't obvious.
- **Git history** — regular, meaningful commits from every team member
  under their own name.
- **Documentation** — a README a stranger could use to build, run, and
  understand your project without asking you anything.

## Try it yourself

1. Confirm your team (or solo status) in GitHub Classroom.
2. Clone your team's repo.
3. Pick a project from §4 (or propose your own).
4. Work through the sprints in §5, committing and pushing regularly.
5. Submit by pushing your final commit before the deadline — there is no
   separate submission step.

You've built something real. Put the repo link on your CV.
