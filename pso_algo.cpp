#include "pso_algo.h"

const int randRange = 0;

pso_algo::pso_algo() {

}

pso_algo::pso_algo(Parameter parameter) {

    srand(time(NULL));

    this->parameter = parameter;
    
    candidateSol = vector<Solution>(parameter.POPULATION, Solution(parameter));
    
    infoLink = vector<vector<int>>(parameter.POPULATION, vector<int>(parameter.POPULATION, 0));

}

pso_algo::~pso_algo() {

}


void pso_algo::initial() {
    
    bestSol.setDimension(D);
    bestSol.fitness = INT_MAX;
    
    //UL[0] - LL[0]; 
        
    for(int i = 0; i < parameter.POPULATION; ++i) {
    
        candidateSol[i].setDimension(D);
        candidateSol[i].setRange(UL, LL);
        candidateSol[i].initLocation();
        candidateSol[i].initVelocity();
        candidateSol[i].calFitness();
        candidateSol[i].updateLocalBest();
        
        if(candidateSol[i].fitness < bestSol.fitness)
            bestSol = candidateSol[i];
    
    }
    
    double p = 1 - pow(1 - 1./ parameter.POPULATION, 3);
    
    initLink(p);    
            
    PX = vector<double>(D, 0);
    GX = vector<double>(D, 0);
    
    //Gr(parameter);
    
    Gr.setDimension(D);
    Gr.setRange(UL, LL);
    //Gr.initLocation();
    //Gr.initVelocity();
    //Gr.calFitness();
    Gr.updateLocalBest();
    
    V1 = vector<double>(D, 0);
    V2 = vector<double>(D, 0);
    
}

void pso_algo::initLink(double p) {

    //Alea alea;

    switch(parameter.topology) {
    
        default:
        
        for(int i = 0; i < parameter.POPULATION; ++i) {
        
            for(int j = 0; j < parameter.POPULATION; ++j) {
            
                if(i == j)
                    infoLink[j][i] = 1;  
            
                if(alea.alea_rand(0, 1) < p)
                    infoLink[j][i] = 1;             
            
                else
                    infoLink[j][i] = 0;
                    
            }
           
        }
        
        break;
    }

}

void pso_algo::candidate(double itr) {

    bool updateTopology = true;
     
    for(int i = 0; i < parameter.POPULATION; ++i) {
    
        int topologyIndex = 0;
    
        double topoBest = candidateSol[i].localFitness;
    
        for(int j = 0; j < parameter.POPULATION; ++j) {
        
            if(infoLink[i][j] == 1 && candidateSol[j].localFitness <= topoBest) {
            
                topologyIndex = j;
                topoBest = candidateSol[j].localFitness;
                
            }
                
        
        }
        
        //cout << topologyIndex << endl;
       
        setPX(candidateSol[i]);
        
        if(i != topologyIndex)
            setGX(candidateSol[i], candidateSol[topologyIndex]);

            
        calGr(candidateSol[i], i == topologyIndex);
        
        calV1(candidateSol[i]);
        
        double rad = distanceL(candidateSol[i]);    
        
        sphere(rad);
        
        candidateSol[i].updateVelocity(V1, V2);
                    
        candidateSol[i].updateAllocation();
        candidateSol[i].calFitness();
        candidateSol[i].updateLocalBest();
        
        if(candidateSol[i].fitness < bestSol.fitness) {
        
            bestSol = candidateSol[i];
            updateTopology = false;
        
        }

        
    }
    
    if(updateTopology) {
            
        double p = 1 - pow(1 - 1./ parameter.POPULATION, 3);
    
        initLink(p);
    
    }
           
}

void pso_algo::sphere(double rad) {

    int distrib = 0;
    double mean = 0.5;
    double sigma  = 1. / 12;

    double pw = 1. / (double) D;
    
    double length = 0;
    
    double r;
    
    for(int i = 0; i < D; ++i) {
    
        V2[i] = stable(2, 0, 1, 0);
        length = length + V2[i] * V2[i];
    
    }
    
    length = sqrt(length);
    
    r = alea.alea_rand(0 , 1); 
    
    for(int i = 0; i < D; ++i) {
    
		V2[i] = rad * r * V2[i] / length;
		
	}
    
}

