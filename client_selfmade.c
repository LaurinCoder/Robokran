#include <stdio.h>
#include "open62541.h"



void MainWindow::opcabfrage() {
    UA_Client *client = UA_Client_new(UA_ClientConfig_standard);
    UA_StatusCode retval = UA_Client_connect(client, "opc.tcp://169.254.25.26:4840");
    if(retval != UA_STATUSCODE_GOOD) {
        UA_Client_delete(client);
        return (int)retval;
    }

    /* Read the value attribute of the node. UA_Client_readValueAttribute is a
     * wrapper for the raw read service available as UA_Client_Service_read. */
    UA_Variant value; /* Variants can hold scalar values and arrays of any type */
    UA_Variant_init(&value);

    UA_Variant myvalue;
    UA_Variant_init(&myvalue);

    UA_Variant mystring;
    UA_Variant_init(&mystring);

    UA_Variant myInput1;
    UA_Variant_init(&myInput1);
    UA_Int16 myInput1Value = 0;

    /* NodeId of the variable holding the current time */
    const UA_NodeId nodeId =
        UA_NODEID_NUMERIC(0, UA_NS0ID_SERVER_SERVERSTATUS_CURRENTTIME);
    /*NodeId VERSUCH VON IRGENDEINER INFO VOM SERVER */
    const UA_NodeId mynodeId =
            UA_NODEID_NUMERIC(0, UA_NS0ID_SERVER_SERVERSTATUS_STARTTIME);
    const UA_NodeId mynodeIdString =
            UA_NODEID_STRING(7, "::Program:string");
    const UA_NodeId mynodeIdInput1 =
            UA_NODEID_STRING(7, "::Program:Input1");

    retval = UA_Client_readValueAttribute(client, nodeId, &value);
    if(retval == UA_STATUSCODE_GOOD &&
       UA_Variant_hasScalarType(&value, &UA_TYPES[UA_TYPES_DATETIME])) {
        UA_DateTime raw_date = *(UA_DateTime*)value.data;
        UA_String string_date = UA_DateTime_toString(raw_date);
        printf("string date is: %.*s\n", (int)string_date.length, string_date.data);
        UA_String_deleteMembers(&string_date);
    }

    retval = UA_Client_readValueAttribute(client, mynodeId, &myvalue);
    if(retval == UA_STATUSCODE_GOOD &&
       UA_Variant_hasScalarType(&myvalue, &UA_TYPES[UA_TYPES_DATETIME])) {
        UA_DateTime raw_date = *(UA_DateTime*)myvalue.data;
        UA_String string_date = UA_DateTime_toString(raw_date);
        printf("string date is: %.*s\n", (int)string_date.length, string_date.data);
        UA_String_deleteMembers(&string_date);
    }

    //String einlesen
    retval = UA_Client_readValueAttribute(client, mynodeIdString, &mystring);
    if(retval == UA_STATUSCODE_GOOD &&
       UA_Variant_hasScalarType(&mystring, &UA_TYPES[UA_TYPES_STRING])) {
        UA_String   string_date = *(UA_String*)mystring.data;
        printf("string date is: %.*s\n", (int)string_date.length, string_date.data);
        UA_String_deleteMembers(&string_date);
}

    //INTEGER EINLESEN
    retval = UA_Client_readValueAttribute(client, mynodeIdInput1, &myInput1);
    if(retval == UA_STATUSCODE_GOOD &&
       UA_Variant_isScalar(&myInput1)) {
        myInput1Value = *(UA_Int16*)myInput1.data;
        printf("the value is: %i\n", myInput1Value);



}
    /* Clean up */
    UA_Variant_deleteMembers(&myvalue);
    UA_Variant_deleteMembers(&value);
    UA_Variant_deleteMembers(&mystring);
    //UA_Variant_deleteMembers(&myInput1);
    UA_Client_delete(client); /* Disconnects the client internally */
//    return UA_STATUSCODE_GOOD;
}
