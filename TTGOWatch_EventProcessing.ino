#include "config.h"

//Variables
bool patternMatched;


// Connection Variables
const char* ssid     = "iPhone von Martin (3)";
const char* password = "987654321";
int ctr = 0;

//Acting as a server
WiFiServer server(1080);
IPAddress ip(172, 20, 10, 14);
//IPAddress ip(172, 20, 10, 13); 
//IPAddress ip(172, 20, 10, 12); 

IPAddress gateway(172, 20, 10, 1);
IPAddress subnet(255, 255, 255, 240);
//------

//Acting as a client (targets - change to not include server number)
WiFiClient master;
IPAddress server1(172, 20, 10, 12);
IPAddress server2(172, 20, 10, 13);

//UI Elements
TTGOClass *ttgo;
lv_obj_t *queueLabel;
lv_obj_t *detectorLabel;

static void init_wifi_connection()
{
     //Init ESP32 Wifi
     WiFi.config(ip, gateway, subnet);       // force to use fixed IP
     WiFi.begin(ssid, password);
     
     while (WiFi.status() != WL_CONNECTED) 
     {
       delay(500);
       Serial.print(".");
     }
     server.begin();
     
     Serial.print(" connected to Wifi! IP address : ");
     Serial.println(WiFi.localIP());
}

// SERVER METHODS
static void handle_connection()
{
     WiFiClient client = server.available();
     client.setTimeout(50);
     
     if(client)
     {
         //Print client IP address
         Serial.print("Client :");
         Serial.println(client.localIP());

         while (client.connected() && client.available()) 
         {
             int res = receiveAndStoreEvent(client);
             if(res < 0)
                break;
         }

         client.stop();
         Serial.println("Client disconnected!");

         patternMatched = CEP();
     }
}

// CLIENT METHODS
static void connect_and_send_event(IPAddress server, Event e)
{
  Serial.print("Trying to connect to server");
  while (master.connect(server, 1080) != 1) // Connection to the server
  { 
    Serial.print(".");
    ctr++;
    if (ctr > 3)
    {
      ctr = 0;
      Serial.println();
      Serial.println("Server not available");
      return;
    }
  }
  Serial.println();
  Serial.println("Connected to Server");  
   
  sendEvent(master, e);
  Serial.println("Sending Event " + events[e]);     
  master.stop();    
}

static void event_a_handler(lv_obj_t *obj, lv_event_t event)
{
  if(event == LV_EVENT_CLICKED)
  {
    connect_and_send_event(server1, A);
    connect_and_send_event(server2, A);
  }
}

static void event_b_handler(lv_obj_t *obj, lv_event_t event)
{
  if(event == LV_EVENT_CLICKED)
  {
    connect_and_send_event(server1, B);
    connect_and_send_event(server2, B);
  }
}

static void event_c_handler(lv_obj_t *obj, lv_event_t event)
{
  if(event == LV_EVENT_CLICKED)
  {
    connect_and_send_event(server1, C);
    connect_and_send_event(server2, C);
  }
}

static void event_d_handler(lv_obj_t *obj, lv_event_t event)
{
  if(event == LV_EVENT_CLICKED)
  {
    connect_and_send_event(server1, D);
    connect_and_send_event(server2, D);
  }
}

static void event_e_handler(lv_obj_t *obj, lv_event_t event)
{
  if(event == LV_EVENT_CLICKED)
  {
    connect_and_send_event(server1, E);
    connect_and_send_event(server2, E);
  }
}

static void event_f_handler(lv_obj_t *obj, lv_event_t event)
{
  if(event == LV_EVENT_CLICKED)
  {
    connect_and_send_event(server1, F);
    connect_and_send_event(server2, F);
  }
}

static void restart_handler(lv_obj_t *obj, lv_event_t event)
{
  Serial.println("Restarting...");
  delay(100);
  ESP.restart();
}

