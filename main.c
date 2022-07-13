#include "Porto-Pontos//Linked_List/linked_list.h"
#include "Genetic-Algorithm/genetic_algorithm.h"


int main() {
    // create linked list
    LINKED_LIST list = LL_constructor();

    // create a client
    CLIENT client_one = CLIENT_constructor("Andre", 321, "Lisbon", 12343453);
    CLIENT client_two = CLIENT_constructor("Hugo", 123, "Porto", 123456789);
    CLIENT client_three = CLIENT_constructor("Ana", 546, "Faro", 123456123);

    // create a trip
    COUNTRY england = COUNTRY_constructor("England");
    COUNTRY france = COUNTRY_constructor("France");
    COUNTRY switzerland = COUNTRY_constructor("Switzerland");
    // insert a booked trip
    client_one.insert_trip(&client_one, england);
    client_one.insert_trip(&client_one, france);
    client_one.insert_trip(&client_one, switzerland);
    // remove a booked trip
    client_one.remove_trip(&client_one, france);
    // edit a booked trip
    client_one.edit_trip(&client_one, england, "Angola");
    //print booked trips
    client_one.print_trips(&client_one, false);

    // create a city
    CITY london = CITY_constructor("London", 12.4f, 54.6f);
    CITY brighton = CITY_constructor("Brighton", 72.3f, 24.6f);
    CITY manchester = CITY_constructor("Manchester", 52.0f, 84.6f);
    CITY porth = CITY_constructor("Porth", 12.4f, 23.45f);
    // insert a city
    england.insert_city(&england, london);
    england.insert_city(&england, brighton);
    england.insert_city(&england, manchester);
    england.insert_city(&england, porth);
    // remove a city
    //england.remove_city(&england, brighton);
    // edit a city
    england.edit_city(&england, london, "Birmingham", 34.2f, 12.345f);
    // print cities
    england.search_city(&england, manchester);

    // insert a client
    list.insert_client(&list, false, client_one);
    list.insert_client(&list, true, client_two);
    list.insert_client(&list, true, client_three);
    // remove a client
    list.remove_client(&list, client_two);
    // print clients
    list.print_clients(&list);

    initialize_algorithm(&england, 5, 4, 0, 0.1f);

    return 0;
}
