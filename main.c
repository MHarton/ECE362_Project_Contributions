#include "jsonParser.h"


//TESTING, I GUESS. WOOPS.




int main()
{

    char *jso_std= "{\"coord\":{\"lon\":-0.13,\"lat\":51.51},\"weather\":[{\"id\":300,\"main\":\"Drizzle\",\"description\":\"light intensity drizzle\",\"icon\":\"09d\"}],\"base\":\"stations\",\"main\":{\"temp\":280.32,\"pressure\":1012,\"humidity\":81,\"temp_min\":279.15,\"temp_max\":281.15},\"visibility\":10000,\"wind\":{\"speed\":4.1,\"deg\":80},\"clouds\":{\"all\":90},\"dt\":1485789600,\"sys\":{\"type\":1,\"id\":5091,\"message\":0.0103,\"country\":\"GB\",\"sunrise\":1485762037,\"sunset\":1485794875},\"id\":2643743,\"name\":\"London\",\"cod\":200}";
    char *jso_metric = "{\"message\":\"accurate\",\"cod\":\"200\",\"count\":1,\"list\":[{\"id\":2643743,\"name\":\"London\",\"coord\":{\"lat\":51.5085,\"lon\":-0.1258},\"main\":{\"temp\":7,\"pressure\":1012,\"humidity\":81,\"temp_min\":5,\"temp_max\":8},\"dt\":1485791400,\"wind\":{\"speed\":4.6,\"deg\":90},\"sys\":{\"country\":\"GB\"},\"rain\":null,\"snow\":null,\"clouds\":{\"all\":90},\"weather\":[{\"id\":701,\"main\":\"Mist\",\"description\":\"mist\",\"icon\":\"50d\"},{\"id\":300,\"main\":\"Drizzle\",\"description\":\"light intensity drizzle\",\"icon\":\"09d\"}]}]}";
    wdata *curr_weather = (wdata *)malloc(sizeof(wdata));
    jtable *jTabby;
    //Standard
    jTabby = split_a_string(jso_std);
    //print_table(*jTabby);
    jsonParse(*jTabby, curr_weather);
    print_weather(*curr_weather);
    free_jTable(jTabby);
    clean_Weather(curr_weather);
    free_Weather(curr_weather);

    //Metric
    curr_weather = (wdata *)malloc(sizeof(wdata));
    jTabby = split_a_string(jso_metric);
    //print_table(*jTabby);
    jsonParse(*jTabby, curr_weather);
    print_weather(*curr_weather);
    free_jTable(jTabby);
    clean_Weather(curr_weather);
    free_Weather(curr_weather);
    return 0;
}
