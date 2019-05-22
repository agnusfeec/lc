#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define IMAGE_DATASET  2051
#define LABEL_DATASET  2049

struct s_lbl_ds {
    int32_t n_itens;
    int32_t * data;
};

typedef struct s_lbl_ds t_lbl_ds;

struct s_img_ds {
    int32_t n_images;
    int32_t n_rows, n_columns;
    unsigned char * data;
};

typedef struct s_img_ds t_img_ds;

using namespace cv;

int to_int(unsigned char data[], int tam) {
    int aux = 0;
 
    for(int i=tam-1, base = 1;i>=0;i--, base*=256) aux += data[i]*base;

    return aux; 
}

void read_label_dataset(char * filename, struct s_lbl_ds * lbl_ds) {

    FILE *ptr;
    unsigned char data_b;
    int32_t data_32;
    unsigned char d32[4];


    ptr = fopen(filename, "rb");

    if(ptr==NULL) {
        printf("Error when opening file: %s!", filename);
        exit(-1);
    }

    fread(d32,sizeof(d32),1,ptr);
    data_32 = to_int(d32, 4);
    
    if(data_32 != LABEL_DATASET) { // test label dataset
        printf("Expected Label dataset! File: %s!", filename);
        exit(-1);
    }

    fread(d32,sizeof(d32),1,ptr);
    lbl_ds->n_itens = to_int(d32, 4);
    
    lbl_ds->data = (int32_t *) malloc(lbl_ds->n_itens * sizeof(int32_t));
    
    if(lbl_ds->data==NULL) {
        printf("Memory fault! Impossible allocate memory to labels!\n");
        exit(-1);
    }

    for(int i=0; i<data_32; i++) {
        fread(&data_b,sizeof(data_b),1,ptr);
        lbl_ds->data[i] = data_b;
    }

    fclose(ptr);

}

void read_image_dataset(char * filename, struct s_img_ds * img_ds){
    FILE *ptr;
    unsigned char data_b;
    int32_t data_32;
    unsigned char d32[4];

    ptr = fopen(filename, "rb");


    if(ptr==NULL) {
        printf("Error when opening file: %s!", "/Projeto/dataset/mnist/t10k-images.idx3-ubyte");
        exit(-1);
    }

    fread(d32,sizeof(d32),1,ptr);
    data_32 = to_int(d32, 4);
    
    if(data_32 != IMAGE_DATASET) { // test image dataset
        printf("Expected Image dataset! File: %s!", filename);
        exit(-1);
    }

    fread(d32,sizeof(d32),1,ptr);
    img_ds->n_images = to_int(d32, 4);

    fread(d32,sizeof(d32),1,ptr);
    img_ds->n_rows = to_int(d32, 4);
    
    fread(d32,sizeof(d32),1,ptr);
    img_ds->n_columns = to_int(d32, 4);

    int32_t size = img_ds->n_rows*img_ds->n_columns*img_ds->n_images;
    img_ds->data = (unsigned char *) malloc(size*sizeof(unsigned char));

    if(img_ds->data==NULL) {
        printf("Memory fault! Impossible allocate memory to images!\n");
        exit(-1);
    }

    for(int i=0; i<size; i++) {
        fread(&data_b,sizeof(data_b),1,ptr);
        img_ds->data[i] = data_b;
    }

    fclose(ptr);

}

int main(void){

    t_lbl_ds test_lbl_ds, train_lbl_ds;
    t_img_ds test_img_ds, train_img_ds;

    char filename[100];

    strcpy(filename, "/Projeto/dataset/mnist/t10k-labels.idx1-ubyte");
    read_label_dataset(filename, &test_lbl_ds);

    strcpy(filename, "/Projeto/dataset/mnist/t10k-images.idx3-ubyte");
    read_image_dataset(filename, &test_img_ds);

    strcpy(filename, "/Projeto/dataset/mnist/train-labels.idx1-ubyte");
    read_label_dataset(filename, &train_lbl_ds);

    strcpy(filename, "/Projeto/dataset/mnist/train-images.idx3-ubyte");
    read_image_dataset(filename, &train_img_ds);

    Mat image = Mat(train_img_ds.n_rows, train_img_ds.n_columns, CV_8UC1, train_img_ds.data); // size_t 	step = AUTO_STEP 

    namedWindow( "Display window", WINDOW_AUTOSIZE ); // Create a window for display.
    imshow( "Display window", image );                // Show our image inside it.
    waitKey(0); // Wait for a keystroke in the window
 
    return 0;

}

