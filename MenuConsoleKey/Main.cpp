#include "head.h"
#include <iostream>
#include <windows.h>
#include <locale.h>
#include "../Stack.h"
#include <limits>
#include <stdlib.h>

void clearRow(int row)
{
	DWORD dw;
	COORD here;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	here.X = 2;
	here.Y = row;
	WriteConsoleOutputCharacter(hStdOut, L"      ", 6, here, &dw);
}

const char* space = "\t\t";
HWND console = nullptr;
POINT PosConsole = { 100,100 };
POINT sizeConsole = { 1200,600 };

void FontsSettings(int width, int height) {
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = width;
	cfi.dwFontSize.Y = height;
	cfi.FontFamily = FF_DONTCARE; 
	cfi.FontWeight = 600;
	//std::wcscpy(cfi.FaceName, L"Sony Sketch EF");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}


void loading()
{
	ProgressBar prog("", 0, 0);
	bool exit = true;
	while (exit)
	{	
		//cls();
		setCursorPosition(65, 16);
		setConsoleColour(0xA);
		std::wcout << "LOADING...";
		setCursorPosition(18, 18);
		prog.Show(0);
		Sleep(10);
		prog.ChangeValue(0);
		std::cout.flush();
		if (prog.value == 100.0F)
			exit = false;
	}

}


int menu(field* Array_field, int cout_Array_field)
{
	cls();

	//Exemple :)
	setConsoleColour(0xA);
	bool change = true;
	bool finish = false;
	int pos = 0;
	int max = 0;
	timer tmr1(100, true);

	while (!finish)
	{
		if (tmr1.timer_on())
		{
			if (change)
			{
				square(40, 5, 1, 0, 0);
				setCursorPosition(8, 0);
				size_t i = 0;
				
				std::cout << " GitHub @Yut-ka \r";
				std::cout << std::endl;
				int line_number = 8;

				for (field* ptr = Array_field; ptr <= &Array_field[cout_Array_field - 1]; ptr++) {
					setCursorPosition(2, line_number++);
					ptr->show(pos);
					++i;
				}
				
				max = i-1;
				change = false;
				
			}
	
			if (GetAsyncKeyState(VK_UP))
			{
				pos--;
				if (pos < 0)
					pos = max;
				change = true;

			}
			if (GetAsyncKeyState(VK_DOWN))
			{
				++pos;
				if (pos > max)
					pos = 0;
				change = true; 
			}
			if (GetAsyncKeyState(VK_RETURN))
			{
				for (field* ptr = Array_field; ptr <= &Array_field[cout_Array_field - 1]; ptr++) {
					ptr->Press(pos);				
				}
				pos == max ? finish = true : finish = false;
				change = true;
				return pos;
			}
			setCursorPosition(2, 2);
			std::cout << "SAOD LAB1";
			setCursorPosition(2, 3);
			std::cout << "by Osipov Danil 4218";	
			setCursorPosition(2, 15);


			std::cout.flush();
		}
		Sleep(1);
	}
}


std::string text(textblock field)
{
	cls();

	//Exemple :)
	setConsoleColour(0xA);
	bool change = true;
	bool finish = false;
	int pos = 0;
	int max = 0;
	timer tmr1(100, true);
	

	while (!finish)
	{
		if (tmr1.timer_on())
		{
			
			std::string a;

			if (change)
			{
				square(40, 5, 1, 0, 0);
				setCursorPosition(8, 0);
				size_t i = 0;

				std::cout << " GitHub @Yut-ka \r" << std::endl;
				std::cout << std::endl;

				setCursorPosition(2, 2);
				std::cout << "SAOD LAB1" << std::endl;
				setCursorPosition(2, 3);
				std::cout << "by Osipov Danil 4218" << std::endl;

				setCursorPosition(2, 8);
				field.show(pos);
				setCursorPosition(2, 10);
				clearRow(10);
				getline(std::cin,a);
				std::cin.clear();
				std::cin.sync();
			}

			

			if (GetAsyncKeyState(VK_RETURN))
			{
				finish = true;
				return a;
			}

			
			
			std::cout.flush();
		}
		Sleep(0.5);
	}
}


std::string Get_el_console() {
	textblock C = "Enter a new stack element";
	std::flush(std::cout);
	std::string A = text(C);
	return A;
}


int main()
{ 
	FontsSettings(0, 16);
	console = GetConsoleWindow();
	SetWindowPos(console, NULL, PosConsole.x, PosConsole.y, sizeConsole.x, sizeConsole.y, NULL);
	SetWindowLong(console, GWL_STYLE, WS_BORDER);
	ShowWindow(console, SW_SHOW);
	ExConsole();
	loading();


	Stack a;
	Stack b;

	field A[6] = { "checking for stack emptiness", "adding an item to the end of the stack" ,"removing an item from the top of the stack","displays the current stack state on the screen","displays the current stack state on the screen","Exit" };
	
	while (1) {
		bool back = 0;
		int choice = menu(A, 6);
		if (choice == 0) {
			while (!back) {
				field B[2] = { "Stack is empty!" ,"Back" };
				if (!a.IsEmpty())
					B[0].name = "Stack is not empty!";
				if (menu(B, 2) == 1) back = 1;
			}
		}
		else if (choice == 1) {
			while (!back) {
				field ADD[3] = { "Add one new element", "Add several new elements" ,"Back" };
				int ADD_choice = menu(ADD, 3);
				if (ADD_choice == 0) {
					field ADD_1[3] = { "Add new element manually", "Add element from secondary stack (if not emty)", "Back" };
					int ADD_1_choice = menu(ADD_1,3);
					if (ADD_1_choice == 0) {
						a.Push(Get_el_console());
						back = 1;
					}
					if (ADD_1_choice == 1) {
						if (!b.IsEmpty()) {
							a.Push(b.sp->inf);
							b.Delete();
						}
						back = 1;
					}
					if (ADD_1_choice == 2) {
						back = 1;
					}
				}
				if (ADD_choice == 1) {
					textblock A = "Enter a number of new elements";
					int COUT_NEW_ITEMS = stoi(text(A));
					field ADD_2[4] = { "Add new elements manually" ,"Add new elements with the RANDOM function", "Add new elements from secondary Stack (while not empty)", "Back" };
					int ADD_2_choice = menu(ADD_2, 4);
					if (ADD_2_choice == 0) {
						for (int i = 0; i < COUT_NEW_ITEMS; i++) {
							a.Push(Get_el_console());
						}
						back = 1;
					}
					if (ADD_2_choice == 1) {
						for (int i = 0; i < COUT_NEW_ITEMS; i++) {
							a.Push(std::to_string(rand()));
						}
						back = 1;
					}
					if (ADD_2_choice == 2) {
						for (int i = 0; i < COUT_NEW_ITEMS; i++) {
							if (!b.IsEmpty()) {
								a.Push(b.sp->inf);
								b.Delete();
							}
						}
						back = 1;
					}
					if (ADD_2_choice == 3) {
						back = 1;
					}
				}
				if (ADD_choice == 2) {
					back = 1;
				}
							
			}
		}
		else if (choice == 2) {
			while (!back){
				field DEL[3] = { "Delete an item with free memory", "Add elements into secondary Stack", "Back" };
				int DEL_choice = menu(DEL, 3);
				if (DEL_choice == 0) {
					field D[2] = { "The top of the stack is removed!" ,"Back" };	
					if (a.IsEmpty())
						D[0].name = "The stack is empty!";
					else
						a.Delete();
					if (menu(D, 2) == 1) back = 1;
				}
				if (DEL_choice == 1) {
					field D[2] = { "The top of the stack is removed!" ,"Back" };
					if (a.sp != NULL) {
						b.Push(a.sp->inf);
						a.Delete();
					}
					else {
						D[0].name = "The stack is empty!";
					}	
					if (menu(D, 2) == 1) back = 1;
				}
				if (DEL_choice == 2) {
					back = 1;
				}
				
			}
		}
		else if (choice == 3) {
			while (!back) {
				field E[3] = { "Output of the entire stack:" , "Back", a.Show() };
				if (menu(E, 3) == 1) back = 1;
			}
		}
		else if (choice == 4) {
			while (!back) {
				field E[3] = { "Output of the secondary stack:" , "Back", b.Show() };
				if (menu(E, 3) == 1) back = 1;
			}
		}
		else if (choice == 5) {
			exit(0);
		}
	}
	
	
	return 0;
}

