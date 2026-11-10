# Bus Seat Reservation Simulator

A menu-driven C program that simulates seat reservation on a bus with 40 seats (10 rows × 4 seats). Built as a PPS (Programming for Problem Solving) project.

## Features
- **View seat chart:** shows every seat as available `[ ]` or booked `[X]`, with a gap for the aisle and a count of free seats
- **Book a seat:** enter a row and seat number to reserve it
- **Cancel a booking:** enter a row and seat number to free it
- **Input validation:** rejects out-of-range numbers, already-booked seats, and seats that aren't booked when cancelling

## How it works
- Seat status is stored in a 2D array `seats[10][4]` (`0` = empty, `1` = booked)
- Bookings exist only while the program is running and reset when it exits
- The program uses functions, nested loops, a `switch` menu and a `do-while` loop

## Concepts used
Arrays (2D), functions, loops, conditionals, input validation

## How to run
```bash
gcc code.c -o bus
./bus
```
(On Windows, run `bus.exe` instead of `./bus`.)

## Sample menu
```
===== BUS SEAT RESERVATION =====
1. View seat chart
2. Book a seat
3. Cancel a seat
4. Exit
```
