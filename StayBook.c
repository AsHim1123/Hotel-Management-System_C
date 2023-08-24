#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

void setcolor(int ForgC)
{
	WORD wColor;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		wColor = (csbi.wAttributes & 0xB0) + (ForgC & 0x0B);
		//	SetConsoleTextAttributes(hStdOut,wColor);
		SetConsoleTextAttribute(hStdOut, wColor);
	}
}

// Defining the structure and it's members!!!
struct CustomerDetails
{
	char roomnumber[10];
	char name[20];
	char address[25];
	char phonenumber[15];
	char nationality[15];
	char email[20];
	char period[10];
	char arrivaldate[13];
	char checkoutdate[13];
} s;

// All Functions are declared here!!!
int calculate_monthly_profit();
void login();
void add_customer();
void list_customer();
void edit_customer();
void delete_customer();
void search_customer();
int casino_game();
int restaurant();

// Main function
int main()
{
	char customername;
	char choice;
	login();
	system("cls");
	while (1)
	{
		system("cls");

		printf("   ******************************  |MAIN MENU|  ***************************** \n");

		printf("\t\t *Please enter your choice for menu*:");
		printf("\n\n");
		printf(" \n Enter 1 -> Book a room");
		printf("\n------------------------");
		printf(" \n Enter 2 -> View Customer Record");
		printf("\n----------------------------------");
		printf(" \n Enter 3 -> Delete Customer Record");
		printf("\n-----------------------------------");
		printf(" \n Enter 4 -> Search Customer Record");
		printf("\n-----------------------------------");
		printf(" \n Enter 5 -> Edit Customer Record");
		printf("\n-----------------------");
		printf(" \n Enter 6 -> Play Casino");
		printf("\n-----------------------");
		printf(" \n Enter 7 -> See Hotel's Status");
		printf("\n-----------------------");
		printf(" \n Enter 8 -> Restaurant (Food Menu)");
		printf("\n-----------------------");
		printf(" \n Enter 9 -> Exit");
		printf("\n-----------------");
		printf("\n");

		choice = getche();
		switch (choice)
		{
		case '1':
			add_customer();
			break;
		case '2':
			system("cls");
			list_customer();
			break;
		case '3':
			system("cls");
			delete_customer();
			break;
		case '4':
			system("cls");
			search_customer();
			break;
		case '5':
			system("cls");
			edit_customer();
			break;
		case '6':
			casino_game();
			break;

		case '7':
		{
			system("cls");
			calculate_monthly_profit();
			printf("--------------------------------------------------------------------\n");
			printf("BILLINGS FOR THE RESPECTIVE ROOMS:\n");
			FILE *f;
			if ((f = fopen("add.txt", "r")) != NULL)
			{
				struct CustomerDetails temp;
				struct RoomBill
				{
					char roomnumber[10];
					float totalBill;
				} roomBills[100];

				int numRoomBills = 0;

				while (fread(&temp, sizeof(temp), 1, f) == 1)
				{
					int days = atoi(temp.period);
					float billAmount = days * 4000;

					int found = 0;
					for (int i = 0; i < numRoomBills; i++)
					{
						if (strcmp(temp.roomnumber, roomBills[i].roomnumber) == 0)
						{
							roomBills[i].totalBill += billAmount;
							found = 1;
							break;
						}
					}
					if (!found)
					{
						strcpy(roomBills[numRoomBills].roomnumber, temp.roomnumber);
						roomBills[numRoomBills].totalBill = billAmount;
						numRoomBills++;
					}
				}
				for (int i = 0; i < numRoomBills; i++)
				{
					printf("Room Number: %s\t Total Bill Amount: Rs. %.2f\n", roomBills[i].roomnumber, roomBills[i].totalBill);
				}

				fclose(f);
			}
			else
			{
				printf("No booking records found.\n");
			}

			getch();
			break;
		}
		case '8':
			system("cls");
			restaurant();
			break;
		case '9':
			system("cls");
			printf("\n\n\t -----------------THANK YOU FOR VISITING!!!------------------\n");
			printf("FOR CONTACTING ME : https://ashims.com.np");
			exit(0);
			break;

		default:
			system("cls");
			printf("Incorrect Input");
			printf("\n Press any key to continue");
			getch();
		}
	}
}
// Calculates the monthly profit of the hotel!!!
int calculate_monthly_profit()
{
	FILE *f;
	float totalProfit = 0.0;

	if ((f = fopen("add.txt", "r")) == NULL)
	{
		return totalProfit;
	}

	while (fread(&s, sizeof(s), 1, f) == 1)
	{
		int days = atoi(s.period);
		totalProfit += days * 4000;
	}
	printf("\n\nTotal Monthly Profit of the hotel: Rs. %.2f\n", totalProfit);
	fclose(f);
}

