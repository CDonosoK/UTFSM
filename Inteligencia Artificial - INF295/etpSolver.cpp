#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <direct.h>

using namespace std;

void imprimirMatriz(int **matriz, int cantidad);
void imprimirVector(vector <vector <int>> listaConflictos );

void crearArchivoRes(string nombreArchivo);
void crearArchivoPen(string nombreArchivo);
void crearArchivoSol(string nombreArchivo);

vector <vector <int>> leerEstudiantes(string archivo);
int **generarMatrizConflictos(int cantidadExamenes, string archivoEstudiantes);
int leerExamenes(string archivoExamenes);
int algoritmoGreedy(int **matriz, int cantidadExamenes);
int algoritmoHC(vector <vector <int>> listaConflictos, int **matriz, int cantidadExamenes, string archivoRespuesta, string archivoEstudiantes);

bool encontrarValor(vector <int> lista, int nBuscar);
bool ordenarColumna(const vector <int>& v1, const vector <int>& v2);

int main(){
    //Se obtienen la cantidad de estudiantes
    string seguir = "1";

    while (seguir != "0"){
        string archivo;

        cout << "Ingrese el nombre del archivo de prueba (debe estar en la carpeta instancias): ";
        cin >> archivo;

        string archivoExamenes = "./Instancias/";
        archivoExamenes+=archivo;
        archivoExamenes+=".exm";

        //Se obtienen la cantidad de examenes
        int cantidadExamenes = leerExamenes(archivoExamenes);
        /*
        Solo se pueden resolver problemas que tengan a lo más 720 exámenes
        Ya que de ser más. la matriz de conflictos queda muy grande y el computador se queda sin memoria
        y entrega el siguiente error: 3221225725
        */
        string archivoEstudiantes = "./Instancias/";
        archivoEstudiantes+=archivo;
        archivoEstudiantes+=".stu";
        int **matrizConflictos = generarMatrizConflictos(cantidadExamenes, archivoEstudiantes);

        vector <vector <int>> listaConflictos;
        for (int ex = 0; ex<cantidadExamenes; ex++){
            vector <int> v1;
            int suma = 0;
            for (int con = 0; con<cantidadExamenes; con++){
                if (matrizConflictos[ex][con] == 1){
                    suma++;
                }
            }
            v1.push_back(ex+1);
            v1.push_back(suma);
            listaConflictos.push_back(v1);
        }
        
        sort(listaConflictos.begin(), listaConflictos.end(),ordenarColumna);

        //Si se desea ver por consola la matriz de conflictos se puede descomentar la siguiente sección:
        /*
        cout <<"Matriz de Conflictos"<<endl;
        imprimirMatriz(matrizConflictos, cantidadExamenes);
        cout <<"Vector de Conflictos"<<endl;
        imprimirVector(listaConflictos);
        */

        //Implementación del algoritmo Greedy para encontrar la primera solución
        int timeslotInicial = algoritmoGreedy(matrizConflictos, cantidadExamenes);
        cout <<"Archivo analizando: "<<archivo << endl;
        cout << "Timeslot Inicial - Usando algoritmo Greedy: "<< timeslotInicial << endl;

        int timeSlotFinal = algoritmoHC(listaConflictos, matrizConflictos, cantidadExamenes, archivo, archivoEstudiantes);
        
        
        

        cout << endl;
        cout << "Desea analizar otro archivo [0] No - [1] Si: ";
        cin >> seguir;

        }
    system("pause");

    return 0;
}

void imprimirVector(vector <vector <int>> listaConflictos ){
    /*
    Función auxiliar para imprimir un vector
    */
    for (int i=0;i<listaConflictos.size();i++){
        {	
            
            if (listaConflictos[i].size()>=2){
                for (int j=0;j<listaConflictos[i].size();j++)
                {	
                    printf("| %d |",listaConflictos[i][j]);							
                }
                printf("\n");
            }
            
        
        }
    }
}

int leerExamenes(string archivoExamenes){
    /*
    Función para encontrar la cantidad de exámenes
    */
    string line;
    int cantidadExamenes = 0;
    ifstream myFile(archivoExamenes);
    string examenActual;
    
    if (myFile.is_open()){
        //Ciclo para obtener la cantidad de examenes
        while (getline (myFile, line)){
            cantidadExamenes ++;
        }
        myFile.close();
    }
    else cout << "No se ha podido abrir el archivo";
    return cantidadExamenes;
}


