#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// ========================================
// Posição do quadrado
// ========================================
float quadX = 100;
float quadY = 100;
float tamanho = 50;

bool isArrastando = false;

// Offset do clique - para o quadrado nao ir para o centro do mouse na hora do clique
float offsetX = 0;
float offsetY = 0;

// ========================================
// Desenha
// ========================================
void Desenha()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glBegin(GL_QUADS);

    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex2f(quadX, quadY);
    glVertex2f(quadX, quadY + tamanho);

    glColor3f(0.0f, 0.7f, 1.0f);
    glVertex2f(quadX + tamanho, quadY + tamanho);
    glVertex2f(quadX + tamanho, quadY);

    glEnd();

    glFlush();
}

// ========================================
// Clique do mouse
// ========================================
void Mouse(int botao, int estado, int x, int y)
{
    // Converte Y do mouse
    y = glutGet(GLUT_WINDOW_HEIGHT) - y;

    // Clique esquerdo
    if (botao == GLUT_LEFT_BUTTON)
    {
        // Mouse pressionado
        if (estado == GLUT_DOWN)
        {
            // Verifica se clicou dentro do quadrado
            if (x >= quadX &&
                x <= quadX + tamanho &&
                y >= quadY &&
                y <= quadY + tamanho)
            {
                isArrastando = true;

                // Guarda distância entre mouse e quadrado
                offsetX = x - quadX;
                offsetY = y - quadY;
            }
        }

        // Soltou mouse
        if (estado == GLUT_UP)
        {
            isArrastando = false;
        }
    }
}

// ========================================
// Mouse sendo arrastado
// ========================================
void MovimentoMouse(int x, int y)
{
    // Converte eixo Y
    y = glutGet(GLUT_WINDOW_HEIGHT) - y;

    if (isArrastando)
    {
        quadX = x - offsetX;
        quadY = y - offsetY;

        glutPostRedisplay();
    }
}

// ========================================
// Resize
// ========================================
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
    if (h == 0)
        h = 1;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(0, w, 0, h);
}

// ========================================
// Inicializa
// ========================================
void Inicializa()
{
    glClearColor(0, 0, 0, 1);
}

// ========================================
// Main
// ========================================
int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    int larguraJanela = 800;
    int alturaJanela = 600;
    glutInitWindowSize(larguraJanela, alturaJanela);

    glutInitWindowPosition(
        (glutGet(GLUT_SCREEN_WIDTH) - larguraJanela) / 2,
        (glutGet(GLUT_SCREEN_HEIGHT) - alturaJanela) / 2);

    glutCreateWindow("Drag and Drop");

    Inicializa();

    glutDisplayFunc(Desenha);

    glutReshapeFunc(AlteraTamanhoJanela);

    // Clique
    glutMouseFunc(Mouse);

    // Arrastar mouse
    glutMotionFunc(MovimentoMouse);

    glutMainLoop();

    return 0;
}