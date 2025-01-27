#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Ticket {
    int ticketNumber;
    char passengerName[50];
    char source[50];
    char destination[50];
    struct Ticket* next;
};

struct Ticket* head = NULL;

// Function to add a new ticket
void addTicket(int ticketNumber, char* passengerName, char* source, char* destination) {
    struct Ticket* newTicket = (struct Ticket*)malloc(sizeof(struct Ticket));
    newTicket->ticketNumber = ticketNumber;
    strcpy(newTicket->passengerName, passengerName);
    strcpy(newTicket->source, source);
    strcpy(newTicket->destination, destination);
    newTicket->next = NULL;

    if (head == NULL) {
        head = newTicket;
    } else {
        struct Ticket* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newTicket;
    }
}

// Function to remove a ticket by ticket number
void removeTicket(int ticketNumber) {
    struct Ticket* temp = head;
    struct Ticket* prev = NULL;

    if (temp != NULL && temp->ticketNumber == ticketNumber) {
        head = temp->next;
        free(temp);
        return;
    }

    while (temp != NULL && temp->ticketNumber != ticketNumber) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) return;

    prev->next = temp->next;
    free(temp);
}

// Function to display all tickets
void displayTickets() {
    struct Ticket* temp = head;
    if (temp == NULL) {
        printf("No tickets booked.\n");
        return;
    }
    while (temp != NULL) {
        printf("Ticket Number: %d\n", temp->ticketNumber);
        printf("Passenger Name: %s\n", temp->passengerName);
        printf("Source: %s\n", temp->source);
        printf("Destination: %s\n", temp->destination);
        printf("-------------------------------\n");
        temp = temp->next;
    }
}

// Function to search for a ticket by ticket number
void searchTicket(int ticketNumber) {
    struct Ticket* temp = head;
    while (temp != NULL) {
        if (temp->ticketNumber == ticketNumber) {
            printf("Ticket Found:\n");
            printf("Ticket Number: %d\n", temp->ticketNumber);
            printf("Passenger Name: %s\n", temp->passengerName);
            printf("Source: %s\n", temp->source);
            printf("Destination: %s\n", temp->destination);
            return;
        }
        temp = temp->next;
    }
    printf("Ticket with number %d not found.\n", ticketNumber);
}

// Function to edit a ticket
void editTicket(int ticketNumber) {
    struct Ticket* temp = head;
    while (temp != NULL) {
        if (temp->ticketNumber == ticketNumber) {
            printf("Editing Ticket Number: %d\n", ticketNumber);
            printf("Enter New Passenger Name: ");
            scanf(" %49[^\n]", temp->passengerName);
            printf("Enter New Source: ");
            scanf(" %49[^\n]", temp->source);
            printf("Enter New Destination: ");
            scanf(" %49[^\n]", temp->destination);
            printf("Ticket updated successfully!\n");
            return;
        }
        temp = temp->next;
    }
    printf("Ticket with number %d not found.\n", ticketNumber);
}