int **generarMatrizConflictos(int cantidadExamenes, string archivoEstudiantes){
    //Se instancia la matriz cuadrada con la cantidad de examenes
    int **matrizConflictos = (int **)malloc(cantidadExamenes*sizeof(int*));
    for (int i = 0; i < cantidadExamenes; i++){
        matrizConflictos[i] = (int*)malloc(cantidadExamenes*sizeof(int));
        for (int j = 0; j <cantidadExamenes; j++){
            matrizConflictos[i][j] = 0;
        }
    }
    //Se instancias las variables auxiliares que se utilizarán
    string line;
    string alumnoPasado = "";
    int pos = 0;
    int numeroEstudiante = 0;
    bool primerValor = true;

    /*Se crea el vector que contendrá los ID de los exámenes por cada alumno,
    Esto quiere decir, que necesariamente esos examenes son los que entrarán en conflicto.
    Con esa información se poblará la matríz de conflictos.
    */
    int examenesAlumno[cantidadExamenes];
        for (int j = 0; j <cantidadExamenes; j++){
            examenesAlumno[j] = 0;
        }

    ifstream myFile(archivoEstudiantes);
    if (myFile.is_open()){
        //Ciclo que recorre a los estudiantes con sus respectivos examenes.
        while (getline (myFile, line)){
            string alumnoActual;
            string examenActual;
            bool esAlumno = true;
            
            
            for (auto x: line){
                if (esAlumno){
                    alumnoActual += x;
                }
                else{
                    examenActual += x;
                }
                if (x == ' '){
                    esAlumno = false;
                    
 
                }
            }
            stringstream geek(examenActual);
            int x = 0;
            geek >> x;
            /*
            En la siguiente sección por cada alumno, se va poblando la matriz de conflictos, según el vector
            de examenes creado anteriormente. Si existe conflicto se poblará con 0.
            */
            if (primerValor){
                primerValor = false;
                alumnoPasado = alumnoActual;
            }

            if(alumnoActual != alumnoPasado){

                for (int i = 0; i < cantidadExamenes; i++){
                    if (examenesAlumno[i] != 0){
                        for (int j = 0; j < cantidadExamenes; j++){
                            if (examenesAlumno[j] != 0){
                                matrizConflictos[examenesAlumno[i]-1][examenesAlumno[j]-1] = 1;
                            }
                        
                        }
                    }
                    
                }

                for (int i = 0; i<cantidadExamenes; i++){
                    examenesAlumno[i] = 0;
                }
                alumnoPasado = alumnoActual;
                pos = 0;
                examenesAlumno[pos] = x;
                pos++;
                
            }
            else{
                examenesAlumno[pos] = x;
                pos++;

            }
        }

        for (int i = 0; i < cantidadExamenes; i++){
            if (examenesAlumno[i] != 0){
                for (int j = 0; j < cantidadExamenes; j++){
                    if (examenesAlumno[j] != 0){
                        matrizConflictos[examenesAlumno[i]-1][examenesAlumno[j]-1] = 1;
                    }
                
                }
            }
            
        }


        myFile.close();
        return matrizConflictos;
    }
    else cout << "No se ha podido abrir el archivo";


    
}


vector <vector <int>> leerEstudiantes(string archivoEstudiantes){
    /*
    Función para obtener un vector con los estudiantes y sus examenes
    */
    vector <vector <int>> estudiantes;
    string line;
    string alumnoPasado = "";
    bool primerValor = true;

    ifstream myFile(archivoEstudiantes);
    if (myFile.is_open()){
        //Ciclo que recorre a los estudiantes con sus respectivos examenes.
        vector <int> examenesEstudiante;
        while (getline (myFile, line)){
            string alumnoActual;
            string examenActual;
            bool esAlumno = true;
            


            for (auto x: line){
                if (esAlumno){
                    alumnoActual += x;
                }
                else{
                    examenActual += x;
                }
                if (x == ' '){
                    esAlumno = false;
                    
 
                }
            }
            stringstream geek(examenActual);
            int x = 0;
            geek >> x;
            examenesEstudiante.push_back(x);

            if (primerValor){
                primerValor = false;
                alumnoPasado = alumnoActual;
            }
            if(alumnoActual != alumnoPasado){
                examenesEstudiante.pop_back();
                estudiantes.push_back(examenesEstudiante);
                examenesEstudiante.clear();
                examenesEstudiante.push_back(x);
                alumnoPasado = alumnoActual;
            }
        }
        estudiantes.push_back(examenesEstudiante);
    }
    else cout << "No se ha podido abrir el archivo";


    return estudiantes;
    
}

