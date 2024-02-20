#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main() {
    printf("Hello, World!\n");
    return 0;
}

//gets two float vectors as arrays and their size and returns their Euclidean distance
double dist(double vec1[], double vec2[], int len)
{
    double sum = 0.0;
    for (int i = 0; i < len; ++i)
    {
        sum += pow(vec1[i] - vec2[i], 2);
    }
    return sqrt(sum);
}

int k_means_calc(int k, int N, int d, int iter, double data[N][d], double delta)
{
    double* centroids;
    int* clusters; //array where clusters[i] = j -> x_i is in cluster j
    centroids = (double*)malloc(k*d*sizeof(double));
    clusters = (int*)malloc(N*sizeof(int));
    //Initialize centroids
    for (int i = 0; i < k; ++i)
        for (int j = 0; j < d; ++j)
            centroids[(i*d)+j] = data[i][j];
    while (iter > 0)
    {
        iter = iter - 1;
        for (int i = 0; i < N; ++i)
        {
            //find minimal distance
            double min_dist = dist(data[i], centroids, d);
            int min_clutter = 0;
            for (int j = 1; j < N; ++j)
            {
                double new_dist = dist(data[i], centroids + (j*d), d);
                if (new_dist < min_dist)
                {
                    min_dist = new_dist;
                    min_clutter = j;
                }
            }
            //assign x to its cluster
            clusters[i] = min_clutter;
        }
        //update clusters
        double max_delta = 0.0;
        for (int i = 0; i < k; ++i)
        {
            double cluster_sum[d];
            int count = 0;
            for (int j = 0; j < k; ++j)
            {
                  if(clusters[j] == i)
                  {
                      count ++;
                      for (int l = 0; l < d; ++l)
                          cluster_sum[l] += data[j][l];
                  }
            }
            for (int l = 0; l < d; ++l)
                cluster_sum[l] = cluster_sum[l]/k;
            double curr_delta = dist(cluster_sum, centroids + (i*d), d);
            if (curr_delta > max_delta)
                max_delta = curr_delta;
            for (int j = 0; j < d; ++j) {
                centroids[(i*d) + j] = cluster_sum[j];
            }
        }
        if (max_delta < delta)
            break;
    }
    free(clusters);
    free(centroids);
    //print
    return(1);
}