// Login system code!!!
void login()
{
	setcolor(15);
	char ch = ' ';
	int i = 0;
	char pass[20], correctPass[20], user_name[20], saved_name[20];

name:
	printf("----------------------------------LOGIN FORM---------------------------------\n\n");
	printf("\t\t\tEnter username: ");
	scanf("%19s", user_name);

	FILE *ptr;
	ptr = fopen("login_data.txt", "r");

	fscanf(ptr, "%19s %19s", saved_name, correctPass);
	fclose(ptr);

	if (strcmp(user_name, saved_name) != 0)
	{
		printf("You have entered wrong username! Try Again.\n");
		goto name;
	}
	else
	{
	pass:

		printf("\n\t\t\tEnter password: ");
		while (1)
		{
			pass[i] = getch();
			ch = pass[i];
			if (ch == 13) // ENTER Button
				break;
			else if (ch == 8) // Backspace Button
			{
				if (i > 0)
				{
					i--;
					pass[i] = '\0';
					printf("\b \b");
				}
			}
			else if (ch == 32 || ch == 9) // Space or Tab Button
			{
				continue;
			}
			else
				printf("*");
			i++;
		}
		pass[i] = '\0';
		i = 0;
		if (strcmp(pass, correctPass) == 0)
		{
			system("cls");
		}
		else
		{
			printf("\nYou have entered incorrect password! Try Again.\n");
			goto pass;
		}
	}
}

// Adding customer details in the file!!!
void add_customer()
{
	FILE *f;
	char test;
	f = fopen("add.txt", "a+");
	while (1)
	{
		system("cls");
		printf("\n Enter Customer Details:");
		printf("\n**************************");
		printf("\n Enter Room number:\n");
		scanf("\n%s", s.roomnumber);
		fflush(stdin);
		printf("Enter Full Name:\n");
		scanf("%[^\n]", s.name);
		printf("Enter Address:\n");
		scanf("%s", s.address);
		printf("Enter Phone Number:\n");
		scanf("%s", s.phonenumber);
		printf("Enter Nationality:\n");
		scanf("%s", s.nationality);
		printf("Enter Email:\n");
		scanf(" %s", s.email);
		printf("Enter Period(\'x\'days):\n");
		scanf("%s", &s.period);
		printf("Enter Arrival date(dd-mm-yyyy):\n");
		scanf("%s", &s.arrivaldate);
		printf("Enter Check-out date(dd-mm-yyyy):\n");
		scanf("%s", s.checkoutdate);

		fwrite(&s, sizeof(s), 1, f);
		fflush(stdin);
		printf("\n\n1 Room is successfully booked!!");
		printf("\n Press esc key to exit,  any other key to add another customer detail:");
		test = getche();
		if (test == 27)
			break;
	}
	fclose(f);
}

// Displaying all the customer details!!!
void list_customer()
{
	FILE *f;
	if ((f = fopen("add.txt", "r")) == NULL)
	{
		exit(0);
	}

	printf("+----------------------+----------------------+----------------------+----------------------+----------------------+----------------------+----------------------+----------------------+----------------------+\n");
	printf("|    ROOM NUMBER      |         NAME         |       ADDRESS        |    PHONE NUMBER     |     NATIONALITY     |        EMAIL        |       PERIOD        |    ARRIVAL DATE     |    CHECKOUT DATE    |\n");
	printf("+----------------------+----------------------+----------------------+----------------------+----------------------+----------------------+----------------------+----------------------+----------------------+\n");

	while (fread(&s, sizeof(s), 1, f) == 1)
	{
		printf("| %-20s | %-20s | %-20s | %-20s | %-20s | %-20s | %-20s | %-20s | %-20s |\n",
			   s.roomnumber, s.name, s.address, s.phonenumber, s.nationality, s.email, s.period, s.arrivaldate, s.checkoutdate);
		printf("+----------------------+----------------------+----------------------+----------------------+----------------------+----------------------+----------------------+----------------------+----------------------+\n");
	}

	if (feof(f))
	{
		printf("End of List!!!\n");
	}

	fclose(f);
	getch(); // Pause for the user to see the output
}

