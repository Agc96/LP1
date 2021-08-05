"""
Modo de uso: {python} {module} <directorio> <nombre_carpeta> 
"""

import os
import sys

def main():
    if len(sys.argv) < 3:
        usage()
    alumnos = os.listdir(sys.argv[1])
    for alumno in alumnos:
        carpetas = [x[0] for x in os.walk(os.path.join(sys.argv[1], alumno))]
        encontrado = False
        for carpeta in carpetas:
            if sys.argv[2] in carpeta:
                encontrado = True
                break
        if not encontrado:
            print(alumno)

def usage():
    python = os.path.basename(sys.executable)
    sys.stderr.write(__doc__.format(python=python, module=sys.argv[0]))
    sys.exit(1)

if __name__ == '__main__':
    main()
