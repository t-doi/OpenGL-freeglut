//---------------------------------------------------------------------------
//OpenGLによる描画
//160805 doi
#ifndef GL_TOOLS		//多重を防ぐ
#define GL_TOOLS

#define WIN32 1
#ifdef WIN32
#include <windows.h>
#endif
//---------------------------------------------------------------------------
//外積計算
char GL_outer_product(double vx1_in,double vy1_in,double vz1_in,
                       double vx2_in,double vy2_in,double vz2_in,
                       double *vx_out,double *vy_out,double *vz_out
                       );

//視点操作
void GL_set_viewpoint(double l,double theta_in,double phi_in);//視点決定
void GL_set_viewpoint(double l,double theta_in,double phi_in,
              double cx_in, double cy_in, double cz_in, double wh_ratio_in);//視点決定

//マテリアル，色，照明
void GL_set_material(double r_in,double g_in,double b_in,double alpha_in);//マテリアル
void GL_Red(void);//色指定：赤
void GL_Green(void);//色指定：緑
void GL_Blue(void);//色指定：青
void GL_set_light(void);//照明
void GL_set_background(char IsWhite);//背景色

//形状
void GL_Facet(double x0,double y0,double z0,
                       double x1,double y1,double z1,
                       double x2,double y2,double z2);//ポリゴン
void GL_Frame(double x0,double x1,double y0,double y1,double z0,double z1);//ポリゴン
void GL_Box(double x0,double x1,double y0,double y1,double z0,double z1);//箱描画
void GL_Arrow(double size, double x0, double y0, double z0, double x1, double y1, double z1);//矢印．頭のサイズ，始点，終点
void GL_Coordinate(int size);//x,y,zの順にRGBの色で座標系を表示
void GL_Cylinder(double radius, double height, int sides);	// 角柱の関数( 外接円の直径, 高さ, 角の数 )
void GL_FloorGrid(double x0, double x1, double y0, double y1, int meshx, int meshy);
//-------------
//GLUTの機能を利用
void GLUT_3D_message(void *font, double x, double y, double z, char *str);//3Dのテキストメッセージ
void GLUT_Coordinate(int size);//x,y,zの順にRGBの色で座標系を表示

//---------------------------------------------------------------------------
#endif
