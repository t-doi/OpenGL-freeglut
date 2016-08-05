//---------------------------------------------------------------------------
//OpenGLによる描画のための基本ツール群
//160805doi
//------------------------------------------------------
//使い方の例
//GL_set_viewpoint(15,theta,phi);
//GL_set_light();
//GL_Frame(-1,1,-1,1,-0.5,0.5);
//GL_Blue();
//GL_Box(0,1,-1,1,-0.5,0.5);
//------------------------------------------------------
#include <windows.h>
extern "C"
{
#include <GL/gl.h>
#include <GL/glu.h>
//#include <GL/glut.h>
}
#include <math.h>
#include "gl_tools.h"
#include "GL/freeglut.h"//テキスト表示に必要

//#define M_PI 3.141592 //gccなら不要

//---------------------------------------------------------------------------
void GL_Box(double x0,double x1,double y0,double y1,double z0,double z1)
{
//箱を描く関数
glBegin(GL_POLYGON);
    glNormal3f(0.0f,0.0f,1.0f);
    glVertex3d(x0,y1,z1);
    glVertex3d(x0,y0,z1);
    glVertex3d(x1,y0,z1);
    glVertex3d(x1,y1,z1);
glEnd();
glBegin(GL_POLYGON);
    glNormal3f(1.0f,0.0f,0.0f);
    glVertex3d(x1,y1,z1);
    glVertex3d(x1,y0,z1);
    glVertex3d(x1,y0,z0);
    glVertex3d(x1,y1,z0);
glEnd();
glBegin(GL_POLYGON);
    glNormal3f(0.0f,0.0f,-1.0f);
    glVertex3d(x1,y1,z0);
    glVertex3d(x1,y0,z0);
    glVertex3d(x0,y0,z0);
    glVertex3d(x0,y1,z0);
glEnd();
glBegin(GL_POLYGON);
    glNormal3f(-1.0f,0.0f,0.0f);
    glVertex3d(x0,y1,z0);
    glVertex3d(x0,y0,z0);
    glVertex3d(x0,y0,z1);
    glVertex3d(x0,y1,z1);
glEnd();
glBegin(GL_POLYGON);
    glNormal3f(0.0f,-1.0f,0.0f);
    glVertex3d(x0,y0,z1);
    glVertex3d(x0,y0,z0);
    glVertex3d(x1,y0,z0);
    glVertex3d(x1,y0,z1);
glEnd();
glBegin(GL_POLYGON);
    glNormal3f(0.0f,1.0f,0.0f);
    glVertex3d(x0,y1,z0);
    glVertex3d(x0,y1,z1);
    glVertex3d(x1,y1,z1);
    glVertex3d(x1,y1,z0);
glEnd();
}
//---------------------------------------------------------------------------
void GL_Arrow(double size, double x0, double y0, double z0, double x1, double y1, double z1)
{
	//矢印．頭のサイズ，始点，終点
	glLineWidth(4.0f);
	glBegin(GL_LINES);//矢印の軸
    	glVertex3d(x0,y0,z0);
    	glVertex3d(x1,y1,z1);
	glEnd();

	//矢印の頭
	double n[3];//方向ベクトル
	double v[3];//ベクトル
	double L;//ベクトルの長さ
	double w1[3];//傘が開く向きの候補1,2,3
	double w2[3];//傘が開く向きの候補1,2,3
	double w3[3];//傘が開く向きの候補1,2,3
	v[0]=x1-x0;
	v[1]=y1-y0;
	v[2]=z1-z0;
	L=sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);
	if(L<0.000000001)return;//長さゼロエラー
	n[0]=v[0]/L;
	n[1]=v[1]/L;
	n[2]=v[2]/L;
	GL_outer_product(n[0],n[1],n[2],1,0,0,&w1[0],&w1[1],&w1[2]);
	GL_outer_product(n[0],n[1],n[2],0,1,0,&w2[0],&w2[1],&w2[2]);
	GL_outer_product(n[0],n[1],n[2],0,0,1,&w3[0],&w3[1],&w3[2]);
	double th=0.001;//有効なベクトルの閾値
	double dx,dy,dz;

	glLineWidth(2.0f);


	dx=w1[0],dy=w1[1];dz=w1[2];
	if((fabs(dx)>th)||(fabs(dy)>th)||(fabs(dz)>th))
	{
	glBegin(GL_LINE_LOOP);//矢印の頭
    	glVertex3d(x1,y1,z1);
    	glVertex3d(x1-n[0]*size+dx*size*0.5,y1-n[1]*size+dy*size*0.5,z1-n[2]*size+dz*size*0.5);
    	glVertex3d(x1-n[0]*size-dx*size*0.5,y1-n[1]*size-dy*size*0.5,z1-n[2]*size-dz*size*0.5);
    	glVertex3d(x1,y1,z1);
	glEnd();
	}
	dx=w2[0],dy=w2[1];dz=w2[2];
	if((fabs(dx)>th)||(fabs(dy)>th)||(fabs(dz)>th))
	{
	glBegin(GL_LINE_LOOP);//矢印の頭
    	glVertex3d(x1,y1,z1);
    	glVertex3d(x1-n[0]*size+dx*size*0.5,y1-n[1]*size+dy*size*0.5,z1-n[2]*size+dz*size*0.5);
    	glVertex3d(x1-n[0]*size-dx*size*0.5,y1-n[1]*size-dy*size*0.5,z1-n[2]*size-dz*size*0.5);
    	glVertex3d(x1,y1,z1);
	glEnd();
	}
	dx=w3[0],dy=w3[1];dz=w3[2];
	if((fabs(dx)>th)||(fabs(dy)>th)||(fabs(dz)>th))
	{
	glBegin(GL_LINE_LOOP);//矢印の頭
    	glVertex3d(x1,y1,z1);
    	glVertex3d(x1-n[0]*size+dx*size*0.5,y1-n[1]*size+dy*size*0.5,z1-n[2]*size+dz*size*0.5);
    	glVertex3d(x1-n[0]*size-dx*size*0.5,y1-n[1]*size-dy*size*0.5,z1-n[2]*size-dz*size*0.5);
    	glVertex3d(x1,y1,z1);
	glEnd();
	}

}

