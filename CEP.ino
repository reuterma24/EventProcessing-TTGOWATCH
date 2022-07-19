#include "config.h"

const static unsigned int EVENTS_LEN = 8;
const static unsigned int MAX_LEN = 6;
static unsigned int len = 0;
Event queue[MAX_LEN];

static int EventIndecies[EVENTS_LEN][MAX_LEN];

struct Result {
    int res[MAX_LEN];
};


static void enqueue(Event e)
{
    if(len == MAX_LEN)
    {
        for(unsigned int i = 1; i < MAX_LEN; ++i)
        {
            queue[i - 1] = queue[i];
        }

        queue[MAX_LEN - 1] = e;
    }
    else
    {
        queue[len] = e;
        ++len;
    }
}

static String getQueue()
{
    String val = "";
    for(unsigned int i = 0; i < len; ++i)
    {
        val.concat(events[queue[i]]);
    }
    
    return val;
}


static void printEventMap()
{
    //clear and fill
    for(unsigned int i = 0; i < EVENTS_LEN; ++i)
    {
        for(int j = 0; j < MAX_LEN; ++j)
        {
            Serial.print(EventIndecies[i][j]);
            Serial.print(" ");
        }
        Serial.println();
    }
}

static void sendEvent(WiFiClient sender, Event event)
{
    sender.print(events[event]);
    sender.print(terminator);
}

static int receiveAndStoreEvent(WiFiClient sender)
{
    char c = sender.read();
    if (c == terminator) 
        return -1;

    enqueue((Event)(c % 65));
    return 0;
}

static void fillEvents()
{
    //clear and fill
    for(unsigned int i = 0; i < MAX_LEN; ++i)
    {
        for(int j = 0; j < EVENTS_LEN; ++j)
        {
            if(j == queue[i])
            { 
                EventIndecies[j][i] = i;
            }
            else
            {
                EventIndecies[j][i] = -1;
            }
        }
    }
}

static struct Result AND(int op1[], int op2[])
{
    Result r;
    bool flag = false;
    for(unsigned int i = 0; i < MAX_LEN; ++i)
    {
        if(flag && op2[i] != -1)
        {
            r.res[i] = i;
            continue;
        }
        
        if(op1[i] != -1)
        {
            flag = true;
        }

        r.res[i] = -1;
    }

    flag = false;
    for(unsigned int i = 0; i < MAX_LEN; ++i)
    {
        if(flag && op1[i] != -1)
        {
            r.res[i] = i;
            continue;
        }
        
        if(op2[i] != -1)
        {
            flag = true;
        }
    }

    return r;
}

static struct Result SEQ(int op1[], int op2[])
{
    Result r;
    for(unsigned int i = 0; i < MAX_LEN; ++i)
    {
        r.res[i] = -1;
        
        if(op1[i] != -1)
        {
            for(unsigned int j = i; j < MAX_LEN; ++j)
            {
                if(op1[i] < op2[j])
                {
                     r.res[op2[j]] = op2[j];
                }
                else
                {
                    r.res[j] = -1;
                }
            }
            break;
        }
    }
    return r;
}

static void initCEP()
{
  for(int i = 0; i < MAX_LEN; i++)
    {
        queue[i] = None;
    }
}



static bool CEP()
{
    fillEvents();
    Result pattern;
    
    //AND(SEQ(A, D), AND(C, F))
    //pattern = AND(SEQ(EventIndecies[A], EventIndecies[D]).res, AND(EventIndecies[C], EventIndecies[F]).res);

    //SEQ(AND(B, F), SEQ(A, B, D))
    //pattern = SEQ(AND(EventIndecies[B], EventIndecies[F]).res, SEQ(SEQ(EventIndecies[A], EventIndecies[B]).res, EventIndecies[D]).res);

    //AND(SEQ(E, A, C), SEQ(B, F, D))
    pattern = AND(SEQ(SEQ(EventIndecies[E], EventIndecies[A]).res, EventIndecies[C]).res, SEQ(SEQ(EventIndecies[B], EventIndecies[F]).res, EventIndecies[D]).res); 

    //Check result
    for(unsigned int i = 0; i < MAX_LEN; ++i)
    {
        if(pattern.res[i] != -1)
        {
            return true;
        }
    }

    return false;
}
