"""
Este script realiza varios procesos que facilitan la corrección de los trabajos
subidos por los alumnos a través de la plataforma Paideia (la cual está basada
en el LMS "Moodle"). Se realizan las siguientes actividades, en este orden:

- Cambiar los nombres de las carpetas de los alumnos, de aquel generado por la
  plataforma, a un formato ordenado de la forma [código] - [nombre].

- Descomprimir los archivos ZIP subidos por los alumnos.

- Verificar si existen archivos de interés contenidos en dichas carpetas, cuya
  última fecha de modificación esté fuera del rango correspondiente para
  resolver el laboratorio.

- Verificar si existen comentarios autogenerados en los archivos de interés
  contenidos en dichas carpetas, que denoten que se han creado fuera del rango
  de fechas/horas correspondiente para resolver el laboratorio.

Modo de uso: {python} {module} <alumnos.csv> <directorio> <fecha> <hora_inicio>
             <hora_fin> [reporte.csv]

Ejemplo: {python} {module} H101.csv INF101\\2020-1\\Lab1\\H101

* <alumnos.csv> es un archivo CSV con los datos principales de los alumnos.
  El archivo debe contener como mínimo el código y nombre de cada alumno:

  Alumno,Nombre,E-mail
  20201234,"PEREZ FLORES, JUAN JESUS",juan.perez@mail.com
  20205678,"FLORES DEL CAMPO, ZACARIAS",zacarias.flores@mail.com

* <directorio> es un directorio padre que contiene las carpetas de los trabajos
  de cada alumno. Las carpetas contenidas en el directorio deben tener nombres
  similares al siguiente:

  FLORES DEL CAMPO, ZACARIAS_2345678_assignsubmission_file_
  PEREZ FLORES, JUAN JESUS_1234567_assignsubmission_file_

* Las carpetas serán cambiadas de nombre al siguiente formato:

  20201234 - PEREZ FLORES, JUAN JESUS
  20205678 - FLORES DEL CAMPO, ZACARIAS
"""

import csv
import os
import sys

ERROR_COLUMNA_CSV = """
Error: no se encontró la columna {column} en el archivo CSV.
Asegúrese de que dicha columna se encuentre en la cabecera del archivo CSV, y
de que el archivo CSV se haya guardado usando la opción "CSV (delimitado por
comas)" en Excel o algún programa similar (no usar la opción CSV UTF-8).
"""

def main():
  # Mostrar modo de uso si es que hacen falta argumentos
  if len(sys.argv) < 3:
    usage()
  # Obtener la lista de directorios y la ubicación actual
  carpetas = os.listdir(sys.argv[2])
  # Leer el archivo CSV
  with open(sys.argv[1], 'r', newline='') as archivo:
    alumnos = csv.DictReader(archivo)
    for alumno in alumnos:
      try:
        # Buscar el nombre del alumno en los directorios
        carpeta = buscar_carpeta(carpetas, alumno)
        if carpeta:
          nombre_completo = alumno['Alumno'] + ' - ' + alumno['Nombre']
          ruta = renombrar_carpeta(nombre_completo, sys.argv[2], carpeta)
          # TODO: Juntar todos los scripts en uno solo
      except KeyError as ex:
        sys.stderr.write(ERROR_COLUMNA_CSV.format(column=ex))
        sys.exit(1)
  # Confirmar que el programa terminó correctamente
  print('Carpetas renombradas correctamente.')

def usage():
  # Imprimir modo de uso
  python = os.path.basename(sys.executable)
  try:
    os.system('more leeme.txt')
  except:
    sys.stderr.write(__doc__.format(python=python, module=sys.argv[0]))
  # Indicar que el programa no terminó correctamente
  sys.exit(1)

def buscar_carpeta(carpetas, alumno):
  for carpeta in carpetas:
    if carpeta.startswith(alumno['Nombre']):
      return carpeta
    # Algunos nombres de los alumnos en Paideia tienen un espacio
    # de más, así que hay que tener en cuenta ello al buscar
    if carpeta.replace(' ,', ',').startswith(alumno['Nombre']):
      return carpeta
  return None

def renombrar_carpeta(nombre_completo, directorio_padre, carpeta):
  ruta_antigua = os.path.join(directorio_padre, carpeta)
  ruta_nueva = os.path.join(directorio_padre, nombre_completo)
  os.rename(ruta_antigua, ruta_nueva)
  return ruta_nueva

if __name__ == '__main__':
  main()
