#include <iostream>
#include <string>
#include <vector>
#include <fstream>

/**
 * 
 * Actividad 1.3
 * Estructura de Datos y Algoritmos 
 * Prof. Baldomero Olvera Villanueva
 * 
 * Código que lee un archivo, ordena los datos en base a su UBI y fecha, pide
 * al usuario los primeros 3 caracteres del UBI e imprime todas las coincidencias.
 * 
 * Andrés Daniel Martínez - A00227463
 * Fernanda Granados - A01252895
 * Santiago Poblete - A01254609
 * Martín Tanori - A01252900
 * 
 */

std::vector<std::string> read_file_and_add_to_vector(std::string file_name)
{
    std::vector<std::string> lines;
    std::ifstream file(file_name);
    std::string line;
    try {
        while (std::getline(file, line))
        {
            lines.push_back(line);
        }
    }
    catch (std::exception e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }
    return lines;
}

template <typename T>
void printVector(std::vector<T> vec) //mayormente por propositos de debugging
{
    for (auto i : vec)
    {
        std::cout << i << std::endl;
    }
}

std::string get_id(std::string line)
{
    size_t lastSpacePos = line.find_last_of(' ');
    std::string id = "";
    if (lastSpacePos != std::string::npos)
    {
        // Porcion del ID empezando del caracter después del último espacio.
        id = line.substr(lastSpacePos + 1);
        id = id.substr(0, 5); // primeros 5 caracteres
    }
    else
    {
        std::cerr << "No ID found in the input string." << std::endl;
    }
    return id;
}


void busqBinaria(std::vector<std::string> vect, std::string clave){
    if (clave.length() != 3) { 
      std::cout << "Por favor elige una clave de 3 digitos." << std::endl; 
      return; 
    }
    int bajo = 0;
    int alto = vect.size()-1;

    while(bajo<=alto){
        int mitad = (alto+bajo)/2;
        if(get_id(vect[mitad]).substr(0,3) == clave){
            int i = 1;
            int j = 1;
            int inicio = 0;
            int fin = 0;

            while(get_id(vect[mitad-i]).substr(0,3) == clave){
                inicio = mitad-i;
                i++;
            }
            while(get_id(vect[mitad+j]).substr(0,3) == clave){
                fin = mitad+j;
                j++;
            }
            
            for(int k = inicio; k <= fin; k++){
                std::cout << vect[k].substr(0,24) << " en posicion " << k+1 << std::endl;
            }
            break;

        } else if(clave < get_id(vect[mitad]).substr(0,3)){
            alto = mitad - 1;
        } else{
            bajo = mitad + 1;
        }
    }
}


void une(std::vector<std::string>& vect, int inicio, int mitad, int fin){
    int i  = inicio; 
    int j = mitad+1;
    int k = inicio;
    std::vector<std::string> aux(vect.size());

    while(i<=mitad && j<=fin){
        if(get_id(vect[i]) < get_id(vect[j])){
            aux[k] = vect[i];
            i++;
        } else if(get_id(vect[i]) == get_id(vect[j])){    //  UBI es igual
            std::string fecha1 = vect[i].substr(6,4) + vect[i].substr(3,2) + vect[i].substr(0,2);
            std::string fecha2 = vect[j].substr(6,4) + vect[j].substr(3,2) + vect[j].substr(0,2);

            if(fecha1<=fecha2){
                aux[k] = vect[i];
                i++;
            } else{
                aux[k] = vect[j];
                j++;
            }
            
        } else{
            aux[k] = vect[j];
            j++;
        }
        k++;
    }

    while(i<=mitad){
        aux[k] = vect[i];
        i++;
        k++;
    }

    while(j<=fin){
        aux[k] = vect[j];
        j++;
        k++;
    }
    
    for(int index=inicio; index<=fin; index++){ // regresa al vector original 
        vect[index] = aux[index];
    }
}

void merge(std::vector<std::string>& vect, int inicio, int fin){
    if(inicio<fin){
        int mitad = (inicio+fin)/2;
        merge(vect, inicio, mitad);
        merge(vect, mitad+1, fin);
        une(vect, inicio, mitad, fin);
    }
}


int main(){
    std::cout << "Escribe el nombre del archivo a utilizar: " << std::endl; 
    std::string inp; 
    std::cin >> inp;
  
    std::vector<std::string> lines = read_file_and_add_to_vector(inp);
  
    merge(lines, 0, lines.size()-1);
    std::ofstream bitacora_output("bitacora_output.txt");

    std::string targettedNum;
    std::cout << "Escribe los primeros tres caracteres del UBI:" << std::endl;
    std::cin >> targettedNum;

    busqBinaria(lines, targettedNum);
    for (int i = 0; i < lines.size(); i++){
        bitacora_output << lines[i] << std::endl;
    }
    std::cout << "Archivos ordenados en bitacora_output.txt" << std::endl; 
    std::cout << "Listo!" << std::endl;

    return 0;
}