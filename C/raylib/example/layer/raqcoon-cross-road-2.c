#include <raylib.h>

#define RACOON_FRAMES 12

int main() {
	InitWindow(1230, 650, "test");
	SetTraceLogLevel(LOG_WARNING);
	SetTargetFPS(24);
	//读入图片文件
	Image imgBackground = LoadImage("background.png");
	Image imgRacoon[RACOON_FRAMES];
	//读入拼接图片
	Image imgRacoonTotal = LoadImage("racoon-total.png");
	//裁切成小图片
	for (int i = 0; i < RACOON_FRAMES; i++) {
		imgRacoon[i] = GenImageColor(200, 200, BLANK);
		int x = (i % 4) * 200;
		int y = (i / 4) * 200;
		ImageDraw(&imgRacoon[i], imgRacoonTotal,
		(Rectangle) {
			x, y, 200, 200
		},
		(Rectangle) {
			0, 0, 200, 200
		},
		WHITE);
	}
	UnloadImage(imgRacoonTotal);

	int stepX = 5;
	int racoonX = 0;
	int racoonY = 300;
	int racoonFrame = 0;
	while (!WindowShouldClose()) {
		racoonFrame++;
		if (racoonFrame >= 11)
			racoonFrame = 0;
		Texture tBackground = LoadTextureFromImage(imgBackground);
		Texture tRacoon = LoadTextureFromImage(imgRacoon[racoonFrame]);
		racoonX += stepX;
		BeginDrawing();
		//叠加显示图层。注意显示的顺序
		DrawTexture(tBackground, 0, 0, WHITE);
		if (racoonX > 1400) {
			racoonX = -60;
			racoonY = 280;
		}
			
		DrawTexture(tRacoon, racoonX, racoonY++, WHITE);
		EndDrawing();
		UnloadTexture(tRacoon);
		UnloadTexture(tBackground);
	}
	for (int i = 0; i < RACOON_FRAMES; i++) {
		UnloadImage(imgRacoon[i]);
	}
	UnloadImage(imgBackground);
	CloseWindow();
}