// Deleting the record of a specific customer!!!
void delete_customer()
{
	FILE *f, *t;
	int i = 1;
	char roomnumber[20];
	if ((t = fopen("temp.txt", "w")) == NULL)
		exit(0);
	if ((f = fopen("add.txt", "r")) == NULL)
		exit(0);
	system("cls");
	printf("Enter the Room Number of the hotel to be deleted from the database: \n");
	fflush(stdin);
	scanf("%s", roomnumber);
	while (fread(&s, sizeof(s), 1, f) == 1)
	{
		if (strcmp(s.roomnumber, roomnumber) == 0)
		{
			i = 0;
			continue;
		}
		else
			fwrite(&s, sizeof(s), 1, t);
	}
	if (i == 1)
	{
		printf("\n\n Records of Customer in this Room number is not found!!");
		getch();
		fclose(f);
		fclose(t);
	}
	else
	{
		fclose(f);
		fclose(t);
		remove("add.txt");
		rename("temp.txt", "add.txt");
		printf("\n\nThe Customer is successfully removed....");
		fclose(f);
		fclose(t);
		getch();
	}
}

// Searching a specific customer!!!
void search_customer()
{
	system("cls");
	FILE *f;
	char roomnumber[20];
	int flag = 1;
	f = fopen("add.txt", "r+");
	if (f == 0)
		exit(0);
	fflush(stdin);
	printf("Enter Room number of the customer to search his/her details: \n");
	scanf("%s", roomnumber);
	printf("+----------------------+----------------------+----------------------+----------------------+----------------------+----------------------+----------------------+----------------------+----------------------+\n");
	printf("|    ROOM NUMBER      |         NAME         |       ADDRESS        |    PHONE NUMBER     |     NATIONALITY     |        EMAIL        |       PERIOD        |    ARRIVAL DATE     |    CHECKOUT DATE    |\n");
	printf("+----------------------+----------------------+----------------------+----------------------+----------------------+----------------------+----------------------+----------------------+----------------------+\n");
	while (fread(&s, sizeof(s), 1, f) == 1)
	{
		if (strcmp(s.roomnumber, roomnumber) == 0)
		{
			flag = 0;
			printf("| %-20s | %-20s | %-20s | %-20s | %-20s | %-20s | %-20s | %-20s | %-20s |\n",
				   s.roomnumber, s.name, s.address, s.phonenumber, s.nationality, s.email, s.period, s.arrivaldate, s.checkoutdate);
			printf("+----------------------+----------------------+----------------------+----------------------+----------------------+----------------------+----------------------+----------------------+----------------------+\n");
			flag = 0;
			break;
		}
	}
	if (flag == 1)
	{
		printf("\n\tRequested Customer could not be found!");
	}
	getch();
	fclose(f);
}

// Editimg the details of a specific customer!!!
void edit_customer()
{
	FILE *f;
	int k = 1;
	char roomnumber[20];
	long int size = sizeof(s);
	if ((f = fopen("add.txt", "r+")) == NULL)
		exit(0);
	system("cls");
	printf("Enter Room number of the customer to edit:\n\n");
	scanf("%[^\n]", roomnumber);
	fflush(stdin);
	while (fread(&s, sizeof(s), 1, f) == 1)
	{
		if (strcmp(s.roomnumber, roomnumber) == 0)
		{
			k = 0;
			printf("\nEnter Room Number     :");
			gets(s.roomnumber);
			printf("\nEnter Name    :");
			fflush(stdin);
			scanf("%s", &s.name);
			printf("\nEnter Address        :");
			scanf("%s", &s.address);
			printf("\nEnter Phone number :");
			scanf("%f", &s.phonenumber);
			printf("\nEnter Nationality :");
			scanf("%s", &s.nationality);
			printf("\nEnter Email :");
			scanf("%s", &s.email);
			printf("\nEnter Period :");
			scanf("%s", &s.period);
			printf("\nEnter Arrival date :");
			scanf("%s", &s.arrivaldate);
			printf("\nEnter Check-out date :");
			scanf("%s", &s.checkoutdate);
			fseek(f, size, SEEK_CUR); // to go to desired position infile
			fwrite(&s, sizeof(s), 1, f);
			break;
		}
	}
	if (k == 1)
	{
		printf("\n\nTHE RECORD DOESN'T EXIST!!!!");
		fclose(f);
		getch();
	}
	else
	{
		fclose(f);
		printf("\n\n\t\tYOUR RECORD IS SUCCESSFULLY EDITED!!!");
		getch();
	}
}

