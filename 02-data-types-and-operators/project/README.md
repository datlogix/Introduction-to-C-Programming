# Module 2 Project — Unit Converter

Remember the hook from the top of this module's README? `7 / 2` gave you
`3`, not `3.5`, because of integer division. Real conversions (temperature,
weight, distance) run into that exact trap constantly. You're building a
small **Unit Converter** now that gets it right, using only what you've
learned so far: types, `sizeof`, arithmetic operators, casting, and
relational/logical operators. No `scanf` yet — hardcode your input values
as variables, that's fair game and exactly how Module 3 will pick up.

## Requirements

Your program must:

1. Declare a variable holding a temperature in Celsius (any value you
   like) and convert it to Fahrenheit using `F = C * 9/5 + 32` —
   **correctly**, without falling into the integer-division trap from
   this module.
2. Declare a variable holding a weight in pounds and convert it to
   kilograms (`1 lb = 0.453592 kg`), printing the result with a decimal
   format specifier.
3. Use `sizeof` to print how many bytes your Celsius variable's type
   takes up.
4. Use a relational operator to print, as `0` or `1`, whether your
   converted Fahrenheit temperature is above 32.
5. Include **at least one comment** explaining a type or casting
   decision you made (not just restating the code).
6. Print at least **6 lines** of output total, clearly labeled (e.g.
   `"25 C = 77.00 F"`, not just a bare number).

## Ideas if you're stuck

- Add a third conversion: cups to milliliters (`1 cup = 236.588 mL`).
- Add miles to kilometers (`1 mile = 1.60934 km`).
- Print the Celsius value classified as "freezing or below" using `<=`
  and print the resulting `0`/`1` (no `if` yet — that's Module 4).
- Try a couple of different Celsius values and see how the output
  changes when you edit the source and recompile.

## Getting started

Open [`starter.c`](starter.c) and build inside `main()`. Compile and run
often — don't write the whole thing before testing your first line.

```bash
gcc starter.c -o converter
./converter
```

## Done?

Commit and push it:

```bash
git add .
git commit -m "Complete Module 2 project: unit converter"
git push
```
