import csv
import os
import re

matches = [
	('Conductor.h',  [r'int +licencia', r'char *\* *nombre']),
	('Conductor.cpp', [r'nombre *= *nullptr', r'delete(.*?) *nombre', r'strcpy\((.*?),(.*?)\)', r'strlen\((.*?)\)']),
	('Infraccion.h', [r'int +codigo', r'char *\* *gravedad']),
	('Infraccion.cpp', [r'gravedad *= *nullptr', r'delete(.*?) *gravedad', r'strcpy\((.*?),(.*?)\)', r'strlen\((.*?)\)']),
	('Falta.h', [r'int +fecha', r'char *\* *placa']),
	('Falta.cpp', [r'placa *= *nullptr', r'delete(.*?) *placa', r'strcpy\((.*?),(.*?)\)', r'strlen\((.*?)\)']),
	('Leve.h', [r'public +Infraccion', r'public +Falta', r'double +descuento']),
	('Grave.h', [r'public +Infraccion', r'public +Falta', r'double +descuento', r'int +puntos']),
	('MuyGrave.h', [r'public +Infraccion', r'public +Falta', r'int +puntos', r'int +meses']),
	('Registro.h', [r'public +Conductor', r'Leve +lleve', r'Grave +lgrave', r'MuyGrave +lmgrave']),
	('Procesa.h', [r'Registro lregistro\[(.*)]', r'int +cantidad', r'void lee\( *(void|) *\)', r'void imprime\( *(void|) *\)']),
	('Procesa.cpp', [r'cantidad *= *0', r'Procesa *:: *lee', r'Procesa *:: *imprime'])
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
