// FuckFuckTicketing.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <d3d9.h>
#include "FuckFuckTicketing.h"
#include "Windows.h"
#include "OleCtl.h"
#include "mmsystem.h"

int _tmain(int argc, _TCHAR* argv[])
{
	LoadDefaults();

	unsigned char* pPixels = new unsigned char[(gScreenWidth * 4 * gScreenHeight)];

	int loopcount = 0;


	while (loopcount < 100000)
	{
		GetScreenPixels(pPixels);

		if (FuckFuckTicketing(pPixels))
			break;

		loopcount++;
	}
	Finalize();

	return 0;
}

bool FuckFuckTicketing(unsigned char* pPixels)
{
	MatchBox match;

	match = FindMatchAndClick(pPixels, gImageFiles["ok.bmp"]);
	if (match.IsValid())
	{
		Click((match.leastX + match.mostX) / 2, (match.leastY + match.mostY) / 2);
		return false;
	}

	match = FindMatchAndClick(pPixels, gImageFiles["ok2.bmp"]);
	if (match.IsValid())
	{
		Click((match.leastX + match.mostX) / 2, (match.leastY + match.mostY) / 2);
		Sleep(1000);
		return false;
	}

	match = FindMatchAndClick(pPixels, gImageFiles["changeday.bmp"]);
	if (match.IsValid())
	{
		MatchBox m2;

		MatchBox m3 = FindMatchAndClick(pPixels, gImageFiles["selected_seat.bmp"]);
		if (!m3.IsValid()) {
			return false;
		}
		///allseats -> then confirm
		bool res = AllSeats(pPixels, MatchBox(m3.leastX + 7, m3.leastY + 29, m3.leastX + 88, m3.leastY + 59));
		if (res)
		{
			MatchBox m4 = FindMatchAndClick(pPixels, gImageFiles["clearseat.bmp"]);
			Click(m4.leastX - 10, m4.leastY - 10);
			return false;
		}
		/*
		m2 = ClickSeats(pPixels, MatchBox(match.leastX + 316, match.leastY + 454, match.leastX + 407, match.leastY + 493), 10, 10, true);
		if (m2.IsValid())
		{
			Click(m2.leastX + 2, m2.leastY + 3);
			return false;
		}
		*/
		
		
		// area click
		m2 = ClickSeats(pPixels, MatchBox(match.leastX + 162, match.leastY + 123, match.leastX + 530, match.leastY + 354), 4, 4, true);
		if (m2.IsValid())
		{
			Click(m2.leastX + 2, m2.leastY + 3);
			return false;
		}
		
		// seat click
		m2 = ClickSeats(pPixels, MatchBox(match.leastX + 14, match.leastY + 46, match.leastX + 624, match.leastY + 628), 5, 6, true);
		if (m2.IsValid())
		{
			Click(m2.leastX + 2, m2.leastY + 3);
			return false;
		}
		

		if (IsAllEmpty(pPixels, MatchBox(match.leastX + 38, match.leastY + 88, match.leastX + 624, match.leastY + 628)))
		{
			

			m2 = FindMatchAndClick(pPixels, gImageFiles["fullview.bmp"]);
			if (m2.IsValid())
			{
				Click((m2.leastX + m2.mostX) / 2, (m2.leastY + m2.mostY) / 2);
				gSeatEmptyTick = 0;
				return false;
			}
			/*
			int deltaX[] = { -20, 40, -20, 40 };
			int deltaY[] = { -300, -250, -250, -300 };
			Click(m3.mostX + deltaX[gSeatEmptyTick % 4], m3.leastY + deltaY[gSeatEmptyTick % 4]);
			*/
			gSeatEmptyTick++;
		}
		///area click

		return false;
	}
	
	match = FindMatchAndClick(pPixels, gImageFiles["next.bmp"]);
	if (match.IsValid())
	{
		return true;
	}

	match = FindMatchAndClick(pPixels, gImageFiles["purchase.bmp"]);
	if (match.IsValid())
	{
		MatchBox m2 = FindMatchAndClick(pPixels, gImageFiles["mutong.bmp"]);
		if (!m2.IsValid())
			return false;
		else
		{
			Click(m2.leastX, m2.leastY);
			Click(m2.leastX + 122, m2.leastY);
			Click(m2.leastX + 122, m2.leastY + 32);
			Click(m2.leastX - 69, m2.leastY + 277);
			Click(m2.leastX + 216, m2.leastY + 277);
			return true;
		}
	}


	match = FindMatchAndClick(pPixels, gImageFiles["btn_seat.bmp"]);
	if (match.IsValid())
	{
		Click((match.leastX + match.mostX) / 2, (match.leastY + match.mostY) / 2);
		return false;
	}

	match = FindMatchAndClick(pPixels, gImageFiles["eight.bmp"]);
	if (match.IsValid())
	{
		if (YesDate(pPixels, MatchBox(match.leastX - 99, match.leastY + 181, match.leastX + 600, match.leastY + 301)))
			return false;

		MatchBox m2 = ClickSeats(pPixels, MatchBox(match.leastX - 99, match.leastY + 181, match.leastX + 600, match.leastY + 301), 28, 28, true, false);
		if (m2.IsValid())
		{
			Click(m2.leastX + 6, m2.leastY + 6);
			//Sleep(500);
			return false;
		}
		else
		{
			//Refresh();
		}
	}

	if (!gClickedReserv)
	{
		match = FindMatchAndClick(pPixels, gImageFiles["btn_reserv.bmp"]);
		if (match.IsValid())
		{
			Click((match.leastX + match.mostX) / 2, (match.leastY + match.mostY) / 2);
			gClickedReserv = true;
			return false;
		}
		else
		{
			match = FindMatchAndClick(pPixels, gImageFiles["btn_reserv2.bmp"]);
			if (match.IsValid())
			{
				Click((match.leastX + match.mostX) / 2, (match.leastY + match.mostY) / 2);
				gClickedReserv = true;
				return false;
			}

		}
	}

	return false;

}

