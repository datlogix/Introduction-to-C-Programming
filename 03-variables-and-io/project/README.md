# Module 3 Project — Fortune Calculator 2.0

Remember the mind-reading hook from the top of this module's README? It
asked for your age and "predicted" a couple of facts using nothing but
arithmetic. You're going to build a bigger, more personal version of it
now, using variables, `const`, and `scanf` -- still no arrays, no
strings, no functions of your own.

## Requirements

Your program must:

1. Declare and use at least **one `const`** value (a "magic number" your
   calculations depend on, e.g. an assumed retirement age, a constant
   used in a formula, or a fixed multiplier).
2. Read **at least two numeric inputs** from the user with `scanf`, and
   they must NOT both be the same type -- use a mix, e.g. one `int` and
   one `float`, or an `int` and a `char`.
3. Perform **at least three different calculations** using arithmetic
   operators (`+`, `-`, `*`, `/`) on the input values or on the `const`.
4. Print **at least five lines** of "prediction" style output, and every
   prediction must reference one of the user's actual input values or a
   computed result -- no generic filler text that would print the same
   way no matter what the user typed.
5. Use a **meaningful, snake_case name** for every variable you declare.

## Ideas if you're stuck

- **Lucky Number Generator:** ask for a birth month (`int`) and a
  favorite letter (`char`), then combine them with a `const` multiplier
  into a "lucky number" and a handful of dramatic predictions.
- **Simple BMI Calculator:** ask for height in meters (`float`) and
  weight in kilograms (`float`), compute
  `bmi = weight / (height * height)`, and print it back with a
  personalized message.
- **Pizza Party Planner:** ask how many people are coming (`int`) and how
  many slices each person eats (`int`), then calculate slices needed and
  how many whole pizzas (8 slices each) that requires.
- **Time Capsule:** ask for the user's current age (`int`), then predict
  their age in 10, 25, and 50 years, plus how many days old they'll be.

## Getting started

Open [`starter.c`](starter.c) and build inside `main()`. Compile and run
often -- add one variable or one `scanf` at a time and test it before
moving on.

```bash
gcc starter.c -o fortune_calculator
./fortune_calculator
```

## Done?

Commit and push it:

```bash
git add .
git commit -m "Complete Module 3 project: fortune calculator"
git push
```
