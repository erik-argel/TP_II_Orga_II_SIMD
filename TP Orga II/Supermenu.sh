#!/bin/bash
#------------------------------------------------------
# PALETA DE COLORES
#------------------------------------------------------
#setaf para color de letras/setab: color de fondo
    red=`tput setaf 1`;
    green=`tput setaf 2`;
    blue=`tput setaf 4`;
    bg_blue=`tput setab 4`;
    reset=`tput sgr0`;
    bold=`tput setaf bold`;
#------------------------------------------------------
# VARIABLES GLOBALES
#------------------------------------------------------
proyectoActual="git@gitlab.com:erik.argel/tp-ii-orga-ii-simd.git";

#------------------------------------------------------
# DISPLAY MENU
#------------------------------------------------------
imprimir_menu () {
       imprimir_encabezado "\t  S  U  P  E  R  -  M  E  N U ";
    
    echo -e "\t\t El proyecto actual es:";
    echo -e "\t\t $proyectoActual";
    
    echo -e "\t\t";
    echo -e "\t\t Opciones:";
    echo "";
    echo -e "\t\t\t a.  Ver contenido de carpeta";
    echo -e "\t\t\t b.  Convertir a Blanco Y Negro";        
    echo -e "\t\t\t c.  Editar interfaceBlancoYNegro"; 
    echo -e "\t\t\t d.  Compilar interfaceBlancoYNegro"; 
    echo -e "\t\t\t e.  Aclarar Imagen"; 
    echo -e "\t\t\t f.  Editar interfaceAclarar";
    echo -e "\t\t\t g.  Compilar interfaceAclarar";
    echo -e "\t\t\t h.  Corromper Imagen"; 
    echo -e "\t\t\t i.  Editar interfaceCorromper"; 
    echo -e "\t\t\t j.  Compilar interfaceCorromper";
    echo -e "\t\t\t k.  MedianFilter"; 
    echo -e "\t\t\t l.  Editar interfaceMedianFilter"; 
    echo -e "\t\t\t m.  Compilar interfaceMedianFilter"; 
    echo -e "\t\t\t n.  MultiplyBlend";          
    echo -e "\t\t\t o.  Editar interfaceMultiplyBlend";       
    echo -e "\t\t\t p.  Compilar interfaceMultiplyBlend";
    echo -e "\t\t\t r.  Abrir estados de procesos";          
    echo -e "\t\t\t s.  Buscar en carpeta";       
    echo -e "\t\t\t t.  Ver estado del proyecto";
    echo -e "\t\t\t w.  Guardar cambios";
    echo -e "\t\t\t x.  Actualizar repo";
    echo -e "\t\t\t q.  Salir";
    echo "";
    echo -e "Escriba la opción y presione ENTER";
}

#------------------------------------------------------
# FUNCTIONES AUXILIARES
#------------------------------------------------------

imprimir_encabezado () {
    clear;
    #Se le agrega formato a la fecha que muestra
    #Se agrega variable $USER para ver que usuario está ejecutando
    echo -e "`date +"%d-%m-%Y %T" `\t\t\t\t\t USERNAME:$USER";
    echo "";
    #Se agregan colores a encabezado
    echo -e "\t\t ${bg_blue} ${red} ${bold}--------------------------------------\t${reset}";
    echo -e "\t\t ${bold}${bg_blue}${red}$1\t\t${reset}";
    echo -e "\t\t ${bg_blue}${red} ${bold} --------------------------------------\t${reset}";
    echo "";
}

esperar () {
    echo "";
    echo -e "Presione enter para continuar";
    read ENTER ;
}

malaEleccion () {
    echo -e "Selección Inválida ..." ;
}

decidir () {
    echo $1;
    while true; do
        echo "desea ejecutar? (s/n)";
            read respuesta;
            case $respuesta in
                [Nn]* ) break;;
                   [Ss]* ) eval $1
                break;;
                * ) echo "Por favor tipear S/s ó N/n.";;
            esac
    done
}


################################################################
###########################B&W##################################
interfaceBlancoYNegro(){
    ./interfaceBlancoYNegro
}
editarInterfaceBlancoYNegro(){
    nano interfaceBlancoYNegro.c
}
compilarInterfaceBlancoYNegro(){
    gcc interfaceBlancoYNegro.c -o interfaceBlancoYNegro
}
################################################################
#########################Aclarar################################
interfaceAclarar(){
    ./interfaceAclarar
}
editarInterfaceAclarar(){
    nano interfaceAclarar.c
}
compilarInterfaceAclarar(){
    gcc interfaceAclarar.c -o interfaceAclarar
}
################################################################
#########################Corromper##############################
interfaceCorromper(){
    ./interfaceCorromper
}
editarInterfaceCorromper(){
    nano interfaceCorromper.c
}
compilarInterfaceCorromper(){
    gcc interfaceCorromper.c -o interfaceCorromper
}
################################################################
########################MedianFilter############################
interfaceMedianFilter(){
    ./interfaceMedianFilter
}
editarInterfaceMedianFilter(){
    nano interfaceMedianFilter.c
}
compilarInterfaceMedianFilter(){
    gcc interfaceMedianFilter.c -o interfaceMedianFilter
}

