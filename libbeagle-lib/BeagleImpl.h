/*
 *  BeagleImpl.h
 *  BEAGLE
 *
 * @author Andrew Rambaut
 * @author Marc Suchard
 * @author Daniel Ayres
 */

#ifndef __beagle_impl__
#define __beagle_impl__

#include "libbeagle-lib/beagle.h"

#ifdef DOUBLE_PRECISION
#define REAL    double
#else
#define REAL    float
#endif

namespace beagle {

class BeagleImpl {
public:
    virtual ~BeagleImpl(){}
    
    virtual int createInstance(int tipCount,
                               int partialsBufferCount,
                               int compactBufferCount,
                               int stateCount,
                               int patternCount,
                               int eigenBufferCount,
                               int matrixBufferCount) = 0;
    
    virtual int initializeInstance(InstanceDetails* returnInfo) = 0;
    
    virtual int setPartials(int bufferIndex,
                            const double* inPartials) = 0;
    
    virtual int getPartials(int bufferIndex,
                            double* outPartials) = 0;
    
    virtual int setTipStates(int tipIndex,
                             const int* inStates) = 0;
    
    virtual int setEigenDecomposition(int eigenIndex,
                                      const double* inEigenVectors,
                                      const double* inInverseEigenVectors,
                                      const double* inEigenValues) = 0;
    
    virtual int setTransitionMatrix(int matrixIndex,
                                    const double* inMatrix) = 0;
    
    virtual int updateTransitionMatrices(int eigenIndex,
                                         const int* probabilityIndices,
                                         const int* firstDerivativeIndices,
                                         const int* secondDervativeIndices,
                                         const double* edgeLengths,
                                         int count) = 0;
    
    virtual int updatePartials(const int* operations,
                               int operationCount,
                               int rescale) = 0;
    
    virtual int waitForPartials(const int* destinationPartials,
                                int destinationPartialsCount) = 0;
    
    virtual int calculateRootLogLikelihoods(const int* bufferIndices,
                                            const double* inWeights,
                                            const double* inStateFrequencies,
                                            int count,
                                            double* outLogLikelihoods) = 0;
    
    virtual int calculateEdgeLogLikelihoods(const int* parentBufferIndices,
                                            const int* childBufferIndices,
                                            const int* probabilityIndices,
                                            const int* firstDerivativeIndices,
                                            const int* secondDerivativeIndices,
                                            const double* inWeights,
                                            const double* inStateFrequencies,
                                            int count,
                                            double* outLogLikelihoods,
                                            double* outFirstDerivatives,
                                            double* outSecondDerivatives) = 0;
};

class BeagleImplFactory {
public:
    virtual BeagleImpl* createImpl(int tipCount,
                                   int partialsBufferCount,
                                   int compactBufferCount,
                                   int stateCount,
                                   int patternCount,
                                   int eigenBufferCount,
                                   int matrixBufferCount) = 0; // pure virtual
    
    virtual const char* getName() = 0; // pure virtual
};

} // end namespace beagle

#endif // __beagle_impl__