//---------------------------------------------------------------------------
void GL_set_viewpoint(double l,double theta_in,double phi_in)
{
	GL_set_viewpoint(l,theta_in,phi_in,0,0,0, 1.0);
}
//---------------------------------------------------------------------------
void GL_set_viewpoint(double l,double theta_in,double phi_in,
              double cx_in, double cy_in, double cz_in, double wh_ratio_in)
{
//視点の設定
//set_view()の代わりに使う．
//距離Lだけ離れたところから3次元シーンを見る

glLoadIdentity();
double p_theta=30;
double p_near=l*0.1;
double p_far=l*10;
  gluPerspective(p_theta,wh_ratio_in,p_near,p_far);
  GL_set_background(1);

//  glFrustum(-1.0,1.0,-1.0,1.0,1.0,7.0);

double eye_x,eye_y,eye_z;
double center_x,center_y,center_z;
double up_x,up_y,up_z;
center_x=cx_in;
center_y=cy_in;
center_z=cz_in;
eye_x=l*cos(phi_in*M_PI/180)*cos(theta_in*M_PI/180)+center_x;
eye_y=l*cos(phi_in*M_PI/180)*sin(theta_in*M_PI/180)+center_y;
eye_z=l*sin(phi_in*M_PI/180)+center_z;
up_x=l*cos((phi_in+90)*M_PI/180)*cos(theta_in*M_PI/180);
up_y=l*cos((phi_in+90)*M_PI/180)*sin(theta_in*M_PI/180);
up_z=l*sin((phi_in+90)*M_PI/180);

gluLookAt(
eye_x,
eye_y,
eye_z,
center_x,
center_y,
center_z,
up_x,
up_y,
up_z
);


}
//---------------------------------------------------------------------------
void GL_set_background(char IsWhite)
{
if(IsWhite==1)
  glClearColor(1.0,1.0,1.0,1.0);//背景白
else
  glClearColor(0.0,0.0,0.0,0.0);//背景黒

  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);//ClearColorを決めてから

}
//---------------------------------------------------------------------------
void GL_set_light()
{
//glShadeModel(GL_SMOOTH);
glShadeModel(GL_FLAT);
glEnable(GL_DEPTH_TEST);


GLfloat ambientLight0[]={0.2f,0.2f,0.2f,1.0f};
GLfloat diffuseLight0[]={0.9f,0.9f,0.9f,1.0f};
GLfloat specularLight0[]={0.7f,0.7f,0.7f,1.0f};
GLfloat ambientLight1[]={0.1f,0.1f,0.1f,1.0f};
GLfloat diffuseLight1[]={0.25f,0.25f,0.25f,1.0f};
GLfloat specularLight1[]={0.5f,0.5f,0.5f,1.0f};

GLfloat scale=100.0f;
//GLfloat positionLight0[]={100.0f,-1000.0f,10.0f,0.0f};
//GLfloat directionLight0[]={-0.1f,1.0f,-0.01f};
GLfloat positionLight0[]={-1*scale,0.4*scale,-1*scale,1.0f};
GLfloat directionLight0[]={-scale,0.4*scale,-1*scale};
GLfloat positionLight1[]={-scale,-0.5*scale,-0.01*scale,0.0f};
GLfloat directionLight1[]={scale,0.5*scale,0.01*scale};

//ライト０
glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight0);
glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight0);
glLightfv(GL_LIGHT0,GL_SPECULAR,specularLight0);
glLightfv(GL_LIGHT0,GL_POSITION,positionLight0);
//glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,directionLight0);

