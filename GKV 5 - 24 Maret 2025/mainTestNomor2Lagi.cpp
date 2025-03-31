// Nama : Mohamad Solkhan Nawawi
// NIM  : 24060123120020
// Lab  : C1
// Tugas : Membuat objek beserta dengan bayangannya

#include <math.h>
#include <stdio.h>
#include <GL/glut.h>
double rx = 0.0;
double ry = 0.0;
float l[] = { 0.0, 80.0, 0.0 }; 
float n[] = { 0.0, -40.0, 0.0 };
float e[] = { 0.0, -60.0, 0.0 };
void help();
// Pyramid object that will be drawn
void draw(int isShadow) {
    // Set uniform shadow color if drawing shadow
    if (isShadow) {
        // Change from solid shadow to blended shadow
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(0.1, 0.1, 0.1, 0.7); // Darker, semi-transparent shadow
    }
    
    // Define colors for the pyramid (from the image)
    float coralRed[3] = {0.95, 0.5, 0.4};      // Top level - coral/red
    float lightBlue[3] = {0.7, 0.85, 0.9};     // Second level - light blue
    float lightGreen[3] = {0.75, 0.87, 0.6};   // Third level - light green
    float yellow[3] = {0.95, 0.9, 0.55};       // Fourth level - yellow
    float turquoise[3] = {0.4, 0.8, 0.8};      // Bottom level - turquoise
    
    // Main pyramid dimensions
    float baseWidth = 30.0;     // Width of the base
    float pyramidHeight = 30.0; // Total height of the pyramid
    
    // Height proportions of each section (from bottom to top)
    float heightRatios[5] = {0.3, 0.22, 0.2, 0.15, 0.13}; // Proportion of total height
    
    // Calculate absolute heights and base widths for each level
    float sectionHeights[5]; // Actual height of each section
    float sectionBaseWidths[6]; // Width at each level boundary (6 to include the top point)
    
    // Calculate section heights
    float currentHeight = 0.0;
    for (int i = 0; i < 5; i++) {
        sectionHeights[i] = pyramidHeight * heightRatios[i];
        currentHeight += sectionHeights[i];
    }
    
    // Calculate section widths at each boundary
    // The width decreases linearly with height
    sectionBaseWidths[0] = baseWidth; // Bottom width
    sectionBaseWidths[5] = 0.0;       // Top point width
    
    for (int i = 1; i < 5; i++) {
        float heightRatio = 0.0;
        for (int j = 0; j < i; j++) {
            heightRatio += heightRatios[j];
        }
        sectionBaseWidths[i] = baseWidth * (1.0 - heightRatio);
    }
    
    if (!isShadow) {
        // Draw the pyramid from bottom to top
        float currentY = -pyramidHeight / 2.0; // Start from bottom
        
        // Draw the 5 sections of the pyramid
        for (int section = 0; section < 5; section++) {
            // Select the color for this section
            switch(section) {
                case 0: glColor3fv(turquoise); break;  // Bottom level - turquoise
                case 1: glColor3fv(yellow); break;     // Fourth level - yellow
                case 2: glColor3fv(lightGreen); break; // Third level - light green
                case 3: glColor3fv(lightBlue); break;  // Second level - light blue
                case 4: glColor3fv(coralRed); break;   // Top level - coral/red
            }
            
            // Calculate the upper Y coordinate for this section
            float nextY = currentY + sectionHeights[section];
            
            // Draw the section as a truncated pyramid (except the top which is a true pyramid)
            glBegin(GL_QUADS);
            
            // Front face
            glVertex3f(-sectionBaseWidths[section] / 2.0, currentY, sectionBaseWidths[section] / 2.0);
            glVertex3f(sectionBaseWidths[section] / 2.0, currentY, sectionBaseWidths[section] / 2.0);
            glVertex3f(sectionBaseWidths[section+1] / 2.0, nextY, sectionBaseWidths[section+1] / 2.0);
            glVertex3f(-sectionBaseWidths[section+1] / 2.0, nextY, sectionBaseWidths[section+1] / 2.0);
            
            // Right face
            glVertex3f(sectionBaseWidths[section] / 2.0, currentY, sectionBaseWidths[section] / 2.0);
            glVertex3f(sectionBaseWidths[section] / 2.0, currentY, -sectionBaseWidths[section] / 2.0);
            glVertex3f(sectionBaseWidths[section+1] / 2.0, nextY, -sectionBaseWidths[section+1] / 2.0);
            glVertex3f(sectionBaseWidths[section+1] / 2.0, nextY, sectionBaseWidths[section+1] / 2.0);
            
            // Back face
            glVertex3f(sectionBaseWidths[section] / 2.0, currentY, -sectionBaseWidths[section] / 2.0);
            glVertex3f(-sectionBaseWidths[section] / 2.0, currentY, -sectionBaseWidths[section] / 2.0);
            glVertex3f(-sectionBaseWidths[section+1] / 2.0, nextY, -sectionBaseWidths[section+1] / 2.0);
            glVertex3f(sectionBaseWidths[section+1] / 2.0, nextY, -sectionBaseWidths[section+1] / 2.0);
            
            // Left face
            glVertex3f(-sectionBaseWidths[section] / 2.0, currentY, -sectionBaseWidths[section] / 2.0);
            glVertex3f(-sectionBaseWidths[section] / 2.0, currentY, sectionBaseWidths[section] / 2.0);
            glVertex3f(-sectionBaseWidths[section+1] / 2.0, nextY, sectionBaseWidths[section+1] / 2.0);
            glVertex3f(-sectionBaseWidths[section+1] / 2.0, nextY, -sectionBaseWidths[section+1] / 2.0);
            
            glEnd();
            
            // Draw the horizontal face for each section (except the topmost one)
            if (section < 4) {
                glBegin(GL_QUADS);
                glVertex3f(-sectionBaseWidths[section+1] / 2.0, nextY, sectionBaseWidths[section+1] / 2.0);
                glVertex3f(sectionBaseWidths[section+1] / 2.0, nextY, sectionBaseWidths[section+1] / 2.0);
                glVertex3f(sectionBaseWidths[section+1] / 2.0, nextY, -sectionBaseWidths[section+1] / 2.0);
                glVertex3f(-sectionBaseWidths[section+1] / 2.0, nextY, -sectionBaseWidths[section+1] / 2.0);
                glEnd();
            }
            
            // Add black outline to each section
            glColor3f(0.0, 0.0, 0.0);
            glLineWidth(2.0);
            glBegin(GL_LINE_LOOP);
            glVertex3f(-sectionBaseWidths[section] / 2.0, currentY, sectionBaseWidths[section] / 2.0);
            glVertex3f(sectionBaseWidths[section] / 2.0, currentY, sectionBaseWidths[section] / 2.0);
            glVertex3f(sectionBaseWidths[section] / 2.0, currentY, -sectionBaseWidths[section] / 2.0);
            glVertex3f(-sectionBaseWidths[section] / 2.0, currentY, -sectionBaseWidths[section] / 2.0);
            glEnd();
            
            // Add black outline to the horizontal face
            glBegin(GL_LINES);
            // Vertical lines at corners
            glVertex3f(-sectionBaseWidths[section] / 2.0, currentY, sectionBaseWidths[section] / 2.0);
            glVertex3f(-sectionBaseWidths[section+1] / 2.0, nextY, sectionBaseWidths[section+1] / 2.0);
            
            glVertex3f(sectionBaseWidths[section] / 2.0, currentY, sectionBaseWidths[section] / 2.0);
            glVertex3f(sectionBaseWidths[section+1] / 2.0, nextY, sectionBaseWidths[section+1] / 2.0);
            
            glVertex3f(sectionBaseWidths[section] / 2.0, currentY, -sectionBaseWidths[section] / 2.0);
            glVertex3f(sectionBaseWidths[section+1] / 2.0, nextY, -sectionBaseWidths[section+1] / 2.0);
            
            glVertex3f(-sectionBaseWidths[section] / 2.0, currentY, -sectionBaseWidths[section] / 2.0);
            glVertex3f(-sectionBaseWidths[section+1] / 2.0, nextY, -sectionBaseWidths[section+1] / 2.0);
            glEnd();
            
            // Outline for the top face of each section
            if (section < 4) {
                glBegin(GL_LINE_LOOP);
                glVertex3f(-sectionBaseWidths[section+1] / 2.0, nextY, sectionBaseWidths[section+1] / 2.0);
                glVertex3f(sectionBaseWidths[section+1] / 2.0, nextY, sectionBaseWidths[section+1] / 2.0);
                glVertex3f(sectionBaseWidths[section+1] / 2.0, nextY, -sectionBaseWidths[section+1] / 2.0);
                glVertex3f(-sectionBaseWidths[section+1] / 2.0, nextY, -sectionBaseWidths[section+1] / 2.0);
                glEnd();
            }
            
            // Move up to the next section
            currentY = nextY;
        }
    } else {
        // For shadow, use simplified geometry with same shape
        
        // Draw the pyramid from bottom to top
        float currentY = -pyramidHeight / 2.0; // Start from bottom
        
        // Draw the 5 sections of the pyramid
        for (int section = 0; section < 5; section++) {
            // Calculate the upper Y coordinate for this section
            float nextY = currentY + sectionHeights[section];
            
            // Draw the section as a truncated pyramid (except the top which is a true pyramid)
            glBegin(GL_QUADS);
            
            // Front face
            glVertex3f(-sectionBaseWidths[section] / 2.0, currentY, sectionBaseWidths[section] / 2.0);
            glVertex3f(sectionBaseWidths[section] / 2.0, currentY, sectionBaseWidths[section] / 2.0);
            glVertex3f(sectionBaseWidths[section+1] / 2.0, nextY, sectionBaseWidths[section+1] / 2.0);
            glVertex3f(-sectionBaseWidths[section+1] / 2.0, nextY, sectionBaseWidths[section+1] / 2.0);
            
            // Right face
            glVertex3f(sectionBaseWidths[section] / 2.0, currentY, sectionBaseWidths[section] / 2.0);
            glVertex3f(sectionBaseWidths[section] / 2.0, currentY, -sectionBaseWidths[section] / 2.0);
            glVertex3f(sectionBaseWidths[section+1] / 2.0, nextY, -sectionBaseWidths[section+1] / 2.0);
            glVertex3f(sectionBaseWidths[section+1] / 2.0, nextY, sectionBaseWidths[section+1] / 2.0);
            
            // Back face
            glVertex3f(sectionBaseWidths[section] / 2.0, currentY, -sectionBaseWidths[section] / 2.0);
            glVertex3f(-sectionBaseWidths[section] / 2.0, currentY, -sectionBaseWidths[section] / 2.0);
            glVertex3f(-sectionBaseWidths[section+1] / 2.0, nextY, -sectionBaseWidths[section+1] / 2.0);
            glVertex3f(sectionBaseWidths[section+1] / 2.0, nextY, -sectionBaseWidths[section+1] / 2.0);
            
            // Left face
            glVertex3f(-sectionBaseWidths[section] / 2.0, currentY, -sectionBaseWidths[section] / 2.0);
            glVertex3f(-sectionBaseWidths[section] / 2.0, currentY, sectionBaseWidths[section] / 2.0);
            glVertex3f(-sectionBaseWidths[section+1] / 2.0, nextY, sectionBaseWidths[section+1] / 2.0);
            glVertex3f(-sectionBaseWidths[section+1] / 2.0, nextY, -sectionBaseWidths[section+1] / 2.0);
            
            glEnd();
            
            // Draw the horizontal face for each section (except the topmost one)
            if (section < 4) {
                glBegin(GL_QUADS);
                glVertex3f(-sectionBaseWidths[section+1] / 2.0, nextY, sectionBaseWidths[section+1] / 2.0);
                glVertex3f(sectionBaseWidths[section+1] / 2.0, nextY, sectionBaseWidths[section+1] / 2.0);
                glVertex3f(sectionBaseWidths[section+1] / 2.0, nextY, -sectionBaseWidths[section+1] / 2.0);
                glVertex3f(-sectionBaseWidths[section+1] / 2.0, nextY, -sectionBaseWidths[section+1] / 2.0);
                glEnd();
            }
            
            // Move up to the next section
            currentY = nextY;
        }
    }
    
    // If shadow was enabled, disable blending when done
    if (isShadow) {
        glDisable(GL_BLEND);
    }
}
// Shadow projection
void glShadowProjection(float *l, float *e, float *n) {
    float d, c;
    float mat[16];
    
    d = n[0] * l[0] + n[1] * l[1] + n[2] * l[2];
    c = e[0] * n[0] + e[1] * n[1] + e[2] * n[2] - d;
    // Create shadow projection matrix
    mat[0] = l[0] * n[0] + c;
    mat[4] = n[1] * l[0];
    mat[8] = n[2] * l[0];
    mat[12] = -l[0] * c - l[0] * d;
    mat[1] = n[0] * l[1];
    mat[5] = l[1] * n[1] + c;
    mat[9] = n[2] * l[1];
    mat[13] = -l[1] * c - l[1] * d;
    mat[2] = n[0] * l[2];
    mat[6] = n[1] * l[2];
    mat[10] = l[2] * n[2] + c;
    mat[14] = -l[2] * c - l[2] * d;
    mat[3] = n[0];
    mat[7] = n[1];
    mat[11] = n[2];
    mat[15] = -d;
    glMultMatrixf(mat); // Multiply matrix
}
void render() {
    glClearColor(1.0, 1.0, 1.0, 0.0); // White background
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    
    // Light source position
    glLightfv(GL_LIGHT0, GL_POSITION, l);
    
    glDisable(GL_CULL_FACE);
    glDisable(GL_LIGHTING);
    
    // Draw light point
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POINTS);
    glVertex3f(l[0], l[1], l[2]);
    glEnd();
    
    // Light blue background for object
    glColor3f(0.8, 0.9, 1.0); // Light blue
    glBegin(GL_QUADS);
    glVertex3f(-1300.0, e[1], 1300.0);
    glVertex3f(1300.0, e[1], 1300.0);
    glVertex3f(1300.0, e[1], -1300.0);
    glVertex3f(-1300.0, e[1], -1300.0);
    glEnd();
    
    // Draw 3D pyramid object (reduced by 30%)
    glPushMatrix();
    glTranslatef(0.0, 20.0, 0.0); // Moved down a bit so shadow is visible below
    glRotatef(ry, 0, 1, 0);
    glRotatef(rx, 1, 0, 0);
    glScalef(2.1, 2.1, 2.1);  // Reduced size by 30% (70% of original 3.0)
    glEnable(GL_LIGHTING);
    draw(0); // not shadow
    glPopMatrix();
    
    // Draw white floor for shadow
    glColor3f(1.0, 1.0, 1.0); // White floor
    glBegin(GL_QUADS);
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(-1300.0, e[1] - 0.1, 1300.0);
    glVertex3f(1300.0, e[1] - 0.1, 1300.0);
    glVertex3f(1300.0, e[1] - 0.1, -1300.0);
    glVertex3f(-1300.0, e[1] - 0.1, -1300.0);
    glEnd();
    
    // Before drawing the shadow
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_ALWAYS, 1, 0xFFFFFFFF);
    glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
    
    // Draw floor first to stencil buffer
    glColor3f(1.0, 1.0, 1.0); // White floor
    glBegin(GL_QUADS);
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(-1300.0, e[1] - 0.1, 1300.0);
    glVertex3f(1300.0, e[1] - 0.1, 1300.0);
    glVertex3f(1300.0, e[1] - 0.1, -1300.0);
    glVertex3f(-1300.0, e[1] - 0.1, -1300.0);
    glEnd();
    
    // Now only draw shadows where floor was drawn
    glStencilFunc(GL_EQUAL, 1, 0xFFFFFFFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
    
    // Draw pyramid shadow
    glPushMatrix();
    glTranslatef(0.0, 20.0, 0.0); // Keep same translation as object
    glShadowProjection(l, e, n);
    glRotatef(ry, 0, 1, 0);
    glRotatef(rx, 1, 0, 0);
    glScalef(2.1, 2.1, 2.1);  // Match the size of the main object (70% of original)
    glDisable(GL_LIGHTING);
    draw(1); // shadow
    glPopMatrix();
    
    glDisable(GL_STENCIL_TEST);
    glutSwapBuffers();
}
void keypress(unsigned char c, int a, int b) {
    if (c == 27) {
        exit(0);
    } else if (c == 's') {
        l[1] -= 5.0;
    } else if (c == 'w') {
        l[1] += 5.0;
    } else if (c == 'a') {
        l[0] -= 5.0;
    } else if (c == 'd') {
        l[0] += 5.0;
    } else if (c == 'q') {
        l[2] -= 5.0;
    } else if (c == 'e') {
        l[2] += 5.0;
    } else if (c == 'h') {
        help();
    }
}
void help() {
    printf("Sung Jin Woo - Ekstraksi Bayangan\n");
}
void idle() {
    rx += 0.005;
    ry += 0.005;
    render();
}
void resize(int w, int h) {
    glViewport(0, 0, w, h);
}
int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL); // Add stencil buffer
    glutInitWindowPosition(300, 30);
    glutCreateWindow("Sung Jin Woo - Ekstraksi Bayangan");
    
    glutReshapeFunc(resize);
    glutReshapeWindow(400, 400);
    glutKeyboardFunc(keypress);
    glutDisplayFunc(render);
    glutIdleFunc(idle);
    
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_TEXTURE_2D);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f, 1.0, 1.0, 400.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -150.0);
    glutMainLoop();
    return 0;
}
