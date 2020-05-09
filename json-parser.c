#include <stdio.h>
#include <ctype.h>
#include <json-c/json.h>

int main(int argc, char **argv) {

    FILE *fp;
    char buffer[1024], thisText[1024];
    


    struct json_object *parsed_json, *idk, *maybe;
    struct json_object_iterator it, that;

    int aSize;

    
//  File Operations
    fp = fopen("items.json", "r");
    fread(buffer, 1024, 1, fp);
    fclose(fp);

//  Defining our json object and starting the parser
    parsed_json = json_tokener_parse(buffer);
    it = json_object_iter_begin(parsed_json);
    aSize = json_object_object_length(parsed_json);
    const char *items[aSize];

//  Welcome message and sharing the number of items in the json object
    printf("Hello, this code will parse a nested json.\nFeel free to add new stuff,\nit should adapt itself\n\n");
    printf("Number of items: %d\n\n", aSize); 


//  Ok so this loop is a bit complex
//  the first loop gets the name of the item, and its length
//  then the second loop gets each field of the values
//  This probably doesn't work with arrays for now...
//  not until I add type checks to do different conversions for the type of the object

    for (int i = 0; i < aSize; i++) {
        items[i] = json_object_iter_peek_name(&it);
        json_object_iter_next(&it);

        json_object_object_get_ex(parsed_json, items[i], &idk);
        that = json_object_iter_begin(idk);
        int idkLength = json_object_object_length(idk);
        
        printf("Name: %s\nLength: %i\nValues:\n", items[i], idkLength);

        for (int a = 0; a < idkLength; a++) {
            snprintf(thisText, sizeof(thisText), json_object_iter_peek_name(&that));

            json_object_object_get_ex(idk, thisText, &maybe);
            thisText[0] = toupper(thisText[0]);
            printf("» %c%s: %s\n", toupper(thisText[0]),  thisText + 1, json_object_get_string(maybe));

            json_object_iter_next(&that);
        }
        printf("\n");
    }
    return 0;
}