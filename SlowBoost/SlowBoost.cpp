/*======================================================================================================================

    Copyright 2011, 2012, 2013, 2014, 2015 Institut fuer Neuroinformatik, Ruhr-Universitaet Bochum, Germany

    This file is part of cedar.

    cedar is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License as published by the
    Free Software Foundation, either version 3 of the License, or (at your
    option) any later version.

    cedar is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
    License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with cedar. If not, see <http://www.gnu.org/licenses/>.

========================================================================================================================

    Institute:   Ruhr-Universitaet Bochum
                 Institut fuer Neuroinformatik

    File:        EarSubscriber.h

    Maintainer:  Tutorial Writer Person
    Email:       cedar@ini.rub.de
    Date:        2011 12 09

    Description:

    Credits:

======================================================================================================================*/

// CEDAR INCLUDES
#include "SlowBoost.h"
#include <cedar/processing/ExternalData.h> // getInputSlot() returns ExternalData
#include <cedar/auxiliaries/MatData.h> // this is the class MatData, used internally in this step
#include "cedar/auxiliaries/math/functions.h"
#include <cmath>



// SYSTEM INCLUDES

//----------------------------------------------------------------------------------------------------------------------
// constructors and destructor
//----------------------------------------------------------------------------------------------------------------------
SlowBoost::SlowBoost()
:
cedar::proc::Step(true),
mBoostStep(new cedar::aux::DoubleParameter(this,"Boost Step",0.01)),
mBoostLim(new cedar::aux::DoubleParameter(this,"Boost Limite",1.8)),
mBoost(new cedar::aux::MatData(cv::Mat::zeros(1, 1, CV_32F)))
{
this->declareInput("peak stop", true);
this->declareInput("start", true);
this->declareInput("reset", true);
this->declareOutput("boost", this->mBoost);
stop = false;
start = false;
reset_b = false;
boost_lim = 1.8;
this->connect(this->mBoostStep.get(), SIGNAL(valueChanged()), this, SLOT(reCompute()));
this->connect(this->mBoostLim.get(), SIGNAL(valueChanged()), this, SLOT(reCompute()));

}
//----------------------------------------------------------------------------------------------------------------------
// methods
//----------------------------------------------------------------------------------------------------------------------
void SlowBoost::compute(const cedar::proc::Arguments&)
{

  auto boost_stop = boost::dynamic_pointer_cast<cedar::aux::ConstMatData>(this->getInput("peak stop"));
  auto boost_reset = boost::dynamic_pointer_cast<cedar::aux::ConstMatData>(this->getInput("reset"));
  auto boost_start = boost::dynamic_pointer_cast<cedar::aux::ConstMatData>(this->getInput("start"));

  reset_boost = cedar::aux::math::getMatrixEntry<double>(boost_reset->getData(), 0, 0);
  stop_boost = cedar::aux::math::getMatrixEntry<double>(boost_stop->getData(), 0, 0);
  start_boost = cedar::aux::math::getMatrixEntry<double>(boost_start->getData(), 0, 0);

  if(reset_boost > 0.8)
  {
     reset_b = true;
  }
  else
  {
     reset_b = false;
  }
  if(stop_boost > 0.8 || boost_current > boost_lim)
  {
     stop = true;
     start = false;
  }
  else
  {
     stop = false;
  }
  if(start_boost > 0.8)
  {
     start = true;
  }
  if(start == true && stop == false)
  {
      boost_current = boost_current + boost_step;
  }
  if(reset_b == true)
  {
     boost_current = 0;
  }



  this->mBoost->getData().at<float>(0, 0) = boost_current;


}

void SlowBoost::reCompute()
{
   boost_step = this->mBoostStep->getValue();
   boost_lim = this->mBoostLim->getValue();
}



void SlowBoost::reset()
{

	boost_current = 0;

}
