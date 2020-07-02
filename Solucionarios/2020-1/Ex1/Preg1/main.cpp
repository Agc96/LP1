/* 
 * Archivo: main.cpp
 * Autor:   Anthony Gutiérrez
 */

int main() {
    char ***cursos, **profesores;
    int *codProfesores;
    leerDatos(cursos, codProfesores, profesores);
    imprimirDatos(cursos, codProfesores, profesores);
    return 0;
}
