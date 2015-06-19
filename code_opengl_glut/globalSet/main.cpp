#include <windows.h>
#include <gl/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <math.h>

#define PLANET_NUM 10

/* add GL_BGR_EXT */
#ifndef GL_EXT_bgra
    #define GL_EXT_bgra 1
    #define GL_BGR_EXT 0x80E0
    #define GL_BGRA_EXT 0x80E1
    #define GLEW_EXT_bgra GLEW_GET_VAR(__GLEW_EXT_bgra)
#endif


GLfloat  whiteLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat	 lightPos[] = { 0.0f, 0.0f, 0.0f, 1.0f };

// 旋转角度
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

static float fEarthRot = 0.0f;
static float fMercuryRot = 0.0f;
static float fVenusRot = 0.0f;
static float fMarsRot = 0.0f;
static float fJupiterRot = 0.0f;
static float fSaturnRot = 0.0f;
static float fUranusRot = 0.0f;
static float fNeptuneRot = 0.0f;
static float fPlutoRot = 0.0f;

static GLubyte *data = NULL;

static GLuint texName[PLANET_NUM] = {0,0,0,0,0,0,0,0,0,0};
static char planet_name[PLANET_NUM][15] =
    {"水星.bmp","金星.bmp","地球.bmp","火星.bmp","木星.bmp",
     "土星.bmp","天王星.bmp","海王星.bmp","冥王星.bmp","太阳.bmp"};


//透视投影
void ChangeSize(int w, int h)
{
    GLfloat fAspect;

    // 防止被0所除
    if(h == 0){
        h = 1;
    }

    // 把视口设置为窗口大小
    glViewport(0, 0, w, h);

    fAspect = (GLfloat)w/(GLfloat)h;   //实际窗口的纵横比
    // 重置透视坐标系统
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // 产生透视投影
    gluPerspective(800.0f, fAspect, 1.0, 400);
	//重置模型视图矩阵
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


//加载纹理
void grab(int  num)
{
    GLsizei width,height;
    GLsizei bytes;
    GLbyte* byte;

    glClearColor(0.0,0.0,0.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(texName[num-1] != 0){
        return ;
    }

    FILE* file = NULL;
    file = fopen(planet_name[num-1],"rb");

    //读取本地图片文件并设置纹理
    if(file != NULL){
        fseek(file,0x0012,0);
        fread(&width,sizeof(width),1,file);
        fread(&height,sizeof(height),1,file);

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
        glGenTextures(1,texName+num-1);
        glBindTexture(GL_TEXTURE_2D,texName[num-1]);

        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_BGR_EXT,GL_UNSIGNED_BYTE,byte);

        glTexGeni(GL_S, GL_TEXTURE_GEN_MODE,  GL_SPHERE_MAP);
        glTexGeni(GL_T, GL_TEXTURE_GEN_MODE,  GL_SPHERE_MAP);
    }else{
        //如果文件读取失败了就不设置纹理
        texName[num-1] = -1;
    }
}


void SetupRC()
{
    glEnable(GL_DEPTH_TEST);	// 启用深度测试
    glEnable(GL_COLOR_MATERIAL);  //使用不同颜色来贴物体表面
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );  //黑色背景
    glEnable(GL_LIGHTING);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,whiteLight);   //使用whiteLight所指定的环境光
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);//0号光源的位置
    glEnable(GL_LIGHT0);
}



void SpecialKeys(int key, int x, int y)
{
	if(key == GLUT_KEY_UP){
		yRot -= 5.0f;
	}

	if(key == GLUT_KEY_DOWN){
		yRot += 5.0f;
	}

	if(key == GLUT_KEY_LEFT){
		yRot -= 5.0f;
	}

	if(key == GLUT_KEY_RIGHT){
		yRot += 5.0f;
	}

    xRot = (GLfloat)((const int)xRot % 360);
    yRot = (GLfloat)((const int)yRot % 360);

	glutPostRedisplay();
}


//播放背景音乐
void music()
{
	MCI_OPEN_PARMS op;
	op.dwCallback = 0;
	op.lpstrAlias = 0;
	op.lpstrDeviceType = "MPEGAudio";
	op.lpstrElementName = "背景音乐.mp3" ;
	op.wDeviceID = 0;
	UINT rs;
	rs = mciSendCommand(0,MCI_OPEN,MCI_OPEN_ELEMENT ,(DWORD)&op);
	if(rs == 0)
	{
		MCI_PLAY_PARMS pp;
		pp.dwCallback = 0;
		pp.dwFrom = 0;
		mciSendCommand(op.wDeviceID,MCI_PLAY,MCI_NOTIFY,(DWORD)&pp);
	}
}