interfaceMultiplyBlend(){
    ./interfaceMultiplyBlend
}
editarInterfaceMultiplyBlend(){
    nano interfaceMultiplyBlend.c
}
compilarInterfaceMultiplyBlend(){
    gcc interfaceMultiplyBlend.c -o interfaceMultiplyBlend
}
################################################################
#####################Buscar en Directorio#######################
buscarEnCarpeta(){
    echo -e "Ingrese el nombre del archivo o directorio que desea buscar";
    read nombre;
    echo "";
    echo "archivos/directorios encontrados:";
    if test -z $nombre; then
       echo "---------------------------------";
       printf "    Cantidad de resultados:";ls | wc -l
       echo "---------------------------------";
       ls -1
       echo "---------------------------------"; 
    else 
       echo "---------------------------------";
       printf "    Cantidad de resultados:";ls | grep $nombre |  wc -l
       echo "---------------------------------";
       ls | grep $nombre
       echo "---------------------------------";
    fi
}
################################################################
########################Git Status##############################
estadoDelProyecto() {
        echo "---------------------------"        
        echo "Somthing to commit?"
        decidir "git status";

        echo "---------------------------"        
        echo "Incoming changes (need a pull)?"
        decidir "git fetch origin"
        decidir "git log HEAD..origin/master --oneline"

}
################################################################
####################Guardar Cambio en Repo######################
guardarCambiosRepositorio() {
        decidir "git add -A";
        echo "Ingrese mensaje para el commit:";
        read mensaje;
        decidir "git commit -m \"$mensaje\"";
        decidir "git push";

}
################################################################
###########################Git Pull#############################
actualizarRepositorio() {
       decidir "git pull";
}

#------------------------------------------------------
# FUNCTIONES del MENU
#------------------------------------------------------
a_funcion() {
        imprimir_encabezado "\tOpción a. Ver estado del proyecto";
        decidir "ls -l";
}

b_funcion() {
    	imprimir_encabezado "\tOpción b. Convertir a Blanco Y Negro";
    	interfaceBlancoYNegro;
}


c_funcion() {
        imprimir_encabezado "\tOpción c. Editar interfaceBlancoYNegro";        
    	decidir editarInterfaceBlancoYNegro;
}


d_funcion() {
    	imprimir_encabezado "\tOpción d. Compilar interfaceBlancoYNegro";
    	decidir compilarInterfaceBlancoYNegro;
}

e_funcion() {
    	imprimir_encabezado "\tOpción e. Aclarar Imagen";
    	interfaceAclarar;
}


f_funcion() {
    	imprimir_encabezado "\tOpción f. Editar interfaceAclarar";
    	decidir editarInterfaceAclarar;
}

g_funcion() {
        imprimir_encabezado "\tOpción g. Compilar interfaceAclarar";
        decidir compilarInterfaceAclarar;
}

h_funcion() {
        imprimir_encabezado "\tOpción h. Corromper Imagen";
        interfaceCorromper;
}

i_funcion() {
        imprimir_encabezado "\tOpción i. Editar interfaceCorromper";
        decidir editarInterfaceCorromper;
}

j_funcion() {
        imprimir_encabezado "\tOpción j. Compilar interfaceCorromper";
        decidir compilarInterfaceCorromper;
}

k_funcion() {
        imprimir_encabezado "\tOpción k. MedianFilter";
        interfaceMedianFilter;
}

l_funcion() {
        imprimir_encabezado "\tOpción l. Editar interfaceMedianFilter";
        decidir editarInterfaceMedianFilter;
}

m_funcion() {
        imprimir_encabezado "\tOpción m. Compilar interfaceMedianFilter";
        decidir compilarInterfaceMedianFilter;
}

n_funcion() {
        imprimir_encabezado "\tOpción n. MultiplyBlend";
        interfaceMultiplyBlend;
}

o_funcion() {
        imprimir_encabezado "\tOpción o. Editar interfaceMultiplyBlend";
        decidir editarInterfaceMultiplyBlend;
}

p_funcion() {
        imprimir_encabezado "\tOpción p. Compilar interfaceMultiplyBlend";
        decidir compilarInterfaceMultiplyBlend;
}

r_funcion() {
    	imprimir_encabezado "\tOpción r. Abrir estados de procesos";
    	decidir "htop";
}

s_funcion(){
        imprimir_encabezado "\tOpción s. Buscar en carpeta";
      	buscarEnCarpeta;
}

t_funcion(){
        imprimir_encabezado "\tOpción t. Ver estado del proyecto";
        estadoDelProyecto;
}

w_funcion(){
        imprimir_encabezado "\tOpción w. Guardar cambios";
        guardarCambiosRepositorio;
}

x_funcion(){
        imprimir_encabezado "\tOpción x. Actualizar repo";
        actualizarRepositorio;
}

#------------------------------------------------------
# LOGICA PRINCIPAL
#------------------------------------------------------
while  true
do
    # 1. mostrar el menu
    imprimir_menu;
    # 2. leer la opcion del usuario
    read opcion;
    
    case $opcion in
        a|A) a_funcion;;
        b|B) b_funcion;;
        c|C) c_funcion;;
        d|D) d_funcion;;
        e|E) e_funcion;;
        f|F) f_funcion;;
	    g|G) g_funcion;;
	    h|H) h_funcion;;
	    i|I) i_funcion;;
        j|J) j_funcion;;
        k|K) k_funcion;;
        l|L) l_funcion;;
        m|M) m_funcion;;
        n|N) n_funcion;;
        o|O) o_funcion;;
        p|P) p_funcion;;
        r|R) r_funcion;;
        s|S) s_funcion;;
        t|T) t_funcion;;
        w|W) w_funcion;;
        x|X) x_funcion;;
        q|Q) break;;
        *) malaEleccion;;
    esac
    esperar;
done

