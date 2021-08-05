"""
Este script permite verificar que en cada archivo .h y .cpp del alumno, él o
ella haya colocado su nombre y código.

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

  20201234 - PEREZ FLORES, JUAN JESUS
  20205678 - FLORES DEL CAMPO, ZACARIAS
"""

import csv
import os
import sys

ERROR_COLUMNA_CSV = """
Error: no se encontró la columna {column} en el archivo CSV. Asegúrese de que
dicha columna se encuentre en la cabecera del archivo CSV, y de que el archivo
CSV se haya guardado usando la opción "CSV (delimitado para comas)" en Excel
o algún programa similar (no use UTF-8 de preferencia).
"""
CARPETAS_NETBEANS = ['build', 'dist', 'nbproject']
EXTENSIONES_EVALUAR = ['.h', '.cpp']
NOM_ARCH_INCIDENCIAS = 'Incidencias-Nombre-Codigo.csv'

def main():
	# Mostrar uso si es que hacen falta argumentos
	if len(sys.argv) < 3:
		usage()
	# Obtener la lista de directorios e inicializar incidencias
	carpetas = os.listdir(sys.argv[2])
	incidencias = []
	# Leer el archivo CSV
	with open(sys.argv[1], 'r', newline='') as arch:
		alumnos = csv.DictReader(arch)
		for alumno in alumnos:
			# Buscar el nombre del alumno en los directorios
			carpeta = obtener_carpeta_buscada(carpetas, alumno)
			if carpeta:
				# Obtener los datos a buscar
				datos = obtener_datos(alumno)
				# Buscar las subcarpetas
				path_alumno = os.path.join(sys.argv[2], carpeta)
				for root, directorios, archivos in os.walk(path_alumno):
					if not evaluar_carpeta(root):
						continue
					# Buscar los archivos de las subcarpetas
					for archivo in archivos:
						if not evaluar_extension(archivo):
							continue
						# Abrir el archivo y evaluar si contiene los datos
						path_archivo = os.path.join(root, archivo)
						evaluar_archivo(path_archivo, datos, incidencias)
	# Colocar las incidencias en un archivo CSV
	if len(incidencias) > 0:
		guardar(incidencias)
	else:
		print('No se encontraron incidencias.')

def usage():
	# Imprimir modo de uso
	python = os.path.basename(sys.executable)
	sys.stderr.write(__doc__.format(python=python, module=sys.argv[0]))
	# Indicar que el programa no terminó correctamente
	sys.exit(1)

def obtener_carpeta_buscada(carpetas, alumno):
	carpeta_buscada = alumno['Alumno'] + ' - ' + alumno['Nombre']
	for carpeta in carpetas:
		if carpeta == carpeta_buscada:
			return carpeta
	return None

def obtener_datos(alumno):
	nombre_completo = convertir_texto(alumno['Nombre'])
	nombre_completo = nombre_completo.split(', ')
	primer_nombre = nombre_completo[0].split(' ')[0]
	primer_apellido = nombre_completo[1].split(' ')[0]
	return [primer_nombre, primer_apellido, alumno['Alumno']]

def convertir_texto(texto):
	texto = texto.lower()
	texto = texto.replace('á', 'a')
	texto = texto.replace('é', 'e')
	texto = texto.replace('í', 'i')
	texto = texto.replace('ó', 'o')
	texto = texto.replace('ú', 'u')
	return texto

def evaluar_carpeta(root):
	for carpeta in CARPETAS_NETBEANS:
		if carpeta in root:
			return False
	return True

def evaluar_extension(archivo):
	for extension in EXTENSIONES_EVALUAR:
		if extension in archivo:
			return True
	return False

def evaluar_archivo(path, datos, incidencias):
	resultados = [False] * len(datos)
	# Verificar que los datos solicitados estén en el archivo
	with open(path, 'r', encoding='UTF-8') as arch:
		for linea in arch:
			linea = convertir_texto(linea)
			for i, dato in enumerate(datos):
				if dato in linea:
					# print(linea, dato)
					resultados[i] = True
	# Colocar incidencias en caso no sea cierto
	for i, resultado in enumerate(resultados):
		if not resultado:
			incidencias.append([path, datos[i]])

def guardar(incidencias):
	with open(NOM_ARCH_INCIDENCIAS, 'w', newline='') as file:
		writer = csv.writer(file)
		writer.writerow(['Archivo', 'Incidencia'])
		writer.writerows(incidencias)
	print('Se encontraron varias incidencias.')
	print('Revise el archivo', NOM_ARCH_INCIDENCIAS, 'para más información.')

if __name__ == '__main__':
	main()
