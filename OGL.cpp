//---------------------------------------------------------------------------
//OpenGLによる描画
//000929doi
//------------------------------------------------------
//使い方の例
//ogl1->set_rc(Canvas->Handle);
//glMatrixMode(GL_MODELVIEW);
//ogl1->set_viewpoint(15,theta,phi);
//ogl1->set_light();
//ogl1->Frame(-1,1,-1,1,-0.5,0.5);
//ogl1->Blue();
//ogl1->Box(0,1,-1,1,-0.5,0.5);
//ogl1->draw(Canvas->Handle);
//------------------------------------------------------
//#include <vcl.h>
#include <windows.h>
extern "C"
{
#include <GL/gl.h>
#include <GL/glu.h>
//#include <GL/glut.h>
}
#include <math.h>
#include "OGL.h"
#include "gl_tools.h"

//#define M_PI 3.141592 //gccなら不要

//---------------------------------------------------------------------------
OGL::OGL()
{
}
//---------------------------------------------------------------------------
OGL::~OGL()
{
#ifdef WIN32
  wglMakeCurrent(NULL,NULL);
  wglDeleteContext(rc1);
#endif
}
//---------------------------------------------------------------------------
void OGL::set_rc(void *dc_in)
{
#ifdef WIN32
  HDC dc1=(HDC)dc_in;
PIXELFORMATDESCRIPTOR pfd=
    {
    sizeof(PIXELFORMATDESCRIPTOR),
    1,
    PFD_DRAW_TO_WINDOW |
        PFD_SUPPORT_OPENGL|
            PFD_DOUBLEBUFFER,
    PFD_TYPE_RGBA,
    24,
    0,0,0,0,0,0,
    0,0,0,0,0,0,0,

    32,
    0,0,
    PFD_MAIN_PLANE,
    0,
    0,0,0
    };

//int pixelFormat;
//pixelFormat=ChoosePixelFormat(dc1,&pfd);//Cygwinでは使わない

//if(pixelFormat==0);ShowMessage("get pfd fail");
//if(SetPixelFormat(dc1,pixelFormat,&pfd)==false);//ShowMessage("set fail");//Cygwinではダメ？
rc1=wglCreateContext(dc1);
//if(rc1==0);ShowMessage("rc error");
if(wglMakeCurrent(dc1,rc1)==0)
    {
    ;
    //ShowMessage("bind error");
    //return;
    }
#endif
}
//---------------------------------------------------------------------------
void OGL::draw(void *dc_in)
{
glFlush();
//glFinish();//これを使うとNTが落ちる
//  if(SwapBuffers((HDC)dc_in)==false)//Cygwinではダメ？
  {
   ;
   //ShowMessage("swap error");
  }

/*
  if(wglMakeCurrent((HDC)dc_in,NULL)==0)
  {
  ;
  //ShowMessage("bind error 2");
  }

wglDeleteContext(rc1);
//↑メモリの解放．これをやらないとNTが固まる
*/
}
//---------------------------------------------------------------------------
void OGL::Box(double x0,double x1,double y0,double y1,double z0,double z1)
{
//箱を描く関数
	GL_Box(x0,x1,y0,y1,z0,z1);
}
//---------------------------------------------------------------------------
void OGL::Arrow(double size, double x0, double y0, double z0, double x1, double y1, double z1)
{
	GL_Arrow(size,x0,y0,z0,x1,y1,z1);
}

//---------------------------------------------------------------------------
void OGL::set_viewpoint(double l,double theta_in,double phi_in)
{
	set_viewpoint(l,theta_in,phi_in,0,0,0, 1.0);
}
//---------------------------------------------------------------------------
void OGL::set_viewpoint(double l,double theta_in,double phi_in,
              double cx_in, double cy_in, double cz_in, double wh_ratio_in)
{
	GL_set_viewpoint(l, theta_in, phi_in,cx_in,cy_in,cz_in,wh_ratio_in);

}
//---------------------------------------------------------------------------
void OGL::set_background(char IsWhite)
{
	GL_set_background(IsWhite);

}
//---------------------------------------------------------------------------
void OGL::set_light()
{
	GL_set_light();
}
//---------------------------------------------------------------------------
void OGL::Frame(double x0,double x1,double y0,double y1,double z0,double z1)
{
	GL_Frame(x0,x1,y0,y1,z0,z1);
}
//---------------------------------------------------------------------------
char OGL::outer_product(double vx1_in,double vy1_in,double vz1_in,
                       double vx2_in,double vy2_in,double vz2_in,
                       double *vx_out,double *vy_out,double *vz_out
                       )
{
return	GL_outer_product(vx1_in,vy1_in,vz1_in,vx2_in,vy2_in,vz2_in,
		vx_out,vy_out,vz_out);
}
//---------------------------------------------------------------------------
void OGL::Facet(double x0,double y0,double z0,
                       double x1,double y1,double z1,
                       double x2,double y2,double z2)
{
	Facet(x0,y0,z0,x1,y1,z1,x2,y2,z2);
}
//---------------------------------------------------------------------------
void OGL::set_material(double r_in,double g_in,double b_in,double alpha_in)
{
	GL_set_material(r_in,g_in,b_in,alpha_in);
}
//---------------------------------------------------------------------------
void OGL::Red(void)
{
	GL_Red();
}
//---------------------------------------------------------------------------
void OGL::Green(void)
{
	GL_Green();
}
//---------------------------------------------------------------------------
void OGL::Blue(void)
{
	GL_Blue();
}
//---------------------------------------------------------------------------
void OGL::coordinate(int size)
{
	GL_Coordinate(size);
}
//---------------------------------------------------------------------------

