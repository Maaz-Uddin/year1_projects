# Bus Seat Reservation Simulator

A menu-driven C program that simulates seat reservation on a bus. It shows a seat chart, lets users book single or group seats, cancel bookings, search for passengers, and view a manifest with total revenue. Everything is stored in memory only while the program runs.

Made for **Programming for Problem Solving (PPS)**, B.E. I Semester, CSE-A, Muffakham Jah College of Engineering & Technology (MJCET), A.Y. 2026-27.

## Features

- Bus with **40 seats** (10 rows x 4 seats, with an aisle between seat 2 and seat 3)
- **Seat chart** showing `[ ]` for empty seats and `[M]` / `[F]` for booked seats
- **Book a single seat** in three ways: choose an exact row and seat, or let the program pick a window seat (seat 1 or 4) or an aisle seat (seat 2 or 3)
- **Book group seats**: 2 passengers on one bench, or 4 passengers in a full row, all under one shared Ticket ID
- **Safety rule**: a seat cannot be booked if the other seat on the same bench is taken by a passenger of a different gender (works for manual and automatic booking)
- **Cancel by Ticket ID**: frees every seat with that ticket and shows the refund
- **Search a passenger** by name
- **Manifest and revenue**: lists all passengers and the total fare collected
- **Input validation** for the menu choice, row and seat numbers, gender and ticket numbers

Each booking gets a Ticket ID (starting from 1001) and a fixed fare of Rs. 250.

## Concepts used

- Structures (`struct Seat`) with 5 fields: `isBooked`, `bookingId`, `passengerName`, `gender`, `fare`
- 2D array of structures: `struct Seat seats[10][4]`
- Strings (`strcpy`, `strstr`)
- Loops (`for`, `while`, `do-while`) and `switch-case`
- Functions and passing arrays to functions

## How to compile and run

You need a C compiler such as GCC.

```
gcc codenewvar.c -o bus
./bus
```

On Windows (Command Prompt) run `bus.exe` instead of `./bus`.

## Menu

```
===== BUS SEAT RESERVATION =====
1. View seat chart
2. Book a single seat
3. Book group seats (adjacent)
4. Cancel booking (by Ticket ID)
5. Search passenger by name
6. View bus manifest & revenue
7. Exit
```

## Sample output

Booking a single seat:

```
Enter your choice (1-7): 2
Enter passenger gender (M/F): M

Booking Preference:
1. Choose exact Row & Seat
2. Auto Window Seat (Seat 1 or 4)
3. Auto Aisle Seat (Seat 2 or 3)
Enter choice (1-3): 1
Enter row number (1-10): 3
Enter seat number (1-4): 2
Enter passenger name: Rahul Sharma

Success! Row 3 Seat 2 is booked.
Ticket ID: 1001 | Passenger: Rahul Sharma | Fare: Rs. 250.00

          SEAT CHART  (Front of bus)
        Seat1 Seat2   Seat3 Seat4
Row  1  [ ]   [ ]     [ ]   [ ]
Row  2  [ ]   [ ]     [ ]   [ ]
Row  3  [ ]   [M]     [ ]   [ ]
Row  4  [ ]   [ ]     [ ]   [ ]
Row  5  [ ]   [ ]     [ ]   [ ]
Row  6  [ ]   [ ]     [ ]   [ ]
Row  7  [ ]   [ ]     [ ]   [ ]
Row  8  [ ]   [ ]     [ ]   [ ]
Row  9  [ ]   [ ]     [ ]   [ ]
Row 10  [ ]   [ ]     [ ]   [ ]
```

The safety rule blocking a booking next to a passenger of a different gender:

```
Safety Rule: Cannot book! Seat 2 is taken by a Male passenger.
```

## Notes

- All data is lost when the program is closed.
- Name search is case-sensitive ("Ali" will not match "ali").
- Group bookings are for exactly 2 (one bench) or 4 (full row) passengers.
- Passenger names are limited to 49 characters.

## Team

- Khaja Maaz Uddin
- Mohammed Anas
- Zaara Khan
- Saba Begum
- Syed Mudassir Shareef
