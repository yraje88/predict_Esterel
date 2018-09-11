#include "ensemble.h"
#include <string.h>
#include <stdio.h>

// Global variables
int numTrainSamples = 0;

// Neural networks for CNNs
network *cnn[NUM_NETS];

// Configuration files
char *tmr_data[NUM_NETS] = {"data/tmr.data"};
char *tmr_cfg[NUM_NETS] = {"data/tmr.cfg"};
char *tmr_weights[NUM_NETS] = {"backup/tmr.weights"};

// Data storage structs
load_args largs[NUM_NETS];
data dbuffer[NUM_NETS];
pthread_t lthreads[NUM_NETS];
char **img_paths[NUM_NETS];
char **class_labels[NUM_CLASSES][NUM_NETS];
char **names;
char *backup_directory[NUM_NETS];
char *base[NUM_NETS];
int epochs[NUM_NETS];
int top[NUM_NETS];

// Network output 
float predictions[NUM_NETS][NUM_CLASSES];
int pred_indexes[NUM_NETS][TOPK];

// Ensemble data storage
float topk_accuracy[NUM_NETS][TOPK];

// User input storage
char buff[256];
char *input = buff;

// Initialisation functions
void initNets()
{
    srand(time(0));
    for(int i = 0; i < NUM_NETS; i++)
    {
        base[i] = basecfg(tmr_cfg[i]);
        char *tmr_weights1 = "backup/tmr.weights";
        cnn[i] = load_network(tmr_cfg[i], tmr_weights1, 0);
    }    
}

void initPredictData()
{
    for(int i = 0; i < NUM_NETS; i++)
    {
        set_batch_network(cnn[i],1);
        list *options = read_data_cfg(tmr_data[i]);

        char *name_list = option_find_str(options, "labels", "data/labels.list");
        top[i] = option_find_int(options,"top",1);
        names = get_labels(name_list);
        for(int a = 0; a < NUM_CLASSES; a++)
        {
            class_labels[a][i] = names[a];    
            // sprintf(class_labels[a][i],"%s",names[a]);
            // printf("%s\n", names[a]);    
            // printf("%s\n", class_labels[a][i]);    
        }        
    }
}

// void predictInput(char * input)
void predictInput()
{
    image im = load_image_color(input, 0, 0);
    //printf("%s\n", input);
    if(input)
    {
        for(int i = 0; i < NUM_NETS; i++)
        {
            image r = letterbox_image(im, cnn[i]->w, cnn[i]->h);
            float *X = r.data;         
            float *predictions = network_predict(cnn[i], X);
            int *indexes = calloc(top[i], sizeof(int));
            // printf("%d\n", top[i]);
            top_k(predictions,cnn[i]->outputs,top[i],indexes);
            int index = indexes[i];
            printf("%5.2f%%: %s\n",predictions[index]*100, class_labels[index][i]);
            if(r.data != im.data) 
                free_image(r);
            free_image(im);
        }
    }
    else
        printf("No Image");
}

void userInput()
{
    // char buff[256];
    // char *input = buff;

    printf("Enter Image Path: ");
    fflush(stdout);
    input = fgets(input, 256, stdin);
    // if(!input) return "-1";
    strtok(input, "\n");
    //printf("Ensemble Predict: \t%s\n", input);
    // return input;
}

/* char * userInput()
{
    char buff[256];
    char *input = buff;

    printf("Enter Image Path: ");
    fflush(stdout);
    input = fgets(input, 256, stdin);
    if(!input) return "-1";
    strtok(input, "\n");
    //printf("Ensemble Predict: \t%s\n", input);
    return input;
} */

void destructNets()
{
    for(int i = 0; i < NUM_NETS; i++)
    {
        free_network(cnn[i]);
    }
}

void destructData()
{
    for(int i = 0; i < NUM_NETS; i++)
    {
        free_ptrs((void**)class_labels[i], NUM_CLASSES);
        free_ptrs((void**)img_paths[i], numTrainSamples);
    }
}

// Helper functions
void tryBackup()
{
    for(int i = 0; i < NUM_NETS; i++)
    {
        if(*cnn[i]->seen/largs[i].m > epochs[i])
        {
            epochs[i] = *cnn[i]->seen/largs[i].m;
            char buff[256];
            sprintf(buff, "%s/%s_%d.weights", backup_directory[i], base[i], epochs[i]);
            save_weights(cnn[i], buff);
        }
        else if(maxEpochs(i))
        {
            char buff[256];
            sprintf(buff, "%s/%s.weights", backup_directory[i], base[i]);
            save_weights(cnn[i], buff);
        }
    }
}

float getSeen(int net){return (float)(*cnn[net]->seen%(largs[net].m))/(float)(largs[net].m);}
void setSeen(int net){*cnn[net]->seen += cnn[net]->batch;}
int maxEpochs(int net){return get_current_batch(cnn[net]) >= cnn[net]->max_batches;}
int getMaxBatches(int net){return cnn[net]->max_batches;};
int getTrainSamples(){return numTrainSamples;}
int getCurrentBatch(int net){return get_current_batch(cnn[net]);};