bool GetPixels(HBITMAP hBmp, unsigned char* &pPixels, int &outwidth, int &outheight, bool init)
{
	BITMAP bm;
	GetObject(hBmp, sizeof(bm), &bm);
	int width(bm.bmWidth),
		height(bm.bmHeight);

	//creating a bitmapheader for getting the dibits
	BITMAPINFOHEADER bminfoheader;
	::ZeroMemory(&bminfoheader, sizeof(BITMAPINFOHEADER));
	bminfoheader.biSize = sizeof(BITMAPINFOHEADER);
	bminfoheader.biWidth = width;
	bminfoheader.biHeight = -height;
	bminfoheader.biPlanes = 1;
	bminfoheader.biBitCount = 32;
	bminfoheader.biCompression = BI_RGB;

	bminfoheader.biSizeImage = width * 4 * height;
	bminfoheader.biClrUsed = 0;
	bminfoheader.biClrImportant = 0;

	if (!init)
		pPixels = new unsigned char[width * 4 * height];

	outwidth = width;
	outheight = height;

	if (!GetDIBits(CreateCompatibleDC(0), hBmp, 0, height, pPixels, (BITMAPINFO*)&bminfoheader, DIB_RGB_COLORS)) // load pixel info 
	{
		return false;
	}
	return true;
}
bool GetScreenPixels(unsigned char* pPixels)
{

	HBITMAP hCaptureBitmap = CreateCompatibleBitmap(gDesktopDC,
		gScreenWidth, gScreenHeight);
	SelectObject(gCaptureDC, hCaptureBitmap);
	BitBlt(gCaptureDC, 0, 0, gScreenWidth, gScreenHeight,
		gDesktopDC, 0, 0, SRCCOPY | CAPTUREBLT);

	int x = 0, y = 0;
	bool result = GetPixels(hCaptureBitmap, pPixels, x, y, true);

	DeleteObject(hCaptureBitmap);
	return result;
}

bool AllSeats(unsigned char* screenPixels, MatchBox mb)
{
	for (int y = mb.leastY; y < mb.mostY; y++)
	{
		for (int x = mb.leastX; x < mb.mostX; x++)
		{
			if (screenPixels[(y*gScreenWidth + x) * 4 + 2] != 255 ||
				screenPixels[(y*gScreenWidth + x) * 4 + 1] != 255 ||
				screenPixels[(y*gScreenWidth + x) * 4 + 0] != 255)
				return true;
		}
	}
	return false;
}