//使用生成的纹理设置GLUquadricObj对象并绘制行星
void drawPlanet(int texName,double planet_size)
{
    GLUquadricObj *quadObj = gluNewQuadric();//创建一个二次曲面物体
    gluQuadricTexture(quadObj,GL_TRUE);        //启用该二次曲面的纹理
    if(texName > 0){
        glBindTexture(GL_TEXTURE_2D,texName);//绑定纹理
    }
    gluSphere(quadObj,planet_size,50,50);                    //绘制一个球体
    gluDeleteQuadric(quadObj);                    //删除二次曲面对象
}

//整个场景的加载和行星的显示
void RenderScene(void)
{
	static GLint width;
	static GLint height;
	static GLint length;

    // 清除颜色和深度缓冲区
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

	//把整个场景移动到视图中
	glTranslatef(0.0f,0.0f,-300.0f);
	glDisable(GL_DEPTH_TEST);//禁用深度测试
	//设置背景

    //防止刷新时重复读数据
	if(data == NULL){
        FILE *star=fopen("星空.bmp","rb");

        if(star != NULL){
            fseek(star,0x0012,0);
            fread(&width,sizeof(width),1,star);
            fread(&height,sizeof(height),1,star);
            length = width*3;
            while(length%4 != 0){
                ++length;
            }
            length *= height;

            data = (GLubyte*)malloc(length);
            fseek(star,54,0);
            fread(data,length,1,star);
            fclose(star);
        }
	}
	glDrawPixels(width,height,GL_BGR_EXT,GL_UNSIGNED_BYTE,data);
	glEnable(GL_DEPTH_TEST);//启用深度测试

	//设置材料颜色，太阳为黄色
	glColor3ub(255,120,0);
	glDisable(GL_LIGHTING);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
	glEnable(GL_TEXTURE_2D);
	drawPlanet(texName[PLANET_NUM-1],35);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0,GL_POSITION,lightPos);

	//绘制水星
	glColor3ub(0, 0, 255);//设置水星颜色
	glRotatef(fMercuryRot, 0.0f, 1.0f, 0.0f);//绕y轴旋转坐标系统，使水星围着太阳转
	glTranslatef(70.0f,0.0f,0.0f); //坐标原点沿x轴移动60
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
	glEnable(GL_TEXTURE_2D);
	drawPlanet(texName[0],3);
	glDisable(GL_TEXTURE_2D);
	glTranslatef(-70.0f,0.0f,0.0f); //恢复原始坐标

	//绘制金星
	glColor3ub(0,255,0);//设置金星颜色
    glRotatef(fVenusRot, 0.0f, 1.0f, 0.0f);//绕y轴旋转坐标系统，使金星围着太阳转
	glTranslatef(85.0f,0.0f,0.0f); //坐标原点沿x轴移动75
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
	glEnable(GL_TEXTURE_2D);
	drawPlanet(texName[1],6.1);
	glDisable(GL_TEXTURE_2D);
	glTranslatef(-85.0f,0.0f,0.0f); //恢复原始坐标

	//绘制地球
	glColor3ub(0, 255, 0);//设置地球颜色
	glRotatef(fEarthRot, 0.0f, 1.0f, 0.0f);//绕y轴旋转坐标系统，使地球围着太阳转
	glTranslatef(100.0f,0.0f,0.0f); //坐标原点沿x轴移动90
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
	glEnable(GL_TEXTURE_2D);
	drawPlanet(texName[2],7.2);
	glTranslatef(-100.0f,0.0f,0.0f);
	glDisable(GL_TEXTURE_2D);

	//绘制火星
	glColor3ub(0,255,0);//设置火星颜色
	glRotatef(fMarsRot, 0.0f, 1.0f, 0.0f);//绕y轴旋转坐标系统，使火星围着太阳转
	glTranslatef(130.0f,0.0f,0.0f); //坐标原点沿x轴移动130
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
	glEnable(GL_TEXTURE_2D);
	drawPlanet(texName[3],3.8);
	glDisable(GL_TEXTURE_2D);
    glTranslatef(-130.0f,0.0f,0.0f); //恢复原始坐标

	//绘制木星
	glColor3ub(0,0,225);//设置木星颜色
	glRotatef(fJupiterRot, 0.0f, 1.0f, 0.0f);//绕y轴旋转坐标系统，使木星围着太阳转
	glTranslatef(160.0f,0.0f,0.0f); //坐标原点沿x轴移动160
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
	glEnable(GL_TEXTURE_2D);
    drawPlanet(texName[4],10);//木星体积
    glDisable(GL_TEXTURE_2D);
    glTranslatef(-160.0f,0.0f,0.0f); //恢复原始坐标

    //绘制土星
	glColor3ub(0,0,255);//设置土星颜色
	glRotatef(fSaturnRot, 0.0f, 1.0f, 0.0f);//绕y轴旋转坐标系统，使土星围着太阳转
    glTranslatef(200.0f,0.0f,0.0f); //坐标原点沿x轴移动200
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
	glEnable(GL_TEXTURE_2D);
	drawPlanet(texName[5],8);//土星体积
	glDisable(GL_TEXTURE_2D);
    glTranslatef(-200.0f,0.0f,0.0f); //恢复原始坐标

	//绘制天王星
	glColor3ub(0, 0, 255);//设置天王星颜色
	glRotatef(fUranusRot, 0.0f, 1.0f, 0.0f);//绕y轴旋转坐标系统，使天王星围着太阳转
	glTranslatef(240.0f,0.0f,0.0f); //坐标原点沿x轴移动240
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
	glEnable(GL_TEXTURE_2D);
	drawPlanet(texName[6],12);//天王星体积
	glDisable(GL_TEXTURE_2D);
	glTranslatef(-240.0f,0.0f,0.0f); //恢复原始坐标

	//绘制海王星
	glColor3ub(0, 0, 255);//设置海王星颜色
	glRotatef(fNeptuneRot, 0.0f, 1.0f, 0.0f);//绕y轴旋转坐标系统，使海王星围着太阳转
	glTranslatef(270.0f,0.0f,0.0f); //坐标原点沿x轴移动270
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
	glEnable(GL_TEXTURE_2D);
	drawPlanet(texName[7],7.5);//海王星体积缩小了100倍
	glDisable(GL_TEXTURE_2D);
	glTranslatef(-270.0f,0.0f,0.0f); //恢复原始坐标

	//绘制冥王星
	glColor3ub(0, 0, 255);//设置地球颜色
	glRotatef(fPlutoRot, 0.0f, 1.0f, 0.0f);//绕y轴旋转坐标系统，使冥王星围着太阳转
	glTranslatef(290.0f,0.0f,0.0f); //坐标原点沿x轴移动290
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
	glEnable(GL_TEXTURE_2D);
	drawPlanet(texName[8],20);
	glDisable(GL_TEXTURE_2D);
	glTranslatef(-290.0f,0.0f,0.0f);
    glPopMatrix(); //回复矩阵状态

    //交换缓冲区
    glutSwapBuffers();
}


