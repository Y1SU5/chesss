@echo off
echo Compilando prbchs1.c...
gcc prbchs1.c -o prbchs1.exe -I "E:/namcompilador/C_COMPILADOR/ucrt64/include" -L "E:/namcompilador/C_COMPILADOR/ucrt64/lib" -lraylib -lopengl32 -lgdi32 -lwinmm

if %ERRORLEVEL% equ 0 (
    echo Compilado con exito. Ejecutando...
    prbchs1.exe
) else (
    echo Hubo un error al compilar.
)