#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

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

int main()
{
    vector<partido> Partidos;
    map<string,equipo> Equipos;
    
    leerarchivo(Partidos);
    contarpartidos(Partidos, Equipos);
    contarpuntos(Partidos, Equipos);
    diferenciagoles(Partidos, Equipos);
    
    ofstream salida2("salida2.txt");
    
    for(partido x: Partidos){
      
      cout<<x.equipo1<<" "<<x.goles1<<" "<<x.equipo2<<" "<<x.goles2<<endl;
      salida2<<x.equipo1<<" "<<x.goles1<<" "<<x.equipo2<<" "<<x.goles2<<endl;
    }
    
    
    ofstream salida("salida.txt");
    
    for(auto x: Equipos){
        
        cout<<x.first<<" Pj: "<<x.second.estadisticas[0]<<" Pts: "<<x.second.estadisticas[1]<<" Gf: "<<x.second.estadisticas[2]<<" Gc: "<<x.second.estadisticas[3]<<" Df: "<<x.second.estadisticas[4]<<" Pg: "<<x.second.estadisticas[5]<<" Pp: "<<x.second.estadisticas[6]<<" Pe: "<<x.second.estadisticas[7]<<endl;
        salida<<x.first<<" Pj: "<<x.second.estadisticas[0]<<" Pts: "<<x.second.estadisticas[1]<<" Gf: "<<x.second.estadisticas[2]<<" Gc: "<<x.second.estadisticas[3]<<" Df: "<<x.second.estadisticas[4]<<" Pg: "<<x.second.estadisticas[5]<<" Pp: "<<x.second.estadisticas[6]<<" Pe: "<<x.second.estadisticas[7]<<endl;
        
    }
    
    salida.close();
    salida2.close();

    return 0;
}