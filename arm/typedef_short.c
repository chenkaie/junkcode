short test (int *data){
    char    idx;
    int     sum = 0;
    for (idx = 0; idx < 64; idx++) {
        sum += data[idx];
    }
    return sum;
}
