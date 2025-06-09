#include<iostream>
#include<vector>
#include<numeric>
#include<sstream>
#include<time.h>
#include<string>
#include<string.h>
#include<cstdlib> 
#include<ctime>
#include<chrono>
#include<fstream>
#include<cstdint>
#include<stack>
#include<random>
#include<climits>


using namespace std;

//-----Creacion de vectores-----

vector<int32_t> crear_vector_random(int size){
	vector<int32_t> vec;
	for(int i = 0; i < size; i++) {
		vec.push_back(1 + rand() % 10000);
	}
	return vec;
}

vector<int32_t> crear_vector_ordenado(int size){
	vector<int32_t> vec;
	for(int i = 0; i < size; i++){
		vec.push_back(i);
	}
	return vec;
}

vector<int32_t> crear_vector_invertido(int size){
	vector<int32_t> vec;
	for(int i = size; i > 0; i--){
		vec.push_back(i);
	}
	return vec;
}

//-----Creacion de archivos-----

void generarArchivo(const std::string& nombreArchivo, int megabytes) {
    const int bytesPorMB = 1024 * 1024;
    const int bytesPorEntero = sizeof(int32_t);
    const int totalEnteros = (megabytes * bytesPorMB) / bytesPorEntero;

    std::ofstream archivo(nombreArchivo, std::ios::binary);
    if (!archivo) {
        std::cerr << "Error al crear el archivo" << std::endl;
        return;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int32_t> distrib(INT32_MIN, INT32_MAX);

    for (int i = 0; i < totalEnteros; ++i) {
        int32_t num = distrib(gen);
        archivo.write(reinterpret_cast<const char*>(&num), sizeof(num));
    }

    std::cout << "Archivo generado: " << nombreArchivo 
              << " - Tamano: " << megabytes << " MB"
              << " - Enteros: " << totalEnteros << std::endl;
}


//-----Lista de sorts-----

//-----Insertion-----
void insertion_sort(vector<int32_t>& vec){
	int temp;
	for(int i = 1; i < vec.size(); i++){
		int key = vec[i];
		int j = i - 1;

		while(j >= 0 && vec[j] > key){
			vec[j+1] = vec[j];
			j = j-1;
		}
		vec[j+1] = key;
	}
}

//-----Heap (Sigue la logica, no esta hecho con nodos)-----
void heap(vector<int32_t>& vec, int i, int n){
	int temp;
	int hijo_izq = 2*i + 1;
	int hijo_der = 2*i + 2;
	int mayor = i;

	if(hijo_izq	< n && vec[hijo_izq] > vec[mayor]){
		mayor = hijo_izq;
	}

	if(hijo_der < n && vec[hijo_der] > vec[mayor]){
		mayor = hijo_der;
	}

	if(mayor != i){
		temp = vec[i];
		vec[i] = vec[mayor];
		vec[mayor] = temp;
		heap(vec, mayor, n);
	}
}

void heap_sort(vector<int32_t>& vec){
	int n = vec.size();
	int temp;

	for(int i = (n/2)-1; i >= 0; i--){
		heap(vec, i, n);
	}

	for(int i = n-1; i > 0; i--){
		temp = vec[0];
		vec[0] = vec[i];
		vec[i] = temp;
		heap(vec, 0, i);
	}
}

//-----Sort de la libreria de c-----
//sort(vec.begin(), vec.end());


//-----Merge-----
vector<int32_t> merge(vector<int32_t> izquierda, vector<int32_t> derecha){
	vector<int32_t> resultado;
	int i = 0;
	int j = 0;

	while(i < izquierda.size() && j < derecha.size()) {
		if(izquierda[i] <= derecha[j]) {
			resultado.push_back(izquierda[i]);
			i++;
		}else {
			resultado.push_back(derecha[j]);
			j++;
		}
	}

	while(i < izquierda.size()){
		resultado.push_back(izquierda[i]);
		i++;
	}

	while(j < derecha.size()){
		resultado.push_back(derecha[j]);
		j++;
	}

	return resultado;
}

vector<int32_t> merge_sort(vector<int32_t> vec){
	if(vec.size() <= 1){
		return vec;
	}
	
	int mitad = vec.size()/2;
	vector<int32_t> subvector_izq(vec.begin(), vec.begin() + mitad);
	vector<int32_t> subvector_der(vec.begin()+mitad, vec.end());
	vector<int32_t> izquierda = merge_sort(subvector_izq);
	vector<int32_t> derecha = merge_sort(subvector_der);

	return merge(izquierda, derecha);
}

//-----Quick recursivo-----
void quick_sort_recursivo(vector<int32_t>& vec, int inicio, int fin){ //vec,0,size-1
	int temp;
	int p;
	int i;
	int pivote;
	if(inicio < fin){
		pivote = vec[rand() % (fin-inicio + 1) + inicio];
		i = inicio - 1;
		for(int j = inicio; j < fin; j++){
			if(vec[j] <= pivote){
				i = i + 1;
				temp = vec[i];
				vec[i] = vec[j];
				vec[j] = temp;
			}
		}
		temp = vec[i+1];
		vec[i+1] = vec[fin];
		vec[fin] = temp;
		p = i+1;

	quick_sort_recursivo(vec, inicio, p-1);
	quick_sort_recursivo(vec, p+1, fin);
	}
}

//-----Quick iterativo-----
void quick_sort_iterativo(vector<int32_t>& vec) {
    stack<pair<int, int>> stack;
    stack.push({0, (int)vec.size() - 1});

    while (!stack.empty()) {
        pair<int, int> current = stack.top();
        stack.pop();
        
        int inicio = current.first;
        int fin = current.second;

        if (inicio >= fin) continue;

        int pivote = vec[(inicio + fin) / 2];
        int i = inicio, j = fin;

        while (i <= j) {
            while (vec[i] < pivote) i++;
            while (vec[j] > pivote) j--;
            if (i <= j) swap(vec[i++], vec[j--]);
        }

        if (inicio < j) stack.push({inicio, j});
        if (i < fin) stack.push({i, fin});
    }
}

//-----Selection-----
vector<int32_t> selection_sort(vector<int32_t> vec){
	int temp;
	int menor = vec[0];
	for(int i = 0; i < vec.size(); i++){
		for(int j = i+1; j < vec.size(); j++){
			if(vec[j] < vec[i]){
				temp = vec[i];
				vec[i] = vec[j];
				vec[j] = temp;
			}
		}
	}
	return vec;
}

//Lectura de vector
vector<int32_t> leer_vector(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cerr << "Error al abrir el archivo: " << filename << endl;
        return {};  // Retorna vector vacío si hay error
    }
    
    file.seekg(0, ios::end);
    size_t file_size = file.tellg();
    file.seekg(0, ios::beg);
    
    if (file_size % sizeof(int32_t) != 0) {
        cerr << "Tamaño de archivo incompatible" << endl;
        return {};
    }
    
    vector<int32_t> vec(file_size / sizeof(int32_t));
    file.read(reinterpret_cast<char*>(vec.data()), file_size);
    
    if (!file) {
        cerr << "Error al leer el archivo" << endl;
        return {};
    }
    
    return vec;
}



