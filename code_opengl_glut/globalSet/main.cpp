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

// ��ת�Ƕ�
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
    {"ˮ��.bmp","����.bmp","����.bmp","����.bmp","ľ��.bmp",
     "����.bmp","������.bmp","������.bmp","ڤ����.bmp","̫��.bmp"};


//͸��ͶӰ
void ChangeSize(int w, int h)
{
    GLfloat fAspect;

    // ��ֹ��0����
    if(h == 0){
        h = 1;
    }

    // ���ӿ�����Ϊ���ڴ�С
    glViewport(0, 0, w, h);

    fAspect = (GLfloat)w/(GLfloat)h;   //ʵ�ʴ��ڵ��ݺ��
    // ����͸������ϵͳ
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // ����͸��ͶӰ
    gluPerspective(800.0f, fAspect, 1.0, 400);
	//����ģ����ͼ����
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


//��������
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

    //��ȡ����ͼƬ�ļ�����������
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
        //����ļ���ȡʧ���˾Ͳ���������
        texName[num-1] = -1;
    }
}


void SetupRC()
{
    glEnable(GL_DEPTH_TEST);	// ������Ȳ���
    glEnable(GL_COLOR_MATERIAL);  //ʹ�ò�ͬ��ɫ�����������
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );  //��ɫ����
    glEnable(GL_LIGHTING);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,whiteLight);   //ʹ��whiteLight��ָ���Ļ�����
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);//0�Ź�Դ��λ��
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


