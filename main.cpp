#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <iomanip>

using namespace std;


struct equipo{
    string nombre;
    vector<double> estadisticas;
    //partidos jugados 0
    //puntos 1 
    //goles favor 2 
    //goles contra 3 
    //diferencia goles 4 
    //partidos ganados 5 
    //partidos perdidos 6 
    //partidos empatados 7
};

struct partido{
    string equipo1;
    string equipo2;
    int goles1;
    int goles2;
};

void leerarchivo(vector<partido>& Partidos){
    
    ifstream entrada("entrada.txt");
    
    string linea;
    
    if (!entrada.is_open()) {
    cout<< "Error: No se pudo abrir el archivo 'entrada'." << endl;
    } 
    
    while (getline(entrada,linea)){
        
        partido pot;
        
        pot.equipo1=linea;
        getline(entrada,pot.equipo2);
        entrada>>pot.goles1;
        entrada>>pot.goles2;
       
       entrada.ignore();
        
        Partidos.push_back(pot);
        
    }
    entrada.close();
}

void contarpartidos(vector<partido>& Partidos,map<string,equipo>& Equipos){
    
    const int tamavector=8;
    
    for(partido p: Partidos){
        
        if((Equipos.find(p.equipo1)==Equipos.end())){
            
            equipo nuevoEquipo;
            nuevoEquipo.nombre = p.equipo1;
            nuevoEquipo.estadisticas = vector<double>(tamavector, 0.0);
            Equipos[p.equipo1] = nuevoEquipo;
        }
        if((Equipos.find(p.equipo2)==Equipos.end())){
            
            equipo nuevoEquipo;
            nuevoEquipo.nombre = p.equipo2;
            nuevoEquipo.estadisticas = vector<double>(tamavector, 0.0);
            Equipos[p.equipo2] = nuevoEquipo;
        }
        
        Equipos[p.equipo1].estadisticas[0]++;
        Equipos[p.equipo2].estadisticas[0]++;
        
    }
}

void contarpuntos(vector<partido>& Partidos,map<string,equipo>& Equipos){
    
    for(partido p: Partidos){
        
        if(p.goles1 < p.goles2){
            
            Equipos[p.equipo2].estadisticas[1]+=3.0;
            
            Equipos[p.equipo1].estadisticas[6]++;
            Equipos[p.equipo2].estadisticas[5]++;
            
        }else if(p.goles1 > p.goles2){
            
            Equipos[p.equipo1].estadisticas[1]+=3.0;
            
            Equipos[p.equipo1].estadisticas[5]++;
            Equipos[p.equipo2].estadisticas[6]++;
            
        }else if(p.goles1==p.goles2){
            
            Equipos[p.equipo1].estadisticas[1]+=1.0;
            Equipos[p.equipo2].estadisticas[1]+=1.0;
            
            Equipos[p.equipo1].estadisticas[7]++;
            Equipos[p.equipo2].estadisticas[7]++;
        }
        
        Equipos[p.equipo1].estadisticas[2]+=p.goles1;
        Equipos[p.equipo1].estadisticas[3]+=p.goles2;
        
        Equipos[p.equipo2].estadisticas[2]+=p.goles2;
        Equipos[p.equipo2].estadisticas[3]+=p.goles1;
        
    }
}

void diferenciagoles(vector<partido>& Partidos,map<string,equipo>& Equipos){
    
    for(auto& par: Equipos){
        
        double golesfavor=par.second.estadisticas[2];
        double golescontra=par.second.estadisticas[3];
        double diferenciagoles= golesfavor - golescontra;
        par.second.estadisticas[4]=diferenciagoles;
    }
    
}

bool compararequipos(const equipo& equipoA, const equipo& equipoB){
    
    if(equipoA.estadisticas[1]!=equipoB.estadisticas[1]){
        
        return equipoA.estadisticas[1]>equipoB.estadisticas[1];
        
    }else if(equipoA.estadisticas[4]!=equipoB.estadisticas[4]){
        
        return equipoA.estadisticas[4]>equipoB.estadisticas[4];
        
    }else if(equipoA.estadisticas[2]!=equipoB.estadisticas[2]){
        
        return equipoA.estadisticas[2]>equipoB.estadisticas[2];
    }
    
    return equipoA.nombre>equipoB.nombre;
}

