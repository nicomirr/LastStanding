#include <SFML/Graphics.hpp>
#include "../src/Program/Program.h"

void main()
{
    Program program;
    program.Run();
            
}




/*
SFML PASOS:

1- Descargar SFML última versión (X64).
2- Crear archivo C++ VACIO (no aplicación de consola).
3- Crear archivo (NO CLASE) llamado Main.
4- Crear clase (NO ARCHIVO) llamada Program.
5- Crear en la carpeta del PROYECTO (no de la solución) la ESTUCTURA DE CARPETAS de SFML.
6- Quitamos los archivos de código fuente "Main" y "Program"(clase y header) para agregarlos a la carpeta "src" (en esta irá nuestro código fuente).
7- Una vez quitados los elementos del programa, movemos todo nuestro código fuente (archivos .cpp y .h) y los movemos todos a la carpeta "src". 
Una vez allí los volvemos a agregar desde la carpeta "src". A partir de acá todos los archivos código fuente creados en el proyecto deberan crearse
en "src" (estar atentos ya que visualstudio por default nos dará la carpeta del proyecto y no la carpeta "src").
8- Ponemos SFML en nuestra carpeta de libs y eliminamos de SFML todo lo innecesario.
9- Configuramos nuestro proyecto para que funcione bien el include de SFML.



CARPETAS:

X64: se crea en tiempo de compilación. No debe estar en entregable.

bin: contiene el archivo EJECUTABLE. No contiene código fuente. Esta carpeta no se entrega si se solicita código fuente. Esta carpeta se genera al ejecutar la
solución.

obj: cuando el ID compila, pasa el código fuente a dos lenguajes intermedios. Esto genera varios archivos. Dichos archivos están en esta carpeta. Esta carpeta,
con sus archivos, se crea en tiempo de compilación al igual que la carpeta "bin". Tampoco debe entregarse si se solicita código fuente.

Carpetas "bin" y "obj" se crean solas al compilar.

lib o libs: aca estarán todas las librerías.

src: código fuente.
 
res: es la carpeta de recursos (resources). Contiene los assets del juego.

CARPETAS IMPORTANTES A CREAR POR NOSOTROS:

	-libs
	-res
	-src



IMPORTANTE: 
La raíz de nuestro programa es la carpeta "src". En nuestra raíz solo debe estar el archivo MAIN. El resto de archivos de código fuente irá en distintas 
subcarpetas. A las clases y headers nuestras las podemos incluir dentro de un archivo si se encuentran todas al mismo nivel. Si el código fuente lo tenemos
a un mismo nivel, podemos incluirlo simplemente con "#include". En nuestro caso, no tendremos a nuestro código fuente en un mismo nivel, este estará distribuído
en diversas subcarpetas. Para lograr acceder a los archivos de código fuente en distintas subcarpetas deberemos manejar el #include de manera distinta.

ACCESO A SUBCARPETAS (USO DE #INCLUDE):
Nuestro punto de partida para explorar las carpetas e incluir código fuente será el lugar desde donde hayamos agregado nuesto código fuente (en nuestro caso, el
punto de partida es "src". Desde aquí deberemos navegar las distintas subcarpetas hasta el archivo de código fuente deseado. Por ejemplo, para llegar a Program.h
debemos acceder primero a la carpeta "Program" y luego, una vez allí, podemos acceder a "Program.h": #include "Program/Program.h".

SUBCARPETAS EN "src":

IMPORTANTE: cada vez que movamos algún archivo desde "src" hacia alguna subcarpeta, deberemos quitar (NO ELIMINAR) el archivo y volver a agregarlo, pero desde la
nueva carpeta en la cual se encuentra (este paso puede saltearse si al crearse el nuevo archivo de código fuente se lo crea ya en la nueva carpeta).

Entities: aquí irán todos los objetos que tengan vida (player, enemy, npc, etc.). Podemos crear aquí subcarpetas para el jugador, los enemigos, y todo otro tipo de 
entidad.

Program: aquí irá el .cpp Program y el .h Program.



CARPETAS EN SFML:

bin: es la más importante. Vamos a linkear con lo que haya acá.

lib: tiene subcarpetas.
	cmake: sirve para compilar. Se elimina.
	debug y release: se eliminan.

Acá dentro de "lib" tenemos todos los archivos .lib. Debemos eliminar todos los estáticos si queremos las librerías dinámicas, y si queremos las liberías estáticas, 
eliminar todas las dinámicas (en nuestro caso también eliminamos todos los archivos que no empiecen con SFML. Usaremos librerías dinámicas).



DIFERENCIA ENTRE LIBRERÍAS DINÁMICAS Y ESTÁTICAS:

En videojuegos suelen usarse las dinámicas.
Si usamos la librería ESTÁTICA, todos los archivos .lib que corresponden a la librería se meten todos en el .exe, haciendo que este pese más. En la dinámica no sucede eso.
El exe así es más pesado pero tiene todo.
La librería DINÁMICA nos permite tener nuestro ".dll" (librería) separado de nuestro archivo ".exe". En este caso el ".exe" le 'hablará' a la ".dll" y esta le devolverá
al ".exe" la función que esté solicitando. En la ".dll" tendremos las funciones, y en el ".exe" tendremos el resto del código.

La .dll se usa mucho porque son menos cosas por compilar así. Cuando hay updates sirve mucho esto ya que solo se descargan los assets y los .dll. Si no se utilizase
.dll habría que bajar todo el .exe nuevamente.



INCLUIR SFML EN NUESTRO PROYECTO:

seguimos instrucciones (VER LAS PROPIEDADES PARA SABER COMO FUE HECHO JUNTO A INSTRUCCIONES DE GUIA).
Los pasos a seguir figuran en la guía de SFML que está en la diapositiva.

PASO 1: accedo a propiedades del proyecto haciendo click derecho sobre el proyecto (NO LA SOLUCIÓN).
PASO 2: vamos a la pestaña C/C++. Vamos a general. En donde dice "directorios de inclusión adicionales" ponemos el directorio de nuestro SFML. 
Debemos poner: $(ProjectDir)\libs\SFML\include. Con "$(ProjectDir)\" nos aseguramos de que acceda al lugar en cuestión desde nuestro programa.
PASO 3: en propiedades vamos a "Vinculador\General" y allí vamos a "Directorio de bibliotecas adicionales". Aquí pondremos la ubicación de "libs":
$(ProjectDir)\libs\SFML.
PASO 4: vamos a "Vinculador\Entrada". Allí en "Dependencias adicionales" ponemos: 
        
            sfml-graphics.lib
            sfml-window.lib
            sfml-system.lib

PASO 5: en propiedades, ponemos la configuración "Debug" (en lugar de todas) y allí agregamos a las dependencias adicionales en nuestro 
"Vinculador/Entrada" el sufijo "-d":

            sfml-graphics-d.lib
            sfml-window-d.lib
            sfml-system-d.lib

PASO 6: limpiar carpeta libs. Borrar las librerías estáticas (sufijo "-s") y dejar las dinámicas (sufijo "-d"). Borrar todo lo que no tenga
prefijo "sfml".

Si usamos librerías estáticas, debemos incluir ciertas dependencias. Estas dependencias son las que en "libs" no tienen prefijo "sfml". Como
usamos librerías dinámicas, podemos eliminar todas estas dependencias.

PASO 7: a la carpeta llamada "bin" que se encuentra dentro de SFML, la renombramos como ".dll". La cortamos y la pegamos en la carpeta "res".
Esto es práctico ya que, al momento de ejecutar nuestro ".exe", necesitamos al lado de este todas las ".dll" para que el ".exe" funcione.
Solo si las ".dll" están junto al ".exe" es que puede el ".exe" comunicarse con las ".dll".

Cuando pasemos el ejecutable, nosotros pasaremos el archivo ".exe" junto a todas las ".dll", todo dentro de una misma carpeta, para que el 
".exe" pueda comunicarse con las ".dll". Podemos, si queremos, ordenar todos los ".dll" en una carpeta llamada "dll" y decirle al 
".exe" que vaya a buscar las ".dll" a dicha carpeta.

Para que nuestro ".exe" vaya a buscar archivos a una carpeta específica podemos:

    - Configurar el proyecto para que lo haga.
    - Crear código con el símbolo del sistema de windows (CMD) en un archivo ".bat" que le indique ir a buscar allí.

PASO 8: vamos a "proyecto/propiedades/propiedades de configuración/general" y hacemos lo siguiente:

    - Directorio de salida: $(ProjectDir)\bin\$(Platform)\$(Configuration)\       En el directorio de salida estará nuestro .exe.
    - Directorio intermedio: $(ProjectDir)\obj\$(Platform)\$(Configuration)\      En el directorio intermedio se encuentran todos los archivos intermedios que llevan al .exe (archivo .exe.recipe, entre otros).
    - Nombre del destino: $(ProjectName)

Con esta configuración del paso 8 logramos que aparezcan las carpetas bin y obj en el directorio de nuestro proyecto. Dichas carpetas deben ser creadas en el tiempo
de compilación.

Con este octavo paso ya logramos la ESTRUCTURA TEMPLATE BÁSICA que deben tener los proyectos de SFML:

    Carpetas: bin, libs, obj, res, src.
    Archivos de proyecto.

PASO 9: mediante comandos en la configuración de VisualStudio tomaremos la carpeta "dll", con las ".dll" y la llevaremos a nuestro ejecutable.
Iremos a "proyecto/propiedades/eventos de compilación/evento posterior a la compilación" y en línea de comandos ponemos: "MKDIR "$(TargetDir)res\"

Con esto logramos que se cree la carpeta "res" dentro de la carpeta debug (o release) tras la compilación.

Luego, nuevamente en "proyecto/propiedades/eventos de compilación/evento posterior a la compilación" agregamos la línea de comandos:
XCOPY "$(ProjectDir)res\" "$(TargetDir)res\" /e /h /y /s. 

Con este comando se copian todos los archivos que se encuentran dentro de la carpeta "res", ubicada en el proyecto, y se pegan dentro de la carpeta "res" 
que se crea dentro de la carpeta debug o release. 



Los eventos de compilación (anterior a compilación, anterior a vinculación, posterior a compilación) son todos para crear carpetas y mover archivos dentro del programa.

$(ProjectDir): nos manda a la dirección en la cual se encuentra nuestro proyecto (no la solución). 
$(Platform): nos devuelve la plataforma en la que se está compilando (X32 o X64).
$(Configuration): nos devuelve la configuración de la ejecución (Debug o Release).
$(TargetDir): donde va a ir el resultado de algo.
MKDIR: es un comando que se utiliza para crear un nuevo directorio (o carpeta= en sistemas operativos como Windows, Linux y macOS. 

¿QUE ES UNA .DLL?

Un archivo .dll (Dynamic Link Library) es una biblioteca de enlaces dinámicos utilizada en sistemas operativos Windows. Estos archivos contienen
código, datos y recursos que pueden ser utilizados por múltiples programas al mismo tiempo. En lugar de compilar todas las funciones y recursos 
necesarios dentro de un solo archivo ejecutable, un archivo .dll permite a los programas compartir y utilizar funcionalidades comunes sin duplicarlas.

Características clave:
    - Reutilización de código: Una .dll permite que múltiples programas accedan a la misma funcionalidad sin incluir todo el código dentro de sus propios archivos ejecutables.
    - Carga dinámica: Un programa puede cargar y ejecutar funciones de una .dll solo cuando las necesita, ahorrando memoria.
    - Modularidad: Facilita la actualización de partes de un software sin necesidad de recompilar el programa completo, ya que las actualizaciones pueden aplicarse solo a la .dll afectada.
    - En el desarrollo de videojuegos, por ejemplo, las .dll se usan comúnmente para manejar bibliotecas externas como motores gráficos, controladores de audio, etc.


Todos los archivos .dll en un juego de steam van a la carpeta de steam.



¿QUE ES UN .BAT?

Un archivo .bat (batch file) es un archivo de procesamiento por lotes que contiene una secuencia de comandos y comandos que pueden ser ejecutados en un sistema operativo basado 
en MS-DOS o Windows. Estos archivos suelen tener la extensión .bat y se utilizan para automatizar tareas repetitivas o para ejecutar una serie de comandos de forma secuencial sin intervención manual.

Características clave:
    - Automatización: Los archivos .bat son utilizados para automatizar tareas, como copiar archivos, abrir programas, configurar entornos, o realizar procesos de mantenimiento.
    - Comandos secuenciales: Contienen una lista de comandos que se ejecutan uno tras otro cuando el archivo es ejecutado.
    - Scripting sencillo: Aunque no es tan poderoso como lenguajes de scripting avanzados, los archivos .bat permiten utilizar condicionales, bucles, y otras estructuras básicas de control.
    - Compatibilidad con CMD: Los archivos .bat son interpretados por el Símbolo del sistema de Windows (CMD.exe), que ejecuta los comandos en el orden en que aparecen en el archivo.

En windows se los escribe con el símbolo del sistema de Windows (CMD). En linux, por ejemplo, con Bash.



IMPORTANTE: Por defecto, el archivo .exe de nuestra solución se encuentra en la carpeta X64 que se crea en la raíz de la SOLUCIÓN. El archivo .exe no se crea en la carpeta X64 del proyecto.



BUSCAR GDD TEMPLATE BASICO!
*/