#if defined __linux__
#include "/home/codeleaded/System/Static/Library/WindowEngine1.0.h"
#include "/home/codeleaded/System/Static/Library/Lib3D_Mathlib.h"
#include "/home/codeleaded/System/Static/Library/Lib3D_Cube.h"
#elif defined _WINE
#include "/home/codeleaded/System/Static/Library/WindowEngine1.0.h"
#include "/home/codeleaded/System/Static/Library/Lib3D_Math.h"
#include "/home/codeleaded/System/Static/Library/Lib3D_Cube.h"
#elif defined _WIN32
#include "F:/home/codeleaded/System/Static/Library/WindowEngine1.0.h"
#include "F:/home/codeleaded/System/Static/Library/Lib3D_Math.h"
#include "/home/codeleaded/System/Static/Library/Lib3D_Cube.h"
#elif defined(__APPLE__)
#error "Apple not supported!"
#else
#error "Platform not supported!"
#endif


Vector tris;
Vec3D cam;
float ax;
float ay;

void Setup(AlxWindow* w){
	cam = Vec3D_New(0.0f,0.0f,0.0f);
	ax = 0.0f;
	ay = 0.0f;

	tris = Vector_New(sizeof(Line));
	Lib3D_Cube(&tris,Vec3D_New(-3.0f,1.0f,0.0f),Vec3D_New(1.0f,1.0f,0.0f),WHITE,WHITE);
	Lib3D_Cube(&tris,Vec3D_New(-1.0f,1.0f,0.0f),Vec3D_New(1.0f,1.0f,0.0f),WHITE,WHITE);
	Lib3D_Cube(&tris,Vec3D_New( 1.0f,1.0f,0.0f),Vec3D_New(1.0f,1.0f,0.0f),WHITE,WHITE);
	Lib3D_Cube(&tris,Vec3D_New( 3.0f,1.0f,0.0f),Vec3D_New(1.0f,1.0f,0.0f),WHITE,WHITE);
}

void Update(AlxWindow* w){
	const M4x4D rot = Matrix_MultiplyMatrix(Matrix_MakeRotationX(ax),Matrix_MakeRotationY(ay));
	const Vec3D front = Matrix_MultiplyVector(rot,Vec3D_New(0.0f,0.0f,1.0f * w->ElapsedTime));

	if(Stroke(ALX_KEY_W).DOWN) cam = Vec3D_Add(cam,front);
	if(Stroke(ALX_KEY_S).DOWN) cam = Vec3D_Sub(cam,front);

	if(Stroke(ALX_KEY_UP).DOWN) 	ax += F32_PI * w->ElapsedTime;
	if(Stroke(ALX_KEY_DOWN).DOWN) 	ax -= F32_PI * w->ElapsedTime;
	if(Stroke(ALX_KEY_LEFT).DOWN) 	ay += F32_PI * w->ElapsedTime;
	if(Stroke(ALX_KEY_RIGHT).DOWN) 	ay -= F32_PI * w->ElapsedTime;

	Clear(BLACK);

	const M4x4D trans = Matrix_MakeTranslation(cam.x,cam.y,cam.z);
	const M4x4D tf = Matrix_MultiplyMatrix(rot,trans);

	for (int i = 0;i<tris.size;i++){
		Tri3D* t = (Tri3D*)Vector_Get(&tris,i);
		
		const Vec3D p0 = Matrix_MultiplyVector(tf,t->p[0]);
		const Vec3D p1 = Matrix_MultiplyVector(tf,t->p[1]);
		const Vec3D p2 = Matrix_MultiplyVector(tf,t->p[2]);

		const Vec3D pp0 = Vec3D_Div(p0,p0.z);
		const Vec3D pp1 = Vec3D_Div(p1,p1.z);
		const Vec3D pp2 = Vec3D_Div(p2,p2.z);
		
		if(pp0.y < 0.0f || pp1.y < 0.0f || pp2.y < 0.0f) continue;
		
		
		const Vec2 op0 = { (pp0.x + 1.0f) * GetWidth() / 2,(pp0.y + 1.0f) * GetHeight() / 2 };
		const Vec2 op1 = { (pp1.x + 1.0f) * GetWidth() / 2,(pp1.y + 1.0f) * GetHeight() / 2 };
		const Vec2 op2 = { (pp2.x + 1.0f) * GetWidth() / 2,(pp2.y + 1.0f) * GetHeight() / 2 };

		//Triangle_RenderX(
		//	WINDOW_STD_ARGS,
		//	(Vec2){ sx,m - sy },
		//	(Vec2){ sx,m + sy },
		//	(Vec2){ ex,m + ey },
		//	WHITE
		//);
		//Triangle_RenderX(
		//	WINDOW_STD_ARGS,
		//	(Vec2){ sx,m - sy },
		//	(Vec2){ ex,m + ey },
		//	(Vec2){ ex,m - ey },
		//	WHITE
		//);

		Triangle_RenderXWire(
			WINDOW_STD_ARGS,
			op0,op1,op2,
			WHITE,1.0f
		);
		Triangle_RenderXWire(
			WINDOW_STD_ARGS,
			op0,op1,op2,
			WHITE,1.0f
		);
	}
}

void Delete(AlxWindow* w){
	Vector_Free(&tris);
}

int main(){
    if(Create("2D Engine",2500,1200,1,1,Setup,Update,Delete))
        Start();
    return 0;
}