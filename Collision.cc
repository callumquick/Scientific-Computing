#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

struct particle {
	long double x; //position
	long double p; //momentum
	long double im; //inverse mass
	long double v; //velocity
	long double T; //kinetic energy
	long double a; //particle radius
};

struct control {
	
};

// Function declaration
void collide(particle &P1, particle &P2); //collide function
void collisionSim(particle a[]); //collision simulation handler
void update(particle &P); //updates particle's data using new v,x
void stepForward(particle a[]); //uses the velocity to update the position of each particle
void showState(particle a[], double time); //prints out the info of the particle array at a given time
void fileWipe(); //clears the output file

// Globals declaration
double T = 1000; //Total simulation time
double dt = 0.01; //Time step for animation
int length = 9; //Length of the array/number of particles
char const fileName[] = "data.txt"; //The filename to write to
ofstream fout; //Output object

int main() {
	//Define test particles.
	particle particle1;
	particle1.x = -10.0;
	particle1.v = 5.0;
	particle1.im = 1.5;
	update(particle1);
	particle1.a = 1.0;
	particle particle2;
	particle2.x = 10.0;
	particle2.v = -7.0;
	particle2.im = 1.5;
	update(particle2);
	particle2.a = 1.0;
	particle particle3;
	particle3.x = 30.0;
	particle3.v = 0.0;
	particle3.im = 1.5;
	update(particle3);
	particle3.a = 3.0;
	particle particle4;
	particle4.x = -30.0;
	particle4.v = 0.0;
	particle4.im = 1.5;
	update(particle4);
	particle4.a = 1.0;
	particle particle5;
	particle5.x = -40.0;
	particle5.v = 5.0;
	particle5.im = 1.5;
	update(particle5);
	particle5.a = 1.0;
	particle particle6;
	particle6.x = 40.0;
	particle6.v = -5.0;
	particle6.im = 1.5;
	update(particle6);
	particle6.a = 1.0;
	particle piston;
	piston.x = 0.0;
	piston.v = 0.0;
	piston.im = 0.1;
	update(piston);
	piston.a = 4.0;
	particle wall1;
	wall1.x = -50.0;
	wall1.v = 0.0;
	wall1.im = 0.0;
	update(wall1);
	wall1.a = 0.0;
	particle wall2;
	wall2.x = 50.0;
	wall2.v = 0.0;
	wall2.im = 0.0;
	update(wall2);
	wall2.a = 0.0;
	//Combine them into an array.
	particle arr[length];
	arr[0]=particle1; arr[1]=particle2; arr[2]=wall1; arr[3]=wall2; arr[4]=particle3; arr[5]=particle4; arr[6]=particle5; arr[7]=particle6; arr[8]=piston;
	//Wipe file ready for input
	fileWipe();
	//Run simulation
	collisionSim(arr);
}

void collide(particle &a, particle &b) //Takes two particles and computes new velocities after elastic collision.
{
		// find the relative velocity 
	  double velocity_along_line =  a.v - b.v;
	  // find a's inverse-mass fraction
	  double af = a.im / ( a.im + b.im ) ; 
	  double bf = b.im / ( a.im + b.im ) ; 
	  // reverse the c.o.m. velocity of each along the line of collision
	  a.v -= 2.0 * af * velocity_along_line ;
	  b.v += 2.0 * bf * velocity_along_line ;
	  // The collision has now happened.
	  // Finally update the other state information
	  update(a); 
	  update(b); 
}

void collisionSim(particle a[]) //Runs the simulation, calling collide when two particles collide.
{
	cout << "Simulation running..." << endl;
	double runningTime = 0;
	while (runningTime < T) {
		//Print the information to file:
		showState(a, runningTime);
		//Check for collisions in this timestep
		for (int i = 0 ; i < length; i++) { //Loop through the array
			for (int j = i+1 ; j < length ; j++) { //For each particle, check all particles ahead of it
				if (abs(a[j].x-a[i].x) < a[j].a+a[i].a) {
					collide(a[i], a[j]);
				}
			}
		}
		//Increment state
		stepForward(a);
		//Increment the running time
		runningTime += dt;
	}
	cout << "Simulation over." << endl;
}

void stepForward(particle a[]) {
	for (int p = 0 ; p < length ; p++) {
		a[p].x += a[p].v*dt;
	}
}

void showState(particle a[], double time) {
    fout.open(fileName, ios::app); // Opens file in append mode.
	fout << time;
	for (int z = 0 ; z < length ; z++) {
		fout << "\t" << a[z].x << "\t" << a[z].v << "\t";
	}
	fout << endl;
	fout.close();
}

void update(particle &P) {
	if(P.im > 0) {
		P.p = P.v/P.im;
	} else {
		P.p = 0;
	}
	P.T = 0.5*P.v*P.p;
}

void fileWipe()
{
    ofstream fout;
    fout.open(fileName, ios::trunc);
    fout.close(); // Wipes data file for new data entry.
}

