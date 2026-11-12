/* Bus Seat Simulator with Structures & Safety Check */
#include <stdio.h>
#include <string.h>

#define ROWS 10   /* 10 rows in the bus   */
#define COLS 4    /* 4 seats in each row */

/* Seat structure storing data for each seat */
struct Seat {
    int isBooked;              /* 0 = empty, 1 = booked */
    int bookingId;             /* Ticket ID */
    char passengerName[50];    /* Name of passenger */
    char gender;               /* 'M' or 'F' */
    float fare;                /* Ticket fare */
};

/* Global counter to issue unique ticket numbers */
int nextBookingId = 1001;

/* Function prototypes */
void initializeSeats(struct Seat seats[ROWS][COLS]);
void displaySeats(struct Seat seats[ROWS][COLS]);
void bookSingleSeat(struct Seat seats[ROWS][COLS]);
void bookGroupSeats(struct Seat seats[ROWS][COLS]);
void cancelBooking(struct Seat seats[ROWS][COLS]);
void searchPassenger(struct Seat seats[ROWS][COLS]);
void displayManifest(struct Seat seats[ROWS][COLS]);
int  countAvailable(struct Seat seats[ROWS][COLS]);
int  getAdjacentCol(int col);
int  isSeatSafeForGender(struct Seat seats[ROWS][COLS], int row, int col, char gender);
int  readInt(void);
char readGender(void);
void readName(char name[]);

int main(void)
{
    struct Seat seats[ROWS][COLS];
    int choice;

    initializeSeats(seats);

    do
    {
        printf("\n===== BUS SEAT RESERVATION =====\n");
        printf("1. View seat chart\n");
        printf("2. Book a single seat\n");
        printf("3. Book group seats (adjacent)\n");
        printf("4. Cancel booking (by Ticket ID)\n");
        printf("5. Search passenger by name\n");
        printf("6. View bus manifest & revenue\n");
        printf("7. Exit\n");
        printf("Enter your choice (1-7): ");
        choice = readInt();

        switch (choice)
        {
            case 1:
                displaySeats(seats);
                break;
            case 2:
                bookSingleSeat(seats);
                displaySeats(seats);
                break;
            case 3:
                bookGroupSeats(seats);
                displaySeats(seats);
                break;
            case 4:
                cancelBooking(seats);
                displaySeats(seats);
                break;
            case 5:
                searchPassenger(seats);
                break;
            case 6:
                displayManifest(seats);
                break;
            case 7:
                printf("\nThank you for using the simulator. Goodbye!\n");
                break;
            default:
                printf("Invalid choice! Please enter 1-7.\n");
        }
    } while (choice != 7);

    return 0;
}

/* Sets all seats to default empty values */
void initializeSeats(struct Seat seats[ROWS][COLS])
{
    int i, j;
    for (i = 0; i < ROWS; i++)
    {
        for (j = 0; j < COLS; j++)
        {
            seats[i][j].isBooked = 0;
            seats[i][j].bookingId = 0;
            seats[i][j].gender = ' ';
            strcpy(seats[i][j].passengerName, "");
            seats[i][j].fare = 0.0f;
        }
    }
}

/* Returns the column of the seat on the same bench */
int getAdjacentCol(int col)
{
    if (col == 0) return 1; /* Seat 1 is next to Seat 2 */
    if (col == 1) return 0; /* Seat 2 is next to Seat 1 */
    if (col == 2) return 3; /* Seat 3 is next to Seat 4 */
    if (col == 3) return 2; /* Seat 4 is next to Seat 3 */
    return -1;
}

/* Safety rule: different genders cannot sit on the same bench */
int isSeatSafeForGender(struct Seat seats[ROWS][COLS], int row, int col, char gender)
{
    int adjCol = getAdjacentCol(col);

    if (seats[row][adjCol].isBooked == 1)
    {
        if (seats[row][adjCol].gender != gender)
        {
            return 0; /* Block booking */
        }
    }
    return 1; /* Allowed */
}

/* Prints the seat chart with aisle and gender indicator */
void displaySeats(struct Seat seats[ROWS][COLS])
{
    int i, j;

    printf("\n          SEAT CHART  (Front of bus)\n");
    printf("        Seat1 Seat2   Seat3 Seat4\n");

    for (i = 0; i < ROWS; i++)
    {
        printf("Row %2d  ", i + 1);
        for (j = 0; j < COLS; j++)
        {
            if (seats[i][j].isBooked == 0)
                printf("[ ]   ");
            else
                printf("[%c]   ", seats[i][j].gender);

            if (j == 1)
                printf("  "); /* Aisle gap */
        }
        printf("\n");
    }

    printf("\n[ ] = Available   [M] = Male   [F] = Female\n");
    printf("Seats available: %d / %d\n", countAvailable(seats), ROWS * COLS);
}

