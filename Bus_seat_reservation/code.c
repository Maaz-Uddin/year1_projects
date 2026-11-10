/* Bus seat simulator */

#include <stdio.h>

#define ROWS 10   /* number of rows in the bus     */
#define COLS 4    /* number of seats in each row   */

/* Function prototypes */
void initializeSeats(int seats[ROWS][COLS]);
void displaySeats(int seats[ROWS][COLS]);
void bookSeat(int seats[ROWS][COLS]);
void cancelSeat(int seats[ROWS][COLS]);
int  countAvailable(int seats[ROWS][COLS]);
int  readInt(void);

int main()
{
    int seats[ROWS][COLS];   /* array that holds all seat states */
    int choice;

    initializeSeats(seats);  /* start with every seat empty */

    do
    {
        printf("\n===== BUS SEAT RESERVATION =====\n");
        printf("1. View seat chart\n");
        printf("2. Book a seat\n");
        printf("3. Cancel a seat\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        choice = readInt();

        switch (choice)
        {
            case 1:
                displaySeats(seats);
                break;
            case 2:
                bookSeat(seats);
                displaySeats(seats);
                break;
            case 3:
                cancelSeat(seats);
                displaySeats(seats);
                break;
            case 4:
                printf("Thank you for using the simulator. Goodbye!\n");
                break;
            default:
                printf("Invalid choice! Please enter 1-4.\n");
        }
    } while (choice != 4);

    return 0;
}

/* Sets every seat to empty using nested loops */
void initializeSeats(int seats[ROWS][COLS])
{
    int i, j;
    for (i = 0; i < ROWS; i++)
    {
        for (j = 0; j < COLS; j++)
        {
            seats[i][j] = 0;
        }
    }
}

/* Prints the seat chart */
void displaySeats(int seats[ROWS][COLS])
{
    int i, j;

    printf("\n          SEAT CHART  (Front of bus)\n");
    printf("        Seat1 Seat2   Seat3 Seat4\n");

    for (i = 0; i < ROWS; i++)
    {
        printf("Row %2d  ", i + 1);          /* row numbers shown from 1 */
        for (j = 0; j < COLS; j++)
        {
            if (seats[i][j] == 0)
                printf("[ ]   ");
            else
                printf("[X]   ");

            if (j == 1)                      /* gap to represent the aisle */
                printf("  ");
        }
        printf("\n");
    }

    printf("\n[ ] = Available   [X] = Booked\n");
    printf("Seats available: %d / %d\n", countAvailable(seats), ROWS * COLS);
}

/* Asks for a row and seat number, then books it if possible */
void bookSeat(int seats[ROWS][COLS])
{
    int row, seat;

    printf("Enter row number (1-%d): ", ROWS);
    row = readInt();
    printf("Enter seat number (1-%d): ", COLS);
    seat = readInt();

    /* Validate the input */
    if (row < 1 || row > ROWS || seat < 1 || seat > COLS)
    {
        printf("Invalid row or seat number!\n");
        return;
    }

    /* User types 1-based numbers, the array is 0-based, so subtract 1 */
    if (seats[row - 1][seat - 1] == 1)
    {
        printf("Sorry, Row %d Seat %d is already booked.\n", row, seat);
    }
    else
    {
        seats[row - 1][seat - 1] = 1;
        printf("Success! Row %d Seat %d is now booked.\n", row, seat);
    }
}

/* Asks for a row and seat number, then cancels it if it was booked */
void cancelSeat(int seats[ROWS][COLS])
{
    int row, seat;

    printf("Enter row number (1-%d): ", ROWS);
    row = readInt();
    printf("Enter seat number (1-%d): ", COLS);
    seat = readInt();

    if (row < 1 || row > ROWS || seat < 1 || seat > COLS)
    {
        printf("Invalid row or seat number!\n");
        return;
    }

    if (seats[row - 1][seat - 1] == 0)
    {
        printf("Row %d Seat %d is not booked, nothing to cancel.\n", row, seat);
    }
    else
    {
        seats[row - 1][seat - 1] = 0;
        printf("Booking cancelled for Row %d Seat %d.\n", row, seat);
    }
}

/* Counts how many seats are still empty */
int countAvailable(int seats[ROWS][COLS])
{
    int i, j, count = 0;
    for (i = 0; i < ROWS; i++)
    {
        for (j = 0; j < COLS; j++)
        {
            if (seats[i][j] == 0)
                count++;
        }
    }
    return count;
}

/* Reads an integer safely: if the user types letters, returns -1
   instead of getting stuck in an endless loop. Whatever is left on
   the line (bad input or extra characters) is always thrown away. */
int readInt(void)
{
    int value;
    int c;
    int ok;

    ok = scanf("%d", &value);

    /* clear the rest of the line from the input buffer */
    while ((c = getchar()) != '\n' && c != EOF)
        ;

    if (ok != 1)
        return -1;

    return value;
}
