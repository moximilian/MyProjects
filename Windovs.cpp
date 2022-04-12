#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"
#include "framework.h"
#include <iostream>
#include <math.h>
#include <string>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <fstream>  
extern int X;
extern int Y;
char strGL[100];
char output[100];
string OutPut;
extern HWND  Graph;
using namespace std;

void PrintRes(HDC hdc);
int allowtoprint = 0;
void Menu(HDC hdc) {
	HFONT hFont;
	hFont = CreateFont(40,
		0, 0, 0, FW_BOLD, 0, 0, 0,
		DEFAULT_CHARSET,
		0, 0, 0, 0,
		L"Robota"
	);
	SelectObject(hdc, hFont);
	SetTextColor(hdc, RGB(0, 0, 50));
	TCHAR  string2[] = _T("Дифференцирование функции y'=f'(x)");
	TextOut(hdc, 20, 20, (LPCWSTR)string2, _tcslen(string2));
	DeleteObject(hFont);

	HFONT hFont3;
	hFont3 = CreateFont(30,
		0, 0, 0, 0, 0, 0, 0,
		DEFAULT_CHARSET,
		0, 0, 0, 0,
		L"Robota"
	);
	SetTextColor(hdc, RGB(75, 75, 75));
	SelectObject(hdc, hFont3);
	HBRUSH button;
	button = CreateSolidBrush(RGB(230, 230, 230));
	SelectObject(hdc, button);
	Rectangle(hdc, 200+50, 150, 350+50, 190); //remember
	//Rectangle(hdc, 370, 150, 520, 190);
	TCHAR  string12[] = _T("Enter");
	TextOut(hdc, 247+50, 155, (LPCWSTR)string12, _tcslen(string12));
	/*TCHAR string13[] = _T("Clear");
	TextOut(hdc, 417, 155, (LPCWSTR)string13, _tcslen(string13));*/
	DeleteObject(string12);
}
void Rememberfunc(HWND hWnd) {
	if (X >= 200+50 && X <= 350+50 && Y >= 150 && Y <= 190) {
		allowtoprint = 1;
		TCHAR StrT[100];
		string input;
		// 200, 150, 350, 190); 
		GetWindowText(Graph, StrT, sizeof(StrT));
		wcstombs(strGL, StrT, sizeof(StrT));
		for (int i = 0; i < sizeof(StrT); i++) { if (strGL[i] == 0)break; input += strGL[i];}
		OutPut = "";
		CheckDivision(input);
		SetFocus(hWnd);
		InvalidateRect(hWnd, NULL, TRUE);
	}
}
int strlen_(const char* str) {
	int n = 0;
	for (int i = 0; str[i] != '\0'; i++)
		n++;
	return n;
}

void PrintRes(HDC hdc) {
	strcpy(output, OutPut.c_str());
	char str[100];
	int i = 0;
	
	HFONT hFont;
	hFont = CreateFont(30,
			0, 0, 10, 1000, 0, 0, 0,
			DEFAULT_CHARSET,
			0, 0, 0, 0,
			L"Robota"
	);
	for (int i = 0; i < 100; i++)str[i] = 0;
	for (int i = 0; i < 100; i++)str[i] = output[i];

	SelectObject(hdc, hFont);
	SetTextColor(hdc, RGB(0, 0, 0));
	TextOutA(hdc, 315-(OutPut.size()*5), 250, (char *)str, strlen_(str));
	DeleteObject(hFont);
}