//设置idle时刷新函数
void idle_Reflash(void)
{
    Sleep(100);
    //设置各大行星的角速度
    fMercuryRot += 1.0f;
	if(fMercuryRot >= 365.0f){
		fMercuryRot = fMercuryRot-365;
	}

    fVenusRot += 0.8f;
	if(fVenusRot >= 365.0f){
		fVenusRot = fVenusRot-365;
	}


	fEarthRot += 0.6f;
	if(fEarthRot >= 365.0f){
		fEarthRot -= 365.0f;
	}

    fMarsRot += 0.4f;
	if(fMarsRot>=365.0f){
		fMarsRot=fMarsRot-365;
	}

    fJupiterRot += 0.3f;
	if(fJupiterRot >= 365.0f){
		fJupiterRot = fJupiterRot-365;
	}

    fSaturnRot += 0.2f;
	if(fSaturnRot >= 365.0f){
		fSaturnRot = fSaturnRot-365;
	}

    fUranusRot += 0.1f;
	if(fUranusRot >= 365.0f){
		fUranusRot = fUranusRot-365;
	}

    fNeptuneRot += 0.08f;
	if(fNeptuneRot >= 365.0f){
		fNeptuneRot = fNeptuneRot-365;
	}

    fPlutoRot += 0.2f;
	if(fPlutoRot >= 365.0f){
		fPlutoRot = fPlutoRot-365;
	}
    glutPostRedisplay();
}


//initial and read pic file to set grab
void init(void)
{
    int index = 1;
    while(index <= PLANET_NUM){
        grab(index++);
    }
}


int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000,600);
    glutInitWindowPosition(10,5);
    glutCreateWindow("Orthographic Projection");
    init();

    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);
    SetupRC();
    music();
	glutSpecialFunc(SpecialKeys);
	glutIdleFunc(idle_Reflash);
    glutMainLoop();

    return 0;
}