/* Handles individual seat bookings */
void bookSingleSeat(struct Seat seats[ROWS][COLS])
{
    int opt;
    int row = -1, col = -1;
    char name[50];
    char gender;
    float fare = 250.0f;

    if (countAvailable(seats) == 0)
    {
        printf("Bus is completely full!\n");
        return;
    }

    printf("Enter passenger gender (M/F): ");
    gender = readGender();

    printf("\nBooking Preference:\n");
    printf("1. Choose exact Row & Seat\n");
    printf("2. Auto Window Seat (Seat 1 or 4)\n");
    printf("3. Auto Aisle Seat (Seat 2 or 3)\n");
    printf("Enter choice (1-3): ");
    opt = readInt();

    if (opt == 1)
    {
        printf("Enter row number (1-%d): ", ROWS);
        row = readInt() - 1;
        printf("Enter seat number (1-%d): ", COLS);
        col = readInt() - 1;

        if (row < 0 || row >= ROWS || col < 0 || col >= COLS)
        {
            printf("Invalid row or seat number!\n");
            return;
        }

        if (seats[row][col].isBooked == 1)
        {
            printf("Sorry, Row %d Seat %d is already booked.\n", row + 1, col + 1);
            return;
        }

        if (!isSeatSafeForGender(seats, row, col, gender))
        {
            int adjCol = getAdjacentCol(col);
            printf("Safety Rule: Cannot book! Seat %d is taken by a %s passenger.\n",
                   adjCol + 1, (gender == 'M') ? "Female" : "Male");
            return;
        }
    }
    else if (opt == 2 || opt == 3)
    {
        int i, j;
        int found = 0;

        for (i = 0; i < ROWS && !found; i++)
        {
            for (j = 0; j < COLS && !found; j++)
            {
                if (seats[i][j].isBooked == 0 && isSeatSafeForGender(seats, i, j, gender))
                {
                    if (opt == 2 && (j == 0 || j == 3))
                    {
                        row = i;
                        col = j;
                        found = 1;
                    }
                    else if (opt == 3 && (j == 1 || j == 2))
                    {
                        row = i;
                        col = j;
                        found = 1;
                    }
                }
            }
        }

        if (!found)
        {
            printf("No available seats match that preference and safety criteria.\n");
            return;
        }
    }
    else
    {
        printf("Invalid option!\n");
        return;
    }

    printf("Enter passenger name: ");
    readName(name);

    /* Store booking */
    seats[row][col].isBooked = 1;
    seats[row][col].bookingId = nextBookingId++;
    seats[row][col].gender = gender;
    strcpy(seats[row][col].passengerName, name);
    seats[row][col].fare = fare;

    printf("\nSuccess! Row %d Seat %d is booked.\n", row + 1, col + 1);
    printf("Ticket ID: %d | Passenger: %s | Fare: Rs. %.2f\n",
           seats[row][col].bookingId, seats[row][col].passengerName, seats[row][col].fare);
}

/* Books adjacent seats on the same bench for a group */
void bookGroupSeats(struct Seat seats[ROWS][COLS])
{
    int groupSize;
    int targetRow = -1, startCol = -1;
    int sharedId;
    char gender;
    int i;

    printf("Enter number of passengers (2 for bench, 4 for full row): ");
    groupSize = readInt();

    if (groupSize != 2 && groupSize != 4)
    {
        printf("Group booking only supports 2 (one bench) or 4 (full row).\n");
        return;
    }

    if (countAvailable(seats) < groupSize)
    {
        printf("Not enough available seats on the bus!\n");
        return;
    }

    printf("Enter gender for group members (M/F): ");
    gender = readGender();

    /* Find empty bench or row */
    if (groupSize == 2)
    {
        for (i = 0; i < ROWS; i++)
        {
            if (seats[i][0].isBooked == 0 && seats[i][1].isBooked == 0)
            {
                targetRow = i;
                startCol = 0;
                break;
            }
            if (seats[i][2].isBooked == 0 && seats[i][3].isBooked == 0)
            {
                targetRow = i;
                startCol = 2;
                break;
            }
        }
    }
    else if (groupSize == 4)
    {
        for (i = 0; i < ROWS; i++)
        {
            if (seats[i][0].isBooked == 0 && seats[i][1].isBooked == 0 &&
                seats[i][2].isBooked == 0 && seats[i][3].isBooked == 0)
            {
                targetRow = i;
                startCol = 0;
                break;
            }
        }
    }

    if (targetRow == -1)
    {
        printf("Could not find an empty bench/row together.\n");
        return;
    }

    sharedId = nextBookingId++;

    printf("Allocated Row %d (Seats %d to %d):\n",
           targetRow + 1, startCol + 1, startCol + groupSize);

    for (i = 0; i < groupSize; i++)
    {
        char name[50];
        int col = startCol + i;

        printf("Enter name for Passenger %d (Seat %d): ", i + 1, col + 1);
        readName(name);

        seats[targetRow][col].isBooked = 1;
        seats[targetRow][col].bookingId = sharedId;
        seats[targetRow][col].gender = gender;
        strcpy(seats[targetRow][col].passengerName, name);
        seats[targetRow][col].fare = 250.0f;
    }

    printf("\nGroup Booking Confirmed! Shared Ticket ID: %d\n", sharedId);
}

