#include "stdafx.h"

struct ImageFile
{
	bool IsValid() { return width > 0; }

	int width = -1;
	int height = -1;
	std::string name = "";
	unsigned char* pixels = nullptr;
};

struct MatchBox
{
	MatchBox()
	{}

	MatchBox(int lx, int ly, int mx, int my) : leastX(lx), leastY(ly), mostX(mx), mostY(my)
	{}
	
	bool IsValid() { return mostX > 0; }

	int leastX = -1;
	int leastY = -1;
	int mostX = -1;
	int mostY = -1;
};

void LoadDefaults();
void Finalize();

bool GetPixels(HBITMAP hBmp, unsigned char* &pixels, int &width, int &height, bool init=false);
bool GetScreenPixels(unsigned char* pixels);
void Click(int x, int y);
void Refresh();
bool FuckFuckTicketing(unsigned char* pPixels);

MatchBox FindMatchAndClick(unsigned char* screenPixels, ImageFile match);
MatchBox ClickSeats(unsigned char* screenPixels, MatchBox borders, int boxX, int boxY, bool random, bool checkInside = true);
bool AllSeats(unsigned char* screenPixels, MatchBox mb);
bool IsAllEmpty(unsigned char* screenPixels, MatchBox clickBox);
bool YesDate(unsigned char* screenPixels, MatchBox clickBox);

int gScreenWidth;
int gScreenHeight;
HWND gDesktopWnd;
HDC gDesktopDC;
HDC gCaptureDC;
bool gClickedReserv = false;
int gSeatEmptyTick = 0;
bool gSeatEnter = false;

std::map<std::string, ImageFile> gImageFiles;