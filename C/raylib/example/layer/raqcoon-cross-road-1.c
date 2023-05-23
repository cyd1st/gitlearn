#include <raylib.h>

int main() {
	InitWindow(1230,650,"test");
	SetTraceLogLevel(LOG_WARNING);
	SetTargetFPS(24);
	//读入图片文件
	Image imgBackground=LoadImage("background.png");
	Image imgRacoon[11];
	for (int i=0, j = 0;i<22;i+=2) {
		const char* filename=TextFormat("walk/walk%04d.png",i+1);
		imgRacoon[j++]=LoadImage(filename);
	}
	
	int stepX=5;
	int racoonX=0;
	int racoonY=60;
	int racoonFrame=0;
	while(!WindowShouldClose()) {
		racoonFrame++;
		if (racoonFrame>=11)
			racoonFrame=0;
		Texture tBackground = LoadTextureFromImage(imgBackground);
		Texture tRacoon = LoadTextureFromImage(imgRacoon[racoonFrame]);
		racoonX+=stepX;
		BeginDrawing();
		//叠加显示图层。注意显示的顺序
		DrawTexture(tBackground,0,0,WHITE);
		DrawTexture(tRacoon,racoonX,racoonY,WHITE);
		EndDrawing();
		UnloadTexture(tRacoon);
		UnloadTexture(tBackground);
	}
	for (int i=0;i<11;i++) {
		UnloadImage(imgRacoon[i]);
	}
	UnloadImage(imgBackground);
	CloseWindow();
}