static void build_ui()
{
    //Build UI
    ttgo = TTGOClass::getWatch();
    ttgo->begin();
    ttgo->openBL();
    ttgo->lvgl_begin();

    lv_obj_t *label;
    
    lv_obj_t *btn1 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_event_cb(btn1, restart_handler);
    lv_obj_align(btn1, NULL, LV_ALIGN_CENTER, 0, 90);
  
    label = lv_label_create(btn1, NULL);
    lv_label_set_text(label, "Restart");
  
    lv_obj_t *btn2 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_event_cb(btn2, event_a_handler);
    lv_obj_align(btn2, NULL, LV_ALIGN_CENTER, -80, -90);
    lv_btn_set_fit2(btn2, LV_FIT_TIGHT, LV_FIT_TIGHT);
  
    label = lv_label_create(btn2, NULL);
    lv_label_set_text(label, "A");
  
    lv_obj_t *btn3 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_event_cb(btn3, event_b_handler);
    lv_obj_align(btn3, NULL, LV_ALIGN_CENTER, 0, -90);
    lv_btn_set_fit2(btn3, LV_FIT_TIGHT, LV_FIT_TIGHT);
  
    label = lv_label_create(btn3, NULL);
    lv_label_set_text(label, "B"); 
  
    lv_obj_t *btn4 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_event_cb(btn4, event_c_handler);
    lv_obj_align(btn4, NULL, LV_ALIGN_CENTER, 80, -90);
    lv_btn_set_fit2(btn4, LV_FIT_TIGHT, LV_FIT_TIGHT);
  
    label = lv_label_create(btn4, NULL);
    lv_label_set_text(label, "C");
  
    lv_obj_t *btn5 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_event_cb(btn5, event_d_handler);
    lv_obj_align(btn5, NULL, LV_ALIGN_CENTER, -80, -40);
    lv_btn_set_fit2(btn5, LV_FIT_TIGHT, LV_FIT_TIGHT);
  
    label = lv_label_create(btn5, NULL);
    lv_label_set_text(label, "D");
  
    lv_obj_t *btn6 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_event_cb(btn6, event_e_handler);
    lv_obj_align(btn6, NULL, LV_ALIGN_CENTER, 0, -40);
    lv_btn_set_fit2(btn6, LV_FIT_TIGHT, LV_FIT_TIGHT);
  
    label = lv_label_create(btn6, NULL);
    lv_label_set_text(label, "E");
  
    lv_obj_t *btn7 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_event_cb(btn7, event_f_handler);
    lv_obj_align(btn7, NULL, LV_ALIGN_CENTER, 80, -40);
    lv_btn_set_fit2(btn7, LV_FIT_TIGHT, LV_FIT_TIGHT);
  
    label = lv_label_create(btn7, NULL);
    lv_label_set_text(label, "F");

    queueLabel = lv_label_create(lv_scr_act() , NULL);
    lv_label_set_text(queueLabel, "");
    lv_obj_align(queueLabel, NULL, LV_ALIGN_CENTER, -115, 25);

    detectorLabel = lv_label_create(lv_scr_act() , NULL);
    lv_label_set_text(detectorLabel, "Detected: -");
    lv_obj_align(detectorLabel, NULL, LV_ALIGN_CENTER, 70, 25);
}

void refreshQueueLabel()
{
    String content = getQueue();
    if(lv_obj_get_screen(queueLabel) == lv_scr_act()) 
    {
        int len = content.length() + 1;
        char buf[len];
        sprintf(buf, "Queue: %s", content);
        lv_label_set_text(queueLabel, buf);
    }
}


void refreshDetectorLabel()
{
    if(lv_obj_get_screen(detectorLabel) == lv_scr_act()) 
    {
        if(patternMatched)
        {
            lv_label_set_text(detectorLabel, "Detected: +");
        }
        else
        {
            lv_label_set_text(detectorLabel, "Detected: -");
        }
    }
}

void setup()
{
    Serial.begin(115200);
    initCEP();
    build_ui();
    init_wifi_connection();
}

void loop()
{
    lv_task_handler();
    handle_connection();
    refreshQueueLabel();
    refreshDetectorLabel();
    delay(500);
}
