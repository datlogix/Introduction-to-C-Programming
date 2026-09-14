#include <stdio.h>

/*
Exercise 1: Build a small library shelf.

1. Define a struct (use typedef) called Book with three members:
       char title[50];
       char author[30];
       int  year;

2. In main(), create an array of 3 Book values called `shelf`, filled in
   with books of your choice (real or made up).

3. Write a function:
       void printBooks(Book *shelf, int count);
   that takes the array BY POINTER (Module 7 style -- an array name
   already decays to a pointer to its first element, so you can pass
   `shelf` directly) and prints every book's title, author, and year,
   one per line, using `->` to reach the members through the pointer as
   you loop.

4. Call printBooks from main() to print your shelf.

Compile and run often. This is the same pattern you'll use for the
module project (and the capstone): a struct type, an array of it, and a
function that receives the array by pointer.
*/

// TODO: define the Book struct with typedef here.


// TODO: declare printBooks(Book *shelf, int count) here.


int main(void) {
    // TODO: create an array of 3 Book values, filled in.


    // TODO: call printBooks to print every book in the array.


    return 0;
}

// TODO: define printBooks here. Loop over the array using a pointer
// index like shelf[i], and print each member with shelf[i].member --
// or, for extra practice with Module 7, walk the array with a moving
// pointer and use `->` instead.
