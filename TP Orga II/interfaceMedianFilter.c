
#include <stdio.h>
#include <stdlib.h>
int main(){
    
    char* imagen; //dato de la imagen
    int sizeVent; //dato del tamaño de la ventana
    char* cmd; //comando a ejecutar

    printf("Escriba el nombre de la imagen:");
    scanf("%s",&imagen);    //escanea el nombre de la imagen que ingrese
    printf("Escriba el tamaño de la ventana que quiere usar:");
    scanf("%i",&sizeVent);    //escanea el tamaño de la ventana que ingrese
    sprintf(cmd, "./tp 4 %s %i", &imagen, sizeVent);    //crea la cadena del comando
    system(cmd);    //ejecuta el comando
}
