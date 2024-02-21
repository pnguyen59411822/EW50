/* ==================================================
** Libraries
**
** =============================================== */


#include "firebase_service.h"
#include "firebase_service.deps.h"
#include "firebase_service.const.h"

#include "Logger.h"
#include "common.h"


/* ==================================================
** Macro definition
**
** =============================================== */


//


/* ==================================================
** Type definition
**
** =============================================== */


//


/* ==================================================
** Extern variables
**
** =============================================== */


String uart_data;


/* ==================================================
** Static variables
**
** =============================================== */


static Logger Log(true);

static FirebaseData fbdo_solar;
static FirebaseData fbdo_water;

static FirebaseAuth auth;
static FirebaseConfig config;

static bool flg_signin = false;


/* ==================================================
** Static function declaration
**
** =============================================== */


static bool signin_anonymous();
static void send_uartData();


/* ==================================================
** Static function definition
**
** =============================================== */


bool signin_anonymous() {

    Log.inf("[Firebase] Sign in as anonymous...");
    if (Firebase.signUp(&config, &auth, "", ""))
    {
        Log.print("Success\n\n");
        return true;
    }
    
    // If the signupError.message showed "ADMIN_ONLY_OPERATION"
    // you need to enable Anonymous provider in project's Authentication.
    Log.print("Fail\n");
    Log.printf("%s\n\n", config.signer.signupError.message.c_str());
    return false;
}


void send_uartData() {
    if(uart_data.isEmpty()) {
        return;
    }

    const String valueNames[] = {
        // Solar
        "Voltage", "Ampe", "Perform",

        // Water
        "Voltage", "Ampe", "Perform", "Flowrate", "totalmilliLitres"
    };


    const String data    = uart_data;
    const char separator = ',';
    int nameIndex_curr   = 0;
    int nameIndex_max    = sizeof(valueNames) / sizeof(valueNames[0]);


    int start = 0;
    int end = data.indexOf(separator);
    FirebaseJson json_solar, json_water;


    while(end >= 0 && nameIndex_curr < nameIndex_max){
        String value = data.substring(start, end);

        if(nameIndex_curr < 3) {
            json_solar.set(valueNames[nameIndex_curr], value);
        }

        else {
            json_water.set(valueNames[nameIndex_curr], value);
        }

        nameIndex_curr += 1;
        start = end + 1;
        end   = data.indexOf(separator, start);
    }


    if(start < data.length() && nameIndex_curr < nameIndex_max){
        String value = data.substring(start);

        if(nameIndex_curr < 3) {
            json_solar.set(valueNames[nameIndex_curr], value);
        }

        else {
            json_water.set(valueNames[nameIndex_curr], value);
        }
    }

    // Reset uart data
    uart_data = "";

    if (!Firebase.RTDB.setJSON(&fbdo_solar, "Solar sytem", &json_solar)) {
        Log.err("[Firebase] Sending solar... failed");
    }
    else{
        Log.inf("[Firebase] Sending solar... success");
    }

    if (!Firebase.RTDB.setJSON(&fbdo_water, "water flow", &json_water)) {
        Log.err("[Firebase] Sending water... failed");
    }
    else{
        Log.inf("[Firebase] Sending water... success");
    }
}


/* ==================================================
** Extern function definition
**
** =============================================== */


void Firebase_init() {

    // config.host = FIREBASE_HOST;
    config.api_key = FIREBASE_API_KEY;
    config.database_url = FIREBASE_DATABASE_URL;

    // Assign the user sign in credentials
    // auth.user.email = FIREBASE_USER_EMAIL;
    // auth.user.password = FIREBASE_USER_PASSWORD;

    // Comment or pass false value when WiFi reconnection will control by your code or third party library e.g. WiFiManager
    Firebase.reconnectNetwork(true);

    /** Since v4.4.x, BearSSL engine was used, the SSL buffer need to be set.
     * Large data transmission may require larger RX buffer, otherwise connection issue or data read time out can be occurred.
     * Rx buffer size in bytes from 512 - 16384
     * Tx buffer size in bytes from 512 - 16384
    */
    fbdo_solar.setBSSLBufferSize(4096 , 1024);
    fbdo_water.setBSSLBufferSize(4096 , 1024);

    flg_signin = signin_anonymous();

    /* Assign the callback function for the long running token generation task */
    config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h

    /** The id token (C++ string) will be available from config.signer.tokens.id_token
     * if the sig-up was successful.
     *
     * Now you can initialize the library using the internal created credentials.
     *
     * If the sign-up was failed, the following function will initialize because
     * the internal authentication credentials are not created.
     */
    Firebase.begin(&config, &auth);
}


void Firebase_loop() {

    if (!Firebase.ready())
    {
        Log.err("[Firebase] Not ready");
        return;
    }

    send_uartData();


    const uint32_t timer = 5000;
    static uint32_t millis_prev = millis();

    if(millis() - millis_prev < timer) {
        return;
    }

    millis_prev = millis();

    if(!flg_signin) {
        flg_signin = signin_anonymous();
        return;
    }
}