//���ű�������
void music()
{
	MCI_OPEN_PARMS op;
	op.dwCallback = 0;
	op.lpstrAlias = 0;
	op.lpstrDeviceType = "MPEGAudio";
	op.lpstrElementName = "��������.mp3" ;
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

//ʹ�����ɵ���������GLUquadricObj���󲢻�������
void drawPlanet(int texName,double planet_size)
{
    GLUquadricObj *quadObj = gluNewQuadric();//����һ��������������
    gluQuadricTexture(quadObj,GL_TRUE);        //���øö������������
    if(texName > 0){
        glBindTexture(GL_TEXTURE_2D,texName);//������
    }
    gluSphere(quadObj,planet_size,50,50);                    //����һ������
    gluDeleteQuadric(quadObj);                    //ɾ�������������
}

//���������ļ��غ����ǵ���ʾ
void RenderScene(void)
{
	static GLint width;
	static GLint height;
	static GLint length;

    // �����ɫ����Ȼ�����
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

	//�����������ƶ�����ͼ��
	glTranslatef(0.0f,0.0f,-300.0f);
	glDisable(GL_DEPTH_TEST);//������Ȳ���
	//���ñ���

    //��ֹˢ��ʱ�ظ�������
	if(data == NULL){
        FILE *star=fopen("�ǿ�.bmp","rb");

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
	glEnable(GL_DEPTH_TEST);//������Ȳ���

	//���ò�����ɫ��̫��Ϊ��ɫ
	glColor3ub(255,120,0);
	glDisable(GL_LIGHTING);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
	glEnable(GL_TEXTURE_2D);
	drawPlanet(texName[PLANET_NUM-1],35);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0,GL_POSITION,lightPos);

	//����ˮ��
	glColor3ub(0, 0, 255);//����ˮ����ɫ
	glRotatef(fMercuryRot, 0.0f, 1.0f, 0.0f);//��y����ת����ϵͳ��ʹˮ��Χ��̫��ת
	glTranslatef(70.0f,0.0f,0.0f); //����ԭ����x���ƶ�60
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
	glEnable(GL_TEXTURE_2D);
	drawPlanet(texName[0],3);
	glDisable(GL_TEXTURE_2D);
	glTranslatef(-70.0f,0.0f,0.0f); //�ָ�ԭʼ����

	//���ƽ���
	glColor3ub(0,255,0);//���ý�����ɫ
    glRotatef(fVenusRot, 0.0f, 1.0f, 0.0f);//��y����ת����ϵͳ��ʹ����Χ��̫��ת
	glTranslatef(85.0f,0.0f,0.0f); //����ԭ����x���ƶ�75
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
	glEnable(GL_TEXTURE_2D);
	drawPlanet(texName[1],6.1);
	glDisable(GL_TEXTURE_2D);
	glTranslatef(-85.0f,0.0f,0.0f); //�ָ�ԭʼ����

	//���Ƶ���
	glColor3ub(0, 255, 0);//���õ�����ɫ
	glRotatef(fEarthRot, 0.0f, 1.0f, 0.0f);//��y����ת����ϵͳ��ʹ����Χ��̫��ת
	glTranslatef(100.0f,0.0f,0.0f); //����ԭ����x���ƶ�90
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
	glEnable(GL_TEXTURE_2D);
	drawPlanet(texName[2],7.2);
	glTranslatef(-100.0f,0.0f,0.0f);
	glDisable(GL_TEXTURE_2D);

	//���ƻ���
	glColor3ub(0,255,0);//���û�����ɫ
	glRotatef(fMarsRot, 0.0f, 1.0f, 0.0f);//��y����ת����ϵͳ��ʹ����Χ��̫��ת
	glTranslatef(130.0f,0.0f,0.0f); //����ԭ����x���ƶ�130
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
	glEnable(GL_TEXTURE_2D);
	drawPlanet(texName[3],3.8);
	glDisable(GL_TEXTURE_2D);
    glTranslatef(-130.0f,0.0f,0.0f); //�ָ�ԭʼ����

	//����ľ��
	glColor3ub(0,0,225);//����ľ����ɫ
	glRotatef(fJupiterRot, 0.0f, 1.0f, 0.0f);//��y����ת����ϵͳ��ʹľ��Χ��̫��ת
	glTranslatef(160.0f,0.0f,0.0f); //����ԭ����x���ƶ�160
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
	glEnable(GL_TEXTURE_2D);
    drawPlanet(texName[4],10);//ľ�����
    glDisable(GL_TEXTURE_2D);
    glTranslatef(-160.0f,0.0f,0.0f); //�ָ�ԭʼ����

    //��������
	glColor3ub(0,0,255);//����������ɫ
	glRotatef(fSaturnRot, 0.0f, 1.0f, 0.0f);//��y����ת����ϵͳ��ʹ����Χ��̫��ת
    glTranslatef(200.0f,0.0f,0.0f); //����ԭ����x���ƶ�200
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
	glEnable(GL_TEXTURE_2D);
	drawPlanet(texName[5],8);//�������
	glDisable(GL_TEXTURE_2D);
    glTranslatef(-200.0f,0.0f,0.0f); //�ָ�ԭʼ����

	//����������
	glColor3ub(0, 0, 255);//������������ɫ
	glRotatef(fUranusRot, 0.0f, 1.0f, 0.0f);//��y����ת����ϵͳ��ʹ������Χ��̫��ת
	glTranslatef(240.0f,0.0f,0.0f); //����ԭ����x���ƶ�240
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
	glEnable(GL_TEXTURE_2D);
	drawPlanet(texName[6],12);//���������
	glDisable(GL_TEXTURE_2D);
	glTranslatef(-240.0f,0.0f,0.0f); //�ָ�ԭʼ����

	//���ƺ�����
	glColor3ub(0, 0, 255);//���ú�������ɫ
	glRotatef(fNeptuneRot, 0.0f, 1.0f, 0.0f);//��y����ת����ϵͳ��ʹ������Χ��̫��ת
	glTranslatef(270.0f,0.0f,0.0f); //����ԭ����x���ƶ�270
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
	glEnable(GL_TEXTURE_2D);
	drawPlanet(texName[7],7.5);//�����������С��100��
	glDisable(GL_TEXTURE_2D);
	glTranslatef(-270.0f,0.0f,0.0f); //�ָ�ԭʼ����

	//����ڤ����
	glColor3ub(0, 0, 255);//���õ�����ɫ
	glRotatef(fPlutoRot, 0.0f, 1.0f, 0.0f);//��y����ת����ϵͳ��ʹڤ����Χ��̫��ת
	glTranslatef(290.0f,0.0f,0.0f); //����ԭ����x���ƶ�290
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
	glEnable(GL_TEXTURE_2D);
	drawPlanet(texName[8],20);
	glDisable(GL_TEXTURE_2D);
	glTranslatef(-290.0f,0.0f,0.0f);
    glPopMatrix(); //�ظ�����״̬

    //����������
    glutSwapBuffers();
}


//����idleʱˢ�º���
void idle_Reflash(void)
{
    Sleep(100);
    //���ø������ǵĽ��ٶ�
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
