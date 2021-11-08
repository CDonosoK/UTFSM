#COMPILADOR DEL JUEGO

from cx_Freeze import setup, Executable

try:
    setup(name = "-_SUDOLU_-",
          version = "1.0",
          description = "Proyecto de LP",
          executables = [Executable("Main.py")]
          )
except:
    print("No se encontró el archivo para realizar el ejecutable.")
