#include <windows.h>
#include <CommCtrl.h>

#define IDC_MAIN_BUTTON	101			// Button identifier
#define IDC_MAIN_EDIT	102			// Edit box identifier
#define IDC_MAIN_BUTTON2	103			// Button identifier
#define IDC_MAIN_BUTTON3	104			// Button identifier
#define IDC_MAIN_STATUS	105			// Status bar identifier
HWND hEdit;
HWND hWndListBox;

LRESULT CALLBACK WinProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInst,HINSTANCE hPrevInst,LPSTR lpCmdLine,int nShowCmd)
{
	WNDCLASSEX wClass;
	ZeroMemory(&wClass,sizeof(WNDCLASSEX));
	wClass.cbClsExtra=NULL;
	wClass.cbSize=sizeof(WNDCLASSEX);
	wClass.cbWndExtra=NULL;
	wClass.hbrBackground=(HBRUSH)COLOR_WINDOW;
	wClass.hCursor=LoadCursor(NULL,IDC_ARROW);
	wClass.hIcon=NULL;
	wClass.hIconSm=NULL;
	wClass.hInstance=hInst;
	wClass.lpfnWndProc=(WNDPROC)WinProc;
	wClass.lpszClassName="Window Class";
	wClass.lpszMenuName=NULL;
	wClass.style=CS_HREDRAW|CS_VREDRAW;

	if(!RegisterClassEx(&wClass))
	{
		int nResult=GetLastError();
		MessageBox(NULL,
			"Window class creation failed\r\n",
			"Window Class Failed",
			MB_ICONERROR);
	}

	HWND hWnd=CreateWindowEx(NULL,
			"Window Class",
			"CalendarBook",
			WS_OVERLAPPEDWINDOW,
			100,
			100,
			800,
			600,
			NULL,
			NULL,
			hInst,
			NULL);

	if(!hWnd)
	{
		int nResult=GetLastError();

		MessageBox(NULL,
			"Window creation failed\r\n",
			"Window Creation Failed",
			MB_ICONERROR);
	}

    ShowWindow(hWnd,nShowCmd);

	MSG msg;
	ZeroMemory(&msg,sizeof(MSG));

	while(GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WinProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
		case WM_CREATE:
		{
			// Create an edit box
			hEdit=CreateWindowEx(WS_EX_CLIENTEDGE,
				"EDIT",
				"",
				WS_CHILD|WS_VISIBLE|
				ES_MULTILINE|ES_AUTOVSCROLL|ES_AUTOHSCROLL,
				50,
				100,
				200,
				100,
				hWnd,
				(HMENU)IDC_MAIN_EDIT,
				GetModuleHandle(NULL),
				NULL);
			HGDIOBJ hfDefault=GetStockObject(DEFAULT_GUI_FONT);
			SendMessage(hEdit,
				WM_SETFONT,
				(WPARAM)hfDefault,
				MAKELPARAM(FALSE,0));
			SendMessage(hEdit,
				WM_SETTEXT,
				NULL,
				(LPARAM)"Insert text here...");

			// Create a push button
			HWND hWndButton=CreateWindowEx(NULL,
				"BUTTON",
				"Log in",
				WS_TABSTOP|WS_VISIBLE|
				WS_CHILD|BS_DEFPUSHBUTTON,
				50,
				220,
				100,
				24,
				hWnd,
				(HMENU)IDC_MAIN_BUTTON,
				GetModuleHandle(NULL),
				NULL);
			SendMessage(hWndButton,
				WM_SETFONT,
				(WPARAM)hfDefault,
				MAKELPARAM(FALSE,0));

			// Create a push button
			HWND hWndButton2=CreateWindowEx(NULL,
				"BUTTON",
				"Sign up",
				WS_TABSTOP|WS_VISIBLE|
				WS_CHILD|BS_DEFPUSHBUTTON,
				50,
				250,
				100,
				24,
				hWnd,
				(HMENU)IDC_MAIN_BUTTON2,
				GetModuleHandle(NULL),
				NULL);
			SendMessage(hWndButton,
				WM_SETFONT,
				(WPARAM)hfDefault,
				MAKELPARAM(FALSE,0));

			// Create a push button
			HWND hWndButton3=CreateWindowEx(NULL,
				"BUTTON",
				"Edit profile",
				WS_TABSTOP|WS_VISIBLE|
				WS_CHILD|BS_DEFPUSHBUTTON,
				170,
				220,
				100,
				24,
				hWnd,
				(HMENU)IDC_MAIN_BUTTON3,
				GetModuleHandle(NULL),
				NULL);
			SendMessage(hWndButton,
				WM_SETFONT,
				(WPARAM)hfDefault,
				MAKELPARAM(FALSE,0));

			// Create a listview
			hWndListBox=CreateWindowEx(WS_EX_CLIENTEDGE,
				"LISTBOX",
				"listview",
				WS_CHILD|WS_VISIBLE|
				WS_VSCROLL|ES_AUTOVSCROLL,
				300,
				100,
				200,
				350,
				hWnd,
				(HMENU)IDC_MAIN_STATUS,
				GetModuleHandle(NULL),
				NULL);
			SendMessage(hWndListBox,
				LB_ADDSTRING,
				0,
				(LPARAM)"David is going to event1");
			SendMessage(hWndListBox,
				LB_ADDSTRING,
				0,
				(LPARAM)"John is going to event2");
		}
		break;

		case WM_COMMAND:
			switch(LOWORD(wParam))
            {
				case IDC_MAIN_BUTTON:
				{
					char buffer[256];
					SendMessage(hEdit,
						WM_GETTEXT,
						sizeof(buffer)/sizeof(buffer[0]),
						reinterpret_cast<LPARAM>(buffer));
					MessageBox(NULL,
						buffer,
						"Information",
						MB_ICONINFORMATION);
					break;
				}
				case IDC_MAIN_STATUS:
				{
					char buffer[256];
					SendMessage(hWndListBox,
						WM_GETTEXT,
						sizeof(buffer)/sizeof(buffer[0]),
						reinterpret_cast<LPARAM>(buffer));
					MessageBox(NULL,
						buffer,
						"Information",
						MB_ICONINFORMATION);
					break;
				}
				break;
			}
			break;

		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
		break;
	}

	return DefWindowProc(hWnd,msg,wParam,lParam);
}
