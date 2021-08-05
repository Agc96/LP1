"""
Este script permite cambiar los nombres de las carpetas de los trabajos subidos
por los alumnos a través de Paideia (Moodle), en vez del nombre generado por la
plataforma, a un formato ordenado de la forma [código] - [nombre].

Modo de uso: {python} {module} <alumnos.csv> <directorio>

Ejemplo: {python} {module} H101.csv INF101\\2020-1\\Lab1\\H101

* <alumnos.csv> es un archivo CSV con los datos principales de los alumnos.
  El archivo debe contener como mínimo el código y nombre de cada alumno:

  Alumno,Nombre,E-mail
  20201234,"PEREZ FLORES, JUAN JESUS",juan.perez@mail.com
  20205678,"FLORES DEL CAMPO, ZACARIAS",zflores@mail.com

* <directorio> es un directorio que contiene las carpetas de los trabajos de
  cada alumno. Las carpetas contenidas en el directorio deben tener nombres
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

ERROR_CSV_KEY = """
Error: no se encontró la columna {column} en el archivo CSV.
Asegúrese de que dicha columna se encuentre en la cabecera del archivo CSV, y
de que el archivo CSV se haya guardado con el formato de codificación de
caracteres estándar de Windows (Windows-1252), no UTF-8.
"""

def main():
	# Mostrar uso si es que hacen falta argumentos
	if len(sys.argv) < 3:
		usage()
	# Obtener la lista de directorios y la ubicación actual
	parent_dir = os.path.join(os.getcwd(), sys.argv[2])
	directories = os.listdir(parent_dir)
	# Leer el archivo CSV
	with open(sys.argv[1], 'r', newline='') as file:
		students = csv.DictReader(file)
		for student in students:
			# Buscar el nombre del alumno en los directorios
			for directory in directories:
				# Algunos nombres de los alumnos en Paideia tienen un espacio
				# de más, así que hay que tener en cuenta ello al buscar
				dir_compare = directory.replace(' ,', ',')
				if dir_compare.startswith(student['Nombre']):
					rename(student, parent_dir, directory)
					break
	# Confirmar que el programa terminó correctamente
	print('Carpetas renombradas correctamente.')

def usage():
	# Imprimir modo de uso
	python = os.path.basename(sys.executable)
	sys.stderr.write(__doc__.format(python=python, module=sys.argv[0]))
	# Indicar que el programa no terminó correctamente
	sys.exit(1)

def rename(student, parent_dir, directory):
	try:
		# Formar los nombres de los directorios
		old_dirname = os.path.join(parent_dir, directory)
		new_format = student['Alumno'] + ' - ' + student['Nombre']
		new_dirname = os.path.join(parent_dir, new_format)
		# Renombrar la carpeta
		os.rename(old_dirname, new_dirname)
	except KeyError as ex:
		sys.stderr.write(ERROR_CSV_KEY.format(column=ex))
		sys.exit(1)

if __name__ == '__main__':
	main()
