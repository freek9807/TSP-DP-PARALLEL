#include <curl/curl.h>
#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include <tsl/robin_map.h>
#include <nlohmann/json.hpp>
#include "external/CImg/CImg.h"
#include "src/TSP/TSP.h"
#include "src/Location/Location.h"
#include "src/Utils/Utils.h"
#include "src/Proj/Proj.h"

using namespace std;
using namespace cimg_library;

using json = nlohmann::json;
/**
 * Application Main
 * @param argc args count from cli
 * @param argv args value from cli
 * @return application result
 */
int main(int argc, char** argv) {
    // Num of nations to retrieve from server
    int limit = argc > 1 ? atoi(argv[1]) : 10;
    // Init CURL
    auto curl = curl_easy_init();
    // Distance matrix
    auto** adj = new double*[limit];
    for(int i = 0; i < limit; i++){
        adj[i] = new double[limit];
    }
    // Try to establish a connection with the server
    if (curl) {
        // Trying to prepare the connection
        curl_easy_setopt(curl, CURLOPT_URL, "https://restcountries.eu/rest/v2/all");
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
        curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
        curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L); 
        std::string response_string;
        std::string header_string;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);
        char* url;
        long response_code;
        double elapsed;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
        curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &elapsed);
        curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &url);
        // Connection is coming
        int res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        // If the connection has end with OKAY status
        if(res == CURLE_OK){
            // From JSON to C++ Object
            auto obj = json::parse(response_string);

            vector<Location*> locations;
            tsl::robin_map<string,Location*> locations_map;
            // From JSON C++ Object to Locations
            int count = 0;
            for (auto& el : obj.items())
            {
                if(count++ >= limit)
                    break;

                if(el.value()["latlng"][0].is_number_float() && el.value()["latlng"][1].is_number_float()){
                    auto* loc = new Location(el.value()["name"],el.value()["latlng"][0],el.value()["latlng"][1]);
                    locations.push_back(loc);
                    locations_map[el.value()["name"]] = loc;
                }
            }
            // Calculating distance
            int c = 0;
            for(auto&& val : locations){
                int j = 0;
                for(auto&& val2 : locations){
                    adj[c][j] = HaversineDistance(val->getLat(),val->getLng(),val2->getLat(),val2->getLng());
                    j++;
                }
                c++;
            }
            // From location to index
            vector<int*> sub;
            int s[locations.size() - 1];
            for(vector<Location*>::size_type i = 1; i < locations.size(); i++){
                s[i - 1] = i;
                sub.push_back(&s[i - 1]);
            }
            // Printing data into a label on stdout
            printTable(locations);
            int s1 = 0;
            // Vector of parallel operation result
            vector<Path*> pathPar(sub.size());
            auto start = chrono::system_clock::now();
            // The first level is parallel, the following not
            #pragma omp parallel for default(none) shared(sub,adj,pathPar,s1)
            for(unsigned long paral = 0; paral < sub.size(); paral++) {
                // Creating the remaining value set for this node
                vector<int*> sub1(sub.size() - 1);
                int i = 0;
                for(int* inside:sub){
                    if(*inside != *sub[paral]){
                        sub1[i++] = inside;
                    }
                } 
                // Crating the class
                auto *t = new TSP_Class(&s1, sub[paral],
                        adj[s1][*sub[paral]], adj, sub1);
                // Start TSP operations
                pathPar[paral] = t->start();
            }
            // Getting the min parallel cost path
            Path* p = *std::min_element(pathPar.begin(),pathPar.end(),myfn);
            // Getting time
            auto end = chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = end-start;
            // Printing time
            std::cout << "\nExecution Time : " << elapsed_seconds.count() << " s\n";
            // Printing time and path
            cout << '\n'<< "Min cost is: " << p->cost<< endl << '\n';
            for(vector<Location*>::size_type j = 0; j < p->path.size() - 1; j++){
                cout << locations[*p->path[j]]->getName() << " -> ";
            }
            cout << locations[*p->path[p->path.size() - 1]]->getName() << endl;
            // Printing Map
            CImg<unsigned char> img("assets/geographic.png");  
            Proj map(img.height(),img.width()); 
            // Printing distance Polygon
            unsigned char color[] = { 108,91,123};
            count = 0;
            for(vector<Location*>::size_type j = 0; j < p->path.size() - 1; j++){
                for(int i = 0; i < 3; i++){
                img.draw_line(
                    map.lngToXCoordinate(locations[*p->path[j]]->getLng()) + 65 + i,
                    map.latToYCoordinate(locations[*p->path[j]]->getLat()) ,
                    map.lngToXCoordinate(locations[*p->path[j + 1]]->getLng()) + 65 + i,
                    map.latToYCoordinate(locations[*p->path[j + 1]]->getLat()) ,
                    color
                    );
                }
            }
            // Printing location pin
            color[0] = 53;
            color[1] = 92;
            color[2] = 125;
            for(vector<Location*>::size_type j = 0; j < p->path.size() - 1; j++){
                auto val = locations[*p->path[j]];
                auto s = std::to_string(++count);
                const unsigned char colorT[] = {255,255,255};
                // Pin
                img.draw_circle(map.lngToXCoordinate(val->getLng()) + 65,map.latToYCoordinate(val->getLat()),8,color);
                // Number
                if(s.size() == 2){
                    img.draw_text(map.lngToXCoordinate(val->getLng()) + 60,map.latToYCoordinate(val->getLat()) - 6,s.c_str(),colorT,0,1,13);
                } else {
                    img.draw_text(map.lngToXCoordinate(val->getLng()) + 63,map.latToYCoordinate(val->getLat()) - 6,s.c_str(),colorT,0,1,13);
                }
            }
            // Storing the image
            CImgDisplay main_disp(img, "Visualization TSP Result");     
            img.save("map.png");  
            cout << "Map has been printed!" <<endl;                      
        } else {
            cout << "Connection error with " << "https://restcountries.eu/rest/v2/all" << endl;
        }
        curl = nullptr;
    }

    return 0;
}