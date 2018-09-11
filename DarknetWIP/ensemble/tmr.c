#include "tmr.h"

// Esterel inputs/running functions
int ensemble();

char * str_input;
// char buff[256];
// char *input = buff;

int predict_tmr(char *datacfg, char *cfgfile, char *weightfile, char *filename, int full)
{
    int top = 0;
    if(full) printf("======= Starting prediction process =======\n\n");
    else printf("Predicting...\n    ");
    network *net = load_network(cfgfile, weightfile, 0);
    set_batch_network(net, 1);
    srand(2222222);

    list *options = read_data_cfg(datacfg);

    char *name_list = option_find_str(options, "names", 0);
    if(!name_list) name_list = option_find_str(options, "labels", "data/labels.list");
    if(top == 0) top = option_find_int(options, "top", 1);

    int i = 0;
    char **names = get_labels(name_list);
    //printf("%s\n", names[0]);
    clock_t time;
    int *indexes = calloc(top, sizeof(int));
    char buff[256];
    char *input = buff;
    while(1){
        if(filename){
            strncpy(input, filename, 256);
        }else{
            printf("Enter Image Path: ");
            fflush(stdout);
            input = fgets(input, 256, stdin);
            if(!input) return -1;
            strtok(input, "\n");
        }
        image im = load_image_color(input, 0, 0);
        image r = letterbox_image(im, net->w, net->h);

        float *X = r.data;        
        time=clock();
        float *predictions = network_predict(net, X);
        if(net->hierarchy) hierarchy_predictions(predictions, net->outputs, net->hierarchy, 1, 1);
        top_k(predictions, net->outputs, top, indexes);
        if(full) fprintf(stderr, "%s: Predicted in %f seconds.\n", input, sec(clock()-time));
        for(i = 0; i < top; ++i){
            int index = indexes[i];            
            if(full || i == 0) printf("%5.2f%%: %s\n", predictions[index]*100, names[index]);
        }
        if(r.data != im.data) free_image(r);
        free_image(im);
        if (filename) break;
    }
    if(full) printf("\n======= Ending prediction process =======\n");
    else printf("...done!\n");
    free_network(net);

    return indexes[0];
}

void predict_Esterel()
{
    // Section 1 - Initialise the Neural Network
    printf("======= Initializing & Loading Neural Network =======\n\n");
    
    initNets();
    initPredictData();
    
    printf("\n======= Loaded Neural Network =======\n\n");

    // Section 2 - While(1) which calls the Esterel program
    while(1)
    {
        // Get the name of the image from user input //
        
        // sprintf(input,"%s",userInput());
        // printf("Esterel Predict: \t%s\n", input);
        // predictInput(input);
        ensemble();
    }

    // Section 3 - Destory the NN
    destructNets();
    destructData();
}
 
void run_tmr(int argc, char **argv)
{
    // char *tmr_data = "cfg/tmr/tmr.data";
    char *tmr_data1 = "data/tmr.data";
    char *tmr_data2 = "data/tmr2.data";
    char *tmr_data3 = "data/tmr3.data";

    // char *tmr_cfg = "cfg/tmr/tmr.cfg";
    char *tmr_cfg1 = "data/tmr.cfg";
    char *tmr_cfg2 = "data/tmr2.cfg";
    char *tmr_cfg3 = "data/tmr3.cfg";

    // char *tmr_weights = "backup/tmr/tmr.weights";
    char *tmr_weights1 = "backup/tmr.weights";
    char *tmr_weights2 = "backup/tmr2.weights";
    char *tmr_weights3 = "backup/tmr3.weights";

    char *filename = (argc > 3) ? argv[3]: 0;
    if(0==strcmp(argv[1], "predict")) predict_tmr(tmr_data1, tmr_cfg1, tmr_weights1, filename, 1);
    else if(0==strcmp(argv[1], "esterel")) predict_Esterel();
}