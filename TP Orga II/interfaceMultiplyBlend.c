
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(){
    
    char imagen[100]; //dato de la imagen
    char imagen2[100]; //dato de la imagen2
    char cmd[250]; //comando a ejecutar

    printf("Escriba el nombre de la primera imagen:");
    scanf("%s",&imagen);    //escanea el nombre de la primera imagen que ingrese
    printf("Escriba el nombre de la segunda imagen:");
    scanf("%s",&imagen2);    //escanea el nombre de la segunda imagen que ingrese
    sprintf(cmd, "./tp 5 %s %s", imagen, imagen2);    //crea la cadena del comando
    system(cmd);    //ejecuta el comando
}