//ライト１
glLightfv(GL_LIGHT1,GL_AMBIENT,ambientLight1);
glLightfv(GL_LIGHT1,GL_DIFFUSE,diffuseLight1);
glLightfv(GL_LIGHT1,GL_SPECULAR,specularLight1);
glLightfv(GL_LIGHT1,GL_POSITION,positionLight1);
glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION,directionLight1);


glEnable(GL_LIGHTING);
glEnable(GL_LIGHT0);
//glEnable(GL_LIGHT1);
}
//---------------------------------------------------------------------------
void GL_Frame(double x0,double x1,double y0,double y1,double z0,double z1)
{
//枠描画
//GLfloat materialWhite[]={1.0f,1.0f,1.0f,1.0f};
GLfloat materialGray[]={0.9f,0.9f,0.9f,0.5f};
glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,materialGray);
glLineWidth(4.0f);
glBegin(GL_LINE_LOOP);
    glVertex3d(x1,y1,z0);
    glVertex3d(x1,y0,z0);
    glVertex3d(x0,y0,z0);
    glVertex3d(x0,y1,z0);
glEnd();

glBegin(GL_LINES);
    glVertex3d(x1,y0,z1);
    glVertex3d(x1,y0,z0);
glEnd();
glBegin(GL_LINES);
    glVertex3d(x0,y0,z0);
    glVertex3d(x0,y0,z1);
glEnd();
glBegin(GL_LINES);
    glVertex3d(x1,y1,z0);
    glVertex3d(x1,y1,z1);
glEnd();
glBegin(GL_LINES);
    glVertex3d(x0,y1,z0);
    glVertex3d(x0,y1,z1);
glEnd();
}
//---------------------------------------------------------------------------
char GL_outer_product(double vx1_in,double vy1_in,double vz1_in,
                       double vx2_in,double vy2_in,double vz2_in,
                       double *vx_out,double *vy_out,double *vz_out
                       )
{
//外積
*vx_out=(vy1_in*vz2_in-vz1_in*vy2_in);
*vy_out=(vz1_in*vx2_in-vx1_in*vz2_in);
*vz_out=(vx1_in*vy2_in-vy1_in*vx2_in);
return 1;
}
//---------------------------------------------------------------------------
void GL_Facet(double x0,double y0,double z0,
                       double x1,double y1,double z1,
                       double x2,double y2,double z2)
{
//↑ポリゴンモデリング．法線も
//0,1,2と，時計周りに入力
GLdouble vx,vy,vz;
GLdouble vx1,vy1,vz1,vx2,vy2,vz2;
double size;

//外積計算
vx1=x0-x1;
vy1=y0-y1;
vz1=z0-z1;
vx2=x2-x1;
vy2=y2-y1;
vz2=z2-z1;

GL_outer_product(vx1,vy1,vz1,vx2,vy2,vz2,&vx,&vy,&vz);
//↑外積計算


//正規化
size=sqrt(vx*vx+vy*vy+vz*vz);
if(size==0)return;
vx=vx/size;
vy=vy/size;
vz=vz/size;

glBegin(GL_POLYGON);//(GL_LINE_LOOP);
    glNormal3f(vx,vy,vz);
    glVertex3d(x0,y0,z0);
    glVertex3d(x1,y1,z1);
    glVertex3d(x2,y2,z2);
glEnd();

}
//---------------------------------------------------------------------------
void GL_set_material(double r_in,double g_in,double b_in,double alpha_in)
{
GLfloat r,g,b,a;
r=r_in;
g=g_in;
b=b_in;
a=alpha_in;
GLfloat materialtemp[]={r,g,b,a};
glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,materialtemp);

