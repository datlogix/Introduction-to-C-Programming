#include <stdio.h>
#include <string.h>

#define MAX_CONTACTS 50
#define DATA_FILE "contacts.txt"

typedef struct {
    char name[30];
    char phone[20];
    char email[40];
} Contact;

// TODO: declare loadContacts, saveContacts, addContact, and viewContacts
// here (see the TODO comments below main for what each one needs to do).


int main(void) {
    Contact contacts[MAX_CONTACTS];
    int count = 0;

    // TODO: call loadContacts(contacts) here and store its return value in
    // `count`. This is what makes contacts survive between runs -- see
    // examples/07_reading_a_file.c for the read-back pattern.

    int choice = 0;
    while (choice != 3) {
        printf("\n--- Contact Book (%d saved) ---\n", count);
        printf("1. Add contact\n");
        printf("2. View contacts\n");
        printf("3. Save & exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        if (choice == 1) {
            // TODO: call addContact(contacts, &count) here.
            //       Pass &count (address-of, Module 7) so addContact can
            //       update the caller's count after adding a contact.
        } else if (choice == 2) {
            // TODO: call viewContacts(contacts, count) here.
        } else if (choice == 3) {
            // TODO: call saveContacts(contacts, count) here, then print a
            //       goodbye message. This is your last chance to write the
            //       data out -- don't forget fclose() inside saveContacts.
        } else {
            printf("Not a valid option, try again.\n");
        }
    }

    return 0;
}

// TODO: define loadContacts(Contact *contacts) here. It should:
//   - fopen(DATA_FILE, "r")
//   - if fopen returns NULL, there's no saved file yet -- that's normal on
//     the very first run, not an error. Just `return 0;` (zero contacts).
//   - otherwise, fscanf contacts back in the same order/format you write
//     them in saveContacts, counting how many you successfully read
//   - fclose() the file, then return the count

// TODO: define saveContacts(Contact *contacts, int count) here. It should:
//   - fopen(DATA_FILE, "w")
//   - ALWAYS check the result isn't NULL before using it
//   - fprintf each contact in `contacts[0..count-1]`, one per line
//   - fclose() when done -- this is what actually guarantees your data
//     reaches disk before the program exits

// TODO: define addContact(Contact *contacts, int *count) here. It should:
//   - take `count` BY POINTER so it can update the caller's count
//     (mirrors examples/05_passing_structs_by_pointer_to_functions.c)
//   - read a name, phone, and email into contacts[*count]
//   - increment *count when done

// TODO: define viewContacts(Contact *contacts, int count) here. It should:
//   - loop over contacts[0..count-1] and print each one, numbered
//   - if count is 0, print a friendlier message than an empty list
