#ifndef porousPhaseInfo_H
#define porousPhaseInfo_H

#include <boost/graph/graph_selectors.hpp>
#include <boost/pending/property.hpp>
#include <variant>
#include <map>

#include <boost/graph/undirected_graph.hpp>
#include <boost/graph/adjacency_list.hpp>

#include "volFieldsFwd.H"
#include "solidThermophysicalTransportModel.H"

namespace Foam {

struct equilibriumHeatTransfer {
};
struct nonEquilibriumHeatTransfer {
    dimensionedScalar heatTransferCoefficient;
    dimensionedScalar effectiveSpecificSurfaceArea;
};
using heatTransfer = std::variant<equilibriumHeatTransfer, nonEquilibriumHeatTransfer>;

heatTransfer parse_heatTransfer(const dictionary& dict);

class porousPhaseInfo {
public:
    static const word FLUID_PHASE_NAME;

    using heatTransferGraph_type = 
    boost::adjacency_list<boost::vecS,boost::vecS,
        boost::undirectedS, std::string, heatTransfer>;

    struct porousPhase {
        volScalarField alpha;
        autoPtr<solidThermo> thermo;
        autoPtr<solidThermophysicalTransportModel> thermophysicalTransport;
        heatTransferGraph_type::vertex_descriptor vertex{};
    };

protected:
    std::map<word, porousPhase> porousPhases_;

    heatTransferGraph_type heatTransferGraph_;
    heatTransferGraph_type::vertex_descriptor fluid_vertex{};


public:
    explicit porousPhaseInfo(fvMesh&mesh, const Time& runTime);
    porousPhaseInfo(const porousPhaseInfo&)=delete;
    ~porousPhaseInfo()=default;

    auto& porousPhases() & {
        return porousPhases_;
    }
    
    const auto& porousPhases() const & {
        return porousPhases_;
    }

    bool isValidPhase(const word& phaseName) const {
        return this->porousPhases_.contains(phaseName) or (phaseName==FLUID_PHASE_NAME);
    }
};

}

#endif //porousPhaseInfo_H