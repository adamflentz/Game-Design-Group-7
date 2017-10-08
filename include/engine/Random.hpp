///////////////
// Random.hpp
//
// Useful random number generator functions that I "appropriated" from
// my simulations class.
//
///////////////
#ifndef SEEDY_RANDOM_HPP
#define SEEDY_RANDOM_HPP

#include <stdio.h>
#include <time.h>
#include <math.h>

double Random(void);
void PlantSeeds(long x);
void GetSeed(long *x);
void PutSeed(long x);
void SelectStream(int index);
void TestRandom(void);

long Bernoulli(double p);
long Binomial(long n, double p);
long Equilikely(long a, long b);
long Geometric(double p);
long Pascal(long n, double p);
long Poisson(double m);

double Uniform(double a, double b);
double Exponential(double m);
double Erlang(long n, double b);
double Normal(double m, double s);
double Lognormal(double a, double b);
double Chisquare(long n);
double Student(long n);

#endif