double pso_algo::stable(double alpha, double beta, double nu, double delta) {

    //Alea alea;

    double betaPrime;
    double d;
    
    double eps;

    double kAlpha;
    
    double min = 0;
	double max = 1;
 
    double phi0, phi;

    double r;
    double s;
    
    double t1, t2, t3;
    double tau;
    double u; 

    double temp;

    double w;
    double z;

    if(alpha < 0 || alpha > 2)
        cout << "alpha " << alpha << endl;
        
    if(nu < 0)
        cout << "nu " << nu << endl;
        
    
    if(alpha < 1)
        kAlpha = alpha;
    else 
        kAlpha = 2 - alpha;
        
    phi0 = 0.5 * beta * (kAlpha / alpha);
    
    temp = tan(alpha * phi0);
    
    if(fabs(alpha - 1) < 0) 
        betaPrime = beta;
	else
		betaPrime = -tan(0.5 * pi * (1 - alpha)) * temp;
	
	// Generate a random variable u uniformly distributed on the interval [0, 1] and compute φ = π(u−½).
	u = alea.alea_rand(min, max);
	phi = pi * (u - 0.5);
	
	//Compute ε=1−α and then τ = −εtan(αφ0) 		
	eps = 1 - alpha; 
	tau= -eps * temp;
	
	//Compute tan(½φ), tan(½εφ) and tan(½εφ)/(½εφ). 
	t1 = tan(0.5 * phi);
	t2 = tan(0.5 * eps * phi);
	t3 = 2 * t2 / (eps * phi);
	
	// Generate a random variable v which has a uniform distribution 
	//	on the interval [0,1] and then compute w=−ln(v)
	w = -log(alea.alea_rand(min, max));
	
	// Compute z = (cos(εφ)−tan(αφ0)sin(εφ)/(wcos(φ))
	z = cos(eps * phi) - tan(alpha * phi0) * sin(eps * phi) / (w * cos(phi));
	
	// Compute d = z^ε/α /ε 
	temp = pow(z , eps / alpha);
	d = temp / eps;
	
	// Compute s = tan(αφ0) + z^ε/α (sin(αφ)−tan(αφ0)cos(αφ))/cos(φ) 
	s = tan(alpha * phi0) + temp * (sin(alpha * phi) - tan(alpha * phi0) * cos(alpha * phi)) / cos(phi);	

	// Multiply by the dispersion, and add the mean
	r = s * nu + delta;
	
	//cout << "r " << r << endl;
	
	return r;
	
}

double pso_algo::distanceL(const Solution &candidateSol) {

    // Distance between two positions
	// L = 2 => Euclidean	
	double n;

	n = 0;

	for (int i = 0; i < D; ++i)
		n = n + pow (fabs(candidateSol.allocation[i] - Gr.allocation[i]), 2);

	n = pow (n, 0.5);
	return n; 
	   
}

void pso_algo::calV1(const Solution &candidateSol) {

    //vector X - G
    for(int i = 0; i < D; ++i) {
        //cout << Gr.allocation[i] << " " << candidateSol.allocation[i];
        V1[i] = Gr.allocation[i] - candidateSol.allocation[i];
    
    }

}

void pso_algo::calGr(const Solution &candidateSol, bool same) {

    double w1 = 1;
    double w2 = 1;
    double w3 = 1;
    
    w1 /= w1 + w2 + w3;
    w2 /= w1 + w2 + w3;
    w3 /= w1 + w2 + w3;
    
    double c = 0.5 + log ((double) 2);
    
    for(int i = 0; i < D; ++i) {
    
        Gr.allocation[i] = w1 * candidateSol.allocation[i] + w2 * (candidateSol.allocation[i] + c * PX[i]);
        
        if(!same) {
        
            Gr.allocation[i] += w3 * (candidateSol.allocation[i] + c * GX[i]);
     
        }
        //cout << i << " " << Gr.allocation[i] << endl;
    }

}

void pso_algo::setGX(const Solution &candidateSol, const Solution &topologySol) {

    //L
  
    for(int i = 0; i < D; ++i) {
    
        GX[i] = topologySol.localBest[i] - candidateSol.allocation[i]; 
    
    }

}

void pso_algo::setPX(const Solution &candidateSol) {

    for(int i = 0; i < D; ++i) {
    
        PX[i] = candidateSol.localBest[i] - candidateSol.allocation[i]; 
    
    }

}

//~~~~~~~~~~~~~~~~~~~
void pso_algo::checkInit() {
 
    for(int i = 0; i < parameter.POPULATION; ++i) {
    
        for(int j = 0; j < D; ++j) {
            if(candidateSol[i].allocation[j] < LL[j] || candidateSol[i].allocation[j] > UL[j])
                cout << i << " " << j << " x error" << candidateSol[i].allocation[j] << endl;
                
            if(candidateSol[i].velocity[j] < (LL[j] * 2) || candidateSol[i].velocity[j] > (UL[j]  * 2))
                cout << i << " " << j << " v error" << candidateSol[i].velocity[j] << endl;
        }
        
    }

}

/**
  * set benchmark function
  */ 
void pso_algo::setBF() {

    //cout << "function " << parameter.FUNC_NUM << endl;
    
    switch(parameter.FUNC_NUM) {
        
        case 0:
        
            D = 20;
            LL = vector<double>(D, -10);
            UL = vector<double>(D, 10);

            break;
            
        case 1:
        
            D = 5;
            LL = vector<double>(D, -5.12);
            UL = vector<double>(D, 5.12);

            break;
        case 2:
            D = 30;
            LL = vector<double>(D, -100);
            UL = vector<double>(D, 100);
            
            break; 
        case 16:
            D = 30;
            LL = vector<double>(D, -30);
            UL = vector<double>(D, 30);
            
            break;  
        case 22:
            D = 30;
            LL = vector<double>(D, -5.12);
            UL = vector<double>(D, 5.12);
            
            break;          
        case 23:
            D = 30;
            LL = vector<double>(D, -500);
            UL = vector<double>(D, 500);
            
            break;            
        case 28:
            D = 2;
            LL = vector<double>(D, -5);
            UL = vector<double>(D, 5);
            
            break;
        case 41:
            D = 30;
            LL = vector<double>(D, -600);
            UL = vector<double>(D, 600);
            
            break;   
        case 101:
            D = 640;
            LL = vector<double>(D, -100);
            UL = vector<double>(D, 100);
            
            break;  
            
        case 202:
         
            D = 30;
            LL = vector<double>(D, -100);
            UL = vector<double>(D, 100);
            
            break;
            
        default:
            cout << "unknown function " << parameter.FUNC_NUM << endl;
            break;
    }

}


 
