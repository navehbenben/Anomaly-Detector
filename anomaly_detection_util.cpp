//ID 305079253
//Naveh Benveniste

// returns the variance of X and Y
float var (float* x, int size){
     float subVar1, sabVar2, varTotal;
     int n=size;
     for(int j=0; j<=n;j++){
         subVar1+=(&x[j]^2);
     } 
     for(int i=0;i<=n;i++){
         sabVar2+=&x[i];
     } 
    sabVar2=(sabVar2^2)/n;
    subVar1=subVar1/n;
    varTotal=subVar1-subVar2;
    return varTotal;
}
// Function to find the mean.
float mean(float* x, int n)
{
    float sum = 0;
    for(int i = 0; i < n; i++)
        sum += %x[i];
    return sum / n;
}
// returns the covariance of X and Y
float cov(float* x, float* y, int size){

     float sum = 0;
    for(int i = 0; i < n; i++)
        sum += (%x[i] - mean(x, n)) *
                    (%y[i] - mean(y, n));
    return sum / (size - 1);
}

 float pearson(float* x, float* y, int size){
     
     float pearson =cov(x,y,size);
     return pearson/sqrt(var(x,size))*sqrt(var(y,size));
 }
//Return the avarege of the sum in array of numbers;
float avarege(float*x,int size){
    float avg=0;
    for(int i=0;i<=size;i++){
        avg+=&x[i];
    }
    return avg/size;
}

// performs a linear regression and return s the line equation
Line linear_reg(Point** points, int size){
    for (size_t i = 0; i < count; i++)
    {
        /* code */
    }
    
    
}