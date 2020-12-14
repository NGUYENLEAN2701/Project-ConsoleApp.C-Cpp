#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <string>
#include <windows.h>
#include <math.h>
#include <algorithm>
#include <conio.h>
#include <sstream>
#ifdef max
#undef max
#endif // max undef
#ifdef ESC
#undef ESC
#endif
#define ESC 27 // ESC
#ifdef ENTER
#undef ENTER
#endif
#define ENTER 13 // ENTER
typedef struct Result_QE
{
	float Real_Value = 0;
	float Virtual_Value = 0;
	int Exist = -1; //-1: Vô Nghiệm; 0:Vô Số Nghiệm; 1:Nghiệm Thực; 2:Nghiệm Ảo;
} Result_QE;

float Input_Value(char c)
{
	float num = 0;
	while (std::wcout << L"Nhập " << c << L" = " && !(std::wcin >> num))
	{
		std::wcin.clear();                                                   //clear bad input flag
		std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
		std::wcout << L"Lỗi dữ liệu, thử lại!" << std::endl;
	}
	return num;
}

void Print_Equation(float a, float b, float c)
{
	std::wcout << L"PT: ";
	//Print a:
	if (a > 0)
	{
		if (a == 1)
			std::wcout << L"x\u00B2 ";
		else
			std::wcout << a << L"x\u00B2 ";
	}
	else if (a < 0)
	{
		if (a == -1)
			std::wcout << L"-x\u00B2 ";
		else
			std::wcout << a << L"x\u00B2 ";
	}
	//Print b:
	if (b == 0)
	{
		if (a == 0)
			std::wcout << L"0x ";
	}
	else if (b > 0)
	{
		if (b == 1)
		{
			if (a == 0)
				std::wcout << L"x ";
			else
				std::wcout << L"+x ";
		}
		else
		{
			if (a == 0)
				std::wcout << b << L"x ";
			else
				std::wcout << L"+" << b << L"x ";
		}
	}
	else
	{
		if (b == -1)
		{
			std::wcout << L"-x ";
		}
		else
		{
			std::wcout << b << L"x ";
		}
	}
	//Print c:
	if (c > 0)
	{
		std::wcout << L"+" << c << L" ";
	}
	else if (c < 0)
	{
		std::wcout << c << L" ";
	}
	std::wcout << L"= 0" << std::endl;
}

void Solve_QuadraticEquation(float a, float b, float c, Result_QE* x1, Result_QE* x2)
{
	if (a == 0 && b == 0 && c == 0)
	{
		x1->Exist = 0;
	}
	else if (a == 0 && b == 0 && c != 0)
		;
	else if (a == 0)
	{
		x1->Exist = 1;
		x1->Real_Value = -c / b;
		if (!x1->Real_Value)
			x1->Real_Value = 0;
	}
	else
	{
		float delta = b * b - 4 * a * c;
		if (delta == 0)
		{
			x1->Exist = 1;
			x1->Real_Value = -b / (2 * a);
			if (!x1->Real_Value)
				x1->Real_Value = 0;
		}
		else if (delta > 0)
		{
			x1->Exist = 1;
			x1->Real_Value = (-b + sqrt(delta)) / (2 * a);
			if (!x1->Real_Value)
				x1->Real_Value = 0;

			x2->Exist = 1;
			x2->Real_Value = (-b - sqrt(delta)) / (2 * a);
			if (!x2->Real_Value)
				x2->Real_Value = 0;
		}
		else
		{
			x1->Exist = 2;
			x1->Real_Value = (-b) / (2 * a);
			x1->Virtual_Value = sqrt(-delta) / (2 * a);

			x2->Exist = 2;
			x2->Real_Value = (-b) / (2 * a);
			x2->Virtual_Value = -sqrt(-delta) / (2 * a);
		}
	}
}

void Print_Value(Result_QE x, std::wstring s)
{
	switch (x.Exist)
	{
	case -1:
	{

		std::wcout << L"->Phương Trình Vô Nghiệm" << std::endl;
		break;
	}
	case 0:
	{
		std::wcout << L"->Phương Trình Có Vô Số Nghiệm " << s << L"\u03f5Z" << std::endl;
		break;
	}
	case 1:
	{
		std::wcout << L"-> " << s << L" = " << x.Real_Value << std::endl;
		break;
	}
	case 2:
	{
		std::wcout << L"-> " << s << L" = ";
		if (x.Real_Value)
		{
			std::wcout << x.Real_Value << L" ";
			if (x.Virtual_Value > 0)
			{
				std::wcout << L"+";
			}
			else
			{
				std::wcout << L"";
			}
			if (x.Virtual_Value * x.Virtual_Value != 1)
				std::wcout << x.Virtual_Value;
			else if (x.Virtual_Value == -1)
				std::wcout << L"-";
		}
		else
		{
			if (x.Virtual_Value * x.Virtual_Value != 1)
				std::wcout << x.Virtual_Value;
			else if (x.Virtual_Value == -1)
				std::wcout << L"-";
		}
		std::wcout << L"i" << std::endl;
		break;
	}
	default:
	{
		std::wcout << L"Error" << std::endl;
	}
	}
}

void Print_Result_QE(Result_QE x1, Result_QE x2)
{
	if (x2.Exist == -1)
	{
		Print_Value(x1, L"x");
	}
	else
	{
		if (x1.Real_Value <= x2.Real_Value)
		{
			Print_Value(x1, L"x\u2081");
			Print_Value(x2, L"x\u2082");
		}
		else
		{
			Print_Value(x2, L"x\u2081");
			Print_Value(x1, L"x\u2082");
		}
	}
}
