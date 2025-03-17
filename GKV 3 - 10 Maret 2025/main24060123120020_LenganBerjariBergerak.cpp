#include <GL/glut.h>  
// Menyertakan pustaka OpenGL GLUT untuk membuat jendela dan menggambar grafik.

static int bahu = 0, siku = 0, pergelangan = 0;  
static int ibu_jari = 0, telunjuk = 0, jari_tengah = 0, jari_manis = 0, kelingking = 0;  
// Variabel global untuk menyimpan sudut rotasi bagian-bagian lengan dan jari.

void init(void) {  
    glClearColor(0.0, 0.0, 0.0, 0.0); // Mengatur warna latar belakang menjadi hitam.
    glShadeModel(GL_FLAT); // Menggunakan model shading datar.
}

void display(void) {  
    glClear(GL_COLOR_BUFFER_BIT); // Membersihkan buffer warna.
    glPushMatrix(); // Menyimpan matriks transformasi saat ini.

    // Menggambar bahu
    glTranslatef(-1.0, 0.0, 0.0); // Menggeser ke kiri.
    glRotatef((GLfloat) bahu, 0.0, 0.0, 1.0); // Memutar bahu di sumbu Z.
    glTranslatef(1.0, 0.0, 0.0); // Mengembalikan posisi ke tengah.
    glPushMatrix(); 
    glScalef(2.0, 0.4, 1.0); // Mengubah ukuran bahu.
    glutWireCube(1.0); // Menggambar bahu sebagai kubus kawat.
    glPopMatrix(); 

    // Menggambar siku
    glTranslatef(1.0, 0.0, 0.0); // Menggeser ke kanan.
    glRotatef((GLfloat) siku, 0.0, 0.0, 1.0); // Memutar siku.
    glTranslatef(1.0, 0.0, 0.0); // Menggeser kembali.
    glPushMatrix(); 
    glScalef(2.0, 0.4, 1.0); // Mengubah ukuran lengan bawah.
    glutWireCube(1.0); // Menggambar siku sebagai kubus kawat.
    glPopMatrix();

    // Menggambar pergelangan tangan
    glTranslatef(1.0, 0.0, 0.0); 
    glRotatef((GLfloat) pergelangan, 0.0, 0.0, 1.0); 
    glTranslatef(0.25, 0.0, 0.0); 
    glPushMatrix(); 
    glScalef(0.5, 0.3, 0.7); // Mengubah ukuran telapak tangan.
    glutWireCube(1.0); 
    glPopMatrix();

    // Menggambar jari-jari
    int jari_angles[] = {ibu_jari, telunjuk, jari_tengah, jari_manis, kelingking};  
    float posisi_jari[] = {0.3, 0.15, 0.0, -0.15, -0.3};  
    for (int i = 0; i < 5; i++) {  
        glPushMatrix();  
        glTranslatef(0.5, posisi_jari[i], 0.0); // Menyesuaikan posisi jari.
        glRotatef((GLfloat) jari_angles[i], 0.0, 0.0, 1.0); // Memutar jari.
        glTranslatef(0.2, 0.0, 0.0);  
        glPushMatrix();  
        glScalef(0.4, 0.1, 0.1); // Mengubah ukuran jari.
        glutWireCube(1.0);  
        glPopMatrix();  
        glPopMatrix();  
    }
    
    glPopMatrix(); // Mengembalikan transformasi awal.
    glutSwapBuffers(); // Menampilkan buffer yang telah digambar.
}

void reshape(int w, int h) {  
    glViewport(0, 0, (GLsizei) w, (GLsizei) h); // Menyesuaikan viewport dengan ukuran jendela.
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();  
    gluPerspective(65.0, (GLfloat) w / (GLfloat) h, 1.0, 20.0); // Mengatur perspektif tampilan.
    glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity();  
    glTranslatef(0.0, 0.0, -5.0); // Menggeser tampilan ke belakang agar objek terlihat.
}

void keyboard(unsigned char key, int x, int y) {  
    switch (key) {  
        case 'b': bahu = (bahu + 5) % 360; break; // Memutar bahu ke depan.
        case 'B': bahu = (bahu - 5) % 360; break; // Memutar bahu ke belakang.
        case 's': siku = (siku + 5) % 360; break; // Memutar siku ke depan.
        case 'S': siku = (siku - 5) % 360; break; // Memutar siku ke belakang.
        case 'p': pergelangan = (pergelangan + 5) % 360; break; // Memutar pergelangan ke depan.
        case 'P': pergelangan = (pergelangan - 5) % 360; break; // Memutar pergelangan ke belakang.
        case '1': ibu_jari = (ibu_jari + 5) % 360; break; // Menggerakkan ibu jari.
        case '!': ibu_jari = (ibu_jari - 5) % 360; break;
        case '2': telunjuk = (telunjuk + 5) % 360; break; // Menggerakkan telunjuk.
        case '@': telunjuk = (telunjuk - 5) % 360; break;
        case '3': jari_tengah = (jari_tengah + 5) % 360; break; // Menggerakkan jari tengah.
        case '#': jari_tengah = (jari_tengah - 5) % 360; break;
        case '4': jari_manis = (jari_manis + 5) % 360; break; // Menggerakkan jari manis.
        case '$': jari_manis = (jari_manis - 5) % 360; break;
        case '5': kelingking = (kelingking + 5) % 360; break; // Menggerakkan kelingking.
        case '%': kelingking = (kelingking - 5) % 360; break;
        case 27: exit(0); // Keluar dari program saat tombol ESC ditekan.
    }
    glutPostRedisplay(); // Memperbarui tampilan setelah ada perubahan.
}

int main(int argc, char** argv) {  
    glutInit(&argc, argv); // Inisialisasi GLUT.
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Menggunakan mode tampilan ganda dan RGB.
    glutInitWindowSize(700, 600); // Menentukan ukuran jendela.
    glutInitWindowPosition(100, 100); // Menentukan posisi jendela.
    glutCreateWindow("24060123120020_Lengan Robot dengan Telapak dan Jari"); // Membuat jendela dengan judul.
    init(); // Memanggil fungsi inisialisasi.
    glutDisplayFunc(display); // Menetapkan fungsi display untuk menggambar objek.
    glutReshapeFunc(reshape); // Menetapkan fungsi reshape untuk menangani perubahan ukuran jendela.
    glutKeyboardFunc(keyboard); // Menetapkan fungsi keyboard untuk menangani input.
    glutMainLoop(); // Memulai loop utama GLUT.
    return 0;
}

