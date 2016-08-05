#include "vcsetting.h"


extern "C"
{
#include <windows.h> //VC++用
#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
//#include <GL/glut.h>
#include "GL/freeglut.h"
//#include "GL/freeglut_std.h"
}
//#include "GL/glui.h"
//#include <GL/glui.h>


#include "mouse_view.h"
#include "OGL2D.h"
#include "gl_tools.h"


//OGL ogl1;//OpenGL応用ライブラリ
MouseView mv1;//マウスモーション管理クラス
int W_Height=500;//ウインドウ高さ.描画で使う。
int W_Width=500;//ウインドウ幅.描画で使う。

//---------------------
void ogl_2d_tri_test(double x0, double y0)//三角形カーソル 2D描画
{
    double r=0.1;
    ogl_2d_triangle(x0,y0,x0-0.5*r,y0-r,x0+0.5*r,y0-r);
}
//---------------------
void disp_overlay( void ) //2D-overlay描画．マウスズームとは無関係にサイズ固定．
{

//マウスズームに無関係の固定枠。二次元指定
    glPushMatrix();
    glDisable(GL_LIGHTING);
    glLoadIdentity();
    glColor3f(0.5f,0.5f,0.5f);
    glRasterPos2d(0,0);
	ogl_2d_tri_test(0,-0.1);//三角形のカーソル

    //ogl_2d_tri_test_p((double)cursor_pos_global[0]/10,(double)cursor_pos_global[1]/10);//三角形カーソル
    //ogl_2d_circle_test_p((double)cursor_pos_global[0]/10,(double)cursor_pos_global[1]/10);//円形カーソル


    //位置固定テキスト
    void *font1=GLUT_BITMAP_9_BY_15;
    glRasterPos2d(-0.9,0.9);//画面座標でメッセージ表示位置指定
    //glutBitmapString(font1, reinterpret_cast<const unsigned char*>("Doi Robotics Lab."));
    glutBitmapString(font1, (unsigned char *)("Doi Robotics Lab.2014.8.21"));

  glPopMatrix();

    //移動するテキスト
    glRasterPos3d(2,0,0);//三次元座標でメッセージ表示位置指定
    glutBitmapString(font1, (unsigned char *)("(2,0,0)"));
    glRasterPos3d(0,2,0);//三次元座標でメッセージ表示位置指定
    glutBitmapString(font1, (unsigned char *)("(0,2,0)"));
    glRasterPos3d(0,0,2);//三次元座標でメッセージ表示位置指定
    glutBitmapString(font1, (unsigned char *)("(0,0,2)"));


}
//-------------------------------------
void disp( void ) //描画
{

//視点の決定
double wh_ratio;//　w/hの比
wh_ratio=(double)W_Width/(double)W_Height;
GL_set_viewpoint(mv1.distance,mv1.azimuth,mv1.elevation,
  mv1.v_center[0], mv1.v_center[1], mv1.v_center[2], wh_ratio);

    disp_overlay();//二次元描画．三次元描画に重ねる形
    GL_set_light();//照明セット

//何か物体を描画したいときにはここにモデルを追加する------

glLineWidth(3);//線の太さ決定
GL_Coordinate(5);//座標軸描画

GL_Blue();//色青に決定
GL_Box(0,1,-1,1,-0.5,0.5);//箱描画


//三次元描画ここまで---------------------------


  //glFlush();
  glutSwapBuffers();
}
//-----------------------
void mbutton(int button , int state , int x , int y) //マウスボタン押し下げ、上げイベント
{
//printf("mouse event x[%d], y[%d]\n",x,y);

  mv1.drag_mode=DRAG_MODE_STOP;
	if (state== GLUT_DOWN)
          {
            if(button==GLUT_LEFT_BUTTON)
              {
                mv1.drag_mode=DRAG_MODE_ZOOM;
              }
            if(button==GLUT_MIDDLE_BUTTON)
              {
                mv1.drag_mode=DRAG_MODE_ROTATE;
              }
            if(button==GLUT_RIGHT_BUTTON)
              {
                mv1.drag_mode=DRAG_MODE_TRANSLATE;
              }
            mv1.init(x,y);
            mv1.flag_drag=1;
          }
  	if (state== GLUT_UP)
          {
            mv1.flag_drag=0;
          }
//disp();
  glutPostRedisplay();
}
//-----------------------
void mmotion(int x , int y) //マウス移動イベント
{
  if(mv1.flag_drag!=1)return;
	//printf("(x,y)=(%d,%d)",x,y);
  if(mv1.drag_mode==DRAG_MODE_ROTATE)
    {
      mv1.Rotate(x,y);
    }
    if(mv1.drag_mode==DRAG_MODE_ZOOM)
    {
      mv1.Zoom(x,y);
    }
    if(mv1.drag_mode==DRAG_MODE_TRANSLATE)
    {
      mv1.Translate(x,y);
    }
  	glutPostRedisplay();
}

