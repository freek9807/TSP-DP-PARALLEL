#ifndef UTI_DEF
#define UTI_DEF

#include <iostream>
#include <string>
#include <vector>
#include "../Location/Location.h"
#include "../TSP/TSP.h"

using namespace std;
/**
 * Callback function for internet connectin
 * @param ptr Pointer where it should append data
 * @param size Message size
 * @param nmemb size of word
 * @param data data from server
 * @return message size
 */
size_t writeFunction(void *ptr, size_t size, size_t nmemb, std::string* data);
/**
 * Print the locations list in a table format
 * @param locations vector of Location pointers  list
 */
void printTable(vector<Location*> locations);
/**
 * Compare function to get min path
 * @param p A path pointer
 * @param p1 A second path pointer
 * @return If p < p1
 */
bool myfn(Path* p,Path* p1);

#endif