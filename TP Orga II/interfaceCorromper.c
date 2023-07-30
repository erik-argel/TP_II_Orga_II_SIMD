
#include <stdio.h>
#include <stdlib.h>
int main(){
    
    char* imagen; //dato de la imagen
    char* cmd; //comando a ejecutar

    printf("Escriba el nombre de la imagen:");
    scanf("%s",&imagen);    //escanea el nombre de la imagen que ingrese
    sprintf(cmd, "./tp 3 %s", &imagen);    //crea la cadena del comando
    system(cmd);    //ejecuta el comando
}
