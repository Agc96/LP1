import csv
import os
import re

matches = [
	('Infraccion.h', [
		r'int +codigo',
		r'char *\* *gravedad',
		r'double +multa',
		r'virtual +void'
	]),
	('Infraccion.cpp', [
		r'#include *<cstring>',
		r'gravedad *= *(nullptr|NULL)',
		r'delete(.*?) *gravedad',
		r'strcpy\((.*?),(.*?)\)',
		r'strlen\((.*?)\)']),
	('Falta.h', [
		r'int +licencia',
		r'int +fecha',
		r'char *\* *placa'
	]),
	('Falta.cpp', [
		r'#include *<cstring>',
		r'placa *= *(nullptr|NULL)',
		r'delete(.*?) *placa',
		r'strcpy\((.*?),(.*?)\)',
		r'strlen\((.*?)\)'
	]),
	('Leve.h', [
		r'#include *"Infraccion.h"',
		r'public +Infraccion',
		r'double +descuento'
	]),
	('Grave.h', [
		r'#include *"Infraccion.h"',
		r'public +Infraccion',
		r'double +descuento',
		r'int +puntos'
	]),
	('MuyGrave.h', [
		r'#include *"Infraccion.h"',
		r'public +Infraccion',
		r'int +puntos',
		r'int +meses'
	]),
	('NFalta.h', [
		r'#include *"Infraccion.h"',
		r'#include *"Falta.h"',
		r'#include *"LFalta.h"',
		r'Infraccion *\* *pfalta',
		r'Falta +dfalta',
		r'friend +class +LFalta'
	]),
	('NFalta.cpp', [
		r'pfalta *= *(nullptr|NULL)',
		r'sig *= *(nullptr|NULL)'
	]),
	('LFalta.h', [
		r'#include *"NFalta.h"',
		r'NFalta *\* *lini',
		r'NFalta *\* *lfin',
		r'void +leer\((.*?)char *\* *(.*?)\)',
		r'void +imprimir\((.*?)char *\* *(.*?)\)'
	]),
	('LFalta.cpp', [
		r'lini *= *(nullptr|NULL)',
		r'lfin *= *(nullptr|NULL)',
		r'LFalta *:: *leer *\((.*?)char *\* *(.*?)\)',
		r'LFalta *:: *imprimir *\((.*?)char *\* *(.*?)\)'
	])
]

blacklist = ['build', 'dist', 'nbproject']

DEFAULT_REPORT_FILENAME = 'Incidencias-Clases-Atributos.csv'

def main():
	errors = []
	# Obtener la lista de estudiantes
	for student in os.listdir():
		if os.path.isdir(student):
			classes = [False] * len(matches)
			for root, directories, filenames in os.walk(student):
				# Ignorar las carpetas build y nbproject
				check = True
				for directory in blacklist:
					if directory in root:
						check = False
				if check:
					# Verificar si hay un archivo deseado en la lista
					for filename in filenames:
						for i, (name, regexes) in enumerate(matches):
							if name == filename:
								# Comenzar verificación del archivo
								classes[i] = True
								results = [False] * len(regexes)
								path = os.path.join(root, name)
								# Abrir el archivo y leer línea por línea
								with open(path, 'r') as file:
									for line in file:
										# Verificar si se cumple algún regex
										for j, regex in enumerate(regexes):
											if re.search(regex, line):
												results[j] = True
								# Verificar que se cumplen todos los regex
								for j, result in enumerate(results):
									if not result:
										errors.append([student, name, regexes[j]]) # name/path
			# Agregar los archivos que no se han podido encontrar
			for i, found in enumerate(classes):
				if not found:
					# print('No se encontró el archivo', matches[i][0], 'del alumno', student)
					errors.append([student, matches[i][0], 'No se encontró'])
	# Imprimir los errores
	if len(errors):
		with open(DEFAULT_REPORT_FILENAME, 'w', newline='') as file:
			writer = csv.writer(file)
			writer.writerow(['Alumno', 'Archivo', 'Incidencia'])
			writer.writerows(errors)
		print('Se encontraron varias incidencias.')
		print('Revise el archivo', DEFAULT_REPORT_FILENAME, 'para más información.')
	else:
		print('No se encontraron incidencias.')

if __name__ == '__main__':
	main()
