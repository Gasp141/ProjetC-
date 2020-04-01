#include <iostream>  
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

string inttostr(int a){
    return std::to_string(a);
}

int strtoint(string a){
    return std::stoi(a);
}

void decodagedate(int a) {
    string code;
    string date;
    code = inttostr(a);
    cout<< code[6] << code[7] << "/" << code[4] << code[5]<< "/" << code[0] << code[1] << code[2] << code[3] <<endl;
    }

string codage(string phrase){
    for (int i = 0; i<phrase.size();i++){
        char esp = ' ';
        char tir = '_';
        if (phrase[i] == esp){
            phrase[i] = tir;
        }
    }
    return phrase;
}
string decodage(string code){
    for (int i = 0; i<code.size();i++){
        char esp = ' ';
        char tir = '_';
        if (code[i] == tir){
            code[i] = esp;
        }
    }
    return code;
}

vector<string> slice(string chaine, int debut=0, int fin=-1) {
	vector<char> v(chaine.begin(), chaine.end());
    int ancienlen = v.size();
    int newlen;
    if (fin == -1 or fin >= ancienlen){
        newlen = ancienlen-debut;
    } else {
        newlen = fin-debut;}
    vector<string> nouveau(newlen);
    for (int i=0; i<newlen; i++) {
        nouveau[i] = v[debut+i]; }
    return nouveau;
}

class comment {
    friend class task;
    string com;
    public:
    comment(string text) : com(text){}
};

class task {
private:
    string id;  
    string title;
    int datedebut;
    int datefin;
    string status;  
    int pourcent;
    string priority;    // high, normal, classified
    vector<comment> com;
    vector<string> subtask;
public:
task(string titre, int debut, int fin, string prio) : title(titre), datedebut(debut), datefin(fin), priority(prio) {
status = "ouverte";
pourcent = 0 ;
ifstream fichier("Taskmanager.txt");
int nb;
    if(fichier){
    //string li; 
    fichier.seekg(0, ios::end);
    //fichier >> li;
    nb = fichier.tellg();}
    else {
        cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;};       
fichier.close();
id = inttostr(nb) + title[0] + title[1] + title[2] + prio[0] +  prio[1] +  prio[2];
ofstream fichier1("Taskmanager.txt", ios::app);
if(fichier1) {
    fichier1.seekp(0, ios::end);
    fichier1 << id << " "<< title << " "<<datedebut<<" "<<datefin<< " "<< status<< " "<< pourcent<< " " << priority<< endl; 
    fichier1.seekp(13, ios::beg); 
}
else {
    cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;};       
fichier1.close();}

void afficher () {
    cout << "Titre : " << decodage(title) << endl;
    cout << "Date début : ";
    decodagedate(datedebut);
    cout << "Date fin : ";
    decodagedate(datefin);
    cout << "Status : " << status << endl;
    cout << "Priorité : " << priority << endl;   
}
};
vector<string> decoupage(string ligne){
    vector<string> liste;
    liste.push_back("");
    int a = 0;
    for (int i(0); i<ligne.size() ;i++){
        char mot =' ';
        if (ligne[i] == mot){
            a=a+1;
            liste.push_back("");
        }
        else{
            liste[a] = liste[a] + ligne[i];
        }
    }
    return liste;
}

void recherche(string parametre, string precision, string precision2 ="none") {
    int nombre;
    if (parametre == "titre") {nombre = 1;}
    if (parametre == "date_debut") {nombre = 2;}
    if (parametre == "date_fin") {nombre = 3;}
    if (parametre == "id") {nombre = 0;}
    if (parametre == "priority") {nombre = 6;}
    ifstream newflux("Taskmanager.txt");
    if(newflux){
        string ligne; 
        while(getline(newflux, ligne)) {
            vector<string> commande;
            commande = decoupage(ligne);
            if (commande[nombre] == precision and (precision2=="none" or precision2=="exact")) {
                cout << ligne << endl;}
            if (precision2 !="none" and precision2!="exact") {
                cout<< "commande non finalisée"<<endl;
                //if (precision2=="avant" and strtoint(commande[nombre])<= strtoint(precision)) {
                   //cout<< ligne<< endl;}
                //if (precision2=="apres" and strtoint(commande[nombre])>= strtoint(precision)){
                  //  cout<< ligne<< endl;}
            }
        }
    }   
    else {
        cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
    }       
newflux.close();
}


int main () {
    
    //std::string const nomFichier("/Users/gasparddeturckheim/desktop/c++/Taskmanager.txt");
    //std::ofstream monFlux(nomFichier.c_str(), std::ios::app);

    string action;
    while (action != "quit") {
        cout << "action ? (create, recherche, quit)" <<endl;
        getline(cin,action);
        if(action == "create"){
            string ligne;
            cout<< "Titre debut fin priorité" <<endl;
            getline(cin,ligne);
            vector<string> commande;
            int d1;
            int d2;
            commande = decoupage(ligne);
            d1= strtoint(commande[1]);
            d2 = strtoint(commande[2]);
            task newtache(commande[0], d1, d2,commande[3]);
            newtache.afficher();
        }
        if(action == "recherche") {
            string ligne;
            cout<< "paramètre ? (titre, date_debut, date_fin, priority) " <<endl;
            getline(cin,ligne);
            if(ligne == "priority") {
                cout<< "préciser ? (high, normal, classified) " <<endl;
                string paramètre;
                getline(cin,paramètre);
                recherche("priority",paramètre);
            }
            if(ligne == "titre") {
                cout<< "nom ?  " <<endl;
                string paramètre;
                getline(cin,paramètre);
                recherche(ligne,paramètre);
            }
            if(ligne == "date_debut" or "date_fin") {
                cout<< "date? (format aaaa/mm/jj)" <<endl;
                string paramètre;
                getline(cin,paramètre);
                cout<< "precision ? (avant, exact, apres)" <<endl;
                string precision;
                getline(cin,precision);
                recherche(ligne,paramètre,precision);
            }
        }
    }    

    return 0;
}

