#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { AND, OR, NAND, NOR, XOR, NOT, PASS, MULTIPLEXER, DECODER } gate_type;

typedef struct{
    gate_type type;
    int size;          // indicates size of DECODER and MULTIPLEXER
    int *inputs;       
    int *outputs;      
    int output;       
} Gate;

int num_inputs;
int num_outputs;
int num_variables = 0;
int num_gates = 0;
int input_variables[256];
int output_variables[256];
int values[256];  
Gate gates[256];
char variables[256][50];  
int last_output = 0;

int var(char *name) {
    if(strcmp(name, "1") == 0){
        return -2;
    } 
    if(strcmp(name, "0") == 0){
        return -1;
    }  
    for(int x = 0; x < num_variables; x++){
        if(strcmp(variables[x], name) == 0){
            return x;
        } 
    }
    strcpy(variables[num_variables], name);
    return num_variables++;
}

int get_value(int index){
    if(index == -1){
        return 0;
    }else if(index == -2){
        return 1;
    } 
    return values[index];
}

void evaluate_gate(Gate *gate){
    int input1 = 0;
    int input2 = 0;
    if(gate->type == AND){
        input1 = get_value(gate->inputs[0]);
        input2 = get_value(gate->inputs[1]);
        if(input1 == 1 && input2 == 1){
            values[gate->output] = 1;
        }else{
            values[gate->output] = 0;
        }
    }else if(gate->type == OR){
        input1 = get_value(gate->inputs[0]);
        input2 = get_value(gate->inputs[1]);
        if(input1 == 1 || input2 == 1){
            values[gate->output] = 1;
        }else{
            values[gate->output] = 0;
        }
    }else if(gate->type == NAND){
        input1 = get_value(gate->inputs[0]);
        input2 = get_value(gate->inputs[1]);
        if(input1 == 1 && input2 == 1){
            values[gate->output] = 0;
        }else{
            values[gate->output] = 1;
        }
    }else if(gate->type == NOR){
        input1 = get_value(gate->inputs[0]);
        input2 = get_value(gate->inputs[1]);
        if(input1 == 1 || input2 == 1){
            values[gate->output] = 0;
        }else{
            values[gate->output] = 1;
        }
    }else if(gate->type == XOR){
        input1 = get_value(gate->inputs[0]);
        input2 = get_value(gate->inputs[1]);
        if((input1 == 1 && input2 == 0) || (input1 == 0 && input2 == 1)){
            values[gate->output] = 1;
        }else{
            values[gate->output] = 0;
        }
    }else if(gate->type == NOT){
        input1 = get_value(gate->inputs[0]);
        if((!input1) == 1){
            values[gate->output] = 1;
        }else{
            values[gate->output] = 0;
        }
    }else if(gate->type == PASS){
        input1 = get_value(gate->inputs[0]);
        if(input1 == 1){
            values[gate->output] = 1;
        }else{
            values[gate->output] = 0;
        }
    }else if(gate->type == DECODER){
        int index = 0;
        for(int x = 0; x < gate->size; x++){
            index = (index * 2) + get_value(gate->inputs[x]);
        }
        for (int x = 0; x < (1 << gate->size); x++) {
            if(index == x){
                values[gate->outputs[x]] = 1;
            }else{
                values[gate->outputs[x]] = 0;
            }
        }
    }else if(gate->type == MULTIPLEXER){
        int sel = 0;
        for(int x = 0; x < gate->size; x++){
            sel = (sel * 2) + get_value(gate->inputs[(1 << gate->size)+x]);
        }
        values[gate->output] = get_value(gate->inputs[sel]);
    }     
}

