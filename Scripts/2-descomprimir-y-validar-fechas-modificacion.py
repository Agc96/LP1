"""
Este script permite descomprimir las carpetas comprimidas .zip que suben los
alumnos, y verificar si existen archivos contenidos en dichas carpetas que se
han modificado fuera del rango de fechas y horas correspondiente para resolver
el laboratorio, y por lo tanto son sospechas de plagio.

Modo de uso: {python} {module} <directorio> <fecha> <hora_inicio> <hora_fin>
             [reporte.csv]

Ejemplo: {python} {module} INF101\\2020-1\\Lab1\\H101 01/06/2020 8:00 10:00

* <directorio> es un directorio que contiene las carpetas de los trabajos de
  cada alumno.
* <fecha> es una cadena con una fecha en el formato dd/mm/aaaa.
* <hora_inicio> y <hora_fin> son cadenas con horas en el formato hh24:mm.
* [reporte.csv] es el nombre del archivo CSV que se generará como reporte de
  los alumnos que contienen archivos sospechosos. Este parámetro es opcional,
  de no colocarse se usará el nombre por defecto ({default}).
"""

import csv
import os
import sys
import zipfile
from datetime import datetime

DEFAULT_REPORT_FILENAME = 'Incidencias-Fechas-Modificacion.csv'
DEFAULT_DATE_FORMAT_ARGUMENT = '%d/%m/%Y %H:%M'
DEFAULT_DATE_FORMAT_REPORT = '%d/%m/%Y %H:%M:%S'

def main():
	if len(sys.argv) < 5:
		usage()
	# Preparar los datos
	min_date = parse_date(sys.argv[2], sys.argv[3])
	max_date = parse_date(sys.argv[2], sys.argv[4])
	if min_date > max_date:
		print('Error: el orden de las fechas no es correcto.')
		sys.exit(1)
	# Escanear cada carpeta y subcarpeta del directorio
	incidents = []
	for root, dirs, entries in os.walk(sys.argv[1]):
		for entry in entries:
			# Verificar si son archivos ZIP
			if entry.endswith('.zip'):
				path = os.path.join(root, entry)
				with zipfile.ZipFile(path) as file:
					verify(file, incidents, path, min_date, max_date)
					extract(file, root)
	# Guardar datos en el archivo, de ser necesario
	if len(incidents) > 0:
		save(incidents)
	else:
		print('No se encontraron incidencias.')

def usage():
	# Imprimir modo de uso
	print(__doc__.format(python=os.path.basename(sys.executable),
						 module=sys.argv[0],
						 default=DEFAULT_REPORT_FILENAME))
	# Indicar que el programa no terminó correctamente
	sys.exit(1)

def parse_date(date, time):
	return datetime.strptime(date + ' ' + time, DEFAULT_DATE_FORMAT_ARGUMENT)

def verify(file, incidents, student, min_date, max_date):
	# Verificar que las fechas de modificación estén en el rango
	for metadata in file.infolist():
		date = datetime(*metadata.date_time)
		if (date < min_date) or (date > max_date):
			# Colocar en el reporte la incidencia
			date_str = datetime.strftime(date, DEFAULT_DATE_FORMAT_REPORT)
			incidents.append([student, metadata.filename, date_str])

def extract(file, path):
	print('Extrayendo {} en {}...'.format(file.filename, path))
	file.extractall(path)

def save(students):
	# Obtener el nombre del archivo
	filename = sys.argv[5] if len(sys.argv) > 5 else DEFAULT_REPORT_FILENAME
	# Crear el archivo y guardar los datos
	with open(filename, 'w', newline='') as file:
		writer = csv.writer(file)
		writer.writerow(['Alumno', 'Archivo', 'Fecha'])
		writer.writerows(students)
	# Imprimir mensaje de confirmación
	print('Se encontraron varias incidencias.')
	print('Revise el archivo', filename, 'para más detalles.')

if __name__ == '__main__':
	main()
