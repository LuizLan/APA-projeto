#include<iostream>
#include<stdlib.h>
#include<iostream>
#include<vector>
#include<algorithm>
#include<utility>
using namespace std;

struct Job{
    int index;
    float time = 99999999999;
    float cost;
    int server = -1;

};

void merge(vector<Job>& arr, int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<Job> L(n1), R(n2);

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i].time > R[j].time) {  // Alterado aqui
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<Job>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}


void printVec(vector<vector<Job>>& vec){
    for (auto &server : vec){
        for (auto &job : server){
            cout << job.time << ' ';
        }
        cout << '\n';
    }
}

pair<vector<vector<Job>>, vector<vector<Job>>> removeJob(vector<vector<Job>>& vec, int index, int servers, int jobs){
    vector<vector<Job>> newVec(servers);  // Cria um vetor com 'servers' vetores vazios
    vector<vector<Job>> assignVec(servers);

    int i = 0;

    for (auto &server : vec){
        for (auto &job : server){
            if (job.index != index){
                newVec[i].push_back(job);
            }else{
                assignVec[i].push_back(job);
            }
        }
        i++;
    }

    printf("New vector status:\n");
    printVec(newVec);

    return make_pair(newVec, assignVec);
}

int main(){

    int custoLoc = 1000;

    float capacidade[] = {220,350};
    vector<vector<float>> matrizT = {{420,80,180,95,35,52},{145,700,330,7,40,42}};
    vector<vector<float>> matrizC = {{350,50,540,245,300,200},{410,100,500,200,100,196}};
    int servers = 2;
    int jobsSize = 6;
    vector<float> jobFin(6);
    vector<vector<Job>> jobs(servers, vector<Job>(jobsSize));
    vector<vector<Job>> assignJobs(servers, vector<Job>(jobsSize));

    float custoFin = 0;

    for(int i = 0; i<servers; i++){
        for(int j = 0; j<jobsSize; j++){
            jobs[i][j].index = j;
            jobs[i][j].time = matrizT[i][j];
            jobs[i][j].cost = matrizC[i][j];
            jobFin[j] = -1;

            printf("%f,",jobs[i][j].time);
        }

        printf("\n");
    }

    for(auto &jobVector : jobs){
        if(!jobVector.empty()){
            mergeSort(jobVector, 0, jobVector.size() - 1);
        }
    }

    printf("\n");

    for(int i = 0; i<servers; i++){
        for(int j = 0; j<jobsSize; j++){
            printf("%d,",jobs[i][j].index);
        }
        printf("\n");
    }

    bool hasSpace = true;

    int fullServers = 0;
    while (hasSpace){

        int chosenServ = 0;

        for(int i = 1; i<servers; i++){
            if(jobs[i].back().time < jobs[chosenServ].back().time){
                chosenServ = i;
            }
        }
        printf("Chosen Server: %d, capacity: %f\n",chosenServ, capacidade[chosenServ]);

        if(jobs[chosenServ].size() == 0){
            jobs[chosenServ].push_back(Job());
            fullServers++;
            continue;
        }

        if(fullServers == servers){
            hasSpace = false;
            break;
        }

        if(jobs[chosenServ].back().time <= capacidade[chosenServ]){
            jobs[chosenServ].back().server = chosenServ;
            capacidade[chosenServ] -= jobs[chosenServ].back().time;
            printf("Jobs left:%ld at server %d\n",jobs[chosenServ].size(),chosenServ);
            printf("Job %d added to server %d, time: %f\n",jobs[chosenServ].back().index,chosenServ, jobs[chosenServ].back().time);
            printf("Server %d has %f time left\n",chosenServ,capacidade[chosenServ]);
            jobFin[jobs[chosenServ].back().index] = chosenServ;
            custoFin += jobs[chosenServ].back().cost;
            if(jobs[chosenServ].size() == 1 ){
                jobs[chosenServ].back().time = 999999999;
                fullServers++;
                continue;
            }else{
                std::pair<vector<vector<Job>>, vector<vector<Job>> > newVecs = removeJob(jobs, jobs[chosenServ].back().index, servers, jobsSize);
                jobs = newVecs.first;
                assignJobs = newVecs.second;
            }
            if(jobs[chosenServ].size() == 0){
                fullServers++;
                continue;
            }
            printf("Job vector status:\n");
            printVec(jobs);

        }else{
            if(jobs[chosenServ].size() == 1 ){
                jobs[chosenServ].back().time = 999999999;
                fullServers++;
            }
            jobs[chosenServ].pop_back();
        }

        printf("Full servers: %d\n",fullServers);

    }


    int k = 0;
    for(auto &servidor : jobFin){
        printf("%f,",servidor);
        if(servidor == -1){
            custoFin += custoLoc;
        }
        k++;
    }

    printf("\n");
    printf("Final cost: %f\n",custoFin);

    /*vector<vector<float>> custoTemp(servers, vector<float>(jobsSize));

    for(int i = 0; i < servers; i++){
        for(int j = 0; j < jobsSize; j++){
            custoTemp[i][j] = (matrizT[i][j]/matrizC[i][j]);
            printf("%f,",custoTemp[i][j]);
        }
        printf("\n");
    }
    
    for(int i = 0; i < servers; i++){
        mergeSort(custoTemp[i], 0, 5);
    }*/

    return 0;
}