GLfloat materialspecular[]={0.5f,0.5f,0.5f,0.5f};
glMaterialfv(GL_FRONT,GL_SPECULAR,materialspecular);
}
//---------------------------------------------------------------------------
void GL_Red(void)
{
GL_set_material(1.0,0.0,0.0,0.5);
}
//---------------------------------------------------------------------------
void GL_Green(void)
{
GL_set_material(0.0,1.0,0.0,0.5);
}
//---------------------------------------------------------------------------
void GL_Blue(void)
{
GL_set_material(0.0,0.0,1.0,0.5);
}
//---------------------------------------------------------------------------
void GL_Coordinate(int size)
{
//x,y,zの順にRGBの色で座標系を表示
//sizeで長さを指定する
GL_Red();
glBegin(GL_LINES);
 glVertex3d(0,0,0);
 glVertex3d(size,0,0);
glEnd();
GL_Green();
glBegin(GL_LINES);
 glVertex3d(0,0,0);
 glVertex3d(0,size,0);
glEnd();
GL_Blue();
glBegin(GL_LINES);
 glVertex3d(0,0,0);
 glVertex3d(0,0,size);
glEnd();

}
//---------------------------------------------------------
void GL_Cylinder(double radius, double height, int sides)	// 角柱の関数( 外接円の直径, 高さ, 角の数 )
{
	double step = 2 * M_PI / (double)sides;
	int i;

	glNormal3d(0.0, 1.0, 0.0);
	glBegin(GL_TRIANGLE_FAN);
	for (i = 0; i < sides; i++)
	{
		double t = step * (double)i;
		glVertex3d(radius * sin(t), height, radius * cos(t));
	}
	glEnd();

	glNormal3d(0.0, -1.0, 0.0);
	glBegin(GL_TRIANGLE_FAN);
	for (i = sides; --i >= 0;)
	{
		double t = step * (double)i;
		glVertex3d(radius * sin(t), 0.0, radius * cos(t));
	}
	glEnd();

	glBegin(GL_QUAD_STRIP);
	for (i = 0; i <= sides; i++)
	{
		double t = step * (double)i;
		double x = sin(t);
		double z = cos(t);

		glNormal3d(x, 0.0, z);
		glVertex3f(radius * x, height, radius * z);
		glVertex3f(radius * x, 0.0, radius * z);
	}
	glEnd();
}
//---------------------------------------------------------------------------
void GL_FloorGrid(double x0, double x1, double y0, double y1, int meshx, int meshy)
{
	//線を引く領域
	double x_min=x0;
	double x_max=x1;
	double y_min=y0;
	double y_max=y1;

    double dx=(x_max-x_min)/((double)meshx);//x間隔
	double i_count=(x_max-x_min)/dx;//x方向の本数
	double dy=(y_max-y_min)/((double)meshy);//y間隔
	double j_count=(y_max-y_min)/dy;//y方向の本数


	//double x,y,z;
	double x,y;

	glLineWidth(1);//線の太さ

		glColor3d(0.0, 0.0, 0.0);
		GL_set_material(0,0,0,0);	//黒に設定

	for(int i = 0;i<i_count+1;i++){
		x=x_min+dx*i;
		glBegin(GL_LINES);					//頂点の指定＋それに対するモード選択（２つの頂点を線で結ぶ）
		glVertex3d(x, y_min, 0);
		glVertex3d(x, y_max, 0);
		glEnd();
	}

	for(int j = 0;j<j_count+1;j++){
		y=y_min+dy*j;
		glBegin(GL_LINES);					//頂点の指定＋それに対するモード選択（２つの頂点を線で結ぶ）
		glVertex3d(x_min, y, 0);
		glVertex3d(x_max, y, 0);
		glEnd();
	}
}

//---------------------------------------------------------
// gl_3D_message関数（指定座標に３Dのメッセージ表示）
//---------------------------------------------------------
void GLUT_3D_message(void * font, double x, double y, double z, char *str)
{
	//freeglutの機能を使ったテキスト表示
    //移動するテキスト
    //void *font1=GLUT_BITMAP_9_BY_15;
	glColor3d(1.0, 0.0, 0.0);
    glRasterPos3d(x,y,z);//三次元座標でメッセージ表示位置指定
    glutBitmapString(font, (unsigned char *)(str));
}
//---------------------------------------------------------------------------
void GLUT_Coordinate(int size)
{
    GL_set_material(1.0,0,0,0);
    GL_Arrow(size*0.1, 0,0,0, size,0,0);
    GLUT_3D_message(GLUT_BITMAP_9_BY_15,size,0,0,"X");

    GL_set_material(0,1.0,0,0);
    GL_Arrow(size*0.1, 0,0,0, 0,size,0);
    GLUT_3D_message(GLUT_BITMAP_9_BY_15,0,size,0,"Y");

    GL_set_material(0,0,1.0,0);
    GL_Arrow(size*0.1, 0,0,0, 0,0,size);
    GLUT_3D_message(GLUT_BITMAP_9_BY_15,0,0,size,"Z");
}
//---------------------------------------------------------