void LoadDefaults()
{
	gScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	gScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	gDesktopWnd = GetDesktopWindow();
	gDesktopDC = GetDC(gDesktopWnd);
	gCaptureDC = CreateCompatibleDC(gDesktopDC);

	gImageFiles = std::map<std::string, ImageFile>();

	std::string fileNames[] = {
		"btn_reserv.bmp",
		"btn_reserv2.bmp",
		"btn_seat.bmp",
		"changeday.bmp",
		"clearseat.bmp",
		"ok.bmp",
		"next.bmp",
		"purchase.bmp",
		"mutong.bmp",
		"ok2.bmp",
		"eight.bmp",
		"fullview.bmp",
		"selected_seat.bmp"
	};

	HBITMAP hBmp;

	for (int i = 0; i < 13; i++)
	{
		std::wstring stemp = std::wstring(fileNames[i].begin(), fileNames[i].end());

		gImageFiles[fileNames[i]] = ImageFile();
		gImageFiles[fileNames[i]].name = fileNames[i];

		hBmp = (HBITMAP)LoadImage(GetModuleHandle(NULL), stemp.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		GetPixels(hBmp, gImageFiles[fileNames[i]].pixels, gImageFiles[fileNames[i]].width, gImageFiles[fileNames[i]].height);
		DeleteObject(hBmp);
	}
}

void Finalize()
{
	ReleaseDC(gDesktopWnd, gDesktopDC);
	DeleteDC(gCaptureDC);
	PlaySound(TEXT("SystemAsterisk"), NULL, SND_ALIAS);
}

void Click(int x, int y)
{
	LONG targetX = x * 65536 / gScreenWidth;
	LONG targetY = y * 65536 / gScreenHeight;

	INPUT inp;
	inp.type = INPUT_MOUSE;
	inp.mi.dx = targetX;
	inp.mi.dy = targetY;
	inp.mi.dwExtraInfo = 0;
	inp.mi.time = 0;
	inp.mi.dwFlags = MOUSEEVENTF_MOVE + MOUSEEVENTF_ABSOLUTE;
	SendInput(1, &inp, sizeof(INPUT));

	inp.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	SendInput(1, &inp, sizeof(INPUT));

	inp.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	SendInput(1, &inp, sizeof(INPUT));

	printf("click %d %d\n", targetX, targetY);
	Sleep(300);
	gSeatEnter = false;

}

void Refresh()
{


	INPUT inp;
	inp.type = INPUT_KEYBOARD;
	inp.ki.wVk = VK_F5;
	inp.ki.dwFlags = 0;

	SendInput(1, &inp, sizeof(INPUT));
	Sleep(1000);

}


MatchBox FindMatchAndClick(unsigned char* screenPixels, ImageFile img)
{
	int matchedPixels = 0;
	int maxMatch = 0;

	int leastX = 0,
		leastY = 0,
		mostX = 0,
		mostY = -1;

	if (!img.IsValid())
		return MatchBox();

	int height = img.height;
	int width = img.width;
	unsigned char* buttenImg = img.pixels;

	for (int y = 0; y < gScreenHeight; y++)
	{
		if (y + height >= gScreenHeight)
			break;

		for (int x = 0; x < gScreenWidth; x++)
		{
			if (x + width >= gScreenWidth)
				break;

			if (screenPixels[(y*gScreenWidth + x) * 4 + 2] == buttenImg[matchedPixels * 4 + 2] &&
				screenPixels[(y*gScreenWidth + x) * 4 + 1] == buttenImg[matchedPixels * 4 + 1] &&
				screenPixels[(y*gScreenWidth + x) * 4 + 0] == buttenImg[matchedPixels * 4 + 0])
			{
				leastX = x;
				leastY = y;

				for (int i = y; i < y + height; i++)
				{
					if (i >= gScreenHeight)
						break;

					for (int j = x; j < x + width; j++)
					{
						if (j >= gScreenWidth)
							break;

						if (screenPixels[(i*gScreenWidth + j) * 4 + 2] == buttenImg[matchedPixels * 4 + 2] &&
							screenPixels[(i*gScreenWidth + j) * 4 + 1] == buttenImg[matchedPixels * 4 + 1] &&
							screenPixels[(i*gScreenWidth + j) * 4 + 0] == buttenImg[matchedPixels * 4 + 0])
						{
							matchedPixels++;

							if (matchedPixels > maxMatch)
								maxMatch = matchedPixels;

							if (matchedPixels >= (width * height * 3) / 4)
							{
								mostX = x + width;
								mostY = i;
								break;
							}
						}
						else
						{
							mostX = 0;
						}

					}

					if (mostX > 0)
						break;
				}

				if (mostX == 0)
					matchedPixels = 0;
			}
			if (mostX > 0)
				break;
		}
		if (mostX > 0)
			break;
	}


	return MatchBox(leastX, leastY, mostX, mostY);

}

MatchBox ClickSeats(unsigned char* screenPixels, MatchBox clickBox, int boxX, int boxY, bool random, bool checkInside)
{
	srand(GetTickCount());
	int startX = clickBox.leastX, startY = clickBox.leastY;

	std::vector<std::pair<int, int>> matches = std::vector<std::pair<int, int>>();
	bool rowmatched = false;

	for (int y = clickBox.leastY; y < clickBox.mostY; y++)
	{
		if (rowmatched)
		{
			y += boxY + 1;
			rowmatched = false;
		}

		for (int x = clickBox.leastX; x < clickBox.mostX; x++)
		{
			bool matched = true;

			// 이 픽셀이 회색이 아니면
			if (abs(screenPixels[(y*gScreenWidth + x) * 4 + 2] - screenPixels[(y*gScreenWidth + x) * 4 + 1]) > 3 ||
				abs(screenPixels[(y*gScreenWidth + x) * 4 + 2] - screenPixels[(y*gScreenWidth + x) * 4 + 0]) > 3 ||
				abs(screenPixels[(y*gScreenWidth + x) * 4 + 1] - screenPixels[(y*gScreenWidth + x) * 4 + 0]) > 3)
			{
				if (checkInside)
				{
					// boxX, boxY 크기 상자 안의 픽셀이 모두 같은 색인지 확인
					for (int i = 1; i <= boxY; i++)
					{
						for (int j = 1; j <= boxX; j++)
						{
							if (screenPixels[(y*gScreenWidth + x) * 4 + 2] != screenPixels[((y + i)*gScreenWidth + (x + j)) * 4 + 2] ||
								screenPixels[(y*gScreenWidth + x) * 4 + 1] != screenPixels[((y + i)*gScreenWidth + (x + j)) * 4 + 1] ||
								screenPixels[(y*gScreenWidth + x) * 4 + 0] != screenPixels[((y + i)*gScreenWidth + (x + j)) * 4 + 0])
							{
								matched = false;
								break;
							}
						}

						if (!matched)
							break;
					}
				}
				else
				{
					// 안쪽 픽셀 색깔은 노상관이고 테두리만 같은 색인지 확인함
					if (screenPixels[(y*gScreenWidth + x) * 4 + 2] != screenPixels[((y + boxY)*gScreenWidth + (x + boxX)) * 4 + 2] ||
						screenPixels[(y*gScreenWidth + x) * 4 + 1] != screenPixels[((y + boxY)*gScreenWidth + (x + boxX)) * 4 + 1] ||
						screenPixels[(y*gScreenWidth + x) * 4 + 0] != screenPixels[((y + boxY)*gScreenWidth + (x + boxX)) * 4 + 0])
						matched = false;
				}

				if (matched)
				{
					if (!random)
					{
						return MatchBox(x, y, clickBox.mostX, clickBox.mostY);
					}

					matches.push_back(std::pair<int, int>(x, y));
					x += boxX + 1;
					matched = false;
					rowmatched = true;
				}
			}
		}
	}

	if (matches.size() > 0)
	{
		int idx = rand() % matches.size();
		return MatchBox(matches[idx].first, matches[idx].second, clickBox.mostX, clickBox.mostY);
	}

	return MatchBox();
}

bool IsAllEmpty(unsigned char* screenPixels, MatchBox clickBox)
{
	int emptySeatCount = 0;
	bool skip = false;

	for (int y = clickBox.leastY; y < clickBox.mostY; y++)
	{
		if (skip)
		{
			y += 6;
			skip = false;
		}

		for (int x = clickBox.leastX; x < clickBox.mostX; x++)
		{
			if (screenPixels[(y*gScreenWidth + x) * 4 + 2] == screenPixels[((y + 6)*gScreenWidth + (x + 5)) * 4 + 2] &&
				screenPixels[(y*gScreenWidth + x) * 4 + 1] == screenPixels[((y + 6)*gScreenWidth + (x + 5)) * 4 + 1] &&
				screenPixels[(y*gScreenWidth + x) * 4 + 0] == screenPixels[((y + 6)*gScreenWidth + (x + 5)) * 4 + 0] &&
				(screenPixels[(y*gScreenWidth + x) * 4 + 2] <= 250 &&
				screenPixels[(y*gScreenWidth + x) * 4 + 2] <= 250 &&
				screenPixels[(y*gScreenWidth + x) * 4 + 1] <= 250))
			{
				x += 5;
				skip = true;
				emptySeatCount++;
				if (emptySeatCount > 30)
				{
					return true;
				}
			}

		}
	}

	return false;
}

bool YesDate(unsigned char* screenPixels, MatchBox clickBox)
{


	for (int y = clickBox.leastY; y < clickBox.mostY; y++)
	{

		for (int x = clickBox.leastX; x < clickBox.mostX; x++)
		{
			if (screenPixels[(y*gScreenWidth + x) * 4 + 2] == screenPixels[((y + 6)*gScreenWidth + (x + 5)) * 4 + 2] &&
				screenPixels[(y*gScreenWidth + x) * 4 + 1] == screenPixels[((y + 6)*gScreenWidth + (x + 5)) * 4 + 1] &&
				screenPixels[(y*gScreenWidth + x) * 4 + 0] == screenPixels[((y + 6)*gScreenWidth + (x + 5)) * 4 + 0] &&
				(screenPixels[(y*gScreenWidth + x) * 4 + 2] == 235 &&
				screenPixels[(y*gScreenWidth + x) * 4 + 2] == 73 &&
				screenPixels[(y*gScreenWidth + x) * 4 + 1] == 86))
			{
				return true;
			}

		}
	}

	return false;
}