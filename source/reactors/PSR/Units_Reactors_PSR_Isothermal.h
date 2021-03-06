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

#ifndef NETSMOKE_UNITS_REACTORS_PSR_ISOTHERMAL_H
#define NETSMOKE_UNITS_REACTORS_PSR_ISOTHERMAL_H

// Parent class
#include "Units_Reactors_PSR.h"

namespace NetSMOKE
{

	class Units_Reactors_PSR_Isothermal : public Units_Reactors_PSR {

	public:
		/* Default constructor */
		Units_Reactors_PSR_Isothermal(OpenSMOKE::ThermodynamicsMap_CHEMKIN *thermodynamicsMapXML, OpenSMOKE::KineticsMap_CHEMKIN *kineticsMapXML, NetSMOKE::UnitInfo unit_data);

		/* Default deconstructor */
		~Units_Reactors_PSR_Isothermal();

		/* Solve */
		int Solve(std::vector<NetSMOKE::StreamInfo> &streams_data_structure);

		/* Solve in the sequential solver */
		int NonIterativeSolve(std::vector<NetSMOKE::StreamInfo> &streams_data_structure);

		/* Get Residuals */
		int GetResiduals(OpenSMOKE::OpenSMOKEVectorDouble &residuals, std::vector<NetSMOKE::StreamInfo> &streams_data_structure);

		/* Print reactor status */
		void PrintStatus(boost::filesystem::path output_folder, std::vector<NetSMOKE::StreamInfo> &streams_data_structure);

		/* Virtual RTD aware solver */
		int RTD(OpenSMOKE::OpenSMOKEVectorDouble &residuals, const double t, std::vector<NetSMOKE::StreamInfo> &streams_data_structure);
		
	private:

		// Static info for solver
		OpenSMOKE::PerfectlyStirredReactor_Options* psr_options;
		OpenSMOKE::ODE_Parameters* ode_parameters;
		OpenSMOKE::OnTheFlyROPA* onTheFlyROPA;
		OpenSMOKE::OnTheFlyPostProcessing* on_the_fly_post_processing;
		OpenSMOKE::PolimiSoot_Analyzer* polimi_soot;

		OpenSMOKE::ThermodynamicsMap_CHEMKIN& thermodynamicsMap;
		OpenSMOKE::KineticsMap_CHEMKIN& kineticsMap;

		
	};

}

#include "Units_Reactors_PSR_Isothermal.hpp"

#endif /* NETSMOKE_UNITS_REACTORS_PSR_ISOTHERMAL_H */