/* Cancels seats using Ticket ID */
void cancelBooking(struct Seat seats[ROWS][COLS])
{
    int ticketId;
    int i, j;
    int cancelledCount = 0;
    float refund = 0.0f;

    printf("Enter Ticket ID to cancel: ");
    ticketId = readInt();

    for (i = 0; i < ROWS; i++)
    {
        for (j = 0; j < COLS; j++)
        {
            if (seats[i][j].isBooked == 1 && seats[i][j].bookingId == ticketId)
            {
                printf("Cancelled: %s (Row %d, Seat %d)\n",
                       seats[i][j].passengerName, i + 1, j + 1);

                refund += seats[i][j].fare;
                seats[i][j].isBooked = 0;
                seats[i][j].bookingId = 0;
                seats[i][j].gender = ' ';
                strcpy(seats[i][j].passengerName, "");
                seats[i][j].fare = 0.0f;
                cancelledCount++;
            }
        }
    }

    if (cancelledCount > 0)
    {
        printf("Success! %d seat(s) cancelled. Refund: Rs. %.2f\n", cancelledCount, refund);
    }
    else
    {
        printf("No active booking found with Ticket ID %d.\n", ticketId);
    }
}

/* Searches passenger names */
void searchPassenger(struct Seat seats[ROWS][COLS])
{
    char query[50];
    int i, j;
    int found = 0;

    printf("Enter passenger name to search: ");
    readName(query);

    printf("\nSearch Results:\n");
    for (i = 0; i < ROWS; i++)
    {
        for (j = 0; j < COLS; j++)
        {
            if (seats[i][j].isBooked == 1 && strstr(seats[i][j].passengerName, query) != NULL)
            {
                printf("Ticket: %d | Name: %s | Gender: %c | Row %d Seat %d\n",
                       seats[i][j].bookingId, seats[i][j].passengerName,
                       seats[i][j].gender, i + 1, j + 1);
                found = 1;
            }
        }
    }

    if (!found)
    {
        printf("No passenger found matching '%s'.\n", query);
    }
}

/* Prints all passengers and total bus revenue */
void displayManifest(struct Seat seats[ROWS][COLS])
{
    int i, j;
    int total = 0;
    float revenue = 0.0f;

    printf("\n===== BUS PASSENGER MANIFEST =====\n");
    for (i = 0; i < ROWS; i++)
    {
        for (j = 0; j < COLS; j++)
        {
            if (seats[i][j].isBooked == 1)
            {
                printf("Ticket: %d | %-20s | Gender: %c | Row %2d, Seat %d | Rs. %.2f\n",
                       seats[i][j].bookingId, seats[i][j].passengerName,
                       seats[i][j].gender, i + 1, j + 1, seats[i][j].fare);
                total++;
                revenue += seats[i][j].fare;
            }
        }
    }

    if (total == 0)
    {
        printf("No booked seats.\n");
    }

    printf("----------------------------------\n");
    printf("Total Booked: %d / %d | Revenue: Rs. %.2f\n", total, ROWS * COLS, revenue);
}

/* Counts empty seats */
int countAvailable(struct Seat seats[ROWS][COLS])
{
    int i, j, count = 0;
    for (i = 0; i < ROWS; i++)
    {
        for (j = 0; j < COLS; j++)
        {
            if (seats[i][j].isBooked == 0)
                count++;
        }
    }
    return count;
}

/* Your original textbook-standard safe integer reader */
int readInt(void)
{
    int value;
    int c;
    int ok;

    ok = scanf("%d", &value);

    while ((c = getchar()) != '\n' && c != EOF)
        ;

    if (ok != 1)
        return -1;

    return value;
}

/* Reads M or F safely using simple scanf and getchar */
char readGender(void)
{
    char g;
    int c;

    while (1)
    {
        if (scanf(" %c", &g) == 1)
        {
            while ((c = getchar()) != '\n' && c != EOF)
                ;

            if (g >= 'a' && g <= 'z')
                g = g - 32; /* Simple ASCII to uppercase */

            if (g == 'M' || g == 'F')
                return g;
        }

        printf("Please enter 'M' or 'F': ");
    }
}

/* Textbook method to read a full line with spaces using scanf */
void readName(char name[])
{
    int c;

    /* Reads up to 49 characters including spaces until Enter is pressed */
    if (scanf(" %49[^\n]", name) != 1)
    {
        strcpy(name, "Unknown");
    }

    /* Clean leftover newline */
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}
