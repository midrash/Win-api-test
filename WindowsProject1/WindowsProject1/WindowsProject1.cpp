// WindowsProject1.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h" // window api 의 인풋 아웃풋 관련된것들이 구현되어이있음
#include "WindowsProject1.h"


#include<time.h>
#include<iostream>
#include<stdio.h>

#include<list>

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

WCHAR lpszText[10] = L"click";
std::list<WCHAR> wCharLst;
// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 여기에 코드를 입력합니다.
	srand(time(NULL));
	// 전역 문자열을 초기화합니다.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 응용 프로그램 초기화를 수행합니다.
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

	MSG msg;

	// 기본 메시지 루프입니다.
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	//wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	wcex.hbrBackground = (HBRUSH)GetStockObject(DKGRAY_BRUSH);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	HWND hWnd = CreateWindowW(szWindowClass, L"제목 여기씀", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적:  주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
bool isTogle;
WORD y;
WORD x;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{

		/************************************************
	case WM_KEYDOWN:
	{
		if (wParam == 0x41) // a 키 누르면 들어옴
		{
			HDC hdc = GetDC(hWnd);
			TextOut(hdc, 100, 100, L"test", 4);
		}
		break;
	}
	**************************************************/

	case WM_MOUSEMOVE:
	{
		y = HIWORD(lParam);
		x = LOWORD(lParam);
		/*
		isTogle = !isTogle;
		if (isTogle)
		{
			HDC hdc = GetDC(hWnd); //현제 윈도우의 주소값으로부터 DC를 가져오고 그걸 기반으로 텍스트를 아웃함
			int r = rand() % 300;
			RECT rt = { 100,100,400, 400 };
			//DrawText(hdc, lpszText, 5, &rt, r);

			TextOut(hdc, x, y, lpszText, 10);


			//TextOut(hdc, rand() % 300, rand()%300, lpszText, 10); //srand 는 시스템 메인에 있음

			ReleaseDC(hWnd, hdc); // 한번쓴 DC는 또쓸게 아니면 날려주는게 좋음, GetDC 는 쓰면 레퍼런스 포인터가 늘어남 이걸 끊어줘서 0개가 되면 자동으로 메모리가 해제됨,(스마트 포인터? 라고하는듯)
		}
		*/
		break;
	}


	/*
	case WM_LBUTTONUP:
	{
		isTogle = false;
	}

	case WM_LBUTTONDOWN:
	{
		WORD y = HIWORD(lParam);
		WORD x = LOWORD(lParam);
		isTogle = !isTogle;
		if (isTogle)
		{
			HDC hdc = GetDC(hWnd); //현제 윈도우의 주소값으로부터 DC를 가져오고 그걸 기반으로 텍스트를 아웃함
			int r = rand() % 300;
			RECT rt = { 100,100,400, 400 };
			//DrawText(hdc, lpszText, 5, &rt, r);

			TextOut(hdc, x, y, lpszText, 10);


			//TextOut(hdc, rand() % 300, rand()%300, lpszText, 10); //srand 는 시스템 메인에 있음

			ReleaseDC(hWnd, hdc); // 한번쓴 DC는 또쓸게 아니면 날려주는게 좋음, GetDC 는 쓰면 레퍼런스 포인터가 늘어남 이걸 끊어줘서 0개가 되면 자동으로 메모리가 해제됨,(스마트 포인터? 라고하는듯)

		}
		else
		{
			//PostMessage(hWnd, WM_PAINT, wParam, lParam);
			InvalidateRect(hWnd, NULL, TRUE);
		}
		break;
	}

	*/

	/*
	case WM_MOUSEMOVE:
	{

		WORD y = HIWORD(lParam);
		WORD x = LOWORD(lParam);
		isTogle = !isTogle;
		if (isTogle)
		{
			InvalidateRect(hWnd, NULL, TRUE);
			HDC hdc = GetDC(hWnd); //현제 윈도우의 주소값으로부터 DC를 가져오고 그걸 기반으로 텍스트를 아웃함
			TextOut(hdc, x, y, , 10);
			}

		WORD ex_x = x;
		WORD ex_y = y;
	*/

	case WM_KEYDOWN:
	{
		InvalidateRect(hWnd, NULL, TRUE);
		WCHAR input;
		HDC hdc = GetDC(hWnd);
		if (wCharLst.size() >= 10)
		{
			wCharLst.pop_front();
		}
		//if (wParam != NULL)
		//{
		//	input = wParam;
		//}

		input = L'a';// wParam;

		wCharLst.push_back(input);
		auto iter = wCharLst.begin();
		int idx = 0;
		for (iter; iter != wCharLst.end(); ++iter)
		{
			TextOut(hdc, x + idx * 9, y, &(*iter), 1);
			idx++;
		}

		ReleaseDC(hWnd, hdc); // 한번쓴 DC는 또쓸게 아니면 날려주는게 좋음, GetDC 는 쓰면 레퍼런스 포인터가 늘어남 이걸 끊어줘서 0개가 되면 자동으로 메모리가 해제됨,(스마트 포인터? 라고하는듯)
		break;
	}
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 메뉴 선택을 구문 분석합니다.
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT: // 첨에 한번 불리고 그 이후로는 특정한 상황에서 임의로 불려진다.
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다.
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
