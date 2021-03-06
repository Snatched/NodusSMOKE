/*-----------------------------------------------------------------------*\
|																		  |
|			 _   _      _    _____ __  __  ____  _  ________         	  |
|			| \ | |    | |  / ____|  \/  |/ __ \| |/ /  ____|        	  |
|			|  \| | ___| |_| (___ | \  / | |  | | ' /| |__   			  |
|			| . ` |/ _ \ __|\___ \| |\/| | |  | |  < |  __|  		  	  |
|			| |\  |  __/ |_ ____) | |  | | |__| | . \| |____ 		 	  |
|			|_| \_|\___|\__|_____/|_|  |_|\____/|_|\_\______|		 	  |
|                                                                         |
|   Author: Matteo Mensi <matteo.mensi@mail.polimi.it>                    |
|   CRECK Modeling Group <http://creckmodeling.chem.polimi.it>            |
|   Department of Chemistry, Materials and Chemical Engineering           |
|   Politecnico di Milano                                                 |
|   P.zza Leonardo da Vinci 32, 20133 Milano                              |
|                                                                         |
\*-----------------------------------------------------------------------*/

#ifndef NETSMOKE_REACTORNETWORK_DENSENLSINTERFACE_H
#define NETSMOKE_REACTORNETWORK_DENSENLSINTERFACE_H

#include "ReactorNetwork.h"

// NLS Solver
#include "math/native-nls-solvers/NonLinearSystemSolver"
#include "NetSMOKE_ReactorNetwork_denseNLSinterface.h"


class NetSMOKE_ReactorNetwork_denseNLSinterface
{
public:

	NetSMOKE_ReactorNetwork_denseNLSinterface() {};

	void SetReactor(NetSMOKE::ReactorNetwork* reactor)
	{
		reactor_ = reactor;
	};

protected:

	unsigned int ne_;

	void MemoryAllocation()
	{
		OpenSMOKE::ChangeDimensions(ne_, &y_, true);
		OpenSMOKE::ChangeDimensions(ne_, &dy_, false);
	};

	virtual void Equations(const Eigen::VectorXd &Y, Eigen::VectorXd &DY)
	{
		y_.CopyFrom(Y.data());
		reactor_->NLSEquations(y_, dy_); // Insert variables in the reactor
		dy_.CopyTo(DY.data());
	};

	virtual void Jacobian(const Eigen::VectorXd &Y, Eigen::SparseMatrix<double> &J) {};

	void Print(const int n_iter, const double t, const double phi, const Eigen::VectorXd &Y, const Eigen::VectorXd &DY)
	{
		dy_.CopyFrom(DY.data());
		reactor_->PrintNLS(dy_);
	};

private:

	NetSMOKE::ReactorNetwork* reactor_;
	OpenSMOKE::OpenSMOKEVectorDouble  y_;
	OpenSMOKE::OpenSMOKEVectorDouble dy_;
};

#endif /* NETSMOKE_REACTORNETWORK_DENSENLSINTERFACE_H */
