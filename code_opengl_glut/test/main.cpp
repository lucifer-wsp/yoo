#include <gl/glut.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <math.h>

#ifndef GL_EXT_bgra
#define GL_EXT_bgra 1
#define GL_BGR_EXT 0x80E0
#define GL_BGRA_EXT 0x80E1
#define GLEW_EXT_bgra GLEW_GET_VAR(__GLEW_EXT_bgra)
#endif /* GL_EXT_bgra */


#define WIDTH 400
#define HEIGHT 400

static GLfloat angle = 0.0f;
static GLuint texName ;

void init(void)
{
    GLsizei width,height;
    GLsizei bytes;
    GLbyte* byte;

    glClearColor(0.0,0.0,0.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    FILE* file = NULL;
    file = fopen("ss.bmp","rb");
    fseek(file,0x0012,0);
    fread(&width,sizeof(width),1,file);
    fread(&height,sizeof(height),1,file);

    printf ("width = %ld,height = %ld.\n",width,height);

    bytes = width*3;
    while(bytes%4 != 0){
        bytes++;
    }
    bytes *= height;

    byte = (GLbyte*) malloc(bytes);
    fseek(file,54,0);
    fread(byte,bytes,1,file);
    fclose(file);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    glGenTextures(1,&texName);
    glBindTexture(GL_TEXTURE_2D,texName);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_BGR_EXT,GL_UNSIGNED_BYTE,byte);

    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE,  GL_SPHERE_MAP);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE,  GL_SPHERE_MAP);
}


void draw(int texName)
{
    GLUquadricObj *quadObj = gluNewQuadric();//创建一个二次曲面物体
    gluQuadricTexture(quadObj,GL_FILL);        //启用该二次曲面的纹理
    glBindTexture(GL_TEXTURE_2D,texName);//绑定纹理
    gluSphere(quadObj,3,50,50);                    //绘制一个球体
    gluDeleteQuadric(quadObj);                    //删除二次曲面对象
}


void idle(void)
{
    angle += 0.1;
    if(angle > 365){
        angle -= 365;
    }
    glutPostRedisplay();
}


void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //清空颜色和深度缓冲

    glMatrixMode(GL_PROJECTION);//对投影矩阵操作
    glLoadIdentity();//将坐标原点移到中心
    gluPerspective(90.0f, 1.0f, 1.0f, 180.0f);//设置透视投影矩阵
    glMatrixMode(GL_MODELVIEW);//对模型视景矩阵操作
    glLoadIdentity();
    gluLookAt(0.0, 5.0, -10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);//视点转换

    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
    glRotatef(angle,0.0,1.0,0.0);
    glTranslated(75.0f,0.0f,0.0f);
    draw(texName);
    glTranslatef(-75.0f,0.0f,0.0f);
    glDisable(GL_TEXTURE_2D);

    glutSwapBuffers(); //交换缓冲区
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE |GLUT_DEPTH) ;
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("OpenGL光照演示");
    init();
    glutDisplayFunc(&myDisplay);
    glutIdleFunc(idle);
    glutMainLoop();

    return 0;
}