// Code for casino game!!!
int casino_game()
{
	system("cls");
	int playerMoney = 10000;
	int betAmount;
	int chosenNumber;
	int diceRoll;

	srand(time(NULL));

	printf("Welcome to the Dice Rolling Casino Game!\n");
	printf("You currently have Rs.%d\n", playerMoney);

	while (playerMoney > 0)
	{
		printf("\nEnter your bet amount (0 to quit): ");
		scanf("%d", &betAmount);

		if (betAmount == 0)
		{
			printf("Thanks for playing! You're leaving with Rs.%d\n", playerMoney);
			break;
		}

		if (betAmount > playerMoney)
		{
			printf("You don't have enough money for that bet!\n");
			continue;
		}

		printf("Enter a number to bet on (1-11): ");
		scanf("%d", &chosenNumber);

		if (chosenNumber < 1 || chosenNumber > 11)
		{
			printf("Invalid number. Please choose a number between 1 and 11.\n");
			continue;
		}

		diceRoll = rand() % 11 + 1;
		printf("The dice rolled: %d\n", diceRoll);

		if (diceRoll == chosenNumber)
		{
			printf("Congratulations! You won Rs.%d\n", betAmount);
			playerMoney += betAmount;
		}
		else
		{
			printf("Sorry, you lost Rs.%d\n", betAmount);
			playerMoney -= betAmount;
		}

		printf("Your current balance: Rs.%d\n", playerMoney);
	}
	if (playerMoney <= 0)
	{
		printf("Game over! You've run out of money.\n");
	}

	return 0;
}
// Code for restaurant menu!!!
int restaurant()
{
	system("cls");
	char foodItems[][50] = {
		"Burger",
		"Pizza",
		"Momo",
		"Chowmein",
		"Salad",
		"French Fries",
		"Chicken Wings",
		"Katti Roll",
		"Coke",
		"Milkshake",
		"Chicken Parautha",
		"Noodles",
		"Black Forest",
		"Cappuccino",
		"Lemon Tea"};

	float prices[] = {180.0, 600.0, 120.0, 100.0, 60.0, 100.0, 300.0, 200.0, 50.0, 140.0, 90.0, 70.0, 65.0, 150.0, 40.0};

	int quantities[15] = {0};

	printf("\n---- Welcome to the Restaurant ----\n");

	printf("\nRestaurant Menu:\n");
	for (int i = 0; i < 15; i++)
	{
		printf("%d. %s - Rs.%.2f\n", i + 1, foodItems[i], prices[i]);
	}

	int choice;
	while (1)
	{
		printf("\nEnter the item number you want to order (0 to finish): ");
		scanf("%d", &choice);

		if (choice == 0)
		{
			break;
		}
		else if (choice < 1 || choice > 15)
		{
			printf("Invalid choice. Please choose a valid item.\n");
			continue;
		}

		int quantity;
		printf("Enter quantity: ");
		scanf("%d", &quantity);

		quantities[choice - 1] += quantity;
	}

	float totalBill = 0.0;
	printf("\n\n--- Your Order ---\n");
	for (int i = 0; i < 15; i++)
	{
		if (quantities[i] > 0)
		{
			printf("%s - Quantity: %d - Subtotal: Rs.%.2f\n", foodItems[i], quantities[i], prices[i] * quantities[i]);
			totalBill += prices[i] * quantities[i];
		}
	}

	printf("\nTotal Bill: Rs.%.2f\n", totalBill);
	printf("\nPress any key to return to the main menu...");
	getch();
	return 0;
}