void imprimirMatriz(int **matriz, int rango){
    //Función auxiliar para imprimir la matriz de conflicto.
    for (int i=0;i<rango;i++){
        {	
            for (int j=0;j<rango;j++)
            {	
                printf("| %d |",matriz[i][j]);							
            }
        printf("\n");
        }
    }
}

bool ordenarColumna( const vector<int>& v1, const vector<int>& v2 ) {
    //función auxiliar para ordenar de manera creciente
 return v1[1] < v2[1];
}

bool encontrarValor(vector<int> lista, int numeroBuscar) {
    /*
    Función auxiliar para retornar true o false, si un valor 
    se encuentra dentro de un vector o no.
    */
    return find(lista.begin(), lista.end(), numeroBuscar) != lista.end();
}

int algoritmoGreedy(int **matrizConflictos, int cantidadExamenes){
    /*
    El algoritmo Greedy está planteado de tal manera de ir recorriendo los exámenes,
    y agregarlos en el primer timeslot, tal que no genere conflicto con los exámenes
    agreados anteriormente.
    */

    //Se genera el vector de Solución y el vector que agregará los examenes.
    vector <vector<int>> vectorSolucion; 
    vector <int> examenesIngresados;

    int timeSlotMax = 0;
    for (int j = 0; j<cantidadExamenes;j++){
        vector <int> v1;
        v1.push_back(0);
        vectorSolucion.push_back(v1);
    } 

    for (int examen = 0; examen < cantidadExamenes; examen++){
        int timeslot = 0;
        
        vector <int> vectorConflicto; 
        for (int conflicto = 0; conflicto<cantidadExamenes; conflicto++){
            //primero se encuentran los exámenes que están en conflicto con el exámen buscado
            if (matrizConflictos[examen][conflicto] == 1){ 
                vectorConflicto.push_back(conflicto);
                
            }
        }
        /*
        Se va poblando el vectorSolución con los examenes en caso que estos no estén instanciados,
        de tal manera que se instancien en el primer timeslot posible.
        */
        for (int conflicto = 0; conflicto<vectorConflicto.size(); conflicto++){
            if (encontrarValor(examenesIngresados, vectorConflicto[conflicto]+1) == false){
                vectorSolucion[timeslot].push_back(vectorConflicto[conflicto]+1);
                examenesIngresados.push_back(vectorConflicto[conflicto]+1);
                timeslot++;  
            }
            
            if (timeslot > timeSlotMax){
                timeSlotMax = timeslot;
            }
        }
    }

    return timeSlotMax;

}

