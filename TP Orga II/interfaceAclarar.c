
#include <stdio.h>
#include <stdlib.h>
int main(){
    
    char* imagen; //dato de la imagen
    int nivel; //dato del nivel
    char* cmd; //comando a ejecutar

    printf("Escriba el nombre de la imagen:");
    scanf("%s",&imagen);    //escanea el nombre de la imagen que ingrese
    printf("Escriba el nivel de aclarado que quiere agregar:");
    scanf("%i",&nivel);    //escanea el nivel que ingrese
    sprintf(cmd, "./tp 2 %s %i", &imagen, nivel);    //crea la cadena del comando
    system(cmd);    //ejecuta el comando
}
