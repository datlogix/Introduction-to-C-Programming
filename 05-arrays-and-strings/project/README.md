# Module 5 Project — Secret Message Encoder/Decoder

Remember the hook from the top of this module's README? It could only
*decode* one hardcoded message, with a shift of 3 baked into the code.
You're building the general version now: a program that can encode **or**
decode **any** message, with **any** shift the user chooses.

This is called a **Caesar cipher** — each letter is shifted a fixed
number of places through the alphabet. Shifting forward encodes a
message; shifting the same amount backward decodes it.

## Requirements

Your program must:

1. Ask the user whether they want to **encode** or **decode**, and read
   their answer.
2. Ask the user to type their **message**, read with `fgets` (not
   `scanf("%s", ...)`, so the message can include spaces).
3. Ask the user for a **shift amount** and read it.
4. Handle **both uppercase and lowercase** letters correctly.
5. Leave **anything that isn't a letter** — spaces, punctuation, digits —
   completely unshifted.
6. Print the resulting message.
7. Prove it works both ways: encoding a message with shift N, then
   decoding that exact output with the same shift N, must give back the
   original message.

## Ideas if you're stuck

- Start by getting encoding working for lowercase letters only, test it,
  *then* add uppercase, *then* add decoding. Small working steps beat one
  giant attempt.
- Decoding by shift `N` is the same math as encoding by shift `26 - N` —
  if that's easier for you to reason about, use it.
- Watch out for negative numbers from the `%` operator in C when you
  shift backward — `(x - shift + 26) % 26` keeps the result positive no
  matter what `shift` is.
- Try shift amounts bigger than 26, or 0 — does your program still behave
  sensibly?

## Getting started

Open [`starter.c`](starter.c) and work through the `TODO` comments in
order — each one builds on the last. Compile and run often; don't write
the whole thing before testing your first piece.

```bash
gcc starter.c -o cipher
./cipher
```

## Done?

Commit and push it:

```bash
git add .
git commit -m "Complete Module 5 project: secret message encoder/decoder"
git push
```
