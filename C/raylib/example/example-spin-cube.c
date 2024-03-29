#include <raylib.h>
#include <math.h>

int main(void)
{
	// 初始化
	const int screenWidth = 640;
	const int screenHeight = 480;
	
	//启用反锯齿
	SetConfigFlags(FLAG_MSAA_4X_HINT);
	
	//初始化窗口
	InitWindow(screenWidth, screenHeight, "Sample");
	
	// 初始化摄像机
	Camera3D camera = { 0 };
	camera.position = (Vector3){ 40.0f, 20.0f, 0.0f }; //相机所在位置{x,y,z}
	camera.target = (Vector3){ 0.0f, 0.0f, 0.0f }; //相机朝向位置{x,y,z}
	camera.up = (Vector3){ 0.0f, 1.0f, 0.0f }; //相机正上方朝向矢量
	camera.fovy = 70.0f; //相机视野宽度
	camera.projection = CAMERA_PERSPECTIVE; //采用透视投影
	
	//设置动画帧率（刷新率，fps）为30帧/秒
	SetTargetFPS(60);
	//--------------------------------------------------------------------------------------
	int angle=0; //多边形旋转角度
	
	// 主游戏循环
	while (!WindowShouldClose())    //关闭窗口或者按ESC键时返回true
	{
		
		double time = GetTime(); 
		// 每次循环更新一帧
		// 摄像机围绕y轴转动
		double cameraTime = time*0.5; // 时间轴(相位wt)
		camera.position.x = (float)cos(cameraTime*1.5f + 100)*20.0f;
		camera.position.z = (float)sin(cameraTime)*40.0f;
		
		BeginDrawing();
		
		ClearBackground(WHITE); //清除之前帧绘制的内容
		//以摄像机视角绘制3d内容
		BeginMode3D(camera);
		DrawCube((Vector3){0,0,0},10,10,10,VIOLET);
		DrawCubeWires((Vector3){0,0,0},10,10,10,BLACK);
		EndMode3D();
		//完成帧的绘制，并根据设置的帧率延时（自动暂停一段时间，以满足帧率要求）。
		EndDrawing();
	}
	
	//关闭窗口
	CloseWindow();
	
	return 0;
}