int algoritmoHC(vector <vector <int>> listaConflictos, int **matrizConflictos, int cantidadExamenes, string archivoRespuesta, string archivoEstudiantes){
    /*
    A partir del algortimo Greedy, se utiliza la matriz de conflictos generada, como también el vector
    con los examenes más conflictivos, y se van modificando las posiciones de estos examenes, de tal manera
    de ir disminuyendo los timeslot.
    Una vez que se asigan los examenes totales, se vuelve a repasar una vez cada uno, si se puede lograr una nueva
    posición tal que disminuya la totalidad de timeslot utilizados. En caso de no lograr esto, se retorna el valor
    de los timeslot a utilizar.
    */
    int timeslotMax = 0;
    vector <int> ultimoValor;
    vector <vector<int>> vectorSolucion; 

    //Se crea la carpeta correspondiente
    mkdir("./Respuestas");


    for (int j = 0; j<cantidadExamenes;j++){
        vector <int> v1;
        v1.push_back(0);
        vectorSolucion.push_back(v1);
    } 

    while (listaConflictos.size()>1){
        ultimoValor = listaConflictos.back();
        listaConflictos.pop_back();

        int timeslot = 0;
        for (int tSlot = 0; tSlot < vectorSolucion.size(); tSlot++){
            bool AgregarEx = true;
            for (int ex = 0; ex <vectorSolucion[tSlot].size(); ex++){
                if (vectorSolucion[tSlot][ex] != 0){
                    if (matrizConflictos[vectorSolucion[tSlot][ex]][ultimoValor[0]-1] == 1){
                        AgregarEx = false;
                        break;
                    }
                }
                
            }
            if (AgregarEx){
                vectorSolucion[tSlot].push_back(ultimoValor[0]-1);
                break;
            }
            else{
                timeslot++;
            }
        }
        if (timeslot>timeslotMax) timeslotMax = timeslot;
        
    }
    //Se escribe el archivo con la cantidad de Bloques
    string arRes = "./Respuestas/";
    arRes += archivoRespuesta;
    arRes += ".res";
    ofstream archivoRes;
    archivoRes.open(arRes);
    archivoRes << timeslotMax;
    archivoRes.close();

    //Se escribe el archivo con la solución (IDExamen - Timeslot)
    string arSol = "./Respuestas/";
    arSol += archivoRespuesta;
    arSol += ".sol";
    ofstream archivoSol;
    archivoSol.open(arSol);
    for (int tSlot = 0; tSlot<vectorSolucion.size(); tSlot ++){
        for (int exam = 0; exam < vectorSolucion[tSlot].size(); exam++){
            if (vectorSolucion[tSlot][exam] != 0){
                archivoSol << vectorSolucion[tSlot][exam];
                archivoSol << " ";
                archivoSol << tSlot;
                archivoSol << "\n";
                }
            
        }
    }
    archivoSol.close();


    //Archivo con la cantidad de penalizaciones promedio
    vector <vector <int>> vectorEstudiantes = leerEstudiantes(archivoEstudiantes);
    
    int penalizacionPromedio = 0;
    cout << "Timeslot Final - Usando algoritmo HillClimbing: "<< timeslotMax << endl;
    
    /*
    Vamos a recorrer los exámenes de cada estudiantes y hacer un cruce con sus respectivos timeslot para obtener
    a que timeslot corresponde cada examen y así guardarlo en un vector para posteriormente trabajar con ello.
    */
    for (int estu = 0; estu< vectorEstudiantes.size(); estu++){
        int penalizacionEstudiante = 0;
        int penalizacion = 0;
        int diferencia = 0;
        vector <int> timeslotEstudiante;
        for (int ex = 0; ex < vectorEstudiantes[estu].size(); ex++){
            for (int ts = 0; ts < vectorSolucion.size(); ts++){
                if (encontrarValor(vectorSolucion[ts],vectorEstudiantes[estu][ex])){
                    timeslotEstudiante.push_back(ts);
                }
            }
        }
        sort(timeslotEstudiante.begin(), timeslotEstudiante.end());
        
        /*
        Se obtienen las diferencias correspondientes entre los timeslot.
        Dif = 1, penalización = 16.
        Dif = 2, penalización = 8.
        Dif = 3, penalización = 4.
        Dif = 4, penalización = 2.
        Dif = 5, penalización = 1.
        Dif = 6++, penalización = 0.
        Solo me interesa obtener la penalización de aquellos estudiantes que solo tienen que dar más de 2 exámenes
        */
        if (timeslotEstudiante.size()>1){
            for (int ts = 0; ts<timeslotEstudiante.size()-1; ts++){
                int valor1 = timeslotEstudiante[ts+1];
                int valor2 = timeslotEstudiante[ts];
                diferencia = valor1 - valor2;
                if (diferencia == 1) penalizacion = 16; 
                else if (diferencia == 2) penalizacion = 8; 
                else if (diferencia == 3) penalizacion = 4; 
                else if (diferencia == 4) penalizacion = 2; 
                else if (diferencia == 5) penalizacion = 1; 
                else if (diferencia >= 6) penalizacion = 0; 
                penalizacionEstudiante += penalizacion;

            }
            penalizacionEstudiante = int(penalizacionEstudiante / timeslotEstudiante.size());
            penalizacionPromedio += penalizacionEstudiante;
        }   
    }
    
    /*
    Se escribe el archivo con las penalizaciones correspondientes.
    */ 
    string arPen = "./Respuestas/";
    arPen += archivoRespuesta;
    arPen += ".pen";
    ofstream archivoPen;
    archivoPen.open(arPen);
    archivoPen << penalizacionPromedio / vectorEstudiantes.size();
    archivoPen.close();

    cout << "Penalizacion promedio: "<< penalizacionPromedio / vectorEstudiantes.size() << endl;
    





    return timeslotMax;
}