//-----------------------
void keyf(unsigned char key , int x , int y)//一般キー入力
{
	printf("key[%c],x[%d],y[%d]\n",key,x,y);
    switch(key)
    {
    case 'q':
    case 'Q':
    case '\033':  /* '\033' は ESC の ASCII コード */
        {
            printf("Exit\n");
            exit(0);
            break;
        }
        default:
        break;
    }
    glutPostRedisplay();
}
/*
GLUT_KEY_F1	F1 function key
GLUT_KEY_F2	F2 function key
GLUT_KEY_F3	F3 function key
GLUT_KEY_F4	F4 function key
GLUT_KEY_F5	F5 function key
GLUT_KEY_F6	F6 function key
GLUT_KEY_F7	F7 function key
GLUT_KEY_F8	F8 function key
GLUT_KEY_F9	F9 function key
GLUT_KEY_F10	F10 function key
GLUT_KEY_F11	F11 function key
GLUT_KEY_F12	F12 function key
GLUT_KEY_LEFT	左矢印キー
GLUT_KEY_UP	上矢印キー
GLUT_KEY_RIGHT	右矢印キー
GLUT_KEY_DOWN	下矢印キー
GLUT_KEY_PAGE_UP	Page up キー
GLUT_KEY_PAGE_DOWN	Page down キー
GLUT_KEY_HOME	Home キー
GLUT_KEY_END	End キー
GLUT_KEY_INSERT	Inset キー
*/

void keyf2(int key , int x , int y)//特殊キーの扱い
{
	switch(key)
	{
		case GLUT_KEY_UP:
			printf("GLUT_KEY_UP\n");
                        break;
		case GLUT_KEY_DOWN:
			printf("GLUT_KEY_DOWN\n");
                        break;
		case GLUT_KEY_RIGHT:
			printf("GLUT_KEY_RIGHT\n");
			break;
		case GLUT_KEY_LEFT:
			printf("GLUT_KEY_LEFT\n");
                        break;

	}
	printf("key[%c],x[%d],y[%d]\n",key,x,y);
  	glutPostRedisplay();
}
//-----------------------
void js_func(unsigned int buttonMask, int x, int y, int z)//ジョイスティックイベント
{
  /*
    GLUT_JOYSTICK_BUTTON_A
    GLUT_JOYSTICK_BUTTON_B
    GLUT_JOYSTICK_BUTTON_C
    GLUT_JOYSTICK_BUTTON_D
    */
  printf("Joystick x,y,z=(%d,%d,%d)\n",x,y,z);
  /*
  switch (buttonMask)
    {
    case GLUT_JOYSTICK_BUTTON_A:
      printf("A ON");
      break;
    case GLUT_JOYSTICK_BUTTON_B:
      printf("B ON");
      break;
    }
    */
  	glutPostRedisplay();
}
//-----------------------
void reshape(int width, int height)//再描画の関数
{
W_Width=width;
W_Height=height;
printf("(width,height)=(%d,%d)\n",width,height);
glViewport(0,0,W_Width,W_Height);
  	glutPostRedisplay();
}
//-----------------------
int main(int argc , char ** argv) {
int id;

  glutInit(&argc , argv);
	glutInitWindowPosition(100 , 50);
	glutInitWindowSize((int)W_Width , (int)W_Height);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);



	id=glutCreateWindow("GLUT test");

        glutDisplayFunc(disp);//描画処理
	glutKeyboardFunc(keyf);//キー入力イベント
	glutSpecialFunc(keyf2);//特殊キー入力イベント
	glutMouseFunc(mbutton);//マウスボタン押し下げ、上げ
	glutMotionFunc(mmotion);//マウス移動イベント
	glutReshapeFunc(reshape);//再描画イベント
   //     glutJoystickFunc(js_func,100);//ジョイスティックイベント

	glutMainLoop();
	return 0;
}
