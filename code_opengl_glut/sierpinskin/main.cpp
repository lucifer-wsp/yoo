#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#define MAXCOLOR 7

float colortab[MAXCOLOR][4]=
{
    {0.2,        0,            0.4,    0.0},    //��
    {0.2,        0,            0.5,    0.0},  //��
    {0.2,        0,            0.6,    0.0},    //��
    {0.3,        0,            1.0,    0.0},    //��
    {0.196,        0.3039,        0.296,    0.0},    //����
    {0.2784,        1.0,        0.1843,    0.0},    //ǳ��
    {1.0,        0.3068,        0.1,    0.0}        //��
};


//��������
void Square(float center[3], float size, float color[4])
{
    glPushMatrix();
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);  // ��������ɫ��ɢ����ɫ���ó�ͬһ��ɫ
    glTranslatef(center[0], center[1], center[2]);        //ƽ������ϵ
    glutSolidCube(size);//���ÿ⺯������һ���뾶Ϊ1�����塣
    glPopMatrix();
}

void init(void)
{
    glClearColor(0.5, 0.5, 0.5, 0.0);    //������ɫ��Ϊ��ɫ����Ҳ����Ϊ�Ǳ�����ɫ��

    float light_diffuse[]= { 1.0, 1.0, 1.0, 1.0};       //�еƹ�������ֲ��ʵ�Ч�������ĵƹ��ǿ������Ĺ�ϵ��ò�����������ʲô�ġ�(0-1)��Χ��
    float light_position[] = { 0, 3, 2.0, 0.0 };        //���õ��Դ�ľ����������Ҳ߯����ˣ�1�����ű䣬0���ű䣬����Ϊ͸��֮������1���ű䣬0�����ű䡣
    float light_specular[] = { 1.0, 1.0, 0.0, 1.0 };    //�����
    float light_ambient[] = {0.5, 0.5, 0.5, 1.0};

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);        //����������������Ч���͸߹��Ч��
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);    //���Դû��������Ч������һֱ�Ǻ�ɫ�ġ������и߹ⷴ���Ч����
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);        //��������û��Ч�����������Ҳ�֪����

    GLfloat no_mat[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat mat_specular[] =  {1.0, 1.0, 1.0, 1.0};
    GLfloat hig_shininess[] = {100.0};
    glMaterialfv(GL_FRONT,GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT,GL_SHININESS, hig_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);    //���ʲô�������ã�GL_LIGHT��Ĭ�ϵ�ֵ��
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
}

//�ڸ������ĵ���Χ��6��������
void SurroundSquare(float center[3], float size, float color[4])
{
    //��Χ6�������������
    float halfcenter[6][3] =
    {
        {center[0] + size * 3/4.0, center[1], center[2]},
        {center[0] - size * 3/4.0, center[1], center[2]},
        {center[0] , center[1] + size * 3/4.0, center[2]},
        {center[0] , center[1] - size * 3/4.0, center[2]},
        {center[0] , center[1], center[2] + size * 3/4.0},
        {center[0] , center[1], center[2] - size * 3/4.0}
    };

    for (int i=0; i<6; i++)
    {
        Square(halfcenter[i], size/2, color);
    }
}

void Iteration(float center[3], float size, int nIter)
{
    if(nIter<0)return;

    SurroundSquare(center, size, colortab[nIter]);

    float halfcenter[6][3] =
    {
        center[0] + size * 3/4.0, center[1], center[2],
        center[0] - size * 3/4.0, center[1], center[2],
        center[0] , center[1] + size * 3/4.0, center[2],
        center[0] , center[1] - size * 3/4.0, center[2],
        center[0] , center[1], center[2] + size * 3/4.0,
        center[0] , center[1], center[2] - size * 3/4.0,
    };

    for (int i=0; i<6; i++)
    {
        Iteration(halfcenter[i], size/2, nIter-1);
    }
}


void display(void)
{
    //�����ɫ�������Ȼ���
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0,1.0,1.0);
    glLoadIdentity();

    gluLookAt(1, -1, 3,   0, 0, 0,   0.4, -3, 0.5);        //�ӵ�ת��
    float center[] = {0.0f, 0.0f, 0.0f};
    float radius = 2;
    float color[] = {1.0, 0.1, 0.0, 0};
    Square(center, radius, color);
    Iteration(center, radius, 10);
    glutSwapBuffers();      //����˫����
}


void reshape(int width,int height)
{
    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-3.0, 3.0, -3.0 * height / width, 3.0* height / width, -5, 5);    //Ϊ�˲����Σ���Ҫ���Ϳ�ɱ���
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


int main(int argc,char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);    //ʹ��˫����ģʽ����Ȼ���
    glutInitWindowSize(600,600);
    glutInitWindowPosition(200,200);
    glutCreateWindow("��ά����");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(display);   //���ÿ���ʱ�õĺ���
    glutMainLoop();

    return 0;
}
