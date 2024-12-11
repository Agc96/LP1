/*
 * Archivo: Preg3_PunterosGenericos.h
 * Autor:   Anthony Gutiérrez
 * Fecha:   21 de mayo de 2023, 06:52 PM
 */

#ifndef PREG3_PUNTEROSGENERICOS_H
#define PREG3_PUNTEROSGENERICOS_H

enum IndiceAlumnoVeces{COD_ALUMNO_AV, CURSOS_TOTAL, CURSOS_APROB, CURSOS_1RA,
                       CURSOS_2DA, CURSOS_3RA, CURSOS_LISTA};
enum IndiceAlumnoCurso{COD_CURSO_AV, SEMESTRE, NOTA};

// Pregunta 3a
void CargaCursos(int *, void *&, const char *);
void inicializarAlumnoVeces(int *, void *&);
void *crearPunteroGenericoCurso(char *, int, int);
int buscarAlumnoCod(int *, int);
void agregarCursoEnAlumno(void *, int, void *);
void asignarEspaciosExactosAListaCursos(void *);

// Pregunta 3b
void ActualizaVeces(void *);
bool cursoYaProcesado(void **, int, char *);
void buscarUltimaNotaCurso(void **, int, char *, int &, int &);
void actualizarEstadisticas(void **, int, int);

#endif /* PREG3_PUNTEROSGENERICOS_H */
