# Ticket-Reservation-System
Backend for an online ticket reservation system. The program display  the current seating arrangement and allow the patron to select seats. A report will be generated at the end of  the program to specify for each individual auditorium and overall for all auditoriums how many seats were  sold/unsold and how much money was earned.

Objectives:
 Directly manipulate files using advanced file functions
 Utilize string and character functions to perform basic input validation

Problem: 
Develop the backend for an online ticket reservation system. The program should display 
the current seating arrangement and allow the patron to select seats. A report should be generated at the end of 
the program to specify for each individual auditorium and overall for all auditoriums how many seats were 
sold/unsold and how much money was earned.

Pseudocode: 
 Main.cpp
	o List functions you plan to create
		 Determine the parameters
		 Determine the return type
		 Detail the step-by-step logic that the function will perform
	o Detail the step-by-step logic of the main function
Details
 The seating arrangement for the auditorium will be stored in a file named A1.txt
 Each line in the file will represent a row in the auditorium. The number of rows in the auditorium is 
unknown to you.
	o There will be a newline character after each line in the file except for the last line which may or 
	may not have a newline character.
 The number of seats in each row of the auditorium will be the same.
 No row will have more than 26 seats.
 Do not hold the auditorium in memory (-15 points if auditorium is held in memory)
	o Utilize random file access to view and modify the auditorium 
 Empty seats are represented by a period (.).
 Reserved seats are represented by a letter (A, C or S) in the file
	o This will be used to create reports
	o A =adult
	o C = child
	o S = senior
 Reserved seats will be represented by a hashtag (#) on the screen
	o The user does not need to know what type of ticket was sold, just that a seat is reserved.
 There is no need to worry about multiple screenings or reserving seats on a specific day.
 Ticket prices are as follows:
	o Adult - $10
	o Child - $5
	o Senior - $7.50

User Interface and Input: Present a user-friendly menu system for the user.
1. Reserve Seats
2. Exit

Loop the menu until the user decides to quit. Imagine this is for a ticket kiosk in the lobby of the theater.

If the user wants to reserve seats, display the current seating availability for that auditorium. An example seating 
chart is provided below for an auditorium with 5 rows and 20 seats per row.

 ABCDEFGHIJKLMNOPQRST
1 ...##..#####........
2 ########....####..##
3 .........##.........
4 #.#.#.#.#.#.#.#.#.#.
5 ########.#####.#####
The rows are numbered and the seats are identified in each row by a letter of the alphabet

After the seating chart has been displayed, prompt the user for the following information in the order below:

 Row number
 Starting seat letter
 Number of adult tickets
 Number of child tickets
 Number of senior tickets
Assume that the user wants to reserve sequential seats to the right of the first seat entered. Adult tickets will be 
reserved first, followed by child and then senior. All seats must be open for a reservation to be processed. 
Remember to mark the seat with the appropriate letter to show it has been reserved.
If the desired seats are not available, check for the best available seats that meet their criteria on that row only. 
The best available seats are the seats closest to the middle of the row measured by the distance from the center 
of the available selection to the middle of the row. If alternate seats are available, prompt the user to enter a Y to 
reserve the best available or N to refuse the best available. Once the selection has been processed, return to the 
main menu. If there are no alternate seats available, display an appropriate message to the user instead of a 
prompt and return to the main menu.
When prompting the user for input, expect anything. Do not assume any input will be valid. If you ask for a 
number, the user could put in a floating point number, symbols or maybe even the Gettysburg Address (or at least 
a sentence or two). Make sure that the user selection does not go out of bounds of the auditorium. If invalid 
input is entered, loop until valid input is received.
User Interface Workflow: Please do not add extra prompts since this will cause a mismatch in the input which will 
either force the program to throw an exception or cause the program to perform an unintended operation.
 Display main menu
 Prompt for input
 If user is reserving tickets
	o Prompt for row
	o Validate – loop until valid
		 Valid row = row number listed in auditorium display
	o Prompt for starting seat
	o Validate – loop until valid
		 Valid seat = seat number listed in auditorium display
	o Prompt for number of adult tickets
	o Validate – loop until valid
		 Valid ticket number = number >= 0
	o Prompt for number of child tickets
	o Validate – loop until valid
		 Valid ticket number = number >= 0
	o Prompt for number of senior tickets
	o Validate – loop until valid
		 Valid ticket number = number >= 0
	o If seats unavailable
		 Display best available
		 Prompt user to reserve (Y/N)
	o If reserved, confirm reservation
	o Return to main menu
 Loop to top of workflow until user selects exit

Output: At the end of the program, display a formatted report to the console. Make sure each column lines up 
properly (no jagged columns). Include the following information in the order given:
 Total Seats in Auditorium
 Total Tickets Sold
 Adult Tickets Sold
 Child Tickets Sold
 Senior Tickets Sold
 Total Ticket Sales – total amount of money collected for tickets in the auditorium
All values except total ticket sales will be an integer value. Total ticket sales will be a floating-point value rounded to 2 decimal places and formatted with a dollar sign before the first digit of the number