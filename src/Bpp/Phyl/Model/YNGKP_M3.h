//
// File: YNGKP_M3.h
// Created by: Laurent Gueguen
// Created on: May 2010
//

/*
Copyright or © or Copr. CNRS, (November 16, 2004)

This software is a computer program whose purpose is to provide classes
for phylogenetic data analysis.

This software is governed by the CeCILL  license under French law and
abiding by the rules of distribution of free software.  You can  use, 
modify and/ or redistribute the software under the terms of the CeCILL
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info". 

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability. 

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or 
data to be ensured and,  more generally, to use and operate it in the 
same conditions as regards security. 

The fact that you are presently reading this means that you have had
knowledge of the CeCILL license and that you accept its terms.
*/

#ifndef _YNGKP_M3_H_
#define _YNGKP_M3_H_

#include "MixedSubstitutionModel.h"
#include "MixtureOfSubstitutionModels.h"
#include "FrequenciesSet.h"

#include <Seq/GeneticCode.h>

namespace bpp
{

/**
 * @brief The Yang et al (2000) M3 substitution model for codons.
 * @author Laurent Guéguen
 *
 * This model is a mixture of models as described in YN98 class, the
 * mixture being defined on the selection parameter to allow it to
 * vary among sites. There are $K$ selection parameters @f$ \omega_0 <
 * ... \omega_{K-1} @f$, with their respective probabilities @f$ p_0,
 * ..., p_{K-1} @f$ with @f$ p_0+p_1+...+p_{K-1}=1@f$. To garantee
 * that the @f$\omega_i@f$ are in increasing order, we define
 * @f$\delta_i=\omega_i - \omega_{i-1}@f$.
 *
 * This model includes 2*K parameters (@f$\kappa@f$, relative
 * probabilities @f$ theta1, theta2, ..., thetaK-1 @f$ and @f$omega0,
 * delta1, deltaK@f$). The codon frequencies @f$\pi_j@f$ are either
 * observed or infered.
 *
 * References:
 *
 * Yang, Z., R. Nielsen, N. Goldman, and A.-M. K. Pedersen (2000)
 * Genetics 155:431-449.
 * 
 */
class YNGKP_M3:
  public MixedSubstitutionModel
{
private:
  MixtureOfSubstitutionModels* pmixmodel_;

private:
  /**
   * @brief Tools to make the link between the Parameters of the
   * object and those of pmixmodel_.
   *
   */

  std::map<std::string,std::string> mapParNamesFromPmodel_;
  
  ParameterList lParPmodel_;
  

public:
  YNGKP_M3(const GeneticCode* gc, FrequenciesSet* codonFreqs, unsigned int nclass=3);

  ~YNGKP_M3();
  
  YNGKP_M3* clone() const { return new YNGKP_M3(*this); }

  YNGKP_M3(const YNGKP_M3&);

  YNGKP_M3& operator=(const YNGKP_M3&);

  void setFreq(std::map<int, double>& m) { pmixmodel_->setFreq(m);  }

  unsigned int getNumberOfStates() const  { return pmixmodel_->getNumberOfStates();  }

protected:
  void updateMatrices();

public:
  const SubstitutionModel* getNModel(unsigned int i) const {
    return pmixmodel_->getNModel(i);
  }

  SubstitutionModel* getNModel(unsigned int i) {
    return pmixmodel_->getNModel(i);
  }

  /**
   * @brief Returns the  probability of a specific model from the mixture
   */
  
  double getNProbability(unsigned int i) const {
    return pmixmodel_->getNProbability(i);
  }

  const std::vector<double>& getProbabilities() const {
    return pmixmodel_->getProbabilities();
  }
    
  unsigned int getNumberOfModels() const {
    return pmixmodel_->getNumberOfModels();
  }

  std::string getName() const { return "YNGKP_M3"; }

  double Pij_t(unsigned int i, unsigned int j, double t) const {
    return pmixmodel_->Pij_t(i,j,t);
  }
  double dPij_dt(unsigned int i, unsigned int j, double t) const {
    return pmixmodel_->dPij_dt(i,j,t);
  };
  double d2Pij_dt2(unsigned int i, unsigned int j, double t) const {
    return pmixmodel_->dPij_dt(i,j,t);
  };
  const Matrix<double>& getPij_t(double t) const {
    return pmixmodel_->getPij_t(t);
  };
  const Matrix<double>& getdPij_dt(double t) const {
    return pmixmodel_->getdPij_dt(t);
  };
  const Matrix<double>& getd2Pij_dt2(double t) const {
    return pmixmodel_->getd2Pij_dt2(t);
  };
  
  const Vdouble& getFrequencies() {
    return pmixmodel_->getFrequencies();
  };
  
  double freq(unsigned int i) const {
    return pmixmodel_->freq(i);
  };


};

} //end of namespace bpp.

#endif	//_YNGKP_M3_H_