// Function to count total tickets
int countTickets() {
    int count = 0;
    struct Ticket* temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

// Function to save tickets to a file
void saveTickets(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    struct Ticket* temp = head;
    while (temp != NULL) {
        fprintf(file, "%d\n%s\n%s\n%s\n", temp->ticketNumber, temp->passengerName, temp->source, temp->destination);
        temp = temp->next;
    }
    fclose(file);
    exit(0);
    printf("Tickets saved to %s successfully!\n", filename);
}

// Function to clear all tickets
void clearAllTickets() {
    struct Ticket* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
    printf("All tickets cleared.\n");
}

// Function to sort tickets based on ticket number
void sortTickets() {
    if (head == NULL || head->next == NULL) return; // No need to sort

    struct Ticket* sorted = NULL;
    struct Ticket* current = head;

    while (current != NULL) {
        struct Ticket* next = current->next; // Store next node
        if (sorted == NULL || sorted->ticketNumber >= current->ticketNumber) {
            current->next = sorted;
            sorted = current;
        } else {
            struct Ticket* temp = sorted;
            while (temp->next != NULL && temp->next->ticketNumber < current->ticketNumber) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }
    head = sorted; // Update head to point to the new sorted list
}

// Function to view tickets by source and destination
void viewBySourceDestination(char* source, char* destination) {
    struct Ticket* temp = head;
    int found = 0;
    while (temp != NULL) {
        if (strcmp(temp->source, source) == 0 && strcmp(temp->destination, destination) == 0) {
            printf("Ticket Number: %d\n", temp->ticketNumber);
            printf("Passenger Name: %s\n", temp->passengerName);
            printf("Source: %s\n", temp->source);
            printf("Destination: %s\n", temp->destination);
            printf("-------------------------------\n");
            found = 1;
        }
        temp = temp->next;
    }
    if (!found) {
        printf("No tickets found from %s to %s.\n", source, destination);
    }
}

// Function to search tickets by passenger name
void searchByPassengerName(char* passengerName) {
    struct Ticket* temp = head;
    int found = 0;
    while (temp != NULL) {
        if (strcmp(temp->passengerName, passengerName) == 0) {
            printf("Ticket Number: %d\n", temp->ticketNumber);
            printf("Passenger Name: %s\n", temp->passengerName);
            printf("Source: %s\n", temp->source);
            printf("Destination: %s\n", temp->destination);
            printf("-------------------------------\n");
            found = 1;
        }
        temp = temp->next;
    }
    if (!found) {
        printf("No tickets found for passenger: %s\n", passengerName);
    }
}



int main() {
    int ticket;
    char passenger[50];
    char source[50], destination[50];
    char choice;

    do {
        printf("Enter Ticket Number: ");
        scanf("%d", &ticket);
        printf("Enter Passenger Name: ");
        scanf(" %49[^\n]", passenger);
        printf("Enter Source: ");
        scanf(" %49[^\n]", source);
        printf("Enter Destination: ");
        scanf(" %49[^\n]", destination);

        addTicket(ticket, passenger, source, destination);

        printf("Do you want to add another Passenger? (y/n): ");
        scanf(" %c", &choice);
    } while (choice == 'y' || choice == 'Y');

    int x;
    do {
        printf("\nEnter What you want to do\n");
        printf("1 - Show All Booked Tickets\n");
        printf("2 - Cancel Ticket From Booked Ticket list\n");
        printf("3 - Search and Display Particular ticket\n");
        printf("4 - Edit a Ticket\n");
        printf("5 - Count Total Tickets\n");
        printf("6 - Save Tickets to File\n");
        printf("7 - Clear All Tickets\n");
        printf("8 - Sort Tickets by Ticket Number\n");
        printf("9 - View Tickets by Source and Destination\n");
        printf("10 - Search Tickets by Passenger Name\n");
        printf("0 - Exit the LIST\n");
        scanf("%d", &x);

        switch (x) {
            case 1:
                printf("\nAll Booked Tickets:\n");
                displayTickets();
                break;
            case 2:{
                int removeTic;
                printf("\nEnter the ticket number you want to Cancel: ");
                scanf("%d", &removeTic);
                removeTicket(removeTic);
                printf("\nAfter Cancelling ticket %d:\n", removeTic);
                printf("Final Booked Ticket List\n");
                displayTickets();
                break;
            }
            case 3:{
                int searchTic;
                printf("\nEnter the ticket number you want to search for: ");
                scanf("%d", &searchTic);
                searchTicket(searchTic);
                break;
            }
            case 4:{
                int editTic;
                printf("\nEnter the ticket number you want to edit: ");
                scanf("%d", &editTic);
                editTicket(editTic);
                break;
            }
            case 5:
                printf("Total Tickets: %d\n", countTickets());
                break;
            case 6:
                saveTickets("tickets.txt");
                break;
            case 7:
                clearAllTickets();
                break;
            case 8:
                sortTickets();
                printf("Tickets sorted successfully!\n");
                break;
            case 9:{
                printf("Enter Source: ");
                scanf(" %49[^\n]", source);
                printf("Enter Destination: ");
                scanf(" %49[^\n]", destination);
                viewBySourceDestination(source, destination);
                break;
            }
            case 10:{
                printf("Enter Passenger Name: ");
                scanf(" %49[^\n]", passenger);
                searchByPassengerName(passenger);
                break;
            }
            case 0:
                printf("Exiting...\n");
        }
    } while (x != 0);

return 0;
}