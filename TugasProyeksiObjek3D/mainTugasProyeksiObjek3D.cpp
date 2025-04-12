// Nama  : Mohamad Solkhan Nawawi
// NIM 	 : 24060123120020
// Kelas : GKV C
// Tugas : Membuat Objek 3D Non Primitif lalu memproyeksikan kedalam 8 proyeksi

#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

// Variabel untuk rotasi dan translasi objek
GLfloat rotateX = 0.0f;
GLfloat rotateY = 0.0f;
GLfloat translateZ = -5.0f;

// Variabel untuk mode proyeksi
int projectionMode = 0;
// 0: Plan view (Orthographic - atas)
// 1: Front view (Orthographic - depan)
// 2: Side view (Orthographic - samping)
// 3: Isometric (Orthographic)
// 4: Dimetric (Orthographic)
// 5: Trimetric (Orthographic)
// 6: 1-point perspective
// 7: 2-point perspective
// 8: 3-point perspective

// Fungsi untuk menggambar tekstur garis pada atap
void drawRoofTexture(float width, float height, float depth, float lineSpacing) {
    // Warna garis atap - sedikit lebih gelap dari warna atap
    glColor3f(0.5f, 0.25f, 0.0f);
    
    // Menggambar garis horizontal pada atap (sisi kanan)
    glBegin(GL_LINES);
    for (float y = 0; y <= height; y += lineSpacing) {
        // Jika masih dalam rentang atap
        if (y <= height) {
            // Hitung posisi x berdasarkan y (untuk segitiga)
            float x = (width/2) * (1 - y/height);
            
            // Garis pada sisi kanan atap
            glVertex3f(x, y, depth/2);
            glVertex3f(x, y, -depth/2);
            
            // Garis pada sisi kiri atap
            glVertex3f(-x, y, depth/2);
            glVertex3f(-x, y, -depth/2);
        }
    }
    glEnd();
}

