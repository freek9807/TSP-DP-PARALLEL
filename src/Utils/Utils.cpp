#include "Utils.h"

void printTable(vector<Location*> locations){
    int maxS = 0;
    int maxLat = 0;
    int maxLng = 0;
    for(auto&& loc: locations){
        int s = snprintf(NULL,0,"%s",loc->getName().c_str());
        int la = snprintf(NULL,0,"%.2f",loc->getLat());
        int ln = snprintf(NULL,0,"%.2f",loc->getLng());
        if(s > maxS)
            maxS = s;
        if(la > maxLat)
            maxLat = la;
        if(ln > maxLng)
            maxLng = ln;
    }
    string row = "| %" + to_string(maxS) + "s | %" + to_string(maxLat) + ".2f | %" + to_string(maxLng) + ".2f |" + "\n";
    string header = "| %-" + to_string(maxS) + "s | %-" + to_string(maxLat) + "s | %-" + to_string(maxLng) + "s |" + "\n"; 
    for(int i = 0; i < maxS + maxLng + maxLat + 4 + 6; i++){
        cout << "-";
    }
    cout << endl;
    printf(header.c_str(),"","","");
    printf(header.c_str(),"City","Lat","Lng"); 
    printf(header.c_str(),"","","");
    for(int i = 0; i < maxS + maxLng + maxLat + 4 + 6; i++){
        cout << "-";
    }
    cout << endl;
    for(auto&& loc:locations){
        printf(row.c_str(),loc->getName().c_str(),loc->getLat(),loc->getLng());
    }
    for(int i = 0; i < maxS + maxLng + maxLat + 4 + 6; i++){
        cout << "-";
    }
    cout << endl;
}

bool myfn(Path* p,Path* p1){
    return p->cost < p1->cost;
}

size_t writeFunction(void *ptr, size_t size, size_t nmemb, std::string* data) {
    data->append((char*) ptr, size * nmemb);
    return size * nmemb;
}