"""
Este script permite verificar si existen comentarios en los archivos ubicados
en las carpetas de trabajo de los alumnos, que permitan observar si se han
modificado fuera del rango de fechas y horas correspondiente para resolver el
laboratorio, y por lo tanto son sospechas de plagio.

Modo de uso: {python} {module} <directorio> <fecha> <hora_inicio> <hora_fin>
             [reporte.csv]

* <directorio> es un directorio que contiene las carpetas de los trabajos
  de cada alumno.
* <fecha> es una cadena con una fecha en el formato dd/mm/aaaa.
* <hora_inicio> y <hora_fin> son cadenas con horas en el formato hh24:mm.
* [reporte.csv] es el nombre del archivo CSV que se generará como reporte de
  los alumnos que contienen archivos sospechosos. Este parámetro es opcional,
  de no colocarse se usará el nombre por defecto ({default}).

Ejemplo: {python} {module} INF101\\2020-1\\L1\\H101 01/07/2020 8:00 10:00
"""

import csv
import locale
import os
import re
import sys
from datetime import datetime, timedelta

DEFAULT_FILENAME = 'Incidencias-Fechas-Archivos.csv'
DATE_FORMAT_ARGS = '%d/%m/%Y %H:%M'
DATE_FORMAT_FILE_ES = '%d de %B de %Y, %H:%M'
DATE_FORMAT_FILE_EN = '%B %d, %Y, %H:%M'

def main():
	if len(sys.argv) < 5:
		usage()
	# Preparar los argumentos
	min_date = parse_date(sys.argv[2], sys.argv[3])
	max_date = parse_date(sys.argv[2], sys.argv[4])
	if min_date > max_date:
		print('Error: el orden de las fechas no es correcto.')
		sys.exit(1)
	# Escanear cada carpeta y subcarpeta del directorio
	incidents = []
	for root, dirs, entries in os.walk(sys.argv[1]):
		for entry in entries:
			# Verificar que no sean archivos generados por NetBeans
			if strincludes(root, ['nbproject', 'build', 'dist']):
				continue
			# Verificar que sí sean archivos de C++
			if strendswith(entry, ['.cpp', '.h', '.hpp', '.cc']):
				verify(incidents, root, entry, min_date, max_date)
	# Guardar datos en el archivo, de ser necesario
	if len(incidents) > 0:
		save(incidents)
	else:
		print('No se encontraron incidencias.')

def parse_date(date, time):
	return datetime.strptime(date + ' ' + time, DATE_FORMAT_ARGS)

def usage():
	# Imprimir modo de uso
	print(__doc__.format(python=os.path.basename(sys.executable),
						 module=sys.argv[0],
						 default=DEFAULT_FILENAME))
	# Indicar que el programa no terminó correctamente
	sys.exit(1)

def verify(incidents, root, entry, min_date, max_date):
	path = os.path.join(root, entry)
	with open(path, 'r', encoding='UTF-8') as file:
		lines = file.readlines()
		for line in lines:
			# Verificar si hay una línea con la fecha de creación
			if 'Created on' in line:
				date = convert_date(line, path)
				# Verificar que las fechas de modificación estén en el rango
				if date is None:
					incidents.append([path, 'Fecha no válida'])
				elif (date < min_date) or (date > max_date):
					incidents.append([path, date.strftime(DATE_FORMAT_ARGS)])

def convert_date(string, path):
	# Quitar partes innecesarias de la cadena, y quitar espacios en blanco
	datestr = re.sub(r'Created on|\*|/|AM|PM|a\.m\.|p\.m\.', '', string).strip()
	# Convertir cadena a un objeto fecha
	date = None
	try:
		locale.setlocale(locale.LC_ALL, 'es_PE') # español de Perú
		date = datetime.strptime(datestr, DATE_FORMAT_FILE_ES)
	except ValueError:
		try:
			locale.setlocale(locale.LC_ALL, 'en_US') # inglés de EE.UU.
			date = datetime.strptime(datestr, DATE_FORMAT_FILE_EN)
		except ValueError:
			print('Ocurrió un error al procesar la fecha del archivo {0}.'.format(path))
	# Verificar manualmente si es PM, ya que la localización no soporta AM/PM
	if date is not None and strincludes(string, ['PM', 'p.m.']):
		date += timedelta(hours=12)
	return date

def save(incidents):
	# Obtener el nombre del archivo
	filename = sys.argv[5] if len(sys.argv) > 5 else DEFAULT_FILENAME
	# Crear el archivo y guardar los datos
	with open(filename, 'w', newline='') as file:
		writer = csv.writer(file)
		writer.writerow(['Archivo', 'Fecha'])
		writer.writerows(incidents)
	# Imprimir mensaje de confirmación
	print('Se encontraron varias incidencias.')
	print('Revise el archivo "{0}" para más detalles.'.format(filename))

def strincludes(string, substrings):
	for substr in substrings:
		if substr in string:
			return True
	return False

def strendswith(string, substrings):
	for substr in substrings:
		if string.endswith(substr):
			return True
	return False

if __name__ == '__main__':
	main()