// Fungsi untuk menggambar rumah (objek 3D non-primitif yang terdiri dari beberapa primitif)
void drawHouse() {
	// Ketebalan awal tepi
	glLineWidth(1.0f);
	
    // Warna dinding rumah - kuning
    glColor3f(1.0f, 0.8f, 0.0f);
    
    // Badan rumah (kubus)
    glPushMatrix();
    glScalef(1.0f, 0.8f, 1.5f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Warna garis tepi untuk memperjelas batas badan rumah
    glColor3f(0.5f, 0.4f, 0.0f);
    glPushMatrix();
    glScalef(1.0f, 0.8f, 1.5f);
    glutWireCube(1.001f);  // Sedikit lebih besar untuk menghindari z-fighting
    glPopMatrix();
    
    // Warna atap - cokelat
    glColor3f(0.6f, 0.3f, 0.0f); 
    
    // Atap (prisma segitiga) - dengan perpanjangan di semua sisi
    glPushMatrix();
    glTranslatef(0.0f, 0.4f, 0.0f); 
    
    // Perpanjangan atap (overhang)
    float overhangSide = 0.15f;   // Perpanjangan di sisi kiri/kanan
    float overhangFront = 0.15f;  // Perpanjangan di depan/belakang
    
    glBegin(GL_TRIANGLES);
        // Segitiga depan (dengan perpanjangan)
        glVertex3f(0.0f, 0.5f, 0.75f + overhangFront);
        glVertex3f(-0.5f - overhangSide, 0.0f, 0.75f + overhangFront);
        glVertex3f(0.5f + overhangSide, 0.0f, 0.75f + overhangFront);
        
        // Segitiga belakang (dengan perpanjangan)
        glVertex3f(0.0f, 0.5f, -0.75f - overhangFront);
        glVertex3f(-0.5f - overhangSide, 0.0f, -0.75f - overhangFront);
        glVertex3f(0.5f + overhangSide, 0.0f, -0.75f - overhangFront);
    glEnd();
    
    glBegin(GL_QUADS);
        // Sisi atap 1 (kanan) - dengan perpanjangan
        glVertex3f(0.0f, 0.5f, 0.75f + overhangFront);
        glVertex3f(0.0f, 0.5f, -0.75f - overhangFront);
        glVertex3f(0.5f + overhangSide, 0.0f, -0.75f - overhangFront);
        glVertex3f(0.5f + overhangSide, 0.0f, 0.75f + overhangFront);
        
        // Sisi atap 2 (kiri) - dengan perpanjangan
        glVertex3f(0.0f, 0.5f, 0.75f + overhangFront);
        glVertex3f(0.0f, 0.5f, -0.75f - overhangFront);
        glVertex3f(-0.5f - overhangSide, 0.0f, -0.75f - overhangFront);
        glVertex3f(-0.5f - overhangSide, 0.0f, 0.75f + overhangFront);
    glEnd();
    
    // Memberi tekstur garis pada atap
    drawRoofTexture(1.0f + 2*overhangSide, 0.5f, 1.5f + 2*overhangFront, 0.08f);
    
    // Garis tepi atap untuk memperjelas batas
    glColor3f(0.4f, 0.2f, 0.0f);  // Diubah untuk sesuai dengan atap cokelat
    glBegin(GL_LINE_LOOP);
        // Garis tepi segitiga depan
        glVertex3f(0.0f, 0.5f, 0.75f + overhangFront);
        glVertex3f(-0.5f - overhangSide, 0.0f, 0.75f + overhangFront);
        glVertex3f(0.5f + overhangSide, 0.0f, 0.75f + overhangFront);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
        // Garis tepi segitiga belakang
        glVertex3f(0.0f, 0.5f, -0.75f - overhangFront);
        glVertex3f(-0.5f - overhangSide, 0.0f, -0.75f - overhangFront);
        glVertex3f(0.5f + overhangSide, 0.0f, -0.75f - overhangFront);
    glEnd();
    
    glBegin(GL_LINES);
        // Garis puncak atap
        glVertex3f(0.0f, 0.5f, 0.75f + overhangFront);
        glVertex3f(0.0f, 0.5f, -0.75f - overhangFront);
        
        // Garis tepi tambahan
        glVertex3f(-0.5f - overhangSide, 0.0f, 0.75f + overhangFront);
        glVertex3f(-0.5f - overhangSide, 0.0f, -0.75f - overhangFront);
        
        glVertex3f(0.5f + overhangSide, 0.0f, 0.75f + overhangFront);
        glVertex3f(0.5f + overhangSide, 0.0f, -0.75f - overhangFront);
    glEnd();
    glPopMatrix();
    
    // Warna pintu - cokelat
    glColor3f(0.5f, 0.25f, 0.0f);
    
    // Pintu 
    glPushMatrix();
    glTranslatef(0.0f, -0.15f, 0.75f);
    glScalef(0.3f, 0.4f, 0.01f); 
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Garis tepi pintu
    glColor3f(0.3f, 0.15f, 0.0f);
    glPushMatrix();
    glTranslatef(0.0f, -0.15f, 0.75f);
    glScalef(0.3f, 0.4f, 0.01f);
    glutWireCube(1.01f);
    glPopMatrix();
    
    // Gagang pintu besar
	glColor3f(0.3f, 0.15f, 0.0f); // Coklat kehitaman
	glPushMatrix();
	// Posisi gagang pintu besar
	glTranslatef(0.08f, -0.15f, 0.76f);  
	// Make it a small rectangular shape
	glScalef(0.03f, 0.06f, 0.02f);
	glutSolidCube(1.0f);
	glPopMatrix();
	
	// Gagang pintu kecil
	glColor3f(0.4f, 0.2f, 0.0f);  
	glPushMatrix();
	//Posisi dari gagang pintu kecil
	glTranslatef(0.08f, -0.15f, 0.755f);  
	glScalef(0.05f, 0.08f, 0.005f);
	glutSolidCube(1.0f);
	glPopMatrix();
    
    // Warna jendela - biru 
    glColor3f(0.0f, 0.5f, 1.0f);
    
    // Jendela kiri depan
    glPushMatrix();
    glTranslatef(-0.3f, 0.1f, 0.75f);
    glScalef(0.2f, 0.2f, 0.001f);  
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Garis tepi jendela 1
    glColor3f(0.8f, 0.6f, 0.3f);
    glPushMatrix();
    glTranslatef(-0.3f, 0.1f, 0.751f);
    glLineWidth(3.0f);
    glScalef(0.2f, 0.2f, 0.001f);
    glutWireCube(1.01f);
    
    // garis untuk membagi jendela
    glBegin(GL_LINES);
        // Garis horizontal
        glVertex3f(-0.5f, 0.0f, 0.0f);
        glVertex3f(0.5f, 0.0f, 0.0f);
        // Garis vertikal
        glVertex3f(0.0f, -0.5f, 0.0f);
        glVertex3f(0.0f, 0.5f, 0.0f);
    glEnd();
    glPopMatrix();
	
    // Jendela kanan depan
    glColor3f(0.0f, 0.5f, 1.0f);
    glPushMatrix();
    glTranslatef(0.3f, 0.1f, 0.75f);
    glScalef(0.2f, 0.2f, 0.001f); 
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Garis tepi jendela depan kanan
    glColor3f(0.8f, 0.6f, 0.3f);
    glPushMatrix();
    glTranslatef(0.3f, 0.1f, 0.751f);
    glLineWidth(3.0f);
    glScalef(0.2f, 0.2f, 0.001f);
    glutWireCube(1.01f);
    
    // garis untuk membagi jendela
    glBegin(GL_LINES);
        // Garis horizontal
        glVertex3f(-0.5f, 0.0f, 0.0f);
        glVertex3f(0.5f, 0.0f, 0.0f);
        // Garis vertikal
        glVertex3f(0.0f, -0.5f, 0.0f);
        glVertex3f(0.0f, 0.5f, 0.0f);
    glEnd();
    glPopMatrix();
	
    // Jendela di sisi kiri bangunan
    glColor3f(0.0f, 0.5f, 1.0f);
    glPushMatrix();
    glTranslatef(-0.5f, 0.1f, 0.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glScalef(0.3f, 0.2f, 0.001f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Garis tepi jendela sisi kiri
    glColor3f(0.8f, 0.6f, 0.3f);
    glPushMatrix();
    glTranslatef(-0.5f, 0.1f, 0.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glLineWidth(3.0f);
    glScalef(0.3f, 0.2f, 0.001f);
    glutWireCube(1.01f);
    
    // garis horizontal dan vertikal untuk membagi jendela menjadi 4 bagian
    glBegin(GL_LINES);
        // Garis horizontal
        glVertex3f(-0.5f, 0.0f, 0.0f);
        glVertex3f(0.5f, 0.0f, 0.0f);
        // Garis vertikal
        glVertex3f(0.0f, -0.5f, 0.0f);
        glVertex3f(0.0f, 0.5f, 0.0f);
    glEnd();
    glPopMatrix();
    
    // Jendela di sisi kanan bangunan
    glColor3f(0.0f, 0.5f, 1.0f);
    glPushMatrix();
    glTranslatef(0.5f, 0.1f, 0.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glScalef(0.3f, 0.2f, 0.001f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Garis tepi jendela sisi kanan
    glColor3f(0.8f, 0.6f, 0.3f);
    glPushMatrix();
    glTranslatef(0.5f, 0.1f, 0.0f);
    glLineWidth(3.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glScalef(0.3f, 0.2f, 0.001f);
    glutWireCube(1.01f);
    
    // Tambahkan garis untuk membagi jendela
    glBegin(GL_LINES);
        // Garis horizontal
        glVertex3f(-0.5f, 0.0f, 0.0f);
        glVertex3f(0.5f, 0.0f, 0.0f);
        // Garis vertikal
        glVertex3f(0.0f, -0.5f, 0.0f);
        glVertex3f(0.0f, 0.5f, 0.0f);
    glEnd();
    glPopMatrix();
    
    // Reset ketebalan tepi
    glLineWidth(1.0f);
    
    // Warna cerobong asap - abu-abu
    glColor3f(0.5f, 0.5f, 0.5f);
    
    // Cerobong asap
    glPushMatrix();
    glTranslatef(0.25f, 0.8f, 0.25f);
    glScalef(0.15f, 0.5f, 0.15f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Garis tepi cerobong asap
    glColor3f(0.3f, 0.3f, 0.3f);
    glPushMatrix();
    glTranslatef(0.25f, 0.8f, 0.25f);
    glScalef(0.15f, 0.5f, 0.15f);
    glutWireCube(1.01f);
    glPopMatrix();
    
    // Menambahkan detail tambahan: jalur menuju rumah
    glColor3f(0.8f, 0.6f, 0.2f);  // Kuning kecokelatan
    glPushMatrix();
    glTranslatef(0.0f, -0.39f, 1.1f);
    glScalef(0.3f, 0.02f, 0.7f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Draw green grass surrounding the house
	glColor3f(0.2f, 0.8f, 0.2f);  // Rumput hijau muda
	glPushMatrix();
	glTranslatef(0.0f, -0.41f, 0.0f); 
	glScalef(4.0f, 0.02f, 4.0f); 
	glutSolidCube(1.0f);
	glPopMatrix();
	
	// Menggambar pagar putih yang mengelilingi rumah kecuali pada bagian jalur menuju rumah
	glColor3f(1.0f, 1.0f, 1.0f);  // White color for fence
	glLineWidth(2.0f);  // Slightly thicker lines for fence
	
	// Nilai untuk pagar
	float fenceHeight = 0.2f;           // Tinggi pagar
	float grassTopY = -0.4f;            // Posisi Y permukaan rumput
	float fenceY = grassTopY;           // Pagar dimulai di permukaan rumput
	float fenceDistance = 2.0f;         // Jarak pagar dari pusat
	
	// Tiang pojok (diperlukan untuk memastikan tiang di sudut)
	glPushMatrix();
	glBegin(GL_LINES);
	// Tiang di keempat sudut (ini dibuat lebih dulu)
	glVertex3f(-fenceDistance, fenceY, fenceDistance);
	glVertex3f(-fenceDistance, fenceY + fenceHeight, fenceDistance);
	    
	glVertex3f(fenceDistance, fenceY, fenceDistance);
	glVertex3f(fenceDistance, fenceY + fenceHeight, fenceDistance);
	    
	glVertex3f(-fenceDistance, fenceY, -fenceDistance);
	glVertex3f(-fenceDistance, fenceY + fenceHeight, -fenceDistance);
	    
	glVertex3f(fenceDistance, fenceY, -fenceDistance);
	glVertex3f(fenceDistance, fenceY + fenceHeight, -fenceDistance);
	glEnd();
	glPopMatrix();
	
	// Bagian depan pagar (sisi kiri jalan)
	glPushMatrix();
	glBegin(GL_LINES);
	
	
	// Tentukan posisi tiang terakhir yang valid
	float lastPostX_left = -fenceDistance;
	// Tiang vertikal bagian depan kiri
	for (float x = -fenceDistance + 0.15f; x <= -0.35f; x += 0.15f) {
	    // Hindari tiang yang melebihi batas dan tiang di sudut
	    glVertex3f(x, fenceY, fenceDistance);
	    glVertex3f(x, fenceY + fenceHeight, fenceDistance);
	    lastPostX_left = x; // Update posisi tiang terakhir
	}
	// Rail horizontal bawah sisi depan kiri
	glVertex3f(-fenceDistance, fenceY + 0.02f, fenceDistance);
	glVertex3f(-0.35f, fenceY + 0.02f, fenceDistance);
	// Rail horizontal atas sisi depan kiri
	glVertex3f(-fenceDistance, fenceY + fenceHeight, fenceDistance);
	glVertex3f(-0.35f, fenceY + fenceHeight, fenceDistance);
	glEnd();
	glPopMatrix();
	
	// Bagian depan pagar (sisi kanan jalan)
	glPushMatrix();
	glBegin(GL_LINES);
	// Tentukan posisi tiang terakhir yang valid
	float lastPostX_right = fenceDistance;
	// Tiang vertikal bagian depan kanan
	for (float x = 0.35f; x < fenceDistance; x += 0.15f) {
	    // Hindari tiang di sudut (sudah dibuat)
	    glVertex3f(x, fenceY, fenceDistance);
	    glVertex3f(x, fenceY + fenceHeight, fenceDistance);
	    lastPostX_right = x; // Update posisi tiang terakhir
	}
	// Pagar horizontal bawah sisi depan kanan
	glVertex3f(0.35f, fenceY + 0.02f, fenceDistance);
	glVertex3f(fenceDistance, fenceY + 0.02f, fenceDistance);
	// Pagar horizontal atas sisi depan kanan
	glVertex3f(0.35f, fenceY + fenceHeight, fenceDistance);
	glVertex3f(fenceDistance, fenceY + fenceHeight, fenceDistance);
	glEnd();
	glPopMatrix();
	
	// Pagar sisi kanan
	glPushMatrix();
	glBegin(GL_LINES);
	// Tiang vertikal sisi kanan
	for (float z = -fenceDistance + 0.15f; z < fenceDistance; z += 0.15f) {
	    // Hindari tiang di sudut (sudah dibuat)
	    glVertex3f(fenceDistance, fenceY, z);
	    glVertex3f(fenceDistance, fenceY + fenceHeight, z);
	}
	// Pagar horizontal bawah sisi kanan
	glVertex3f(fenceDistance, fenceY + 0.02f, -fenceDistance);
	glVertex3f(fenceDistance, fenceY + 0.02f, fenceDistance);
	// Pagar horizontal atas sisi kanan
	glVertex3f(fenceDistance, fenceY + fenceHeight, -fenceDistance);
	glVertex3f(fenceDistance, fenceY + fenceHeight, fenceDistance);
	glEnd();
	glPopMatrix();
	
	// Pagar sisi kiri
	glPushMatrix();
	glBegin(GL_LINES);
	// Tiang vertikal sisi kiri
	for (float z = -fenceDistance + 0.15f; z < fenceDistance; z += 0.15f) {
	    // Hindari tiang di sudut
	    glVertex3f(-fenceDistance, fenceY, z);
	    glVertex3f(-fenceDistance, fenceY + fenceHeight, z);
	}
	// Pagar horizontal bawah sisi kiri
	glVertex3f(-fenceDistance, fenceY + 0.02f, -fenceDistance);
	glVertex3f(-fenceDistance, fenceY + 0.02f, fenceDistance);
	// Pagar horizontal atas sisi kiri
	glVertex3f(-fenceDistance, fenceY + fenceHeight, -fenceDistance);
	glVertex3f(-fenceDistance, fenceY + fenceHeight, fenceDistance);
	glEnd();
	glPopMatrix();
	
	// Pagar sisi belakang
	glPushMatrix();
	glBegin(GL_LINES);
	// Tiang vertikal sisi belakang
	for (float x = -fenceDistance + 0.15f; x < fenceDistance; x += 0.15f) {
	    // Hindari tiang di sudut
	    glVertex3f(x, fenceY, -fenceDistance);
	    glVertex3f(x, fenceY + fenceHeight, -fenceDistance);
	}
	// Pagar horizontal bawah sisi belakang
	glVertex3f(-fenceDistance, fenceY + 0.02f, -fenceDistance);
	glVertex3f(fenceDistance, fenceY + 0.02f, -fenceDistance);
	// Pagar horizontal atas sisi belakang
	glVertex3f(-fenceDistance, fenceY + fenceHeight, -fenceDistance);
	glVertex3f(fenceDistance, fenceY + fenceHeight, -fenceDistance);
	glEnd();
	glPopMatrix();
	
	// Reset line width
	glLineWidth(1.0f);

}

// Fungsi untuk mengatur proyeksi berdasarkan mode yang dipilih
void setProjection() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    GLfloat aspect = (GLfloat)glutGet(GLUT_WINDOW_WIDTH) / (GLfloat)glutGet(GLUT_WINDOW_HEIGHT);
    
    switch (projectionMode) {
        case 0: // Plan view (Orthographic - atas)
            glOrtho(-3.0*aspect, 3.0*aspect, -3.0, 3.0, -15.0, 15.0);
            break;
        case 1: // Front view (Orthographic - depan)
            glOrtho(-2.0*aspect, 2.0*aspect, -2.0, 2.0, -10.0, 10.0);
            break;
        case 2: // Side view (Orthographic - samping)
            glOrtho(-2.0*aspect, 2.0*aspect, -2.0, 2.0, -10.0, 10.0);
            break;
        case 3: // Isometric (Orthographic)
            glOrtho(-2.0*aspect, 2.0*aspect, -2.0, 2.0, -10.0, 10.0);
            break;
        case 4: // Dimetric (Orthographic)
            glOrtho(-2.0*aspect, 2.0*aspect, -2.0, 2.0, -10.0, 10.0);
            break;
        case 5: // Trimetric (Orthographic)
            glOrtho(-2.0*aspect, 2.0*aspect, -2.0, 2.0, -10.0, 10.0);
            break;
        case 6: // 1-point perspective
            gluPerspective(45.0f, aspect, 0.1f, 100.0f);
            break;
        case 7: // 2-point perspective
            gluPerspective(45.0f, aspect, 0.1f, 100.0f);
            break;
        case 8: // 3-point perspective
            gluPerspective(45.0f, aspect, 0.1f, 100.0f);
            break;
    }
    
    glMatrixMode(GL_MODELVIEW);
}

// Fungsi untuk mengatur posisi dan orientasi kamera berdasarkan mode proyeksi
void setCamera() {
    glLoadIdentity();
    
    switch (projectionMode) {
        case 0: // Plan view (Orthographic - atas)
            gluLookAt(0.0f, 6.0f, 0.0f,  // posisi kamera
                      0.0f, 0.0f, 0.0f,  // titik yang dilihat
                      0.0f, 0.0f, -1.0f); // vektor up
            break;
        case 1: // Front view (Orthographic - depan)
            gluLookAt(0.0f, 0.0f, 5.0f,  // posisi kamera
                      0.0f, 0.0f, 0.0f,  // titik yang dilihat
                      0.0f, 1.0f, 0.0f); // vektor up
            break;
        case 2: // Side view (Orthographic - samping)
            gluLookAt(8.0f, 0.0f, 0.0f,  // posisi kamera
                      0.0f, 0.0f, 0.0f,  // titik yang dilihat
                      0.0f, 1.0f, 0.0f); // vektor up
            break;
        case 3: // Isometric (Orthographic)
            gluLookAt(3.0f, 3.0f, 3.0f,  // posisi kamera
                      0.0f, 0.0f, 0.0f,  // titik yang dilihat
                      0.0f, 1.0f, 0.0f); // vektor up
            break;
        case 4: // Dimetric (Orthographic)
            gluLookAt(5.0f, 2.0f, 5.0f,  // posisi kamera
                      0.0f, 0.0f, 0.0f,  // titik yang dilihat
                      0.0f, 1.0f, 0.0f); // vektor up
            break;
        case 5: // Trimetric (Orthographic)
            gluLookAt(4.0f, 3.0f, 2.5f,  // posisi kamera
                      0.0f, 0.0f, 0.0f,  // titik yang dilihat
                      0.0f, 1.0f, 0.0f); // vektor up
            break;
        case 6: // 1-point perspective
            gluLookAt(0.0f, 0.0f, 7.0f,  // posisi kamera
                      0.0f, 0.0f, 0.0f,  // titik yang dilihat
                      0.0f, 1.0f, 0.0f); // vektor up
            break;
        case 7: // 2-point perspective
            gluLookAt(5.0f, 0.0f, 5.0f,  // posisi kamera
                      0.0f, 0.0f, 0.0f,  // titik yang dilihat
                      0.0f, 1.0f, 0.0f); // vektor up
            break;
        case 8: // 3-point perspective
            gluLookAt(5.0f, 3.0f, 5.0f,  // posisi kamera
                      0.0f, 0.0f, 0.0f,  // titik yang dilihat
                      0.0f, 1.0f, 0.0f); // vektor up
            break;
    }
    
    // Menerapkan rotasi untuk semua mode
    glRotatef(rotateX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotateY, 0.0f, 1.0f, 0.0f);
}

// Fungsi untuk menampilkan label proyeksi saat ini
void drawProjectionLabel() {
    const char* labels[] = {
        "Plan View (Orthographic)",
        "Front View (Orthographic)",
        "Side View (Orthographic)",
        "Isometric (Orthographic)",
        "Dimetric (Orthographic)",
        "Trimetric (Orthographic)",
        "1-Point Perspective",
        "2-Point Perspective",
        "3-Point Perspective"
    };
    
    // Menyimpan matriks proyeksi dan modelview saat ini
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT), -1, 1);
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    // Mengatur posisi teks (pojok kiri atas)
    glRasterPos2i(10, glutGet(GLUT_WINDOW_HEIGHT) - 20);
    
    // Menampilkan teks
    const char* label = labels[projectionMode];
    for (int i = 0; label[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, label[i]);
    }
    
    // Memulihkan matriks
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

// Fungsi untuk menggambar
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    setProjection();
    setCamera();
    
    // Menggambar grid untuk referensi
    glPushMatrix();
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_LINES);
    for (float i = -5.0f; i <= 5.0f; i += 0.5f) {
        glVertex3f(i, -0.5f, -5.0f);
        glVertex3f(i, -0.5f, 5.0f);
        glVertex3f(-5.0f, -0.5f, i);
        glVertex3f(5.0f, -0.5f, i);
    }
    glEnd();
    glPopMatrix();
    
    glDisable(GL_LIGHTING);
    // Menggambar objek rumah
    drawHouse();
    glEnable(GL_LIGHTING);
    
    // Menampilkan label proyeksi
    drawProjectionLabel();
    
    glutSwapBuffers();
}

// Fungsi untuk mengatur ukuran jendela
void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    setProjection();
}

// Fungsi untuk menangani input keyboard
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case '0': case '1': case '2': case '3': case '4': 
        case '5': case '6': case '7': case '8':
            // Mengubah mode proyeksi
            projectionMode = key - '0';
            break;
        case 'q': case 'Q': case 27: // ESC key
            // Keluar dari program
            exit(0);
            break;
        case 'r':
            // Reset rotasi
            rotateX = 0.0f;
            rotateY = 0.0f;
            break;
    }
    
    glutPostRedisplay();
}

// Fungsi untuk menangani tombol khusus
void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            rotateX += 5.0f;
            break;
        case GLUT_KEY_DOWN:
            rotateX -= 5.0f;
            break;
        case GLUT_KEY_RIGHT:
            rotateY += 5.0f;
            break;
        case GLUT_KEY_LEFT:
            rotateY -= 5.0f;
            break;
    }
    
    glutPostRedisplay();
}

// Fungsi untuk inisialisasi OpenGL
void init() {
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    
    // Mengaktifkan pencahayaan
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    // Mengaktifkan ketebalan
    glEnable(GL_LINE_SMOOTH);
    
    // Mengatur properti cahaya
    GLfloat light_position[] = { 1.0f, 1.0f, 1.0f, 0.0f };
    GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    
    // Mengatur properti material
    GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
    GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat mat_shininess[] = { 100.0f };
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    
    // Mengatur model shading
    glShadeModel(GL_SMOOTH);
}

// Fungsi utama
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("MOHAMAD SOLKHAN NAWAWI - 24060123120020");
    
    init();
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    
    printf("Kontrol:\n");
    printf("0-8: Mengubah mode proyeksi\n");
    printf("Tombol Panah: Memutar objek\n");
    printf("r: Reset rotasi\n");
    printf("q/ESC: Keluar\n");
    
    glutMainLoop();
    
    return 0;
}
