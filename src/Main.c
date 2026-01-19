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
float ar;

void Setup(AlxWindow* w){
	cam = Vec3D_New(0.0f,0.0f,0.0f);
	ax = 0.0f;
	ay = 0.0f;
	ar = 16.0f / 9.0f;

	tris = Vector_New(sizeof(Tri3D));
	Lib3D_Cube(&tris,Vec3D_New(-4.0f,0.0f,3.0f),Vec3D_New(1.0f,1.0f,1.0f),WHITE,WHITE);
	Lib3D_Cube(&tris,Vec3D_New(-2.0f,0.0f,3.0f),Vec3D_New(1.0f,1.0f,1.0f),WHITE,WHITE);
	Lib3D_Cube(&tris,Vec3D_New( 0.0f,0.0f,3.0f),Vec3D_New(1.0f,1.0f,1.0f),WHITE,WHITE);
	Lib3D_Cube(&tris,Vec3D_New( 2.0f,0.0f,3.0f),Vec3D_New(1.0f,1.0f,1.0f),WHITE,WHITE);
	Lib3D_Cube(&tris,Vec3D_New( 4.0f,0.0f,3.0f),Vec3D_New(1.0f,1.0f,1.0f),WHITE,WHITE);
}

void Update(AlxWindow* w){
	const M4x4D rotY = Matrix_MakeRotationY(ay);

	const Vec3D left = Matrix_MultiplyVector(rotY,Vec3D_New(1.0f * w->ElapsedTime,0.0f,0.0f));
	const Vec3D front = Matrix_MultiplyVector(rotY,Vec3D_New(0.0f,0.0f,1.0f * w->ElapsedTime));

	if(Stroke(ALX_KEY_W).DOWN) cam = Vec3D_Add(cam,front);
	if(Stroke(ALX_KEY_S).DOWN) cam = Vec3D_Sub(cam,front);
	if(Stroke(ALX_KEY_A).DOWN) cam = Vec3D_Sub(cam,left);
	if(Stroke(ALX_KEY_D).DOWN) cam = Vec3D_Add(cam,left);
	if(Stroke(ALX_KEY_R).DOWN) cam.y -= 1.0f * w->ElapsedTime;
	if(Stroke(ALX_KEY_F).DOWN) cam.y += 1.0f * w->ElapsedTime;

	if(Stroke(ALX_KEY_UP).DOWN) 	ax += F32_PI * w->ElapsedTime;
	if(Stroke(ALX_KEY_DOWN).DOWN) 	ax -= F32_PI * w->ElapsedTime;
	if(Stroke(ALX_KEY_LEFT).DOWN) 	ay += F32_PI * w->ElapsedTime;
	if(Stroke(ALX_KEY_RIGHT).DOWN) 	ay -= F32_PI * w->ElapsedTime;

	Clear(BLACK);

	const M4x4D rot = Matrix_MultiplyMatrix(Matrix_MakeRotationY(-ay),Matrix_MakeRotationX(-ax));
	const M4x4D trans = Matrix_MakeTranslation(-cam.x,-cam.y,-cam.z);
	const M4x4D tf = Matrix_MultiplyMatrix(trans,rot);

	for (int i = 0;i<tris.size;i++){
		Tri3D* t = (Tri3D*)Vector_Get(&tris,i);
		
		const Vec3D p0 = Matrix_MultiplyVector(tf,t->p[0]);
		const Vec3D p1 = Matrix_MultiplyVector(tf,t->p[1]);
		const Vec3D p2 = Matrix_MultiplyVector(tf,t->p[2]);

		if(p0.z < 0.0f || p1.z < 0.0f || p2.z < 0.0f)
			continue;

		const Vec3D pp0 = Vec3D_Div(p0,p0.z);
		const Vec3D pp1 = Vec3D_Div(p1,p1.z);
		const Vec3D pp2 = Vec3D_Div(p2,p2.z);
		
		const float w = (float)GetWidth() * 0.5f;
		const float h = (float)GetHeight() * 0.5f;
		const Vec2 op0 = { pp0.x * w + w,pp0.y * h * ar + h };
		const Vec2 op1 = { pp1.x * w + w,pp1.y * h * ar + h };
		const Vec2 op2 = { pp2.x * w + w,pp2.y * h * ar + h };

		// Triangle_RenderX(
		// 	WINDOW_STD_ARGS,
		// 	op0,op1,op2,
		// 	GRAY
		// );

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
    if(Create("3D Engine",2500,1200,1,1,Setup,Update,Delete))
        Start();
    return 0;
}