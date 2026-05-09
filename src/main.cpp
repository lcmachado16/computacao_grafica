// Quadrado.cpp
// OpenGL + GLUT funcionando no Linux/macOS

// =========================================
// Exemplo extraido de https://www.inf.pucrs.br/~manssour/OpenGL/Desenhando.html
// Quadrado.c - Isabel H. Manssour
// Um programa OpenGL simples que desenha um 
// quadrado em  uma janela GLUT.
// Este código está baseado no GLRect.c, exemplo 
// disponível no livro "OpenGL SuperBible", 
// 2nd Edition, de Richard S. e Wright Jr.
// ========================================

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

// ========================================
// Função de desenho
// ========================================
void Desenha(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Limpa tela
    glClear(GL_COLOR_BUFFER_BIT);

    // Cor vermelha
    glColor3f(1.0f, 0.0f, 0.0f);

    // Desenha quadrado
    glBegin(GL_QUADS);

        glVertex2i(100, 150);
        glVertex2i(100, 100);

        // Muda para azul
        glColor3f(0.0f, 0.0f, 1.0f);

        glVertex2i(150, 100);
        glVertex2i(150, 150);

    glEnd();

    glFlush();
}

// ========================================
// Inicialização
// ========================================
void Inicializa(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

// ========================================
// Resize da janela
// ========================================
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
    if (h == 0)
        h = 1;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (w <= h)
    {
        gluOrtho2D(
            0.0f,
            250.0f,
            0.0f,
            250.0f * h / w
        );
    }
    else
    {
        gluOrtho2D(
            0.0f,
            250.0f * w / h,
            0.0f,
            250.0f
        );
    }
}

// ========================================
// Main
// ========================================
int main(int argc, char** argv)
{
    // Inicializa GLUT
    glutInit(&argc, argv);

    // Modo de exibição
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    // Tamanho da janela
    glutInitWindowSize(400, 350);

    // Posição
    glutInitWindowPosition(10, 10);

    // Cria janela
    glutCreateWindow("Quadrado");

    // Callbacks
    glutDisplayFunc(Desenha);
    glutReshapeFunc(AlteraTamanhoJanela);

    Inicializa();

    glutMainLoop();

    return 0;
}