//-----Ejemplo de testeo-----
int main() {
	srand(time(0));
	/*int size = 500000;
	vector<int32_t> vec*/;
	vector<double> duraciones_promedio;
	vector<double> duraciones;
	chrono::high_resolution_clock::time_point start, end;
    chrono::duration<double> duracion;
	int Tarchivo = 1;
	int automatico = 1; 
	while(automatico < 4){
		duraciones.clear();
		for(int i = 0; i < 30; i++){

			generarArchivo("vector.bin", Tarchivo);
			vector<int32_t> vec = leer_vector("vector.bin");
			start = chrono::high_resolution_clock::now(); //Toma el tiempo de ejecucion.
			quick_sort_iterativo(vec);
			end = chrono::high_resolution_clock::now();
			duracion = end - start;
			duraciones.push_back(duracion.count());
		}
		for(int i = 0; i < duraciones.size(); i++){
			cout << "duracion " << i << ":" << duraciones[i] << endl;
		}
		double suma = 0.0;
        for(double d : duraciones) {
            suma += d;
        }
		duraciones_promedio.push_back(suma / duraciones.size());
		automatico++;
		Tarchivo = Tarchivo*2;
	}

	cout << "\nResumen de promedios por tamano:" << endl;
    int current_size = 1;
    for(int i = 0; i < duraciones_promedio.size(); i++) {
        cout << current_size << " MB: " << duraciones_promedio[i] << " s" << endl;
        current_size *= 2;
    }
	

	/*for(int i = 0; i < 100; i++){
		vec = crear_vector_random(size);
		start = chrono::high_resolution_clock::now(); //Toma el tiempo de ejecucion.
		vec = insertion_sort(vec);
		end = chrono::high_resolution_clock::now();
		duracion = end - start;
		duraciones.push_back(duracion.count());
	}
	cout << endl;

	for(int i = 0; i < duraciones.size(); i++){
		cout << "duracion " << i << ":" << duraciones[i] << endl;
	}

	//caso ordenado:
	vec = crear_vector_ordenado(size);
	start = chrono::high_resolution_clock::now();
	vec = insertion_sort(vec);
	end = chrono::high_resolution_clock::now();
	duracion = end - start;
	cout << "ordenado: "<< duracion.count() << endl;

	//caso invertido:
	vec = crear_vector_invertido(size);
	start = chrono::high_resolution_clock::now();
	vec = insertion_sort(vec);
	end = chrono::high_resolution_clock::now();
	duracion = end - start;
	cout << "invertido: "<< duracion.count() << endl;
	*/

	return 0;
}