void ordenartabla(map<string,equipo>& Equipos, vector<equipo>& tablaordenada){
    
    for(auto const& x: Equipos){
        
        tablaordenada.push_back(x.second);
    }
    
    sort(tablaordenada.begin(),tablaordenada.end(),compararequipos);
    
}

void imprimirtabla(const vector<equipo>& tablaordenada){
    
    ofstream salida("salida.txt");
    
    cout << "Tabla de Equipos" << endl;
    salida << "Tabla de Equipos" << endl;

    cout << "------------------------------------------------------------------------------------------------" << endl;
    salida << "------------------------------------------------------------------------------------------------" << endl;

   cout << left << setw(25) << "Equipo"
         << setw(8) << "PJ"
         << setw(8) << "Pts"
         << setw(8) << "GF"
         << setw(8) << "GC"
         << setw(8) << "DG"
         << setw(8) << "PG"
         << setw(8) << "PP"
         << setw(8) << "PE" << endl;

    salida << left << setw(25) << "Equipo"
           << setw(8) << "PJ"
           << setw(8) << "Pts"
           << setw(8) << "GF"
           << setw(8) << "GC"
           << setw(8) << "DG"
           << setw(8) << "PG"
           << setw(8) << "PP"
           << setw(8) << "PE" << endl;
           
    cout << "------------------------------------------------------------------------------------------------" << endl;
    salida << "------------------------------------------------------------------------------------------------" << endl;
    
     for (const auto& eq : tablaordenada) {
         
        cout << left << setw(25) << eq.nombre
             << right <<setw(8) << (int)eq.estadisticas[0]
             << setw(8) << (int)eq.estadisticas[1]
             << setw(8) << (int)eq.estadisticas[2]
             << setw(8) << (int)eq.estadisticas[3]
             << setw(8) << (int)eq.estadisticas[4]
             << setw(8) << (int)eq.estadisticas[5]
             << setw(8) << (int)eq.estadisticas[6]
             << setw(8) << (int)eq.estadisticas[7] << endl;

        salida << left << setw(25) << eq.nombre
             << right <<setw(8) << (int)eq.estadisticas[0]
             << setw(8) << (int)eq.estadisticas[1]
             << setw(8) << (int)eq.estadisticas[2]
             << setw(8) << (int)eq.estadisticas[3]
             << setw(8) << (int)eq.estadisticas[4]
             << setw(8) << (int)eq.estadisticas[5]
             << setw(8) << (int)eq.estadisticas[6]
             << setw(8) << (int)eq.estadisticas[7] << endl;
    }
    cout << "------------------------------------------------------------------------------------------------" << endl;
    salida << "------------------------------------------------------------------------------------------------" << endl;
    
    salida.close();
}

int main()
{
    vector<partido> Partidos;
    map<string,equipo> Equipos;
    vector<equipo> tablaordenada;
    
    leerarchivo(Partidos);
    contarpartidos(Partidos, Equipos);
    contarpuntos(Partidos, Equipos);
    diferenciagoles(Partidos, Equipos);
    ordenartabla(Equipos,tablaordenada);
    imprimirtabla(tablaordenada);
    
    ofstream salida2("salida2.txt");
    
    for(partido x: Partidos){
      
      cout << left << setw(25) << x.equipo1 << setw(8) <<x.goles1;
      cout << right <<setw(25) << x.equipo2 << setw(8) << x.goles2<<endl;
      
      salida2 << left << setw(25) << x.equipo1 << setw(8) <<x.goles1;
      salida2 << right <<setw(25) << x.equipo2 << setw(8) << x.goles2<<endl;
      
    }
    
    salida2.close();

    return 0;
}